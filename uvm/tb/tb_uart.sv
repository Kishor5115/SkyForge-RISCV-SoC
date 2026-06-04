// =============================================================================
// tb_uart.sv - Unit testbench for uart_ctrl_apb
// Purpose : Connects the APB agent interface directly to the UART DUT and runs
//           the UART test. RX is looped back to TX (serial loopback).
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================
`timescale 1ns/1ps
`default_nettype none

module tb_uart;
    import uvm_pkg::*;
    `include "uvm_macros.svh"
    import soc_uvm_pkg::*;

    logic clk = 1'b0;
    logic resetn;
    always #5 clk = ~clk;   // 100 MHz

    apb_if apb (.clk(clk), .resetn(resetn));

    wire uart_tx;
    wire irq;

    uart_ctrl_apb dut (
        .clk(clk), .resetn(resetn),
        .psel(apb.psel), .penable(apb.penable), .pwrite(apb.pwrite),
        .paddr(apb.paddr), .pwdata(apb.pwdata), .pstrb(apb.pstrb), .pprot(apb.pprot),
        .prdata(apb.prdata), .pready(apb.pready), .pslverr(apb.pslverr),
        .uart_tx(uart_tx), .uart_rx(uart_tx),   // loopback
        .irq(irq)
    );

    initial begin
        resetn = 1'b0;
        repeat (5) @(posedge clk);
        resetn = 1'b1;
    end

    initial begin
        uvm_config_db #(virtual apb_if)::set(null, "*", "vif", apb);
        run_test("uart_test");
    end

    initial begin
        #2ms;
        `uvm_error("TB_UART", "global timeout reached")
        $finish;
    end
endmodule

`default_nettype wire
