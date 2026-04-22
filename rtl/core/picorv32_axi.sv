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

module picorv32_axi #(
	parameter [ 0:0] ENABLE_COUNTERS = 1,
	parameter [ 0:0] ENABLE_COUNTERS64 = 0,
	parameter [ 0:0] ENABLE_REGS_16_31 = 1,
	parameter [ 0:0] ENABLE_REGS_DUALPORT = 1,
	parameter [ 0:0] TWO_STAGE_SHIFT = 0,
	parameter [ 0:0] BARREL_SHIFTER = 0,
	parameter [ 0:0] TWO_CYCLE_COMPARE = 0,
	parameter [ 0:0] TWO_CYCLE_ALU = 0,
	parameter [ 0:0] COMPRESSED_ISA = 0,
	parameter [ 0:0] CATCH_MISALIGN = 0,
	parameter [ 0:0] CATCH_ILLINSN = 0,
	parameter [ 0:0] ENABLE_PCPI = 0,
	parameter [ 0:0] ENABLE_MUL = 0,
	parameter [ 0:0] ENABLE_FAST_MUL = 0,
	parameter [ 0:0] ENABLE_DIV = 0,
	parameter [ 0:0] ENABLE_IRQ = 0,
	parameter [ 0:0] ENABLE_IRQ_QREGS = 0,
	parameter [ 0:0] ENABLE_IRQ_TIMER = 0,
	parameter [ 0:0] ENABLE_TRACE = 0,
	parameter [ 0:0] REGS_INIT_ZERO = 0,
	parameter [31:0] MASKED_IRQ = 32'h 0000_0000,
	parameter [31:0] LATCHED_IRQ = 32'h ffff_ffff,
	parameter [31:0] PROGADDR_RESET = 32'h 0000_0000,
	parameter [31:0] PROGADDR_IRQ = 32'h 0000_0010,
	parameter [31:0] STACKADDR = 32'h ffff_ffff
) (
	input  logic clk, resetn,
	output logic trap,
	input  logic [31:0] irq,
	output logic [31:0] eoi,

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

	// CPU Instruction Trace (active when ENABLE_TRACE=1)
	output logic        trace_valid,
	output logic [35:0] trace_data
);
	logic        mem_valid;
	logic [31:0] mem_addr;
	logic [31:0] mem_wdata;
	logic [ 3:0] mem_wstrb;
	logic        mem_instr;
	logic        mem_ready;
	logic [31:0] mem_rdata;

    
    logic        pcpi_valid;
    logic [31:0] pcpi_insn;
    logic [31:0] pcpi_rs1;
    logic [31:0] pcpi_rs2;
    logic        pcpi_wr = '0;
    logic [31:0] pcpi_rd = '0;
    logic        pcpi_wait = '0;
    logic        pcpi_ready = '0;

	picorv32_axi_adapter axi_adapter (
		.clk            (clk            ),
		.resetn         (resetn         ),
		.mem_axi_awvalid(mem_axi_awvalid),
		.mem_axi_awready(mem_axi_awready),
		.mem_axi_awaddr (mem_axi_awaddr ),
		.mem_axi_awprot (mem_axi_awprot ),
		.mem_axi_wvalid (mem_axi_wvalid ),
		.mem_axi_wready (mem_axi_wready ),
		.mem_axi_wdata  (mem_axi_wdata  ),
		.mem_axi_wstrb  (mem_axi_wstrb  ),
		.mem_axi_bvalid (mem_axi_bvalid ),
		.mem_axi_bready (mem_axi_bready ),
		.mem_axi_arvalid(mem_axi_arvalid),
		.mem_axi_arready(mem_axi_arready),
		.mem_axi_araddr (mem_axi_araddr ),
		.mem_axi_arprot (mem_axi_arprot ),
		.mem_axi_rvalid (mem_axi_rvalid ),
		.mem_axi_rready (mem_axi_rready ),
		.mem_axi_rdata  (mem_axi_rdata  ),
		.mem_valid      (mem_valid      ),
		.mem_instr      (mem_instr      ),
		.mem_ready      (mem_ready      ),
		.mem_addr       (mem_addr       ),
		.mem_wdata      (mem_wdata      ),
		.mem_wstrb      (mem_wstrb      ),
		.mem_rdata      (mem_rdata      )
	);

	picorv32 #(
		.ENABLE_COUNTERS     (ENABLE_COUNTERS     ),
		.ENABLE_COUNTERS64   (ENABLE_COUNTERS64   ),
		.ENABLE_REGS_16_31   (ENABLE_REGS_16_31   ),
		.ENABLE_REGS_DUALPORT(ENABLE_REGS_DUALPORT),
		.TWO_STAGE_SHIFT     (TWO_STAGE_SHIFT     ),
		.BARREL_SHIFTER      (BARREL_SHIFTER      ),
		.TWO_CYCLE_COMPARE   (TWO_CYCLE_COMPARE   ),
		.TWO_CYCLE_ALU       (TWO_CYCLE_ALU       ),
		.COMPRESSED_ISA      (COMPRESSED_ISA      ),
		.CATCH_MISALIGN      (CATCH_MISALIGN      ),
		.CATCH_ILLINSN       (CATCH_ILLINSN       ),
		.ENABLE_PCPI         (ENABLE_PCPI         ),
		.ENABLE_MUL          (ENABLE_MUL          ),
		.ENABLE_FAST_MUL     (ENABLE_FAST_MUL     ),
		.ENABLE_DIV          (ENABLE_DIV          ),
		.ENABLE_IRQ          (ENABLE_IRQ          ),
		.ENABLE_IRQ_QREGS    (ENABLE_IRQ_QREGS    ),
		.ENABLE_IRQ_TIMER    (ENABLE_IRQ_TIMER    ),
		.ENABLE_TRACE        (ENABLE_TRACE        ),
		.REGS_INIT_ZERO      (REGS_INIT_ZERO      ),
		.MASKED_IRQ          (MASKED_IRQ          ),
		.LATCHED_IRQ         (LATCHED_IRQ         ),
		.PROGADDR_RESET      (PROGADDR_RESET      ),
		.PROGADDR_IRQ        (PROGADDR_IRQ        ),
		.STACKADDR           (STACKADDR           )
	) picorv32_core (
		.clk      (clk   ),
		.resetn   (resetn),
		.trap     (trap  ),

		.mem_valid(mem_valid),
		.mem_addr (mem_addr ),
		.mem_wdata(mem_wdata),
		.mem_wstrb(mem_wstrb),
		.mem_instr(mem_instr),
		.mem_ready(mem_ready),
		.mem_rdata(mem_rdata),

		.pcpi_valid(pcpi_valid),
		.pcpi_insn (pcpi_insn ),
		.pcpi_rs1  (pcpi_rs1  ),
		.pcpi_rs2  (pcpi_rs2  ),
		.pcpi_wr   (pcpi_wr   ),
		.pcpi_rd   (pcpi_rd   ),
		.pcpi_wait (pcpi_wait ),
		.pcpi_ready(pcpi_ready),

		.irq(irq),
		.eoi(eoi),

`ifdef RISCV_FORMAL
		.rvfi_valid    (rvfi_valid    ),
		.rvfi_order    (rvfi_order    ),
		.rvfi_insn     (rvfi_insn     ),
		.rvfi_trap     (rvfi_trap     ),
		.rvfi_halt     (rvfi_halt     ),
		.rvfi_intr     (rvfi_intr     ),
		.rvfi_rs1_addr (rvfi_rs1_addr ),
		.rvfi_rs2_addr (rvfi_rs2_addr ),
		.rvfi_rs1_rdata(rvfi_rs1_rdata),
		.rvfi_rs2_rdata(rvfi_rs2_rdata),
		.rvfi_rd_addr  (rvfi_rd_addr  ),
		.rvfi_rd_wdata (rvfi_rd_wdata ),
		.rvfi_pc_rdata (rvfi_pc_rdata ),
		.rvfi_pc_wdata (rvfi_pc_wdata ),
		.rvfi_mem_addr (rvfi_mem_addr ),
		.rvfi_mem_rmask(rvfi_mem_rmask),
		.rvfi_mem_wmask(rvfi_mem_wmask),
		.rvfi_mem_rdata(rvfi_mem_rdata),
		.rvfi_mem_wdata(rvfi_mem_wdata),
`endif

		.trace_valid(trace_valid),
		.trace_data (trace_data)
	);
endmodule
