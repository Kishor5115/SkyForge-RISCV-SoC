// =============================================================================
// tb_gpio.sv - Unit testbench for gpio_apb
// Purpose : Connects the APB agent interface to the GPIO DUT and runs the GPIO
//           test. gpio_in is looped back from gpio_out.
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================
`timescale 1ns/1ps
`default_nettype none

module tb_gpio;
    import uvm_pkg::*;
    `include "uvm_macros.svh"
    import soc_uvm_pkg::*;

    logic clk = 1'b0;
    logic resetn;
    always #5 clk = ~clk;

    apb_if apb (.clk(clk), .resetn(resetn));

    wire [31:0] gpio_out, gpio_oe, gpio_pue, gpio_ds, iof_en, iof_sel;
    wire        gpio_irq;

    gpio_apb dut (
        .clk(clk), .resetn(resetn),
        .psel(apb.psel), .penable(apb.penable), .pwrite(apb.pwrite),
        .paddr(apb.paddr), .pwdata(apb.pwdata), .pstrb(apb.pstrb), .pprot(apb.pprot),
        .prdata(apb.prdata), .pready(apb.pready), .pslverr(apb.pslverr),
        .gpio_in(gpio_out),     // loopback: input mirrors output
        .gpio_out(gpio_out), .gpio_oe(gpio_oe),
        .gpio_pue(gpio_pue), .gpio_ds(gpio_ds),
        .iof_en(iof_en), .iof_sel(iof_sel),
        .gpio_irq(gpio_irq)
    );

    initial begin
        resetn = 1'b0;
        repeat (5) @(posedge clk);
        resetn = 1'b1;
    end

    initial begin
        uvm_config_db #(virtual apb_if)::set(null, "*", "vif", apb);
        run_test("gpio_test");
    end

    initial begin
        #2ms;
        `uvm_error("TB_GPIO", "global timeout reached")
        $finish;
    end
endmodule

`default_nettype wire
