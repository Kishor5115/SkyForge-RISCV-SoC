/*
 * icache_512b — 512 B Direct-Mapped Instruction/Read Cache for Flash XIP  (v2)
 *
 * Sits between the CPU read path and the external QSPI flash XIP read port.
 * Flash XIP fetches are ~50-100+ SPI cycles each; this cache returns a hit
 * in a single cycle and amortises misses over a full 8-word (32-byte) line.
 *
 * Design configuration (as instantiated in flash_xip.sv):
 *   NUM_LINES  = 16   (direct-mapped)  — PPA/congestion trade vs the original 32
 *   LINE_WORDS = 8    (32 bytes per line)   -> 16 * 32 B = 512 B
 *   Storage is flip-flop based (NO OpenRAM macro), so it hardens as std cells.
 *
 * PPA rationale: at 100 MHz the cache hit-latency is not on any critical path.
 *   32 lines (1 KB) = 8192 FFs — dominant area, dynamic power, and GRT congestion
 *   source (req_foff[2:4] fanout 1k-3.4k). 16 lines (512 B) = 4096 FFs, ~half
 *   the store, clears routing congestion, same 8-word burst fill efficiency.
 *   See docs/SOC_TOP_WARNING_RESOLUTION.md for the full analysis.
 *
 * Address model (flash offset = low 24 bits of the AXI address):
 *   foff[ 1:0]  byte offset within word (ignored — word reads)
 *   foff[ 4:2]  word index within line   (3 bits  -> 8 words)
 *   foff[ 8:5]  line index               (4 bits  -> 16 lines)
 *   foff[23:9]  tag                       (15 bits)
 *
 * Interfaces (AXI4-Lite, read-only):
 *   s_axi_*  — SLAVE  : read requests from the flash-XIP wrapper (CPU side)
 *   m_axi_*  — MASTER : single-beat read requests to flash_ctrl.xip port
 *
 * On a miss the cache issues LINE_WORDS sequential single-word reads to the
 * flash XIP port (flash CMD_READ 0x03), fills the line, then returns the
 * requested word. Writes are not handled here (the wrapper routes them).
 */

module icache_512b #(
    parameter int NUM_LINES  = 32,
    parameter int LINE_WORDS = 8
) (
    input  logic        clk,
    input  logic        resetn,

    // ── Slave (CPU side) read address ─────────────────────────
    input  logic        s_axi_arvalid,
    output logic        s_axi_arready,
    input  logic [31:0] s_axi_araddr,
    input  logic [ 2:0] s_axi_arprot,

    // ── Slave (CPU side) read data ────────────────────────────
    output logic        s_axi_rvalid,
    input  logic        s_axi_rready,
    output logic [31:0] s_axi_rdata,
    output logic [ 1:0] s_axi_rresp,

    // ── Master (flash XIP port) read address ──────────────────
    output logic        m_axi_arvalid,
    input  logic        m_axi_arready,
    output logic [31:0] m_axi_araddr,

    // ── Master (flash XIP port) read data ─────────────────────
    input  logic        m_axi_rvalid,
    output logic        m_axi_rready,
    input  logic [31:0] m_axi_rdata,
    input  logic [ 1:0] m_axi_rresp
);

    // ── Derived geometry ──────────────────────────────────────
    localparam int WORD_BITS = $clog2(LINE_WORDS);          // 3
    localparam int IDX_BITS  = $clog2(NUM_LINES);           // 5
    localparam int TAG_LSB   = 2 + WORD_BITS + IDX_BITS;    // 10
    localparam int TAG_BITS  = 24 - TAG_LSB;                // 14 (flash offset = 24b)

    // ── Storage (flip-flop based) ─────────────────────────────
    logic                 valid_arr [0:NUM_LINES-1];
    logic [TAG_BITS-1:0]  tag_arr   [0:NUM_LINES-1];
    logic [31:0]          data_arr  [0:NUM_LINES-1][0:LINE_WORDS-1];

    // ── Latched request fields ────────────────────────────────
    logic [23:0]          req_foff;
    wire  [WORD_BITS-1:0] req_word = req_foff[2 +: WORD_BITS];
    wire  [IDX_BITS-1:0]  req_idx  = req_foff[TAG_LSB-1 -: IDX_BITS];
    wire  [TAG_BITS-1:0]  req_tag  = req_foff[23 -: TAG_BITS];

    wire hit = valid_arr[req_idx] && (tag_arr[req_idx] == req_tag);

    // ── FSM ────────────────────────────────────────────────────
    typedef enum logic [2:0] {
        C_IDLE,      // accept a read request
        C_CHECK,     // hit/miss decision
        C_FILL_REQ,  // drive flash read address
        C_FILL_RX,   // capture flash read data
        C_RESP       // return word to CPU
    } cstate_t;

    cstate_t                cstate;
    logic [WORD_BITS-1:0]   fill_cnt;
    logic [31:0]            resp_data;

    assign s_axi_arready = (cstate == C_IDLE);
    assign s_axi_rvalid  = (cstate == C_RESP);
    assign s_axi_rdata   = resp_data;
    assign s_axi_rresp   = 2'b00;

    // Flash master: line-aligned word address = {tag, idx, fill_cnt, 2'b00}
    assign m_axi_arvalid = (cstate == C_FILL_REQ);
    assign m_axi_araddr  = {8'h00, req_tag, req_idx, fill_cnt, 2'b00};
    assign m_axi_rready  = (cstate == C_FILL_RX);

    integer i, j;
    always_ff @(posedge clk) begin
        if (!resetn) begin
            cstate    <= C_IDLE;
            fill_cnt  <= '0;
            req_foff  <= '0;
            resp_data <= '0;
            for (i = 0; i < NUM_LINES; i = i + 1)
                valid_arr[i] <= 1'b0;
        end else begin
            case (cstate)
                C_IDLE: begin
                    if (s_axi_arvalid) begin
                        req_foff <= s_axi_araddr[23:0];
                        cstate   <= C_CHECK;
                    end
                end

                C_CHECK: begin
                    if (hit) begin
                        resp_data <= data_arr[req_idx][req_word];
                        cstate    <= C_RESP;
                    end else begin
                        fill_cnt <= '0;
                        cstate   <= C_FILL_REQ;
                    end
                end

                C_FILL_REQ: begin
                    if (m_axi_arvalid && m_axi_arready)
                        cstate <= C_FILL_RX;
                end

                C_FILL_RX: begin
                    if (m_axi_rvalid) begin
                        data_arr[req_idx][fill_cnt] <= m_axi_rdata;
                        if (fill_cnt == req_word)
                            resp_data <= m_axi_rdata;
                        if (fill_cnt == LINE_WORDS-1) begin
                            valid_arr[req_idx] <= 1'b1;
                            tag_arr[req_idx]   <= req_tag;
                            cstate             <= C_RESP;
                        end else begin
                            fill_cnt <= fill_cnt + 1'b1;
                            cstate   <= C_FILL_REQ;
                        end
                    end
                end

                C_RESP: begin
                    if (s_axi_rready)
                        cstate <= C_IDLE;
                end

                default: cstate <= C_IDLE;
            endcase
        end
    end

endmodule
