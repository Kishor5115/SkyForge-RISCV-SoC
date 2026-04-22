/*
 *  PicoRV32 -- A Small RISC-V (RV32I) Processor Core
 *
 *  Copyright (C) 2015  Claire Xenia Wolf <claire@yosyshq.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/* verilator lint_off WIDTH */
/* verilator lint_off PINMISSING */
/* verilator lint_off CASEOVERLAP */
/* verilator lint_off CASEINCOMPLETE */

`timescale 1 ns / 1 ps

module picorv32_axi_adapter (
	input logic clk, 
    input logic resetn,

	// AXI4-lite master memory interface

	output logic        mem_axi_awvalid,
	input  logic        mem_axi_awready,
	output logic [31:0] mem_axi_awaddr,
	output logic [ 2:0] mem_axi_awprot,

	output logic        mem_axi_wvalid,
	input  logic        mem_axi_wready,
	output logic [31:0] mem_axi_wdata,
	output logic [ 3:0] mem_axi_wstrb,

	input  logic        mem_axi_bvalid,
	output logic        mem_axi_bready,

	output logic        mem_axi_arvalid,
	input  logic        mem_axi_arready,
	output logic [31:0] mem_axi_araddr,
	output logic [ 2:0] mem_axi_arprot,

	input  logic        mem_axi_rvalid,
	output logic        mem_axi_rready,
	input  logic [31:0] mem_axi_rdata,

	// Native PicoRV32 memory interface

	input  logic        mem_valid,
	input  logic        mem_instr,
	output logic        mem_ready,
	input  logic [31:0] mem_addr,
	input  logic [31:0] mem_wdata,
	input  logic [ 3:0] mem_wstrb,
	output logic [31:0] mem_rdata
);
	logic ack_awvalid;
	logic ack_arvalid;
	logic ack_wvalid;
	logic xfer_done;

	assign mem_axi_awvalid = mem_valid && |mem_wstrb && !ack_awvalid;
	assign mem_axi_awaddr = mem_addr;
	assign mem_axi_awprot = 0;

	assign mem_axi_arvalid = mem_valid && !mem_wstrb && !ack_arvalid;
	assign mem_axi_araddr = mem_addr;
	assign mem_axi_arprot = mem_instr ? 3'b100 : 3'b000;

	assign mem_axi_wvalid = mem_valid && |mem_wstrb && !ack_wvalid;
	assign mem_axi_wdata = mem_wdata;
	assign mem_axi_wstrb = mem_wstrb;

	assign mem_ready = (mem_axi_bvalid && mem_axi_bready) || (mem_axi_rvalid && mem_axi_rready);
	assign mem_axi_bready = mem_valid && |mem_wstrb;
	assign mem_axi_rready = mem_valid && !mem_wstrb;
	assign mem_rdata = mem_axi_rdata;

	always_ff @(posedge clk) begin
		if (!resetn) begin
			ack_awvalid <= 0;
			ack_arvalid <= 0;
			ack_wvalid <= 0;
			xfer_done <= 0;
		end else begin
			xfer_done <= mem_valid && mem_ready;
			if (mem_axi_awready && mem_axi_awvalid)
				ack_awvalid <= 1;
			if (mem_axi_arready && mem_axi_arvalid)
				ack_arvalid <= 1;
			if (mem_axi_wready && mem_axi_wvalid)
				ack_wvalid <= 1;
			if (xfer_done || !mem_valid) begin
				ack_awvalid <= 0;
				ack_arvalid <= 0;
				ack_wvalid <= 0;
			end
		end
	end
endmodule
