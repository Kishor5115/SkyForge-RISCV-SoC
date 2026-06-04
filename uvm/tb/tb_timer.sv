// =============================================================================
// tb_timer.sv - Unit testbench for timer_apb
// Purpose : Connects the APB agent interface to the Timer DUT and runs the
//           Timer test.
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================
`timescale 1ns/1ps
`default_nettype none

module tb_timer;
    import uvm_pkg::*;
    `include "uvm_macros.svh"
    import soc_uvm_pkg::*;

    logic clk = 1'b0;
    logic resetn;
    always #5 clk = ~clk;

    apb_if apb (.clk(clk), .resetn(resetn));

    wire timer_irq;

    timer_apb dut (
        .clk(clk), .resetn(resetn),
        .psel(apb.psel), .penable(apb.penable), .pwrite(apb.pwrite),
        .paddr(apb.paddr), .pwdata(apb.pwdata), .pstrb(apb.pstrb), .pprot(apb.pprot),
        .prdata(apb.prdata), .pready(apb.pready), .pslverr(apb.pslverr),
        .timer_irq(timer_irq)
    );

    initial begin
        resetn = 1'b0;
        repeat (5) @(posedge clk);
        resetn = 1'b1;
    end

    initial begin
        uvm_config_db #(virtual apb_if)::set(null, "*", "vif", apb);
        run_test("timer_test");
    end

    initial begin
        #2ms;
        `uvm_error("TB_TIMER", "global timeout reached")
        $finish;
    end
endmodule

`default_nettype wire
