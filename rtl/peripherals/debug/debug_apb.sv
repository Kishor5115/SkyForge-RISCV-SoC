/*
 * Debug Mailbox APB Peripheral
 *
 * APB4-mapped debug mailbox used by firmware-assisted debug service and JTAG
 * transport requests.
 *
 * Design intent and references:
 *   - ARM AMBA APB4 protocol (single-cycle slave model used here)
 *   - RISC-V Debug architecture concept (host request + target service model)
 *   - OpenTitan mailbox/event-style software-visible debug control patterns
 *
 * Features:
 *   - Command mailbox registers (CMD/ADDR/WDATA/RDATA/GO/ACK)
 *   - Interrupt generation for request/done/forced events
 *   - CPU-local reset request for debug recovery flows
 */

module debug_apb (
    input  logic        clk,
    input  logic        resetn,

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

    input  logic        jtag_valid,
    input  logic        jtag_write,
    input  logic [7:0]  jtag_addr,
    input  logic [31:0] jtag_wdata,
    input  logic [3:0]  jtag_wstrb,
    output logic [31:0] jtag_rdata,
    output logic        jtag_ready,

    output logic        debug_irq,
    output logic        cpu_reset_req
);

    localparam logic [31:0] DBG_ID = 32'h4442_4731; // "DBG1"

    localparam logic [7:0] REG_ID         = 8'h00;
    localparam logic [7:0] REG_CTRL       = 8'h04;
    localparam logic [7:0] REG_CMD        = 8'h08;
    localparam logic [7:0] REG_ADDR       = 8'h0C;
    localparam logic [7:0] REG_WDATA      = 8'h10;
    localparam logic [7:0] REG_RDATA      = 8'h14;
    localparam logic [7:0] REG_GO         = 8'h18;
    localparam logic [7:0] REG_ACK        = 8'h1C;
    localparam logic [7:0] REG_IRQ_EN     = 8'h20;
    localparam logic [7:0] REG_IRQ_STATUS = 8'h24;

    logic [31:0] reg_cmd;
    logic [31:0] reg_addr;
    logic [31:0] reg_wdata;
    logic [31:0] reg_rdata;

    logic        cmd_valid;
    logic        cmd_done;
    logic        cmd_error;

    logic [2:0] irq_en;
    logic [2:0] irq_status;

    logic apb_write;
    logic apb_read;

    logic bus_wr_en;
    logic [7:0] bus_addr;
    logic [31:0] bus_wdata;
    logic [3:0]  bus_wstrb;

    logic set_go;
    logic ack_done_ok;
    logic ack_done_err;
    logic clr_force_irq;

    logic [31:0] bus_rdata;

    assign apb_write = psel && penable && pwrite;
    assign apb_read  = psel && penable && !pwrite;

    assign pready  = 1'b1;
    assign pslverr = 1'b0;

    assign bus_wr_en = apb_write || (jtag_valid && jtag_write);
    assign bus_addr  = apb_write ? paddr[7:0] : jtag_addr;
    assign bus_wdata = apb_write ? pwdata     : jtag_wdata;
    assign bus_wstrb = apb_write ? pstrb      : jtag_wstrb;

    assign set_go        = bus_wr_en && (bus_addr == REG_GO)  && bus_wdata[0];
    assign ack_done_ok   = bus_wr_en && (bus_addr == REG_ACK) && bus_wdata[0];
    assign ack_done_err  = bus_wr_en && (bus_addr == REG_ACK) && bus_wdata[1];
    assign clr_force_irq = bus_wr_en && (bus_addr == REG_ACK) && bus_wdata[2];

    always_ff @(posedge clk) begin
        if (!resetn) begin
            cpu_reset_req <= 1'b0;
            reg_cmd       <= 32'h0;
            reg_addr      <= 32'h0;
            reg_wdata     <= 32'h0;
            reg_rdata     <= 32'h0;
            cmd_valid     <= 1'b0;
            cmd_done      <= 1'b0;
            cmd_error     <= 1'b0;
            irq_en        <= 3'b000;
            irq_status    <= 3'b000;
        end else begin
            if (bus_wr_en) begin
                case (bus_addr)
                    REG_CTRL: begin
                        if (bus_wstrb[0]) begin
                            if (bus_wdata[0]) cpu_reset_req <= 1'b1;
                            if (bus_wdata[8]) cpu_reset_req <= 1'b0;
                            if (bus_wdata[1]) irq_status[2] <= 1'b1;
                        end
                    end
                    REG_CMD: begin
                        if (bus_wstrb[0]) reg_cmd[7:0] <= bus_wdata[7:0];
                        if (bus_wstrb[1]) reg_cmd[15:8] <= bus_wdata[15:8];
                        if (bus_wstrb[2]) reg_cmd[23:16] <= bus_wdata[23:16];
                        if (bus_wstrb[3]) reg_cmd[31:24] <= bus_wdata[31:24];
                    end
                    REG_ADDR: begin
                        if (bus_wstrb[0]) reg_addr[7:0] <= bus_wdata[7:0];
                        if (bus_wstrb[1]) reg_addr[15:8] <= bus_wdata[15:8];
                        if (bus_wstrb[2]) reg_addr[23:16] <= bus_wdata[23:16];
                        if (bus_wstrb[3]) reg_addr[31:24] <= bus_wdata[31:24];
                    end
                    REG_WDATA: begin
                        if (bus_wstrb[0]) reg_wdata[7:0] <= bus_wdata[7:0];
                        if (bus_wstrb[1]) reg_wdata[15:8] <= bus_wdata[15:8];
                        if (bus_wstrb[2]) reg_wdata[23:16] <= bus_wdata[23:16];
                        if (bus_wstrb[3]) reg_wdata[31:24] <= bus_wdata[31:24];
                    end
                    REG_RDATA: begin
                        if (bus_wstrb[0]) reg_rdata[7:0] <= bus_wdata[7:0];
                        if (bus_wstrb[1]) reg_rdata[15:8] <= bus_wdata[15:8];
                        if (bus_wstrb[2]) reg_rdata[23:16] <= bus_wdata[23:16];
                        if (bus_wstrb[3]) reg_rdata[31:24] <= bus_wdata[31:24];
                    end
                    REG_IRQ_EN: begin
                        if (bus_wstrb[0]) irq_en <= bus_wdata[2:0];
                    end
                    REG_IRQ_STATUS: begin
                        if (bus_wstrb[0]) irq_status <= irq_status & ~bus_wdata[2:0];
                    end
                    default: ;
                endcase
            end

            if (set_go) begin
                cmd_valid      <= 1'b1;
                cmd_done       <= 1'b0;
                cmd_error      <= 1'b0;
                irq_status[1]  <= 1'b1;
            end

            if (ack_done_ok) begin
                cmd_valid      <= 1'b0;
                cmd_done       <= 1'b1;
                cmd_error      <= 1'b0;
                irq_status[0]  <= 1'b1;
                irq_status[1]  <= 1'b0;
            end

            if (ack_done_err) begin
                cmd_valid      <= 1'b0;
                cmd_done       <= 1'b1;
                cmd_error      <= 1'b1;
                irq_status[0]  <= 1'b1;
                irq_status[1]  <= 1'b0;
            end

            if (clr_force_irq)
                irq_status[2] <= 1'b0;
        end
    end

    always_comb begin
        case (bus_addr)
            REG_ID:         bus_rdata = DBG_ID;
            REG_CTRL:       bus_rdata = {23'h0, cpu_reset_req, 2'b0, cmd_error, cmd_done, cmd_valid, 1'b0};
            REG_CMD:        bus_rdata = reg_cmd;
            REG_ADDR:       bus_rdata = reg_addr;
            REG_WDATA:      bus_rdata = reg_wdata;
            REG_RDATA:      bus_rdata = reg_rdata;
            REG_GO:         bus_rdata = 32'h0;
            REG_ACK:        bus_rdata = 32'h0;
            REG_IRQ_EN:     bus_rdata = {29'h0, irq_en};
            REG_IRQ_STATUS: bus_rdata = {29'h0, irq_status};
            default:        bus_rdata = 32'h0;
        endcase
    end

    always_comb begin
        prdata = 32'h0;
        if (apb_read)
            prdata = bus_rdata;
    end

    assign jtag_rdata = bus_rdata;
    assign jtag_ready = 1'b1;

    assign debug_irq = |(irq_status & irq_en);

endmodule
