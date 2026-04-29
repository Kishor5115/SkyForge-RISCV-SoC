/*
 * SPI Master Controller with APB Interface
 *
 * Custom SPI peripheral for RISC-V SoC, inspired by SiFive FE310 SPI
 * register conventions (sckdiv, sckmode, csid, csdef, csmode, fmt) and
 * OpenTitan SPI_HOST patterns (watermarks, event/error separation, FIFO
 * depth reporting).
 *
 * Features:
 *   - Master-only SPI with configurable CPOL/CPHA (Mode 0–3)
 *   - MSB-first or LSB-first selectable
 *   - 8/16/32-bit transfer widths
 *   - 8-deep TX and RX synchronous FIFOs
 *   - Programmable clock divider: SCLK = PCLK / (2 * (CLKDIV + 1))
 *   - Up to 4 chip-select outputs, active-low, with configurable idle polarity
 *   - CS mode: AUTO (per-frame), HOLD (manual), OFF
 *   - Interrupt support: TX watermark, RX watermark, transfer complete, errors
 *   - Software reset capability
 *
 * Register Map (APB offset, 32-bit aligned):
 *   0x00 SCKDIV   — Clock divisor  [15:0] div
 *   0x04 SCKMODE  — Clock mode     [0] pha, [1] pol
 *   0x08 CSID     — Chip select ID [1:0]
 *   0x0C CSDEF    — CS default (idle) polarity [3:0]
 *   0x10 CSMODE   — CS assertion mode [1:0] (AUTO=0, HOLD=2, OFF=3)
 *   0x14 FMT      — Frame format [0] endian, [2:1] proto, [19:16] len
 *   0x18 TXDATA   — TX FIFO write port [7:0/15:0/31:0] data, [31] full flag
 *   0x1C RXDATA   — RX FIFO read port  [7:0/15:0/31:0] data, [31] empty flag
 *   0x20 TXMARK   — TX watermark threshold [2:0]
 *   0x24 RXMARK   — RX watermark threshold [2:0]
 *   0x28 IE       — Interrupt enable  [0] txwm, [1] rxwm, [2] xfer_done, [3] error
 *   0x2C IP       — Interrupt pending [0] txwm, [1] rxwm, [2] xfer_done, [3] error (W1C)
 *   0x30 STATUS   — Status register (read-only)
 *                    [3:0] txqd, [7:4] rxqd, [28] busy, [29] txfull,
 *                    [30] rxempty, [31] ready
 *   0x34 CTRL     — Control register [0] enable, [1] sw_rst
 *
 */

module spi_master_apb #(
    parameter FIFO_DEPTH  = 8,        // TX/RX FIFO depth (must be power of 2)
    parameter NUM_CS      = 4,        // Number of chip-select outputs
    parameter DEFAULT_DIV = 16'd3     // Default clock divider (SCLK = PCLK/8)
) (
    input  logic        clk,
    input  logic        resetn,

    // ── APB Slave Interface ──
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] paddr,
    input  logic [31:0] pwdata,
    input  logic [3:0]  pstrb,
    input  logic [2:0]  pprot,
    output logic [31:0] prdata,
    output logic        pready,
    output logic        pslverr,

    // ── SPI Master I/O ──
    output logic              spi_sclk,
    output logic              spi_mosi,
    input  logic              spi_miso,
    output logic [NUM_CS-1:0] spi_cs_n,

    // ── Interrupt Output ──
    output logic        irq
);

    // =========================================================================
    //  Register Address Offsets
    // =========================================================================
    localparam ADDR_SCKDIV  = 6'h00;
    localparam ADDR_SCKMODE = 6'h04;
    localparam ADDR_CSID    = 6'h08;
    localparam ADDR_CSDEF   = 6'h0C;
    localparam ADDR_CSMODE  = 6'h10;
    localparam ADDR_FMT     = 6'h14;
    localparam ADDR_TXDATA  = 6'h18;
    localparam ADDR_RXDATA  = 6'h1C;
    localparam ADDR_TXMARK  = 6'h20;
    localparam ADDR_RXMARK  = 6'h24;
    localparam ADDR_IE      = 6'h28;
    localparam ADDR_IP      = 6'h2C;
    localparam ADDR_STATUS  = 6'h30;
    localparam ADDR_CTRL    = 6'h34;

    // =========================================================================
    //  CS Mode Encoding (inspired by SiFive)
    // =========================================================================
    localparam [1:0] CS_AUTO = 2'b00;
    localparam [1:0] CS_HOLD = 2'b10;
    localparam [1:0] CS_OFF  = 2'b11;

    // =========================================================================
    //  Configuration Registers
    // =========================================================================
    logic [15:0] reg_sckdiv;
    logic        reg_cpol, reg_cpha;         // sckmode
    logic [1:0]  reg_csid;
    logic [NUM_CS-1:0] reg_csdef;
    logic [1:0]  reg_csmode;
    logic        reg_endian;                 // fmt: 0=MSB-first, 1=LSB-first
    logic [4:0]  reg_framelen;               // fmt: bits per frame (1–32)
    logic [2:0]  reg_txmark, reg_rxmark;
    logic [3:0]  reg_ie;                     // interrupt enable
    logic [3:0]  reg_ip;                     // interrupt pending (W1C)
    logic        reg_enable, reg_sw_rst;

    // =========================================================================
    //  FIFO signals
    // =========================================================================
    localparam PTR_W = $clog2(FIFO_DEPTH);

    // TX FIFO
    logic [31:0] tx_fifo [0:FIFO_DEPTH-1];
    logic [PTR_W:0] tx_wptr, tx_rptr;
    wire  [PTR_W:0] tx_count = tx_wptr - tx_rptr;
    wire  tx_full   = (tx_count == FIFO_DEPTH[PTR_W:0]);
    wire  tx_empty  = (tx_count == 0);

    // RX FIFO
    logic [31:0] rx_fifo [0:FIFO_DEPTH-1];
    logic [PTR_W:0] rx_wptr, rx_rptr;
    wire  [PTR_W:0] rx_count = rx_wptr - rx_rptr;
    wire  rx_full   = (rx_count == FIFO_DEPTH[PTR_W:0]);
    wire  rx_empty  = (rx_count == 0);

    // =========================================================================
    //  SPI Shift Engine — state machine
    // =========================================================================
    typedef enum logic [2:0] {
        SPI_IDLE,
        SPI_CS_ASSERT,
        SPI_LEADING,
        SPI_SHIFT,
        SPI_TRAILING,
        SPI_CS_DEASSERT
    } spi_state_t;

    spi_state_t  spi_state;
    logic [15:0] clk_cnt;           // Clock divider counter
    logic        clk_phase;         // Toggles every half-SCLK period
    logic [4:0]  bit_cnt;           // Current bit index
    logic [31:0] shift_out;         // TX shift register
    logic [31:0] shift_in;          // RX shift register
    logic        sclk_reg;
    logic        mosi_reg;
    logic        spi_busy;
    logic [3:0]  cs_setup_cnt;      // CS-to-SCLK setup counter
    logic [3:0]  cs_hold_cnt;       // SCLK-to-CS-deassert hold counter

    assign spi_sclk = sclk_reg;
    assign spi_mosi = mosi_reg;
    assign spi_busy = (spi_state != SPI_IDLE);

    // =========================================================================
    //  Chip Select Output Logic
    // =========================================================================
    always_comb begin
        spi_cs_n = reg_csdef;  // Default: all idle
        if (reg_csmode != CS_OFF && spi_state != SPI_IDLE) begin
            spi_cs_n[reg_csid] = ~reg_csdef[reg_csid];  // Assert (active-low)
        end
    end

    // =========================================================================
    //  APB Interface — single-cycle pready
    // =========================================================================
    assign pready  = 1'b1;
    assign pslverr = 1'b0;

    wire apb_write = psel && penable && pwrite;
    wire apb_read  = psel && penable && !pwrite;
    wire [5:0] reg_addr = paddr[5:0];

    // ─── FIFO write/read pulse from APB ───
    logic tx_push, rx_pop;

    // =========================================================================
    //  Register Write Logic
    // =========================================================================
    always_ff @(posedge clk) begin
        if (!resetn || reg_sw_rst) begin
            reg_sckdiv   <= DEFAULT_DIV;
            reg_cpol     <= 1'b0;
            reg_cpha     <= 1'b0;
            reg_csid     <= 2'b00;
            reg_csdef    <= {NUM_CS{1'b1}};  // All CS idle high
            reg_csmode   <= CS_AUTO;
            reg_endian   <= 1'b0;            // MSB-first
            reg_framelen <= 5'd8;            // 8-bit default
            reg_txmark   <= 3'd1;
            reg_rxmark   <= 3'd0;
            reg_ie       <= 4'b0000;
            reg_enable   <= 1'b0;
            reg_sw_rst   <= 1'b0;
        end else begin
            // Self-clearing SW reset
            if (reg_sw_rst)
                reg_sw_rst <= 1'b0;

            if (apb_write) begin
                case (reg_addr)
                    ADDR_SCKDIV:  reg_sckdiv   <= pwdata[15:0];
                    ADDR_SCKMODE: begin
                                      reg_cpha <= pwdata[0];
                                      reg_cpol <= pwdata[1];
                                  end
                    ADDR_CSID:    reg_csid     <= pwdata[1:0];
                    ADDR_CSDEF:   reg_csdef    <= pwdata[NUM_CS-1:0];
                    ADDR_CSMODE:  reg_csmode   <= pwdata[1:0];
                    ADDR_FMT:     begin
                                      reg_endian   <= pwdata[0];
                                      reg_framelen <= (pwdata[20:16] == 5'd0) ? 5'd8 : pwdata[20:16];
                                  end
                    ADDR_TXMARK:  reg_txmark   <= pwdata[2:0];
                    ADDR_RXMARK:  reg_rxmark   <= pwdata[2:0];
                    ADDR_IE:      reg_ie       <= pwdata[3:0];
                    ADDR_CTRL:    begin
                                      reg_enable <= pwdata[0];
                                      reg_sw_rst <= pwdata[1];
                                  end
                    default: ;
                endcase
            end
        end
    end

    // =========================================================================
    //  Interrupt Pending — W1C (write-1-to-clear) + event set
    // =========================================================================
    wire ip_txwm  = (tx_count <= {1'b0, reg_txmark});
    wire ip_rxwm  = (rx_count >= {1'b0, reg_rxmark});
    logic xfer_done_pulse;
    logic error_event;

    always_ff @(posedge clk) begin
        if (!resetn || reg_sw_rst) begin
            reg_ip <= 4'b0;
        end else begin
            // Set on event
            if (ip_txwm)           reg_ip[0] <= 1'b1;
            if (ip_rxwm)           reg_ip[1] <= 1'b1;
            if (xfer_done_pulse)   reg_ip[2] <= 1'b1;
            if (error_event)       reg_ip[3] <= 1'b1;

            // W1C: clear on write
            if (apb_write && reg_addr == ADDR_IP) begin
                reg_ip <= reg_ip & ~pwdata[3:0];
            end
        end
    end

    assign irq = |(reg_ie & reg_ip);

    // =========================================================================
    //  Register Read Logic
    // =========================================================================
    always_comb begin
        prdata = 32'h0;
        rx_pop = 1'b0;

        if (apb_read) begin
            case (reg_addr)
                ADDR_SCKDIV:  prdata = {16'b0, reg_sckdiv};
                ADDR_SCKMODE: prdata = {30'b0, reg_cpol, reg_cpha};
                ADDR_CSID:    prdata = {30'b0, reg_csid};
                ADDR_CSDEF:   prdata = {{(32-NUM_CS){1'b0}}, reg_csdef};
                ADDR_CSMODE:  prdata = {30'b0, reg_csmode};
                ADDR_FMT:     prdata = {11'b0, reg_framelen, 15'b0, reg_endian};
                ADDR_TXDATA:  prdata = {tx_full, 31'b0};  // Write-only; read returns full flag
                ADDR_RXDATA:  begin
                    if (!rx_empty) begin
                        prdata = {1'b0, rx_fifo[rx_rptr[PTR_W-1:0]][30:0]};
                        rx_pop = 1'b1;
                    end else begin
                        prdata = {1'b1, 31'b0};  // Empty flag
                    end
                end
                ADDR_TXMARK:  prdata = {29'b0, reg_txmark};
                ADDR_RXMARK:  prdata = {29'b0, reg_rxmark};
                ADDR_IE:      prdata = {28'b0, reg_ie};
                ADDR_IP:      prdata = {28'b0, reg_ip};
                ADDR_STATUS:  prdata = {
                    /* [31] ready     */ !spi_busy,
                    /* [30] rxempty   */ rx_empty,
                    /* [29] txfull    */ tx_full,
                    /* [28] busy      */ spi_busy,
                    /* [27:8] rsvd    */ 20'b0,
                    /* [7:4] rxqd     */ rx_count[3:0],
                    /* [3:0] txqd     */ tx_count[3:0]
                };
                ADDR_CTRL:    prdata = {30'b0, reg_sw_rst, reg_enable};
                default:      prdata = 32'h0;
            endcase
        end
    end

    // =========================================================================
    //  TX FIFO — Write from APB, Read from shift engine
    // =========================================================================
    logic tx_pop;
    assign tx_push = apb_write && (reg_addr == ADDR_TXDATA) && !tx_full;

    always_ff @(posedge clk) begin
        if (!resetn || reg_sw_rst) begin
            tx_wptr <= 0;
        end else if (tx_push) begin
            tx_fifo[tx_wptr[PTR_W-1:0]] <= pwdata;
            tx_wptr <= tx_wptr + 1;
        end
    end

    always_ff @(posedge clk) begin
        if (!resetn || reg_sw_rst) begin
            tx_rptr <= 0;
        end else if (tx_pop) begin
            tx_rptr <= tx_rptr + 1;
        end
    end

    // =========================================================================
    //  RX FIFO — Write from shift engine, Read from APB
    // =========================================================================
    logic rx_push;

    always_ff @(posedge clk) begin
        if (!resetn || reg_sw_rst) begin
            rx_wptr <= 0;
        end else if (rx_push && !rx_full) begin
            rx_fifo[rx_wptr[PTR_W-1:0]] <= shift_in;
            rx_wptr <= rx_wptr + 1;
        end
    end

    always_ff @(posedge clk) begin
        if (!resetn || reg_sw_rst) begin
            rx_rptr <= 0;
        end else if (rx_pop && !rx_empty) begin
            rx_rptr <= rx_rptr + 1;
        end
    end

    // Error: TX FIFO overflow attempted
    assign error_event = apb_write && (reg_addr == ADDR_TXDATA) && tx_full;

    // =========================================================================
    //  SPI Shift Engine — core transfer FSM
    // =========================================================================
    //
    //  SiFive-style state machine:
    //   IDLE → CS_ASSERT → LEADING → SHIFT (bit loop) → TRAILING → CS_DEASSERT
    //
    //  CPOL/CPHA handling:
    //   Mode 0 (CPOL=0,CPHA=0): data sampled on rising, shifted on falling
    //   Mode 1 (CPOL=0,CPHA=1): data shifted on rising, sampled on falling
    //   Mode 2 (CPOL=1,CPHA=0): data sampled on falling, shifted on rising
    //   Mode 3 (CPOL=1,CPHA=1): data shifted on falling, sampled on rising
    // =========================================================================

    assign xfer_done_pulse = (spi_state == SPI_TRAILING) && (cs_hold_cnt == 0) && clk_phase;
    assign tx_pop = (spi_state == SPI_IDLE) && !tx_empty && reg_enable;

    // Determine current output bit based on endianness
    wire [4:0] out_bit_idx = reg_endian ? bit_cnt : (reg_framelen - 1 - bit_cnt);

    always_ff @(posedge clk) begin
        if (!resetn || reg_sw_rst) begin
            spi_state    <= SPI_IDLE;
            clk_cnt      <= 16'b0;
            clk_phase    <= 1'b0;
            bit_cnt      <= 5'b0;
            shift_out    <= 32'b0;
            shift_in     <= 32'b0;
            sclk_reg     <= 1'b0;
            mosi_reg     <= 1'b0;
            cs_setup_cnt <= 4'd2;
            cs_hold_cnt  <= 4'd2;
            rx_push      <= 1'b0;
        end else begin
            rx_push <= 1'b0;  // Default: one-cycle pulse

            case (spi_state)
                // ─── IDLE: wait for data in TX FIFO ───────────────
                SPI_IDLE: begin
                    sclk_reg <= reg_cpol;  // Idle SCLK polarity
                    bit_cnt  <= 5'b0;
                    clk_cnt  <= 16'b0;
                    clk_phase <= 1'b0;
                    if (!tx_empty && reg_enable) begin
                        shift_out    <= tx_fifo[tx_rptr[PTR_W-1:0]];
                        cs_setup_cnt <= 4'd2;
                        spi_state    <= SPI_CS_ASSERT;
                    end
                end

                // ─── CS_ASSERT: assert CS, wait setup time ────────
                SPI_CS_ASSERT: begin
                    if (cs_setup_cnt == 0) begin
                        spi_state <= SPI_LEADING;
                        clk_cnt   <= 16'b0;
                    end else begin
                        cs_setup_cnt <= cs_setup_cnt - 1;
                    end
                end

                // ─── LEADING: first SCLK edge setup ───────────────
                SPI_LEADING: begin
                    // Drive MOSI for first bit before first clock edge
                    mosi_reg <= shift_out[out_bit_idx];
                    if (reg_cpha == 1'b0) begin
                        // Mode 0/2: data is valid before first edge
                        spi_state <= SPI_SHIFT;
                        clk_cnt   <= 16'b0;
                    end else begin
                        // Mode 1/3: first edge shifts data out
                        spi_state <= SPI_SHIFT;
                        clk_cnt   <= 16'b0;
                    end
                end

                // ─── SHIFT: clock data in/out ─────────────────────
                SPI_SHIFT: begin
                    if (clk_cnt >= reg_sckdiv) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;

                        if (reg_cpha == 1'b0) begin
                            // CPHA=0: sample on leading edge, shift on trailing
                            if (!clk_phase) begin
                                // Leading edge (sample)
                                sclk_reg <= ~reg_cpol;
                                shift_in[out_bit_idx] <= spi_miso;
                            end else begin
                                // Trailing edge (shift)
                                sclk_reg <= reg_cpol;
                                if (bit_cnt == reg_framelen - 1) begin
                                    // Transfer complete
                                    cs_hold_cnt <= 4'd2;
                                    spi_state   <= SPI_TRAILING;
                                end else begin
                                    bit_cnt  <= bit_cnt + 1;
                                    mosi_reg <= shift_out[reg_endian ?
                                        (bit_cnt + 1) :
                                        (reg_framelen - 2 - bit_cnt)];
                                end
                            end
                        end else begin
                            // CPHA=1: shift on leading edge, sample on trailing
                            if (!clk_phase) begin
                                // Leading edge (shift)
                                sclk_reg <= ~reg_cpol;
                                mosi_reg <= shift_out[out_bit_idx];
                            end else begin
                                // Trailing edge (sample)
                                sclk_reg <= reg_cpol;
                                shift_in[out_bit_idx] <= spi_miso;
                                if (bit_cnt == reg_framelen - 1) begin
                                    cs_hold_cnt <= 4'd2;
                                    spi_state   <= SPI_TRAILING;
                                end else begin
                                    bit_cnt <= bit_cnt + 1;
                                end
                            end
                        end
                    end else begin
                        clk_cnt <= clk_cnt + 1;
                    end
                end

                // ─── TRAILING: hold CS after last clock, push RX ──
                SPI_TRAILING: begin
                    sclk_reg <= reg_cpol;  // Return SCLK to idle
                    if (cs_hold_cnt == 0) begin
                        rx_push <= 1'b1;
                        if (reg_csmode == CS_HOLD && !tx_empty) begin
                            // Keep CS asserted, start next frame
                            shift_out <= tx_fifo[tx_rptr[PTR_W-1:0]];
                            bit_cnt   <= 5'b0;
                            clk_phase <= 1'b0;
                            spi_state <= SPI_LEADING;
                        end else begin
                            spi_state <= SPI_CS_DEASSERT;
                        end
                    end else begin
                        cs_hold_cnt <= cs_hold_cnt - 1;
                    end
                end

                // ─── CS_DEASSERT: return CS to idle ───────────────
                SPI_CS_DEASSERT: begin
                    spi_state <= SPI_IDLE;
                end

                default: spi_state <= SPI_IDLE;
            endcase
        end
    end

endmodule
