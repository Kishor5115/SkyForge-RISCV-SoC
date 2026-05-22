/*
 * Boot ROM — AXI4-Lite Read-Only Memory
 *
 * Parameterized single-cycle read-only ROM for RISC-V SoC boot.
 * Initialized from hex file via $readmemh.
 *
 * Design Reference:
 *   - SiFive FE310 Mask ROM (single-cycle, address-aligned reads)
 *   - Ibex boot ROM (simple AXI-Lite read slave)
 *
 * Features:
 *   - Single-cycle read latency
 *   - Parameterized size (default 16KB for simulation)
 *   - Write attempts are silently acknowledged (no write effect)
 *   - Aliased at 0x0000_0000 for RISC-V reset vector
 */

module bootrom #(
    parameter ADDR_WIDTH    = 14,              // 16KB default (2^14)
    parameter DATA_WIDTH    = 32,
    parameter MEM_INIT_FILE = "bootrom.hex"    // Hex file for initialization
) (
    input  logic clk,
    input  logic resetn,

    // AXI4-Lite Slave Read-Only Interface
    input  logic [ADDR_WIDTH-1:0] axi_araddr,
    input  logic [2:0]            axi_arprot,
    input  logic                  axi_arvalid,
    output logic                  axi_arready,

    output logic [DATA_WIDTH-1:0] axi_rdata,
    output logic                  axi_rvalid,
    input  logic                  axi_rready,
    output logic [1:0]            axi_rresp,

    // Write channel — accepted but ignored (ROM is read-only)
    input  logic [ADDR_WIDTH-1:0] axi_awaddr,
    input  logic [2:0]            axi_awprot,
    input  logic                  axi_awvalid,
    output logic                  axi_awready,

    input  logic [DATA_WIDTH-1:0] axi_wdata,
    input  logic                  axi_wvalid,
    output logic                  axi_wready,
    input  logic [3:0]            axi_wstrb,

    output logic                  axi_bvalid,
    input  logic                  axi_bready,
    output logic [1:0]            axi_bresp
);

    // ── Memory Array ─────────────────────────────────────────
    localparam MEM_DEPTH = 2 ** (ADDR_WIDTH - 2);  // Word-addressable
    logic [DATA_WIDTH-1:0] rom [0:MEM_DEPTH-1];

    // Initialize ROM from hex file
    initial begin
        for (int i = 0; i < MEM_DEPTH; i++)
            rom[i] = 32'h0000_0013;  // NOP (addi x0, x0, 0) as default
        if (MEM_INIT_FILE != "")
            $readmemh(MEM_INIT_FILE, rom);
    end

    // ── Read Channel — single-cycle latency ──────────────────
    assign axi_rresp = 2'b00;  // Always OKAY

    logic rvalid_reg;
    logic [DATA_WIDTH-1:0] rdata_reg;

    assign axi_arready = !rvalid_reg;
    assign axi_rvalid  = rvalid_reg;
    assign axi_rdata   = rdata_reg;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            rvalid_reg <= 1'b0;
            rdata_reg  <= '0;
        end else begin
            if (axi_arvalid && axi_arready) begin
                rdata_reg  <= rom[axi_araddr[ADDR_WIDTH-1:2]];
                rvalid_reg <= 1'b1;
            end
            if (rvalid_reg && axi_rready)
                rvalid_reg <= 1'b0;
        end
    end

    // ── Write Channel — accept and ignore (read-only ROM) ────
    // ROM silently ACKs writes without modifying content.
    // This prevents bus hangs if firmware accidentally writes.
    assign axi_bresp = 2'b10;  // SLVERR — ROM is read-only; write is an error

    logic aw_done, w_done, bvalid_reg;

    assign axi_awready = !aw_done && !bvalid_reg;
    assign axi_wready  = !w_done  && !bvalid_reg;
    assign axi_bvalid  = bvalid_reg;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            aw_done    <= 1'b0;
            w_done     <= 1'b0;
            bvalid_reg <= 1'b0;
        end else begin
            if (axi_awvalid && axi_awready) aw_done <= 1'b1;
            if (axi_wvalid  && axi_wready)  w_done  <= 1'b1;
            if (aw_done && w_done && !bvalid_reg)
                bvalid_reg <= 1'b1;
            if (bvalid_reg && axi_bready) begin
                bvalid_reg <= 1'b0;
                aw_done    <= 1'b0;
                w_done     <= 1'b0;
            end
        end
    end

endmodule
