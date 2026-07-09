/*
 * SRAM AXI Wrapper — ASIC-Ready (OpenRAM / Behavioral)
 *
 * 16KB SRAM with AXI4-Lite slave interface.   (v2: was 32KB/8 banks)
 *   8KB = 2048 words × 32 bits, ADDR_WIDTH = 13
 *
 * Simulation : behavioral register-file model (1-cycle read latency)
 * Synthesis  : 4× sky130_sram_4kbyte_1rw_32x1024_8 OpenRAM macros = 16KB
 *              with 2-bit bank select from addr[11:10]
 */
module sram_axi #(
    parameter ADDR_WIDTH = 13,          // 8KB = 2^13 bytes (v2; was 14 = 16KB)
    parameter DATA_WIDTH = 32,
    parameter SRAM_INIT_FILE = ""       // Optional hex file for simulation preload
)(
    input  logic                  clk,
    input  logic                  resetn,

    // AXI4-Lite Write Address
    input  logic [ADDR_WIDTH-1:0] axi_awaddr,
    input  logic [2:0]            axi_awprot,
    input  logic                  axi_awvalid,
    output logic                  axi_awready,

    // AXI4-Lite Write Data
    input  logic [DATA_WIDTH-1:0] axi_wdata,
    input  logic                  axi_wvalid,
    output logic                  axi_wready,
    input  logic [3:0]            axi_wstrb,

    // AXI4-Lite Write Response
    output logic                  axi_bvalid,
    input  logic                  axi_bready,
    output logic [1:0]            axi_bresp,

    // AXI4-Lite Read Address
    input  logic [ADDR_WIDTH-1:0] axi_araddr,
    input  logic [2:0]            axi_arprot,
    input  logic                  axi_arvalid,
    output logic                  axi_arready,

    // AXI4-Lite Read Data
    output logic [DATA_WIDTH-1:0] axi_rdata,
    output logic                  axi_rvalid,
    input  logic                  axi_rready,
    output logic [1:0]            axi_rresp
);

    assign axi_bresp = 2'b00;
    assign axi_rresp = 2'b00;

    localparam WORD_AW   = ADDR_WIDTH - 2;   // 11 bits for 2048 words (v2)
    localparam NUM_WORDS = 2 ** WORD_AW;
    localparam BANK_AW   = 10;               // 1024 words per 4KB bank
    localparam NUM_BANKS = NUM_WORDS / (2 ** BANK_AW);  // 2 banks for 8KB (v2)
    localparam BANK_SEL_AW = WORD_AW - BANK_AW;         // bank-select width

    // ── SRAM port signals ───────────────────────────────────────
    logic                  sram_csb0;
    logic                  sram_web0;
    logic [3:0]            sram_wmask0;
    logic [WORD_AW-1:0]   sram_addr0;
    logic [DATA_WIDTH-1:0] sram_din0;
    logic [DATA_WIDTH-1:0] sram_dout0;

`ifdef SYNTHESIS
    // ── 4× 4KB OpenRAM banks ────────────────────────────────────
    logic [BANK_SEL_AW-1:0] bank_sel_rd_d;
    logic [DATA_WIDTH-1:0] bank_dout [0:NUM_BANKS-1];

    always_ff @(posedge clk)
        if (!sram_csb0 && sram_web0)
            bank_sel_rd_d <= sram_addr0[WORD_AW-1:BANK_AW];

    assign sram_dout0 = bank_dout[bank_sel_rd_d];

    genvar gi;
    generate
        for (gi = 0; gi < NUM_BANKS; gi++) begin : gen_sram_bank
            logic bank_csb0;
            logic [BANK_AW:0] bank_addr0;
            logic [DATA_WIDTH:0] bank_din0;
            logic [DATA_WIDTH:0] bank_dout0;

            assign bank_csb0 = sram_csb0 | (sram_addr0[WORD_AW-1:BANK_AW] != gi[BANK_SEL_AW-1:0]);
            assign bank_addr0 = {1'b0, sram_addr0[BANK_AW-1:0]};
            assign bank_din0 = {1'b0, sram_din0};
            assign bank_dout[gi] = bank_dout0[DATA_WIDTH-1:0];

            sky130_sram_4kbyte_1rw_32x1024_8 u_bank (
                .clk0   (clk),
                .csb0   (bank_csb0),
                .web0   (sram_web0),
                .wmask0 (sram_wmask0),
                .spare_wen0 (1'b0),
                .addr0  (bank_addr0),
                .din0   (bank_din0),
                .dout0  (bank_dout0)
            );
        end
    endgenerate
`else
    // ── Behavioral SRAM — 1-cycle read latency ──────────────────
    logic [DATA_WIDTH-1:0] mem [0:NUM_WORDS-1];

    always_ff @(posedge clk) begin
        if (!sram_csb0) begin
            if (!sram_web0) begin
                if (sram_wmask0[0]) mem[sram_addr0][ 7: 0] <= sram_din0[ 7: 0];
                if (sram_wmask0[1]) mem[sram_addr0][15: 8] <= sram_din0[15: 8];
                if (sram_wmask0[2]) mem[sram_addr0][23:16] <= sram_din0[23:16];
                if (sram_wmask0[3]) mem[sram_addr0][31:24] <= sram_din0[31:24];
            end
            sram_dout0 <= mem[sram_addr0];
        end
    end

    initial begin
        for (int i = 0; i < NUM_WORDS; i++) mem[i] = 32'h0;
`ifndef SYNTHESIS
        if (SRAM_INIT_FILE != "")
            $readmemh(SRAM_INIT_FILE, mem);
`endif
    end
`endif

    // ── AXI Write FSM ───────────────────────────────────────────
    logic        aw_captured, w_captured, bvalid_r, wr_pending;
    logic [WORD_AW-1:0] aw_addr_r;
    logic [DATA_WIDTH-1:0] w_data_r;
    logic [3:0]  w_strb_r;

    assign axi_awready = !aw_captured && !bvalid_r;
    assign axi_wready  = !w_captured  && !bvalid_r;
    assign axi_bvalid  = bvalid_r;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            aw_captured <= 0; w_captured <= 0; bvalid_r <= 0; wr_pending <= 0;
        end else begin
            if (axi_awvalid && axi_awready) begin
                aw_addr_r <= axi_awaddr[ADDR_WIDTH-1:2]; aw_captured <= 1;
            end
            if (axi_wvalid && axi_wready) begin
                w_data_r <= axi_wdata; w_strb_r <= axi_wstrb; w_captured <= 1;
            end
            if (aw_captured && w_captured && !bvalid_r && !wr_pending)
                wr_pending <= 1;
            if (wr_pending) begin wr_pending <= 0; bvalid_r <= 1; end
            if (bvalid_r && axi_bready) begin
                bvalid_r <= 0; aw_captured <= 0; w_captured <= 0;
            end
        end
    end

    // ── AXI Read FSM ────────────────────────────────────────────
    typedef enum logic [1:0] { RD_IDLE, RD_SRAM, RD_RESP } rd_state_t;
    rd_state_t rd_state;
    logic [DATA_WIDTH-1:0] rdata_r;

    assign axi_arready = (rd_state == RD_IDLE) && !wr_pending && !(aw_captured && w_captured);
    assign axi_rvalid  = (rd_state == RD_RESP);
    assign axi_rdata   = rdata_r;

    always_ff @(posedge clk) begin
        if (!resetn) begin rd_state <= RD_IDLE; rdata_r <= '0; end
        else case (rd_state)
            RD_IDLE: if (axi_arvalid && axi_arready) rd_state <= RD_SRAM;
            RD_SRAM: begin rdata_r <= sram_dout0; rd_state <= RD_RESP; end
            RD_RESP: if (axi_rready) rd_state <= RD_IDLE;
            default: rd_state <= RD_IDLE;
        endcase
    end

    // ── SRAM port mux ───────────────────────────────────────────
    wire rd_access = (rd_state == RD_IDLE) && axi_arvalid && axi_arready;

    always_comb begin
        if (aw_captured && w_captured && !bvalid_r && !wr_pending) begin
            sram_csb0 = 0; sram_web0 = 0; sram_wmask0 = w_strb_r;
            sram_addr0 = aw_addr_r; sram_din0 = w_data_r;
        end else if (rd_access) begin
            sram_csb0 = 0; sram_web0 = 1; sram_wmask0 = 4'b0;
            sram_addr0 = axi_araddr[ADDR_WIDTH-1:2]; sram_din0 = '0;
        end else begin
            sram_csb0 = 1; sram_web0 = 1; sram_wmask0 = 4'b0;
            sram_addr0 = '0; sram_din0 = '0;
        end
    end

endmodule
