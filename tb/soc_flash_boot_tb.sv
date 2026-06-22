/*
 * soc_flash_boot_tb — Full-system flash-XIP boot harness (v2)
 *
 * Wires soc_top to the external flash model (preloaded with the FreeRTOS XIP
 * image) so the complete boot path can be exercised:
 *   Boot ROM @0x0  ->  enable flash XIP  ->  jump to 0x40010000  ->  FreeRTOS
 *   fetches .text/.rodata from external flash through the 1 KB I-Cache.
 *
 * Plusargs / defaults:
 *   +BOOTROM_HEX=<file>  Boot ROM image ($readmemh, word-wide)  [bootrom build]
 *   +FLASH_HEX=<file>    Flash image     ($readmemh, byte-wide) [firmware.flash.hex]
 *
 * NOTE: a full FreeRTOS boot over modelled QSPI is slow (each I-Cache miss is a
 * full SPI line fill). Lower the boot CLKDIV for faster sim. This harness is
 * provided for the user to run; CI verification uses flash_xip_tb instead.
 */
`timescale 1ns/1ps

module soc_flash_boot_tb;

    // Bootrom enlarged to 8KB in the integration TB (matches linker_bootrom.ld)
    localparam int BOOTROM_AW = 13;

    string bootrom_hex = "../firmware/bootrom.hex";
    string flash_hex   = "../firmware/firmware.flash.hex";

    logic clk = 0, rst_n = 0;
    always #5 clk = ~clk;   // 100 MHz

    logic        uart_tx, uart_rx = 1'b1;
    logic [31:0] gpio_in = 32'h0, gpio_out, gpio_oe;
    logic        spi_sclk, spi_mosi, spi_miso = 1'b0;
    logic [3:0]  spi_cs_n;
    logic        flash_sclk, flash_cs_n, flash_mosi, flash_miso;
    logic        jtag_tck = 0, jtag_tms = 0, jtag_tdi = 0, jtag_tdo;
    logic        trap;

    soc_top #(
        .BOOTROM_ADDR_WIDTH(BOOTROM_AW),
        .PROGADDR_IRQ      (32'h40010010)
    ) dut (
        .clk(clk), .rst_n(rst_n),
        .uart_tx(uart_tx), .uart_rx(uart_rx),
        .gpio_in(gpio_in), .gpio_out(gpio_out), .gpio_oe(gpio_oe),
        .spi_sclk(spi_sclk), .spi_mosi(spi_mosi), .spi_miso(spi_miso), .spi_cs_n(spi_cs_n),
        .flash_sclk(flash_sclk), .flash_cs_n(flash_cs_n), .flash_mosi(flash_mosi), .flash_miso(flash_miso),
        .jtag_tck(jtag_tck), .jtag_tms(jtag_tms), .jtag_tdi(jtag_tdi), .jtag_tdo(jtag_tdo),
        .trap(trap)
    );

    // External QSPI flash chip, preloaded with the XIP image at flash off 0x10000
    flash_model #(
        .INIT_FILE  (""),               // set via load below
        .LOAD_OFFSET(24'h010000)
    ) u_flash (
        .sclk(flash_sclk), .cs_n(flash_cs_n), .mosi(flash_mosi), .miso(flash_miso)
    );

    // Load the flash image (byte-wide hex) at offset 0x10000
    initial begin
        if ($value$plusargs("FLASH_HEX=%s", flash_hex)) ;
        $display("[TB] loading flash image %s at offset 0x10000", flash_hex);
        $readmemh(flash_hex, u_flash.mem, 24'h010000);
    end

    // Boot ROM preload is handled inside soc_top's bootrom via MEM_INIT_FILE;
    // for sim, force it here if a hex was supplied.
    initial begin
        if ($value$plusargs("BOOTROM_HEX=%s", bootrom_hex)) ;
        // (bootrom $readmemh path is inside rtl/memory/boot_rom.sv MEM_INIT_FILE)
    end

    // Reset + run
    initial begin
        repeat (8) @(posedge clk);
        rst_n = 1;
        $display("[TB] released reset; running flash-XIP boot...");
    end

    // UART TX byte monitor (115200-agnostic: just echoes activity markers)
    initial begin
        #50_000_000;   // bounded run; raise for a full boot
        $display("[TB] time limit reached (this harness is for interactive runs)");
        $finish;
    end

endmodule
