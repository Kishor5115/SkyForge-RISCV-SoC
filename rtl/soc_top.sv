/*
 * RISC-V SoC Top-Level — ASIC Target
 *
 * Integrates soc_core with reset/clock controller and boot FSM.
 * This is the module to be wrapped inside Caravel user_project_wrapper.
 *
 * Memory Map:
 *   0x00000000 - 0x000000FF : Boot ROM (256 Bytes)
 *   0x00010000 - 0x00013FFF : SRAM (16KB, 4× OpenRAM 4KB)
 *   0x20000000 - 0x2000FFFF : APB Peripherals
 *   0x40000000 - 0x40FFFFFF : Flash Controller (QSPI + XIP)
 */

module soc_top #(
    parameter MEM_INIT_FILE = "",
    parameter PROGADDR_IRQ  = 32'h00010010
)(
    input  logic        clk,
    input  logic        rst_n,          // Async active-low reset

    // UART
    output logic        uart_tx,
    input  logic        uart_rx,

    // GPIO
    input  logic [31:0] gpio_in,
    output logic [31:0] gpio_out,
    output logic [31:0] gpio_oe,

    // SPI Master
    output logic        spi_sclk,
    output logic        spi_mosi,
    input  logic        spi_miso,
    output logic [3:0]  spi_cs_n,

    // Flash QSPI
    output logic        flash_sclk,
    output logic        flash_cs_n,
    output logic        flash_mosi,
    input  logic        flash_miso,

    // JTAG
    input  logic        jtag_tck,
    input  logic        jtag_tms,
    input  logic        jtag_tdi,
    output logic        jtag_tdo,

    // Status
    output logic        trap
);

    // ── Internal wires ──────────────────────────────────────────
    logic sys_resetn;

    // ── Reset synchronizer (async assert, sync deassert) ────────
    logic rst_ff1, rst_ff2;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rst_ff1 <= 1'b0;
            rst_ff2 <= 1'b0;
        end else begin
            rst_ff1 <= 1'b1;
            rst_ff2 <= rst_ff1;
        end
    end
    assign sys_resetn = rst_ff2;

    // ── SoC Core ────────────────────────────────────────────────
    soc_core #(
        .MEM_INIT_FILE(MEM_INIT_FILE),
        .PROGADDR_IRQ(PROGADDR_IRQ)
    ) u_soc_core (
        .clk_i        (clk),
        .rst_ni       (sys_resetn),
        // UART
        .uart_tx_o    (uart_tx),
        .uart_rx_i    (uart_rx),
        // GPIO
        .gpio_in_i    (gpio_in),
        .gpio_out_o   (gpio_out),
        .gpio_oe_o    (gpio_oe),
        // SPI
        .spi_sclk_o   (spi_sclk),
        .spi_mosi_o   (spi_mosi),
        .spi_miso_i   (spi_miso),
        .spi_cs_n_o   (spi_cs_n),
        // Flash
        .flash_sclk_o (flash_sclk),
        .flash_cs_n_o (flash_cs_n),
        .flash_mosi_o (flash_mosi),
        .flash_miso_i (flash_miso),
        // JTAG
        .jtag_tck_i   (jtag_tck),
        .jtag_tms_i   (jtag_tms),
        .jtag_tdi_i   (jtag_tdi),
        .jtag_tdo_o   (jtag_tdo),
        // Status
        .trap_o       (trap)
    );

endmodule
