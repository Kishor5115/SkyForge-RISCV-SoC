/*
 * Reset & Clock Controller
 *
 * Provides synchronized reset distribution and clock gating for RISC-V SoC.
 *
 * Design Reference:
 *   - SiFive FE310 PRCI (Power, Reset, Clock, Interrupts)
 *   - OpenTitan rstmgr (reset manager with reset trees)
 *   - PULP cluster clock/reset distribution
 *
 * Features:
 *   - Power-on reset stretcher (minimum 16 clock cycles)
 *   - Synchronous reset tree with configurable fan-out
 *   - PLL lock detection input
 *   - Per-domain clock gating cells
 *   - Watchdog timer (32-bit, kick register to prevent timeout)
 */

module reset_clk #(
    parameter RESET_STRETCH = 5'd16,        // Minimum reset width in clocks
    parameter WDT_DEFAULT   = 32'h00FF_FFFF // Default watchdog timeout
) (
    input  logic clk,                        // System clock
    input  logic rst_n_async,                // Asynchronous external reset (active-low)

    // PLL interface
    input  logic pll_locked,                 // PLL lock status

    // System reset output
    output logic sys_resetn,                 // Synchronized system reset (active-low)

    // Per-domain clock enables
    input  logic spi_clk_en,
    input  logic flash_clk_en,
    input  logic gpio_clk_en,

    output logic spi_clk_gated,
    output logic flash_clk_gated,
    output logic gpio_clk_gated,

    // Watchdog interface (APB-accessible via memory-mapped register)
    input  logic        wdt_kick,            // Write to kick register resets WDT
    input  logic        wdt_enable,          // Watchdog enable
    output logic        wdt_timeout,         // Watchdog timeout flag
    output logic        wdt_irq              // Watchdog interrupt
);

    // =========================================================================
    //  Reset Synchronizer — double-flop async-to-sync
    // =========================================================================
    logic rst_sync_ff1, rst_sync_ff2;

    always_ff @(posedge clk or negedge rst_n_async) begin
        if (!rst_n_async) begin
            rst_sync_ff1 <= 1'b0;
            rst_sync_ff2 <= 1'b0;
        end else begin
            rst_sync_ff1 <= 1'b1;
            rst_sync_ff2 <= rst_sync_ff1;
        end
    end

    wire rst_synced = rst_sync_ff2;

    // =========================================================================
    //  Reset Stretcher — hold reset for minimum N cycles after deassertion
    // =========================================================================
    logic [4:0] stretch_cnt;
    logic       reset_stretched;

    always_ff @(posedge clk or negedge rst_n_async) begin
        if (!rst_n_async) begin
            stretch_cnt     <= 5'd0;
            reset_stretched <= 1'b0;
        end else begin
            if (!rst_synced) begin
                stretch_cnt     <= 5'd0;
                reset_stretched <= 1'b0;
            end else if (stretch_cnt < RESET_STRETCH) begin
                stretch_cnt <= stretch_cnt + 1;
                reset_stretched <= 1'b0;
            end else begin
                reset_stretched <= 1'b1;
            end
        end
    end

    // System reset: stretched AND PLL locked
    assign sys_resetn = reset_stretched & pll_locked;

    // =========================================================================
    //  Clock Gating Cells — simple AND-gate style (latch-based for ASIC)
    // =========================================================================
    // Simulation/RTL model: simple AND gate
    // ASIC implementation: replace with library ICG (integrated clock gating) cell
    assign spi_clk_gated   = clk & spi_clk_en;
    assign flash_clk_gated = clk & flash_clk_en;
    assign gpio_clk_gated  = clk & gpio_clk_en;

    // =========================================================================
    //  Watchdog Timer — 32-bit downcounter
    // =========================================================================
    logic [31:0] wdt_counter;

    always_ff @(posedge clk or negedge rst_n_async) begin
        if (!rst_n_async) begin
            wdt_counter <= WDT_DEFAULT;
            wdt_timeout <= 1'b0;
        end else if (!sys_resetn) begin
            wdt_counter <= WDT_DEFAULT;
            wdt_timeout <= 1'b0;
        end else begin
            if (wdt_kick) begin
                wdt_counter <= WDT_DEFAULT;
                wdt_timeout <= 1'b0;
            end else if (wdt_enable) begin
                if (wdt_counter == 32'd0) begin
                    wdt_timeout <= 1'b1;
                end else begin
                    wdt_counter <= wdt_counter - 1;
                end
            end
        end
    end

    assign wdt_irq = wdt_timeout;

endmodule
