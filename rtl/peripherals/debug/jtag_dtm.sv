/*
 * JTAG Debug Transport Module (DTM) — RISC-V Debug Spec 0.13 Compliant
 *
 * Implements IEEE 1149.1 TAP state machine with:
 *   - IDCODE   (mandatory, IR=5'b00001)
 *   - BYPASS   (mandatory, IR=5'b11111)
 *   - DTMCS    (Debug Transport Module Control/Status, IR=5'b10000)
 *   - DMI      (Debug Module Interface, IR=5'b10001)
 *
 * The DMI register provides standard {address, data, op} fields that allow
 * OpenOCD to communicate with the Debug Module via the JTAG TAP.
 *
 * Design references:
 *   - RISC-V External Debug Support Version 0.13.2
 *   - IEEE 1149.1 TAP controller state machine
 *
 * JTAG clock domain: all logic runs on tck.
 * CDC to system clock is handled by the dmi_valid/dmi_ready handshake.
 */

module jtag_dtm (
    // JTAG pins
    input  logic        tck,
    input  logic        tms,
    input  logic        tdi,
    output logic        tdo,

    // System clock domain interface → debug_apb
    input  logic        clk,
    input  logic        resetn,

    output logic        dbg_valid,
    output logic        dbg_write,
    output logic [7:0]  dbg_addr,
    output logic [31:0] dbg_wdata,
    output logic [3:0]  dbg_wstrb,
    input  logic [31:0] dbg_rdata,
    input  logic        dbg_ready
);

    // ── JTAG Instruction Register (5-bit per RISC-V Debug Spec) ─
    localparam IR_LEN    = 5;
    localparam [IR_LEN-1:0] IR_BYPASS = 5'b11111;
    localparam [IR_LEN-1:0] IR_IDCODE = 5'b00001;
    localparam [IR_LEN-1:0] IR_DTMCS  = 5'b10000;  // 0x10
    localparam [IR_LEN-1:0] IR_DMI    = 5'b10001;  // 0x11

    // IDCODE: Version=0x1, PartNumber=0x0005, ManufId=0x000, LSB=1
    localparam [31:0] IDCODE_VAL = 32'h1000_5001;

    // ── DMI Configuration ───────────────────────────────────────
    // DMI address width: 7 bits (sufficient for Debug Module registers)
    localparam DMI_ABITS  = 7;
    // DMI register width: op(2) + data(32) + address(ABITS) = 41 bits
    localparam DMI_WIDTH  = 2 + 32 + DMI_ABITS;  // 41 bits

    // ── DTMCS Register Fields (Read-only status, per spec §6.1.4) ──
    // [31:18] = 0 (reserved)
    // [17]    = dmihardreset (W1: resets DMI, clears sticky error)
    // [16]    = dmireset     (W1: clears sticky error in dmistat)
    // [15]    = 0 (reserved)
    // [14:12] = idle (hint: 1 = must enter Run-Test/Idle for 1 cycle)
    // [11:10] = dmistat (00=no error, 01/10/11=error/busy)
    // [9:4]   = abits (number of address bits in DMI)
    // [3:0]   = version (0001 = version 0.13)
    localparam [31:0] DTMCS_FIXED = {14'b0,                // [31:18] reserved
                                      1'b0, 1'b0,           // [17:16] hardreset/reset (W1, read as 0)
                                      1'b0,                  // [15] reserved
                                      3'd1,                  // [14:12] idle = 1
                                      2'b00,                 // [11:10] dmistat (updated dynamically)
                                      DMI_ABITS[5:0],        // [9:4] abits = 7
                                      4'd1};                 // [3:0] version = 0.13

    // ── TAP State Machine (IEEE 1149.1) ─────────────────────────
    typedef enum logic [3:0] {
        TEST_LOGIC_RESET = 4'd0,
        RUN_TEST_IDLE    = 4'd1,
        SELECT_DR_SCAN   = 4'd2,
        CAPTURE_DR       = 4'd3,
        SHIFT_DR         = 4'd4,
        EXIT1_DR         = 4'd5,
        PAUSE_DR         = 4'd6,
        EXIT2_DR         = 4'd7,
        UPDATE_DR        = 4'd8,
        SELECT_IR_SCAN   = 4'd9,
        CAPTURE_IR       = 4'd10,
        SHIFT_IR         = 4'd11,
        EXIT1_IR         = 4'd12,
        PAUSE_IR         = 4'd13,
        EXIT2_IR         = 4'd14,
        UPDATE_IR        = 4'd15
    } tap_state_t;

    tap_state_t tap_state;

    // TAP state transitions
    always_ff @(posedge tck) begin
        if (!resetn) begin
            tap_state <= TEST_LOGIC_RESET;
        end else begin
            case (tap_state)
                TEST_LOGIC_RESET: if (tms) tap_state <= TEST_LOGIC_RESET; else tap_state <= RUN_TEST_IDLE;
                RUN_TEST_IDLE:    if (tms) tap_state <= SELECT_DR_SCAN;   else tap_state <= RUN_TEST_IDLE;
                SELECT_DR_SCAN:   if (tms) tap_state <= SELECT_IR_SCAN;   else tap_state <= CAPTURE_DR;
                CAPTURE_DR:       if (tms) tap_state <= EXIT1_DR;         else tap_state <= SHIFT_DR;
                SHIFT_DR:         if (tms) tap_state <= EXIT1_DR;         else tap_state <= SHIFT_DR;
                EXIT1_DR:         if (tms) tap_state <= UPDATE_DR;        else tap_state <= PAUSE_DR;
                PAUSE_DR:         if (tms) tap_state <= EXIT2_DR;         else tap_state <= PAUSE_DR;
                EXIT2_DR:         if (tms) tap_state <= UPDATE_DR;        else tap_state <= SHIFT_DR;
                UPDATE_DR:        if (tms) tap_state <= SELECT_DR_SCAN;   else tap_state <= RUN_TEST_IDLE;
                SELECT_IR_SCAN:   if (tms) tap_state <= TEST_LOGIC_RESET; else tap_state <= CAPTURE_IR;
                CAPTURE_IR:       if (tms) tap_state <= EXIT1_IR;         else tap_state <= SHIFT_IR;
                SHIFT_IR:         if (tms) tap_state <= EXIT1_IR;         else tap_state <= SHIFT_IR;
                EXIT1_IR:         if (tms) tap_state <= UPDATE_IR;        else tap_state <= PAUSE_IR;
                PAUSE_IR:         if (tms) tap_state <= EXIT2_IR;         else tap_state <= PAUSE_IR;
                EXIT2_IR:         if (tms) tap_state <= UPDATE_IR;        else tap_state <= SHIFT_IR;
                UPDATE_IR:        if (tms) tap_state <= SELECT_DR_SCAN;   else tap_state <= RUN_TEST_IDLE;
                default:          tap_state <= TEST_LOGIC_RESET;
            endcase
        end
    end

    // ── Instruction Register ────────────────────────────────────
    logic [IR_LEN-1:0] ir_shift;
    logic [IR_LEN-1:0] ir_reg;

    always_ff @(posedge tck) begin
        case (tap_state)
            TEST_LOGIC_RESET: ir_reg <= IR_IDCODE;
            CAPTURE_IR:       ir_shift <= {3'b000, 2'b01};  // Per spec: capture value LSB=01
            SHIFT_IR:         ir_shift <= {tdi, ir_shift[IR_LEN-1:1]};
            UPDATE_IR:        ir_reg <= ir_shift;
            default: ;
        endcase
    end

    // ── Data Registers ──────────────────────────────────────────

    // BYPASS register (1 bit)
    logic bypass_reg;

    // IDCODE register (32 bits)
    logic [31:0] idcode_shift;

    // DTMCS register (32 bits)
    logic [31:0] dtmcs_shift;

    // DMI register (41 bits): {address[40:34], data[33:2], op[1:0]}
    logic [DMI_WIDTH-1:0] dmi_shift;
    logic [DMI_WIDTH-1:0] dmi_shift_rev;

    // DMI status tracking
    logic [1:0] dmi_stat;  // 00=ok, 01=reserved, 10=failed, 11=busy
    logic       dmi_busy;  // Transaction in progress

    // Response data latched from last completed DMI read
    logic [31:0] dmi_resp_data;
    logic [1:0]  dmi_resp_op;  // Response op: 00=success, 10=failed, 11=busy

    always_ff @(posedge tck) begin
        case (tap_state)
            CAPTURE_DR: begin
                case (ir_reg)
                    IR_IDCODE: idcode_shift <= IDCODE_VAL;
                    IR_DTMCS:  dtmcs_shift  <= {DTMCS_FIXED[31:12], dmi_stat, DTMCS_FIXED[9:0]};
                    IR_DMI:    dmi_shift    <= {7'b0, dmi_resp_data, dmi_resp_op};
                    IR_BYPASS: bypass_reg   <= 1'b0;
                    default:   bypass_reg   <= 1'b0;
                endcase
            end
            SHIFT_DR: begin
                case (ir_reg)
                    IR_IDCODE: idcode_shift <= {tdi, idcode_shift[31:1]};
                    IR_DTMCS:  dtmcs_shift  <= {tdi, dtmcs_shift[31:1]};
                    IR_DMI:    dmi_shift    <= {tdi, dmi_shift[DMI_WIDTH-1:1]};
                    IR_BYPASS: bypass_reg   <= tdi;
                    default:   bypass_reg   <= tdi;
                endcase
            end
            default: ;
        endcase
    end

    // ── DTMCS Write Processing (on UPDATE_DR) ────────────────────
    // Handle dmireset (bit 16) and dmihardreset (bit 17)
    wire dtmcs_dmireset_pulse =
        (tap_state == UPDATE_DR) && (ir_reg == IR_DTMCS) && (dtmcs_shift[17] || dtmcs_shift[16]);

    // ── TDO output mux (active on negedge tck per JTAG spec) ────
    always_ff @(negedge tck) begin
        case (tap_state)
            SHIFT_IR: tdo <= ir_shift[0];
            SHIFT_DR: begin
                case (ir_reg)
                    IR_IDCODE: tdo <= idcode_shift[0];
                    IR_DTMCS:  tdo <= dtmcs_shift[0];
                    IR_DMI:    tdo <= dmi_shift[0];
                    default:   tdo <= bypass_reg;
                endcase
            end
            default: tdo <= 1'b0;
        endcase
    end

    // ── DMI Transaction → System Clock Domain ────────────────────
    //
    // DMI register format (LSB-first shift):
    //   [1:0]              = op     (0=NOP, 1=Read, 2=Write)
    //   [33:2]             = data   (32-bit write data)
    //   [DMI_WIDTH-1:34]   = address (7-bit DM register address)
    //
    // On UPDATE_DR with IR=DMI and op!=0, we issue a transaction
    // to the debug_apb module.

    logic update_dmi_pulse;
    logic update_dmi_d;

    always_ff @(posedge tck) begin
        if (!resetn)
            update_dmi_d <= 1'b0;
        else
            update_dmi_d <= (tap_state == UPDATE_DR) && (ir_reg == IR_DMI) && (dmi_shift[1:0] != 2'b00) && !update_dmi_d;
    end

    assign update_dmi_pulse = update_dmi_d;

    // Latch DMI transaction fields in tck domain
    logic        dmi_write_tck;
    logic [6:0]  dmi_addr_tck;
    logic [31:0] dmi_wdata_tck;

    always_ff @(posedge tck) begin
        if (tap_state == UPDATE_DR && ir_reg == IR_DMI && dmi_shift[1:0] != 2'b00) begin
            dmi_write_tck <= (dmi_shift[1:0] == 2'b10);  // op=2 → write
            dmi_addr_tck  <= dmi_shift[DMI_WIDTH-1:34];
            dmi_wdata_tck <= dmi_shift[33:2];
        end
    end

    // CDC: synchronize pulse to system clock
    logic sync_ff1, sync_ff2, sync_ff3;
    always_ff @(posedge clk) begin
        if (!resetn) begin
            sync_ff1 <= 1'b0;
            sync_ff2 <= 1'b0;
            sync_ff3 <= 1'b0;
        end else begin
            sync_ff1 <= update_dmi_d;
            sync_ff2 <= sync_ff1;
            sync_ff3 <= sync_ff2;
        end
    end

    wire sys_pulse = sync_ff2 && !sync_ff3;

    // CDC: synchronize response back to tck domain using a persistent toggle.
    // This avoids missing a one-cycle clk pulse when tck is asynchronous/slower.
    logic        resp_toggle_sys;
    logic [31:0] resp_data_sys;
    logic [1:0]  resp_op_sys;
    logic        resp_tog_sync1, resp_tog_sync2, resp_tog_last;

    always_ff @(posedge tck) begin
        if (tap_state == TEST_LOGIC_RESET) begin
            resp_tog_sync1 <= 1'b0;
            resp_tog_sync2 <= 1'b0;
            resp_tog_last  <= 1'b0;
        end else begin
            resp_tog_sync1 <= resp_toggle_sys;
            resp_tog_sync2 <= resp_tog_sync1;
            resp_tog_last  <= resp_tog_sync2;
        end
    end

    wire resp_tck_pulse = resp_tog_sync2 ^ resp_tog_last;

    // Latch response data in tck domain
    always_ff @(posedge tck) begin
        if (tap_state == TEST_LOGIC_RESET || dtmcs_dmireset_pulse) begin
            dmi_resp_data <= 32'h0;
            dmi_resp_op   <= 2'b00;
            dmi_busy      <= 1'b0;
            dmi_stat      <= 2'b00;
        end else begin
            if (update_dmi_pulse) begin
                dmi_busy <= 1'b1;
                dmi_resp_op <= 2'b11; // busy until response crosses back
                dmi_stat <= 2'b11;
            end
            if (resp_tck_pulse) begin
                dmi_resp_data <= resp_data_sys;
                dmi_resp_op   <= resp_op_sys;
                dmi_busy      <= 1'b0;
                dmi_stat      <= resp_op_sys;
            end
        end
    end

    // Reverse DMI shift order to handle LSB-first JTAG shifts
    genvar dmi_i;
    generate
        for (dmi_i = 0; dmi_i < DMI_WIDTH; dmi_i = dmi_i + 1) begin : gen_dmi_rev
            assign dmi_shift_rev[dmi_i] = dmi_shift[DMI_WIDTH-1-dmi_i];
        end
    endgenerate

    // System clock domain outputs to debug_apb
    always_ff @(posedge clk) begin
        if (!resetn) begin
            dbg_valid     <= 1'b0;
            dbg_write     <= 1'b0;
            dbg_addr      <= 8'h0;
            dbg_wdata     <= 32'h0;
            dbg_wstrb     <= 4'h0;
            resp_toggle_sys <= 1'b0;
            resp_data_sys   <= 32'h0;
            resp_op_sys     <= 2'b00;
        end else begin
            if (sys_pulse && !dbg_valid) begin
                dbg_valid <= 1'b1;
                dbg_write <= dmi_write_tck;
                dbg_addr  <= {1'b0, dmi_addr_tck};  // Zero-extend 7-bit to 8-bit
                dbg_wdata <= dmi_wdata_tck;
                dbg_wstrb <= 4'hF;
            end else if (dbg_valid && dbg_ready) begin
                dbg_valid      <= 1'b0;
                resp_data_sys  <= dbg_rdata;
                resp_op_sys    <= 2'b00;  // success
                resp_toggle_sys <= ~resp_toggle_sys;
            end
        end
    end

endmodule
