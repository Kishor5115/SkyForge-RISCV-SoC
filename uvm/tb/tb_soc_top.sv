// =============================================================================
// tb_soc_top.sv - SoC-level testbench (DUT = soc_top)
// Purpose : Register-level SoC test with no firmware (MEM_INIT_FILE=""). The
//           UVM APB master cannot reach the internal APB bus through ports, so
//           the agent's apb_if is bound to the SoC's internal APB bus by:
//             * continuously forcing the request signals onto the internal bus
//             * continuously assigning the internal response back to the agent
//
//   Internal APB bus path (see rtl/asic/soc_core.sv):
//       dut.u_soc_core.apb_psel    / apb_penable / apb_pwrite
//       dut.u_soc_core.apb_paddr   / apb_pwdata  / apb_pstrb  / apb_pprot
//       dut.u_soc_core.apb_prdata  / apb_pready  / apb_pslverr
//
//   Runs soc_smoke_test by default; +UVM_TESTNAME=soc_stress_test overrides.
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================
`timescale 1ns/1ps
`default_nettype none

module tb_soc_top;
    import uvm_pkg::*;
    `include "uvm_macros.svh"
    import soc_uvm_pkg::*;

    logic clk = 1'b0;
    logic rst_n;
    always #5 clk = ~clk;

    soc_if socif (.clk(clk), .rst_n(rst_n));
    apb_if apb   (.clk(clk), .resetn(rst_n));

    // ---- DUT ----
    soc_top #(.MEM_INIT_FILE("")) dut (
        .clk(clk), .rst_n(rst_n),
        .uart_tx(socif.uart_tx), .uart_rx(socif.uart_rx),
        .gpio_in(socif.gpio_in), .gpio_out(socif.gpio_out), .gpio_oe(socif.gpio_oe),
        .spi_sclk(socif.spi_sclk), .spi_mosi(socif.spi_mosi),
        .spi_miso(socif.spi_miso), .spi_cs_n(socif.spi_cs_n),
        .flash_sclk(socif.flash_sclk), .flash_cs_n(socif.flash_cs_n),
        .flash_mosi(socif.flash_mosi), .flash_miso(socif.flash_miso),
        .jtag_tck(socif.jtag_tck), .jtag_tms(socif.jtag_tms),
        .jtag_tdi(socif.jtag_tdi), .jtag_tdo(socif.jtag_tdo),
        .trap(socif.trap)
    );

    // ---- Top-level tie-offs / loopbacks ----
    assign socif.uart_rx   = socif.uart_tx;
    assign socif.gpio_in   = socif.gpio_out;
    assign socif.spi_miso  = socif.spi_mosi;
    assign socif.flash_miso = 1'b0;
    assign socif.jtag_tck  = 1'b0;
    assign socif.jtag_tms  = 1'b0;
    assign socif.jtag_tdi  = 1'b0;

    // ---- Bind agent interface to the internal APB bus ----
    initial begin
        force dut.u_soc_core.apb_psel    = apb.psel;
        force dut.u_soc_core.apb_penable = apb.penable;
        force dut.u_soc_core.apb_pwrite  = apb.pwrite;
        force dut.u_soc_core.apb_paddr   = apb.paddr;
        force dut.u_soc_core.apb_pwdata  = apb.pwdata;
        force dut.u_soc_core.apb_pstrb   = apb.pstrb;
        force dut.u_soc_core.apb_pprot   = apb.pprot;
    end
    assign apb.prdata  = dut.u_soc_core.apb_prdata;
    assign apb.pready  = dut.u_soc_core.apb_pready;
    assign apb.pslverr = dut.u_soc_core.apb_pslverr;

    initial begin
        rst_n = 1'b0;
        repeat (10) @(posedge clk);
        rst_n = 1'b1;
    end

    initial begin
        uvm_config_db #(virtual apb_if)::set(null, "*", "vif", apb);
        uvm_config_db #(virtual soc_if)::set(null, "*", "soc_vif", socif);
        run_test("soc_smoke_test");
    end

    initial begin
        #10ms;
        `uvm_error("TB_SOC", "global timeout reached")
        $finish;
    end
endmodule

`default_nettype wire
