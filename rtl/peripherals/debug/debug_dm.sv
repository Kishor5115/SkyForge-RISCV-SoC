/*
 * RISC-V Debug Module (DM) — Minimal 0.13-compatible implementation
 *
 * Features:
 *   - DMCONTROL/DMSTATUS/HARTINFO
 *   - ABSTRACTCS/COMMAND/DATA0 for GPR access
 *   - System Bus Access (SBA) for 32-bit memory reads/writes
 *   - APB + JTAG DMI access paths
 */

module debug_dm (
    input  logic        clk,
    input  logic        resetn,

    // APB4 slave interface
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] paddr,
    input  logic [31:0] pwdata,
    input  logic [3:0]  pstrb,
    input  logic [2:0]  pprot,
    output logic [31:0] prdata,
    output logic        pready,
    output logic        pslverr,

    // DMI from JTAG DTM
    input  logic        jtag_valid,
    input  logic        jtag_write,
    input  logic [7:0]  jtag_addr,
    input  logic [31:0] jtag_wdata,
    input  logic [3:0]  jtag_wstrb,
    output logic [31:0] jtag_rdata,
    output logic        jtag_ready,

    // Debug core control
    output logic        dbg_halt_req,
    output logic        dbg_resume_req,
    input  logic        dbg_halted,
    output logic        dbg_reg_write,
    output logic        dbg_reg_read,
    output logic [4:0]  dbg_reg_addr,
    output logic [31:0] dbg_reg_wdata,
    input  logic [31:0] dbg_reg_rdata,

    // CPU PC for DPC reads
    input  logic [31:0] dbg_cpu_pc,

    // Debug PC set (to update CPU PC from DPC on resume)
    output logic        dbg_set_pc,
    output logic [31:0] dbg_set_pc_val,

    // Debug system bus access (AXI-lite master)
    output logic        dbg_axi_awvalid,
    input  logic        dbg_axi_awready,
    output logic [31:0] dbg_axi_awaddr,
    output logic [ 2:0] dbg_axi_awprot,
    output logic        dbg_axi_wvalid,
    input  logic        dbg_axi_wready,
    output logic [31:0] dbg_axi_wdata,
    output logic [ 3:0] dbg_axi_wstrb,
    input  logic        dbg_axi_bvalid,
    output logic        dbg_axi_bready,
    input  logic [ 1:0] dbg_axi_bresp,
    output logic        dbg_axi_arvalid,
    input  logic        dbg_axi_arready,
    output logic [31:0] dbg_axi_araddr,
    output logic [ 2:0] dbg_axi_arprot,
    input  logic        dbg_axi_rvalid,
    output logic        dbg_axi_rready,
    input  logic [ 1:0] dbg_axi_rresp,
    input  logic [31:0] dbg_axi_rdata,

    output logic        debug_irq,
    output logic        cpu_reset_req
);

    // ---------------------------------------------------------------------
    // DMI/DM register addresses (RISC-V Debug Spec 0.13)
    // ---------------------------------------------------------------------
    localparam logic [6:0] DM_DATA0     = 7'h04;
    localparam logic [6:0] DM_DMCONTROL = 7'h10;
    localparam logic [6:0] DM_DMSTATUS  = 7'h11;
    localparam logic [6:0] DM_HARTINFO  = 7'h12;
    localparam logic [6:0] DM_ABSTRACTCS= 7'h16;
    localparam logic [6:0] DM_COMMAND   = 7'h17;
    localparam logic [6:0] DM_SBCS      = 7'h38;
    localparam logic [6:0] DM_SBADDRESS0= 7'h39;
    localparam logic [6:0] DM_SBDATA0   = 7'h3c;

    // ---------------------------------------------------------------------
    // Bus decode (APB or JTAG DMI)
    // ---------------------------------------------------------------------
    logic bus_write;
    logic bus_read;
    logic [6:0] bus_addr;
    logic [31:0] bus_wdata;
    logic [3:0]  bus_wstrb;

    assign bus_write = (psel && penable && pwrite) || (jtag_valid && jtag_write);
    assign bus_read  = (psel && penable && !pwrite) || (jtag_valid && !jtag_write);
    assign bus_addr  = (psel && penable) ? paddr[8:2] : jtag_addr[6:0];
    assign bus_wdata = (psel && penable) ? pwdata : jtag_wdata;
    assign bus_wstrb = (psel && penable) ? pstrb  : jtag_wstrb;

    assign pready  = 1'b1;
    assign pslverr = 1'b0;

    // ---------------------------------------------------------------------
    // DM state
    // ---------------------------------------------------------------------
    logic        dmactive;
    logic        haltreq;
    logic        resumereq;

    logic [31:0] data0;
    logic [31:0] command;
    logic [31:0] dpc_shadow;
    logic [31:0] dcsr_shadow;
    logic        dbg_halted_q;

    logic        abstract_busy;
    logic [2:0]  cmderr;
    logic        dpc_written;   // Track if DPC was explicitly written by debugger

    // System bus access state
    logic        sbreadonaddr;
    logic        sbautoincrement;
    logic        sbreadondata;
    logic        sbbusyerror;
    logic [2:0]  sberror;
    logic [2:0]  sbaccess_size;
    logic [31:0] sbaddress0;
    logic [31:0] sbdata0;

    // ---------------------------------------------------------------------
    // Debug core interface
    // ---------------------------------------------------------------------
    assign dbg_halt_req   = dmactive && haltreq && !dbg_halted;
    assign dbg_resume_req = dmactive && resumereq;

    // Drive dbg_set_pc: pulse when resuming and DPC was explicitly written
    // This ensures the CPU PC is updated from DPC shadow on resume.
    logic resume_pending_q;
    always_ff @(posedge clk) begin
        if (!resetn) begin
            resume_pending_q <= 1'b0;
        end else begin
            resume_pending_q <= dbg_resume_req;
            // Clear dpc_written after the resume pulse has been sent
            if (resume_pending_q)
                dpc_written <= 1'b0;
        end
    end
    assign dbg_set_pc     = dbg_halted && dpc_written;
    assign dbg_set_pc_val = dpc_shadow;

    // ---------------------------------------------------------------------
    // Abstract command handling (Access Register only)
    // ---------------------------------------------------------------------
    logic        cmd_start;
    logic        cmd_write;
    logic        cmd_transfer;
    logic [15:0] cmd_regno;
    logic [2:0]  cmd_aarsize;
    logic        cmd_is_gpr;
    logic        cmd_is_misa;
    logic        cmd_is_dpc;
    logic        cmd_is_dcsr;

    assign cmd_start    = bus_write && (bus_addr == DM_COMMAND);
    assign cmd_write    = command[16];
    assign cmd_transfer = command[17];
    assign cmd_regno    = command[15:0];
    assign cmd_aarsize  = command[22:20];
    assign cmd_is_gpr   = (cmd_regno[15:12] == 4'h1);
    assign cmd_is_misa  = (cmd_regno == 16'h0301);
    assign cmd_is_dpc   = (cmd_regno == 16'h07b1);
    assign cmd_is_dcsr  = (cmd_regno == 16'h07b0);

    assign dbg_reg_addr  = cmd_regno[4:0];
    assign dbg_reg_wdata = data0;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            dmactive    <= 1'b0;
            haltreq     <= 1'b0;
            resumereq   <= 1'b0;
            data0       <= 32'h0;
            command     <= 32'h0;
            dpc_shadow  <= 32'h0001_0000;
            dcsr_shadow <= 32'h4000_01C3;
            dbg_halted_q <= 1'b0;
            abstract_busy <= 1'b0;
            cmderr      <= 3'b000;
            dpc_written <= 1'b0;
            sbreadonaddr   <= 1'b0;
            sbautoincrement<= 1'b0;
            sbreadondata   <= 1'b0;
            sbbusyerror    <= 1'b0;
            sberror        <= 3'b000;
            sbaccess_size  <= 3'b010;
            sbaddress0     <= 32'h0;
            sbdata0        <= 32'h0;
        end else begin
            // Clear one-shot resume when observed
            if (dbg_resume_req)
                resumereq <= 1'b0;

            // Track halt edges to set the DCSR cause field on entry.
            dbg_halted_q <= dbg_halted;
            if (!dbg_halted_q && dbg_halted)
                dcsr_shadow[8:6] <= 3'b011;

            if (bus_write && bus_addr == DM_DMCONTROL) begin
                if (!dmactive && bus_wdata[0]) begin
                    dmactive <= 1'b1;
                end else if (dmactive) begin
                    if (bus_wstrb[0]) begin
                        dmactive <= bus_wdata[0];
                        // `resumereq` is W1 and should not be blocked by a stale
                        // latched halt request in this minimal implementation.
                        if (bus_wdata[30]) begin
                            haltreq   <= 1'b0;
                            resumereq <= 1'b1;
                        end else begin
                            haltreq   <= bus_wdata[31];
                            resumereq <= 1'b0;
                        end
                    end
                    if (!bus_wdata[0]) begin
                        haltreq   <= 1'b0;
                        resumereq <= 1'b0;
                        cmderr    <= 3'b000;
                    end
                end
            end else if (bus_write) begin
                case (bus_addr)
                    DM_DATA0: begin
                        if (bus_wstrb[0]) data0[7:0]   <= bus_wdata[7:0];
                        if (bus_wstrb[1]) data0[15:8]  <= bus_wdata[15:8];
                        if (bus_wstrb[2]) data0[23:16] <= bus_wdata[23:16];
                        if (bus_wstrb[3]) data0[31:24] <= bus_wdata[31:24];
                    end
                    DM_COMMAND: begin
                        if (bus_wstrb[0]) command[7:0]   <= bus_wdata[7:0];
                        if (bus_wstrb[1]) command[15:8]  <= bus_wdata[15:8];
                        if (bus_wstrb[2]) command[23:16] <= bus_wdata[23:16];
                        if (bus_wstrb[3]) command[31:24] <= bus_wdata[31:24];
                        abstract_busy <= 1'b1;
                    end
                    DM_ABSTRACTCS: begin
                        if (bus_wstrb[0] && bus_wdata[10])
                            cmderr <= 3'b000;
                    end
                    DM_SBCS: begin
                        // Byte 1 (bits 15:8): sbreadondata[15], sberror[14:12]
                        if (bus_wstrb[1]) begin
                            sbreadondata <= bus_wdata[15];
                            if (bus_wdata[14:12] != 3'b000) sberror <= 3'b000;
                        end
                        // Byte 2 (bits 23:16): sbreadonaddr[20], sbaccess[19:17], sbautoincrement[16]
                        if (bus_wstrb[2]) begin
                            sbreadonaddr    <= bus_wdata[20];
                            sbaccess_size   <= bus_wdata[19:17];
                            sbautoincrement <= bus_wdata[16];
                        end
                        // Byte 3 (bits 31:24): sbbusyerror[22] W1C — note: bit 22 is in byte 2
                        // Actually bit 22 is in byte 2 as well, handle it there:
                        if (bus_wstrb[2] && bus_wdata[22]) sbbusyerror <= 1'b0;
                        // Bit 29 (sbbusyerror W1C alternate) is in byte 3
                        if (bus_wstrb[3] && bus_wdata[29]) sbbusyerror <= 1'b0;
                    end
                    DM_SBADDRESS0: begin
                        if (bus_wstrb[0]) sbaddress0[7:0]   <= bus_wdata[7:0];
                        if (bus_wstrb[1]) sbaddress0[15:8]  <= bus_wdata[15:8];
                        if (bus_wstrb[2]) sbaddress0[23:16] <= bus_wdata[23:16];
                        if (bus_wstrb[3]) sbaddress0[31:24] <= bus_wdata[31:24];
                    end
                    DM_SBDATA0: begin
                        if (bus_wstrb[0]) sbdata0[7:0]   <= bus_wdata[7:0];
                        if (bus_wstrb[1]) sbdata0[15:8]  <= bus_wdata[15:8];
                        if (bus_wstrb[2]) sbdata0[23:16] <= bus_wdata[23:16];
                        if (bus_wstrb[3]) sbdata0[31:24] <= bus_wdata[31:24];
                    end
                    default: ;
                endcase
            end

            if (abstract_busy) begin
                abstract_busy <= 1'b0;
                if (cmd_transfer && (cmd_aarsize != 3'b010)) begin
                    // Minimal DM only supports 32-bit abstract register accesses.
                    cmderr <= 3'b010;
                end else if (cmd_transfer && cmd_is_gpr) begin
                    if (!dbg_halted) begin
                        cmderr <= 3'b010;
                    end else begin
                        if (cmd_write) begin
                            // write GPR
                        end else begin
                            data0 <= dbg_reg_rdata;
                        end
                    end
                end else if (cmd_transfer && cmd_is_misa && !cmd_write) begin
                    // Minimal CSR support used by OpenOCD during examination.
                    data0 <= 32'h4000_0100; // RV32I
                end else if (cmd_transfer && cmd_is_dpc) begin
                    if (cmd_write) begin
                        dpc_shadow <= data0;
                        dpc_written <= 1'b1;
                    end else
                        data0 <= dbg_cpu_pc;  // Read actual CPU PC, not shadow
                end else if (cmd_transfer && cmd_is_dcsr) begin
                    if (cmd_write)
                        dcsr_shadow <= data0;
                    else
                        data0 <= dcsr_shadow;
                end else if (cmd_transfer && (cmd_regno[15:12] == 4'h0)) begin
                    // Minimal fallback CSR behavior: allow reads/writes so
                    // debugger register enumeration can proceed.
                    if (!cmd_write)
                        data0 <= 32'h0;
                end else begin
                    cmderr <= 3'b010;
                end
            end
        end
    end

    assign dbg_reg_write = abstract_busy && cmd_transfer && cmd_write && cmd_is_gpr && dbg_halted;
    assign dbg_reg_read  = abstract_busy && cmd_transfer && !cmd_write && cmd_is_gpr && dbg_halted;

    // ---------------------------------------------------------------------
    // SBA simple AXI-lite master (32-bit only)
    // ---------------------------------------------------------------------
    typedef enum logic [2:0] {
        SBA_IDLE,
        SBA_W_ADDR,
        SBA_W_RESP,
        SBA_R_ADDR,
        SBA_R_RESP
    } sba_state_t;

    sba_state_t sba_state;

    logic sba_start_read;
    logic sba_start_write;

    assign sba_start_read  = bus_write && (bus_addr == DM_SBADDRESS0) && sbreadonaddr;
    assign sba_start_write = bus_write && (bus_addr == DM_SBDATA0);

    logic aw_done;
    logic w_done;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            sba_state <= SBA_IDLE;
            aw_done <= 1'b0;
            w_done <= 1'b0;
        end else begin
            case (sba_state)
                SBA_IDLE: begin
                    aw_done <= 1'b0;
                    w_done <= 1'b0;
                    if (sba_start_write)
                        sba_state <= SBA_W_ADDR;
                    else if (sba_start_read)
                        sba_state <= SBA_R_ADDR;
                end
                SBA_W_ADDR: begin
                    if (dbg_axi_awready) aw_done <= 1'b1;
                    if (dbg_axi_wready) w_done <= 1'b1;
                    if ((aw_done || dbg_axi_awready) && (w_done || dbg_axi_wready))
                        sba_state <= SBA_W_RESP;
                end
                SBA_W_RESP: begin
                    if (dbg_axi_bvalid)
                        sba_state <= SBA_IDLE;
                end
                SBA_R_ADDR: begin
                    if (dbg_axi_arready)
                        sba_state <= SBA_R_RESP;
                end
                SBA_R_RESP: begin
                    if (dbg_axi_rvalid)
                        sba_state <= SBA_IDLE;
                end
                default: sba_state <= SBA_IDLE;
            endcase
        end
    end

    always_ff @(posedge clk) begin
        if (!resetn) begin
            sbdata0 <= 32'h0;
        end else begin
            if (sba_state == SBA_R_RESP && dbg_axi_rvalid) begin
                case (sbaccess_size)
                    3'b000: begin
                        case (sbaddress0[1:0])
                            2'b00: sbdata0 <= {24'h0, dbg_axi_rdata[7:0]};
                            2'b01: sbdata0 <= {24'h0, dbg_axi_rdata[15:8]};
                            2'b10: sbdata0 <= {24'h0, dbg_axi_rdata[23:16]};
                            default: sbdata0 <= {24'h0, dbg_axi_rdata[31:24]};
                        endcase
                    end
                    3'b001: sbdata0 <= sbaddress0[1] ? {16'h0, dbg_axi_rdata[31:16]}
                                                     : {16'h0, dbg_axi_rdata[15:0]};
                    default: sbdata0 <= dbg_axi_rdata;
                endcase
                if (sbautoincrement)
                    sbaddress0 <= sbaddress0 + ((sbaccess_size == 3'b000) ? 32'd1 :
                                                (sbaccess_size == 3'b001) ? 32'd2 : 32'd4);
            end
            if (sba_state == SBA_W_RESP && dbg_axi_bvalid) begin
                if (sbautoincrement)
                    sbaddress0 <= sbaddress0 + ((sbaccess_size == 3'b000) ? 32'd1 :
                                                (sbaccess_size == 3'b001) ? 32'd2 : 32'd4);
            end
        end
    end

    always_ff @(posedge clk) begin
        if (!resetn) begin
            sbbusyerror <= 1'b0;
            sberror     <= 3'b000;
        end else begin
            if (sba_state != SBA_IDLE) begin
                if (sba_start_read || sba_start_write)
                    sbbusyerror <= 1'b1;
            end
            if (sba_state == SBA_W_RESP && dbg_axi_bvalid && dbg_axi_bresp != 2'b00)
                sberror <= 3'b010;
            if (sba_state == SBA_R_RESP && dbg_axi_rvalid && dbg_axi_rresp != 2'b00)
                sberror <= 3'b010;
        end
    end

    logic [3:0]  sba_wstrb;
    logic [31:0] sba_wdata_aligned;

    always_comb begin
        sba_wstrb = 4'hF;
        sba_wdata_aligned = sbdata0;
        case (sbaccess_size)
            3'b000: begin // 8-bit
                sba_wstrb = (4'b0001 << sbaddress0[1:0]);
                sba_wdata_aligned = ({24'h0, sbdata0[7:0]} << (8 * sbaddress0[1:0]));
            end
            3'b001: begin // 16-bit
                sba_wstrb = sbaddress0[1] ? 4'b1100 : 4'b0011;
                sba_wdata_aligned = sbaddress0[1] ? {sbdata0[15:0], 16'h0}
                                                  : {16'h0, sbdata0[15:0]};
            end
            default: begin
                sba_wstrb = 4'hF;
                sba_wdata_aligned = sbdata0;
            end
        endcase
    end

    assign dbg_axi_awvalid = (sba_state == SBA_W_ADDR) && !aw_done;
    assign dbg_axi_awaddr  = {sbaddress0[31:2], 2'b00};
    assign dbg_axi_awprot  = 3'b000;

    assign dbg_axi_wvalid  = (sba_state == SBA_W_ADDR) && !w_done;
    assign dbg_axi_wdata   = sba_wdata_aligned;
    assign dbg_axi_wstrb   = sba_wstrb;

    assign dbg_axi_bready  = (sba_state == SBA_W_RESP);

    assign dbg_axi_arvalid = (sba_state == SBA_R_ADDR);
    assign dbg_axi_araddr  = {sbaddress0[31:2], 2'b00};
    assign dbg_axi_arprot  = 3'b000;

    assign dbg_axi_rready  = (sba_state == SBA_R_RESP);

    // ---------------------------------------------------------------------
    // Read mux
    // ---------------------------------------------------------------------
    always_comb begin
        prdata = 32'h0;
        case (bus_addr)
            DM_DATA0: begin
                prdata = data0;
            end
            DM_DMCONTROL: begin
                prdata[31] = haltreq;
                prdata[30] = resumereq;
                prdata[0]  = dmactive;
            end
            DM_DMSTATUS: begin
                prdata = 32'h0;
                // Debug Spec 0.13 single-hart status encoding.
                prdata[11]   = !dbg_halted; // allrunning
                prdata[10]   = !dbg_halted; // anyrunning
                prdata[9]    = dbg_halted;  // allhalted
                prdata[8]    = dbg_halted;  // anyhalted
                prdata[7]    = 1'b1;        // authenticated
                prdata[6]    = 1'b0;        // authbusy
                prdata[17]   = !dbg_halted; // allresumeack
                prdata[16]   = !dbg_halted; // anyresumeack
                prdata[3:0]  = 4'h2;        // version=2 (Debug Spec 0.13)
            end
            DM_HARTINFO: begin
                prdata = {8'h0, 4'h0, 1'b1, 3'b000, 4'h1, 12'h0};
            end
            DM_ABSTRACTCS: begin
                prdata[12] = abstract_busy;
                prdata[10:8] = cmderr;
                prdata[3:0] = 4'd1;
            end
            DM_COMMAND: begin
                prdata = command;
            end
            DM_SBCS: begin
                prdata = 32'h0;
                prdata[31:29] = 3'b001;          // sbversion
                prdata[22]    = sbbusyerror;
                prdata[21]    = (sba_state != SBA_IDLE);
                prdata[20]    = sbreadonaddr;
                prdata[19:17] = sbaccess_size;   // current sbaccess
                prdata[16]    = sbautoincrement;
                prdata[15]    = sbreadondata;
                prdata[14:12] = sberror;
                prdata[11:5]  = 7'd32;           // sbasize = 32 address bits
                prdata[0]     = 1'b1;            // sbaccess8 supported
                prdata[1]     = 1'b1;            // sbaccess16 supported
                prdata[2]     = 1'b1;            // sbaccess32 supported
            end
            DM_SBADDRESS0: begin
                prdata = sbaddress0;
            end
            DM_SBDATA0: begin
                prdata = sbdata0;
            end
            default: begin
                prdata = 32'h0;
            end
        endcase
    end

    assign jtag_rdata = prdata;
    assign jtag_ready = (sba_state == SBA_IDLE) && !abstract_busy;

    assign debug_irq = 1'b0;
    assign cpu_reset_req = 1'b0;

endmodule
