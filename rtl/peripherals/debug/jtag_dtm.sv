/*
 * Minimal JTAG Debug Transport Module (DTM)
 *
 * Implements IEEE 1149.1 TAP state machine with:
 *   - IDCODE (mandatory)
 *   - BYPASS (mandatory)
 *   - DEBUG  (custom: bridges to debug_apb mailbox)
 *
 * Design references:
 *   - RISC-V Debug Specification 0.13
 *   - IEEE 1149.1 TAP controller state machine
 *   - OpenTitan JTAG TAP (simplified)
 *
 * JTAG clock domain: all logic runs on tck.
 * CDC to system clock is handled by the dbg_valid/dbg_ready handshake.
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

    // ── JTAG instruction register ───────────────────────────────
    localparam IR_LEN   = 4;
    localparam IR_IDCODE = 4'b0001;
    localparam IR_DEBUG  = 4'b0010;
    localparam IR_BYPASS = 4'b1111;

    localparam [31:0] IDCODE_VAL = 32'h1000_5001; // Custom IDCODE

    // ── TAP state machine (IEEE 1149.1) ─────────────────────────
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

    // ── Instruction Register ────────────────────────────────────
    logic [IR_LEN-1:0] ir_shift;
    logic [IR_LEN-1:0] ir_reg;

    always_ff @(posedge tck) begin
        case (tap_state)
            TEST_LOGIC_RESET: ir_reg <= IR_IDCODE;
            CAPTURE_IR:       ir_shift <= IR_IDCODE; // Capture: fixed pattern
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

    // DEBUG register (41 bits: 1 write + 8 addr + 32 data)
    logic [40:0] debug_shift;

    always_ff @(posedge tck) begin
        case (tap_state)
            CAPTURE_DR: begin
                case (ir_reg)
                    IR_IDCODE: idcode_shift <= IDCODE_VAL;
                    IR_DEBUG:  debug_shift  <= {dbg_rdata, 8'h0, 1'b0};
                    IR_BYPASS: bypass_reg   <= 1'b0;
                    default:   bypass_reg   <= 1'b0;
                endcase
            end
            SHIFT_DR: begin
                case (ir_reg)
                    IR_IDCODE: idcode_shift <= {tdi, idcode_shift[31:1]};
                    IR_DEBUG:  debug_shift  <= {tdi, debug_shift[40:1]};
                    IR_BYPASS: bypass_reg   <= tdi;
                    default:   bypass_reg   <= tdi;
                endcase
            end
            default: ;
        endcase
    end

    // ── TDO output mux (active on negedge tck per JTAG spec) ────
    always_ff @(negedge tck) begin
        case (tap_state)
            SHIFT_IR: tdo <= ir_shift[0];
            SHIFT_DR: begin
                case (ir_reg)
                    IR_IDCODE: tdo <= idcode_shift[0];
                    IR_DEBUG:  tdo <= debug_shift[0];
                    default:   tdo <= bypass_reg;
                endcase
            end
            default: tdo <= 1'b0;
        endcase
    end

    // ── Debug register → system clock domain handshake ──────────
    // On UPDATE_DR with IR=DEBUG: issue a debug transaction
    // debug_shift format: [0]=write, [8:1]=addr, [40:9]=wdata
    logic update_dr_pulse;
    logic update_dr_d;

    always_ff @(posedge tck)
        update_dr_d <= (tap_state == UPDATE_DR) && (ir_reg == IR_DEBUG);

    assign update_dr_pulse = (tap_state == UPDATE_DR) && (ir_reg == IR_DEBUG) && !update_dr_d;

    // CDC: synchronize pulse to system clock
    logic sync_ff1, sync_ff2, sync_ff3;
    always_ff @(posedge clk) begin
        if (!resetn) begin
            sync_ff1 <= 1'b0;
            sync_ff2 <= 1'b0;
            sync_ff3 <= 1'b0;
        end else begin
            sync_ff1 <= update_dr_d;
            sync_ff2 <= sync_ff1;
            sync_ff3 <= sync_ff2;
        end
    end

    wire sys_pulse = sync_ff2 && !sync_ff3;

    // Latch debug transaction in tck domain
    logic        dbg_write_tck;
    logic [7:0]  dbg_addr_tck;
    logic [31:0] dbg_wdata_tck;

    always_ff @(posedge tck) begin
        if (update_dr_pulse) begin
            dbg_write_tck <= debug_shift[0];
            dbg_addr_tck  <= debug_shift[8:1];
            dbg_wdata_tck <= debug_shift[40:9];
        end
    end

    // System clock domain outputs
    always_ff @(posedge clk) begin
        if (!resetn) begin
            dbg_valid <= 1'b0;
            dbg_write <= 1'b0;
            dbg_addr  <= 8'h0;
            dbg_wdata <= 32'h0;
            dbg_wstrb <= 4'h0;
        end else begin
            if (sys_pulse) begin
                dbg_valid <= 1'b1;
                dbg_write <= dbg_write_tck;
                dbg_addr  <= dbg_addr_tck;
                dbg_wdata <= dbg_wdata_tck;
                dbg_wstrb <= 4'hF;
            end else if (dbg_valid && dbg_ready) begin
                dbg_valid <= 1'b0;
            end
        end
    end

endmodule
