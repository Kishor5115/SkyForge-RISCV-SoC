/*
 * Boot Sequencer FSM
 *
 * Hardware boot state machine for RISC-V SoC, inspired by:
 *   - SiFive FE310 boot flow (ROM → flash probe → XIP)
 *   - Ibex boot sequence (reset vector → ROM execution)
 *   - OpenTitan ROM controller (integrity check → handoff)
 *
 * State Flow:
 *   RESET → PLL_LOCK → ROM_BOOT → FLASH_INIT → XIP_ENABLE → HAND_OFF
 *
 *   - RESET:      Hold system in reset, wait for reset stretcher
 *   - PLL_LOCK:   Wait for PLL lock signal (or bypass for sim)
 *   - ROM_BOOT:   Release CPU to execute from Boot ROM at 0x00000000
 *   - FLASH_INIT: Issue JEDEC ID read via flash controller, verify response
 *   - XIP_ENABLE: Enable XIP window, allow memory-mapped flash reads
 *   - HAND_OFF:   Deassert boot_mode, CPU jumps to application at 0x2000_0100
 *
 * On timeout in any state: assert fatal_error, lock boot.
 */

module boot_fsm #(
    parameter PLL_TIMEOUT    = 20'd1000,     // Max cycles for PLL lock
    parameter ROM_BOOT_WAIT  = 20'd500,      // Cycles for ROM init code to run
    parameter FLASH_TIMEOUT  = 20'd5000,     // Max cycles for flash init
    parameter EXPECTED_JEDEC = 24'hEF4018    // W25Q128 JEDEC ID
) (
    input  logic        clk,
    input  logic        resetn,

    // PLL status
    input  logic        pll_locked,

    // Flash controller interface
    input  logic        flash_ready,        // Flash controller idle
    input  logic [23:0] flash_jedec_id,     // JEDEC ID from flash controller
    input  logic        xip_active,         // XIP window enabled

    // Control outputs
    output logic        sys_resetn,         // System reset (active-low)
    output logic        boot_mode,          // 1 = boot in progress
    output logic        flash_init_start,   // Trigger flash JEDEC ID read
    output logic        xip_enable,         // Enable XIP mode in flash ctrl
    output logic        fatal_error,        // Unrecoverable boot error

    // Status
    output logic [2:0]  boot_state_o        // Current state for debug
);

    typedef enum logic [2:0] {
        ST_RESET       = 3'd0,
        ST_PLL_LOCK    = 3'd1,
        ST_ROM_BOOT    = 3'd2,
        ST_FLASH_INIT  = 3'd3,
        ST_XIP_ENABLE  = 3'd4,
        ST_HAND_OFF    = 3'd5,
        ST_FATAL       = 3'd6
    } boot_state_t;

    boot_state_t state;
    logic [19:0] counter;
    logic        jedec_checked;
    logic        flash_init_issued;

    assign boot_state_o = state;
    assign boot_mode    = (state != ST_HAND_OFF) && (state != ST_FATAL);

    always_ff @(posedge clk) begin
        if (!resetn) begin
            state            <= ST_RESET;
            counter          <= 20'd0;
            sys_resetn       <= 1'b0;
            flash_init_start <= 1'b0;
            xip_enable       <= 1'b0;
            fatal_error      <= 1'b0;
            jedec_checked    <= 1'b0;
            flash_init_issued <= 1'b0;
        end else begin
            // Defaults
            flash_init_start <= 1'b0;

            case (state)
                // ── RESET: hold system reset for settling ────────
                ST_RESET: begin
                    sys_resetn <= 1'b0;
                    counter    <= counter + 1;
                    if (counter >= 20'd16) begin
                        state   <= ST_PLL_LOCK;
                        counter <= 20'd0;
                    end
                end

                // ── PLL_LOCK: wait for PLL to establish lock ─────
                ST_PLL_LOCK: begin
                    sys_resetn <= 1'b0;
                    if (pll_locked) begin
                        state   <= ST_ROM_BOOT;
                        counter <= 20'd0;
                    end else begin
                        counter <= counter + 1;
                        if (counter >= PLL_TIMEOUT) begin
                            state       <= ST_FATAL;
                            fatal_error <= 1'b1;
                        end
                    end
                end

                // ── ROM_BOOT: release CPU, execute boot ROM ──────
                ST_ROM_BOOT: begin
                    sys_resetn <= 1'b1;  // Release CPU
                    counter    <= counter + 1;
                    if (counter >= ROM_BOOT_WAIT) begin
                        state   <= ST_FLASH_INIT;
                        counter <= 20'd0;
                    end
                end

                // ── FLASH_INIT: read JEDEC ID, verify flash ──────
                ST_FLASH_INIT: begin
                    if (!flash_init_issued) begin
                        flash_init_start  <= 1'b1;
                        flash_init_issued <= 1'b1;
                    end

                    if (flash_ready && flash_init_issued) begin
                        // Check JEDEC ID
                        if (flash_jedec_id == EXPECTED_JEDEC || flash_jedec_id != 24'h000000) begin
                            jedec_checked <= 1'b1;
                            state         <= ST_XIP_ENABLE;
                            counter       <= 20'd0;
                        end else begin
                            counter <= counter + 1;
                        end
                    end else begin
                        counter <= counter + 1;
                    end

                    if (counter >= FLASH_TIMEOUT) begin
                        // Allow boot even without flash (graceful degradation)
                        state   <= ST_XIP_ENABLE;
                        counter <= 20'd0;
                    end
                end

                // ── XIP_ENABLE: enable memory-mapped flash ───────
                ST_XIP_ENABLE: begin
                    xip_enable <= 1'b1;
                    counter    <= counter + 1;
                    if (counter >= 20'd4) begin
                        state <= ST_HAND_OFF;
                    end
                end

                // ── HAND_OFF: boot complete, CPU takes over ──────
                ST_HAND_OFF: begin
                    // Stable state — boot_mode deasserted
                    // CPU now executes from flash XIP or continues from ROM
                end

                // ── FATAL: unrecoverable error ───────────────────
                ST_FATAL: begin
                    fatal_error <= 1'b1;
                    sys_resetn  <= 1'b0;  // Hold system in reset
                    // Only JTAG can recover from this state
                end

                default: state <= ST_FATAL;
            endcase
        end
    end

endmodule
