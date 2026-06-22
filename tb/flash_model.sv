/*
 * flash_model — Behavioral External QSPI Flash (simulation only)  [v2]
 *
 * Models the OFF-CHIP serial flash that the SoC's flash_ctrl talks to over
 * QSPI single-bit SPI (mode-0-like). NOT part of the SoC RTL — testbench use.
 *
 * Supported commands:
 *   0x9F  Read JEDEC ID  -> returns {MFR, MEMTYPE, CAP} = JEDEC_ID (3 bytes)
 *   0x03  Read Data      -> 24-bit address (MSB first), then streams bytes
 *                           mem[addr], mem[addr+1], ... until CS# deasserts
 *
 * Protocol timing (matches rtl/peripherals/flash/flash_ctrl.sv):
 *   - Master drives MOSI on the rising edge of SCLK; this model samples MOSI
 *     on posedge SCLK.
 *   - Master samples MISO on the falling edge of SCLK; this model presents the
 *     next MISO bit on posedge SCLK so it is stable through the high phase.
 *   - CS# high resets the transaction bit/byte counters.
 *
 * Memory is byte-addressed. INIT_FILE (if set) is loaded via $readmemh at
 * byte offset LOAD_OFFSET (the flash image's byte 0 maps to flash offset
 * 0x10000 for the XIP window 0x40010000).
 */

module flash_model #(
    parameter int    MEM_BYTES   = 1 << 20,        // 1 MB model (enough for sim)
    parameter [23:0] JEDEC_ID    = 24'hEF4018,     // Winbond W25Q128-like
    parameter        INIT_FILE   = "",
    parameter int    LOAD_OFFSET = 24'h010000      // where INIT_FILE byte 0 lands
) (
    input  logic sclk,
    input  logic cs_n,
    input  logic mosi,
    output logic miso
);

    logic [7:0] mem [0:MEM_BYTES-1];

    integer k;
    initial begin
        for (k = 0; k < MEM_BYTES; k = k + 1) mem[k] = 8'h00;
        if (INIT_FILE != "")
            $readmemh(INIT_FILE, mem, LOAD_OFFSET);
    end

    // ── Transaction state ─────────────────────────────────────
    localparam ST_CMD  = 2'd0;
    localparam ST_ADDR = 2'd1;
    localparam ST_DATA = 2'd2;
    localparam ST_JEDEC= 2'd3;

    logic [1:0]  state;
    logic [7:0]  cmd;
    logic [23:0] addr;
    logic [4:0]  bit_cnt;     // bits collected in current field
    logic [7:0]  out_sr;      // output shift register (MISO)
    logic [1:0]  jedec_idx;   // which JEDEC byte
    logic        miso_r;
    logic [7:0]  in_sr;

    assign miso = miso_r;

    // Reset on CS# deassert
    always_ff @(posedge cs_n) begin
        state   <= ST_CMD;
        bit_cnt <= 5'd0;
        cmd     <= 8'd0;
        addr    <= 24'd0;
        miso_r  <= 1'b0;
    end

    // Sample MOSI / advance on rising edge; present MISO for the high phase
    always_ff @(posedge sclk) begin
        if (!cs_n) begin
            case (state)
                // ── Command byte ──────────────────────────────
                ST_CMD: begin
                    in_sr   <= {in_sr[6:0], mosi};
                    bit_cnt <= bit_cnt + 1'b1;
                    if (bit_cnt == 5'd7) begin
                        cmd     <= {in_sr[6:0], mosi};
                        bit_cnt <= 5'd0;
                        if ({in_sr[6:0], mosi} == 8'h9F) begin
                            state     <= ST_JEDEC;
                            jedec_idx <= 2'd0;
                            out_sr    <= JEDEC_ID[23:16];   // first JEDEC byte (presented in ST_JEDEC)
                        end else begin
                            state <= ST_ADDR;               // assume read (0x03)
                        end
                    end
                end

                // ── 24-bit address ────────────────────────────
                ST_ADDR: begin
                    addr    <= {addr[22:0], mosi};
                    bit_cnt <= bit_cnt + 1'b1;
                    if (bit_cnt == 5'd23) begin
                        bit_cnt <= 5'd0;
                        state   <= ST_DATA;
                        // Load first data byte; ST_DATA presents its MSB next pulse
                        out_sr  <= mem[{addr[22:0], mosi}];
                        addr    <= {addr[22:0], mosi} + 24'd1;
                    end
                end

                // ── Stream data bytes (present MSB, then shift) ─
                ST_DATA: begin
                    miso_r  <= out_sr[7];
                    bit_cnt <= bit_cnt + 1'b1;
                    if (bit_cnt == 5'd7) begin
                        bit_cnt <= 5'd0;
                        out_sr  <= mem[addr];        // next byte
                        addr    <= addr + 24'd1;
                    end else begin
                        out_sr <= {out_sr[6:0], 1'b0};
                    end
                end

                // ── JEDEC ID (3 bytes; present MSB, then shift) ─
                ST_JEDEC: begin
                    miso_r  <= out_sr[7];
                    bit_cnt <= bit_cnt + 1'b1;
                    if (bit_cnt == 5'd7) begin
                        bit_cnt   <= 5'd0;
                        jedec_idx <= jedec_idx + 1'b1;
                        case (jedec_idx)
                            2'd0: out_sr <= JEDEC_ID[15:8];
                            2'd1: out_sr <= JEDEC_ID[7:0];
                            default: out_sr <= 8'h00;
                        endcase
                    end else begin
                        out_sr <= {out_sr[6:0], 1'b0};
                    end
                end

                default: state <= ST_CMD;
            endcase
        end
    end

endmodule
