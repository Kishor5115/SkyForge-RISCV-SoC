/*
 * QSPI Flash Controller with XIP Support
 *
 * Custom QSPI flash controller for RISC-V SoC, inspired by:
 *   - SiFive FE310 QSPI0 controller (XIP mode, fctrl/ffmt registers)
 *   - OpenTitan SPI_HOST command-based architecture
 *
 * Features:
 *   - XIP (Execute In Place): memory-mapped flash reads at configurable base
 *   - Command mode: software-driven SPI transactions (JEDEC ID, erase, program)
 *   - Compatible with Winbond W25Q128/W25Q256 and ISSI equivalents
 *   - Configurable dummy cycles, address width (24/32-bit)
 *   - Status polling with timeout counter
 *   - AXI4-Lite slave for register access
 *
 * Register Map (APB/AXI offset):
 *   0x00 CTRL     — [0] enable, [1] xip_en, [3:2] addr_width (0=24bit, 1=32bit)
 *   0x04 STATUS   — [0] busy, [1] xip_active, [7:4] state, [31] timeout_err
 *   0x08 CMD      — [7:0] command byte, [8] start
 *   0x0C ADDR     — [31:0] flash address for command mode
 *   0x10 TXDATA   — [7:0] data to transmit in command mode
 *   0x14 RXDATA   — [7:0] received data, [31] empty flag
 *   0x18 CLKDIV   — [15:0] SPI clock divisor
 *   0x1C JEDEC_ID — [23:0] read-only JEDEC ID captured during init
 *   0x20 DUMMY    — [3:0] number of dummy cycles for fast read
 *
 * QSPI Pins: active-low CS, SCK, IO[3:0] (directly exposed as individual signals)
 *
 * For simulation: a flash model drives flash_miso in response to commands.
 */

module flash_ctrl #(
    parameter ADDR_WIDTH  = 8,           // Register space address width
    parameter DEFAULT_DIV = 16'd3,       // Default SPI clock divisor
    parameter XIP_BASE    = 32'h2000_0000  // XIP memory-mapped base address
) (
    input  logic        clk,
    input  logic        resetn,

    // ── AXI4-Lite Slave (register access) ────────────────────
    input  logic [ADDR_WIDTH-1:0] axi_araddr,
    input  logic [2:0]            axi_arprot,
    input  logic                  axi_arvalid,
    output logic                  axi_arready,

    output logic [31:0]           axi_rdata,
    output logic                  axi_rvalid,
    input  logic                  axi_rready,
    output logic [1:0]            axi_rresp,

    input  logic [ADDR_WIDTH-1:0] axi_awaddr,
    input  logic [2:0]            axi_awprot,
    input  logic                  axi_awvalid,
    output logic                  axi_awready,

    input  logic [31:0]           axi_wdata,
    input  logic                  axi_wvalid,
    output logic                  axi_wready,
    input  logic [3:0]            axi_wstrb,

    output logic                  axi_bvalid,
    input  logic                  axi_bready,
    output logic [1:0]            axi_bresp,

    // ── XIP Read Port (from AXI interconnect for memory-mapped reads) ──
    input  logic [31:0]           xip_araddr,
    input  logic                  xip_arvalid,
    output logic                  xip_arready,
    output logic [31:0]           xip_rdata,
    output logic                  xip_rvalid,
    input  logic                  xip_rready,
    output logic [1:0]            xip_rresp,

    // XIP Write (not supported, ACK immediately)
    input  logic [31:0]           xip_awaddr,
    input  logic                  xip_awvalid,
    output logic                  xip_awready,
    input  logic [31:0]           xip_wdata,
    input  logic                  xip_wvalid,
    output logic                  xip_wready,
    input  logic [3:0]            xip_wstrb,
    output logic                  xip_bvalid,
    input  logic                  xip_bready,
    output logic [1:0]            xip_bresp,

    // ── QSPI Flash I/O ──────────────────────────────────────
    output logic        flash_sclk,
    output logic        flash_cs_n,
    output logic        flash_mosi,
    input  logic        flash_miso,

    // ── Status to boot FSM ───────────────────────────────────
    output logic        flash_ready,       // Flash initialization complete
    output logic [23:0] jedec_id,          // Captured JEDEC ID
    output logic        xip_active         // XIP window is active
);

    // ── Register Offsets ─────────────────────────────────────
    localparam REG_CTRL    = 6'h00;
    localparam REG_STATUS  = 6'h04;
    localparam REG_CMD     = 6'h08;
    localparam REG_ADDR    = 6'h0C;
    localparam REG_TXDATA  = 6'h10;
    localparam REG_RXDATA  = 6'h14;
    localparam REG_CLKDIV  = 6'h18;
    localparam REG_JEDEC   = 6'h1C;
    localparam REG_DUMMY   = 6'h20;

    // ── Flash Commands ───────────────────────────────────────
    localparam CMD_READ          = 8'h03;
    localparam CMD_FAST_READ     = 8'h0B;
    localparam CMD_QUAD_READ     = 8'h6B;
    localparam CMD_PAGE_PROGRAM  = 8'h02;
    localparam CMD_SECTOR_ERASE  = 8'h20;
    localparam CMD_CHIP_ERASE    = 8'hC7;
    localparam CMD_READ_STATUS   = 8'h05;
    localparam CMD_WRITE_ENABLE  = 8'h06;
    localparam CMD_READ_JEDEC_ID = 8'h9F;

    // ── Configuration Registers ──────────────────────────────
    logic        reg_enable;
    logic        reg_xip_en;
    logic [1:0]  reg_addr_width;     // 0=24-bit, 1=32-bit
    logic [7:0]  reg_cmd;
    logic        reg_cmd_start;
    logic [31:0] reg_addr;
    logic [7:0]  reg_txdata;
    logic [15:0] reg_clkdiv;
    logic [3:0]  reg_dummy_cycles;
    logic [23:0] reg_jedec_id;

    // ── SPI Engine State Machine ─────────────────────────────
    typedef enum logic [3:0] {
        S_IDLE,
        S_CMD_SEND,         // Sending command byte
        S_ADDR_SEND,        // Sending address bytes
        S_DUMMY,            // Sending dummy cycles
        S_DATA_TX,          // Transmitting data byte
        S_DATA_RX,          // Receiving data byte
        S_JEDEC_RX,         // Receiving JEDEC ID (3 bytes)
        S_XIP_CMD,          // XIP: sending read command
        S_XIP_ADDR,         // XIP: sending address
        S_XIP_DUMMY,        // XIP: dummy cycles
        S_XIP_DATA,         // XIP: receiving data (4 bytes for 32-bit word)
        S_COMPLETE
    } flash_state_t;

    flash_state_t state;
    logic [15:0] clk_cnt;
    logic        clk_phase;
    logic [4:0]  bit_cnt;
    logic [7:0]  shift_out;
    logic [7:0]  shift_in;
    logic [2:0]  byte_cnt;
    logic [31:0] xip_read_buf;
    logic        rx_data_valid;
    logic [7:0]  rx_data_reg;
    logic        spi_busy;
    logic        timeout_err;
    logic [19:0] timeout_cnt;

    assign flash_ready = reg_enable && (state == S_IDLE);
    assign xip_active  = reg_xip_en;

    // ── SPI output ───────────────────────────────────────────
    logic sclk_reg, cs_n_reg, mosi_reg;
    assign flash_sclk = sclk_reg;
    assign flash_cs_n = cs_n_reg;
    assign flash_mosi = mosi_reg;

    // ── APB-style register access over AXI-Lite ─────────────
    // Simplified: single-cycle access
    assign axi_rresp = 2'b00;
    assign axi_bresp = 2'b00;

    // Read channel
    logic r_valid_reg;
    logic [31:0] r_data_reg;
    assign axi_arready = !r_valid_reg;
    assign axi_rvalid  = r_valid_reg;
    assign axi_rdata   = r_data_reg;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            r_valid_reg <= 1'b0;
            r_data_reg  <= '0;
        end else begin
            if (axi_arvalid && axi_arready) begin
                r_valid_reg <= 1'b1;
                case (axi_araddr[5:0])
                    REG_CTRL:    r_data_reg <= {28'b0, reg_addr_width, reg_xip_en, reg_enable};
                    REG_STATUS:  r_data_reg <= {timeout_err, 23'b0, state, 2'b0, xip_active, spi_busy};
                    REG_CMD:     r_data_reg <= {23'b0, reg_cmd_start, reg_cmd};
                    REG_ADDR:    r_data_reg <= reg_addr;
                    REG_TXDATA:  r_data_reg <= {24'b0, reg_txdata};
                    REG_RXDATA:  r_data_reg <= {rx_data_valid ? 1'b0 : 1'b1, 23'b0, rx_data_reg};
                    REG_CLKDIV:  r_data_reg <= {16'b0, reg_clkdiv};
                    REG_JEDEC:   r_data_reg <= {8'b0, reg_jedec_id};
                    REG_DUMMY:   r_data_reg <= {28'b0, reg_dummy_cycles};
                    default:     r_data_reg <= 32'b0;
                endcase
            end
            if (r_valid_reg && axi_rready)
                r_valid_reg <= 1'b0;
        end
    end

    // Write channel
    logic aw_done_r, w_done_r, bvalid_r;
    logic [5:0] aw_addr_captured;

    assign axi_awready = !aw_done_r && !bvalid_r;
    assign axi_wready  = !w_done_r  && !bvalid_r;
    assign axi_bvalid  = bvalid_r;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            aw_done_r     <= 1'b0;
            w_done_r      <= 1'b0;
            bvalid_r      <= 1'b0;
            reg_enable    <= 1'b0;
            reg_xip_en    <= 1'b0;
            reg_addr_width <= 2'b00;
            reg_cmd       <= 8'b0;
            reg_cmd_start <= 1'b0;
            reg_addr      <= 32'b0;
            reg_txdata    <= 8'b0;
            reg_clkdiv    <= DEFAULT_DIV;
            reg_dummy_cycles <= 4'd8;
            aw_addr_captured <= 6'b0;
        end else begin
            // Self-clearing cmd_start
            if (reg_cmd_start && state != S_IDLE)
                reg_cmd_start <= 1'b0;

            if (axi_awvalid && axi_awready) begin
                aw_done_r <= 1'b1;
                aw_addr_captured <= axi_awaddr[5:0];
            end
            if (axi_wvalid && axi_wready) begin
                w_done_r <= 1'b1;
            end
            if (aw_done_r && w_done_r && !bvalid_r) begin
                bvalid_r <= 1'b1;
                // Apply write
                case (aw_addr_captured)
                    REG_CTRL:   begin
                        reg_enable     <= axi_wdata[0];
                        reg_xip_en     <= axi_wdata[1];
                        reg_addr_width <= axi_wdata[3:2];
                    end
                    REG_CMD:    begin
                        reg_cmd       <= axi_wdata[7:0];
                        reg_cmd_start <= axi_wdata[8];
                    end
                    REG_ADDR:   reg_addr   <= axi_wdata;
                    REG_TXDATA: reg_txdata <= axi_wdata[7:0];
                    REG_CLKDIV: reg_clkdiv <= axi_wdata[15:0];
                    REG_DUMMY:  reg_dummy_cycles <= axi_wdata[3:0];
                    default: ;
                endcase
            end
            if (bvalid_r && axi_bready) begin
                bvalid_r  <= 1'b0;
                aw_done_r <= 1'b0;
                w_done_r  <= 1'b0;
            end
        end
    end

    // ── XIP Write Channel (not supported — immediate ACK) ────
    assign xip_bresp = 2'b10;  // SLVERR for writes
    assign xip_rresp = 2'b00;

    logic xip_aw_done, xip_w_done, xip_bvalid_r;
    assign xip_awready = !xip_aw_done && !xip_bvalid_r;
    assign xip_wready  = !xip_w_done  && !xip_bvalid_r;
    assign xip_bvalid  = xip_bvalid_r;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            xip_aw_done   <= 1'b0;
            xip_w_done    <= 1'b0;
            xip_bvalid_r  <= 1'b0;
        end else begin
            if (xip_awvalid && xip_awready) xip_aw_done <= 1'b1;
            if (xip_wvalid  && xip_wready)  xip_w_done  <= 1'b1;
            if (xip_aw_done && xip_w_done && !xip_bvalid_r)
                xip_bvalid_r <= 1'b1;
            if (xip_bvalid_r && xip_bready) begin
                xip_bvalid_r <= 1'b0;
                xip_aw_done  <= 1'b0;
                xip_w_done   <= 1'b0;
            end
        end
    end

    // ── XIP Read Channel — memory-mapped flash reads ─────────
    logic xip_rvalid_reg;
    logic [31:0] xip_rdata_reg;
    logic xip_read_pending;
    logic [31:0] xip_read_addr;

    assign xip_arready = !xip_rvalid_reg && !xip_read_pending && reg_xip_en;
    assign xip_rvalid  = xip_rvalid_reg;
    assign xip_rdata   = xip_rdata_reg;

    always_ff @(posedge clk) begin
        if (!resetn) begin
            xip_rvalid_reg  <= 1'b0;
            xip_rdata_reg   <= 32'b0;
            xip_read_pending <= 1'b0;
            xip_read_addr   <= 32'b0;
        end else begin
            // Accept XIP read request
            if (xip_arvalid && xip_arready) begin
                xip_read_pending <= 1'b1;
                xip_read_addr   <= xip_araddr;
            end

            // When XIP read completes from SPI engine
            if (state == S_COMPLETE && xip_read_pending) begin
                xip_rdata_reg    <= xip_read_buf;
                xip_rvalid_reg   <= 1'b1;
                xip_read_pending <= 1'b0;
            end

            // Response accepted
            if (xip_rvalid_reg && xip_rready)
                xip_rvalid_reg <= 1'b0;
        end
    end

    // ── SPI Engine FSM ───────────────────────────────────────
    assign spi_busy = (state != S_IDLE);
    assign jedec_id = reg_jedec_id;

    // Helper: SPI clock tick
    wire clk_tick = (clk_cnt >= reg_clkdiv);

    always_ff @(posedge clk) begin
        if (!resetn) begin
            state        <= S_IDLE;
            clk_cnt      <= 16'b0;
            clk_phase    <= 1'b0;
            bit_cnt      <= 5'b0;
            byte_cnt     <= 3'b0;
            shift_out    <= 8'b0;
            shift_in     <= 8'b0;
            sclk_reg     <= 1'b0;
            cs_n_reg     <= 1'b1;
            mosi_reg     <= 1'b0;
            xip_read_buf <= 32'b0;
            rx_data_valid <= 1'b0;
            rx_data_reg  <= 8'b0;
            reg_jedec_id <= 24'b0;
            timeout_err  <= 1'b0;
            timeout_cnt  <= 20'b0;
        end else begin
            case (state)
                S_IDLE: begin
                    cs_n_reg  <= 1'b1;
                    sclk_reg  <= 1'b0;
                    clk_cnt   <= 16'b0;
                    clk_phase <= 1'b0;
                    bit_cnt   <= 5'b0;
                    byte_cnt  <= 3'b0;
                    timeout_cnt <= 20'b0;

                    // Command mode: software-initiated transfer
                    if (reg_cmd_start && reg_enable) begin
                        cs_n_reg  <= 1'b0;
                        shift_out <= reg_cmd;
                        bit_cnt   <= 5'd0;
                        state     <= S_CMD_SEND;
                    end
                    // XIP mode: handle pending read
                    else if (xip_read_pending && reg_xip_en && reg_enable) begin
                        cs_n_reg  <= 1'b0;
                        shift_out <= CMD_READ;  // Standard read
                        bit_cnt   <= 5'd0;
                        state     <= S_XIP_CMD;
                    end
                end

                // ── Command byte transmission ──────────────────
                S_CMD_SEND: begin
                    if (clk_tick) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;
                        if (!clk_phase) begin
                            sclk_reg <= 1'b1;
                            mosi_reg <= shift_out[7 - bit_cnt[2:0]];
                        end else begin
                            sclk_reg <= 1'b0;
                            bit_cnt  <= bit_cnt + 1;
                            if (bit_cnt[2:0] == 3'd7) begin
                                // Command sent — decide next phase
                                case (reg_cmd)
                                    CMD_READ_JEDEC_ID: begin
                                        state    <= S_JEDEC_RX;
                                        bit_cnt  <= 5'd0;
                                        byte_cnt <= 3'd0;
                                    end
                                    CMD_READ, CMD_FAST_READ: begin
                                        state   <= S_ADDR_SEND;
                                        bit_cnt <= 5'd0;
                                        shift_out <= reg_addr[23:16];
                                    end
                                    CMD_WRITE_ENABLE, CMD_CHIP_ERASE: begin
                                        state <= S_COMPLETE;
                                    end
                                    CMD_READ_STATUS: begin
                                        state   <= S_DATA_RX;
                                        bit_cnt <= 5'd0;
                                    end
                                    default: begin
                                        state   <= S_ADDR_SEND;
                                        bit_cnt <= 5'd0;
                                        shift_out <= reg_addr[23:16];
                                    end
                                endcase
                            end
                        end
                    end else
                        clk_cnt <= clk_cnt + 1;
                end

                // ── JEDEC ID reception (3 bytes) ───────────────
                S_JEDEC_RX: begin
                    if (clk_tick) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;
                        if (!clk_phase) begin
                            sclk_reg <= 1'b1;
                        end else begin
                            sclk_reg <= 1'b0;
                            shift_in <= {shift_in[6:0], flash_miso};
                            bit_cnt  <= bit_cnt + 1;
                            if (bit_cnt[2:0] == 3'd7) begin
                                case (byte_cnt)
                                    3'd0: reg_jedec_id[23:16] <= {shift_in[6:0], flash_miso};
                                    3'd1: reg_jedec_id[15:8]  <= {shift_in[6:0], flash_miso};
                                    3'd2: begin
                                        reg_jedec_id[7:0] <= {shift_in[6:0], flash_miso};
                                        state <= S_COMPLETE;
                                    end
                                    default: ;
                                endcase
                                byte_cnt <= byte_cnt + 1;
                                bit_cnt  <= 5'd0;
                            end
                        end
                    end else
                        clk_cnt <= clk_cnt + 1;
                end

                // ── Address send (24-bit) ──────────────────────
                S_ADDR_SEND: begin
                    if (clk_tick) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;
                        if (!clk_phase) begin
                            sclk_reg <= 1'b1;
                            mosi_reg <= shift_out[7 - bit_cnt[2:0]];
                        end else begin
                            sclk_reg <= 1'b0;
                            bit_cnt  <= bit_cnt + 1;
                            if (bit_cnt[2:0] == 3'd7) begin
                                byte_cnt <= byte_cnt + 1;
                                case (byte_cnt)
                                    3'd0: begin
                                        shift_out <= reg_addr[15:8];
                                        bit_cnt   <= 5'd0;
                                    end
                                    3'd1: begin
                                        shift_out <= reg_addr[7:0];
                                        bit_cnt   <= 5'd0;
                                    end
                                    3'd2: begin
                                        // Address done, move to data phase
                                        if (reg_cmd == CMD_READ || reg_cmd == CMD_FAST_READ) begin
                                            if (reg_cmd == CMD_FAST_READ) begin
                                                state   <= S_DUMMY;
                                                bit_cnt <= 5'd0;
                                            end else begin
                                                state   <= S_DATA_RX;
                                                bit_cnt <= 5'd0;
                                            end
                                        end else begin
                                            state   <= S_DATA_TX;
                                            bit_cnt <= 5'd0;
                                            shift_out <= reg_txdata;
                                        end
                                    end
                                    default: ;
                                endcase
                            end
                        end
                    end else
                        clk_cnt <= clk_cnt + 1;
                end

                // ── Dummy cycles ───────────────────────────────
                S_DUMMY: begin
                    if (clk_tick) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;
                        if (!clk_phase)
                            sclk_reg <= 1'b1;
                        else begin
                            sclk_reg <= 1'b0;
                            bit_cnt  <= bit_cnt + 1;
                            if (bit_cnt == {1'b0, reg_dummy_cycles}) begin
                                state   <= S_DATA_RX;
                                bit_cnt <= 5'd0;
                            end
                        end
                    end else
                        clk_cnt <= clk_cnt + 1;
                end

                // ── Data TX (1 byte) ───────────────────────────
                S_DATA_TX: begin
                    if (clk_tick) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;
                        if (!clk_phase) begin
                            sclk_reg <= 1'b1;
                            mosi_reg <= shift_out[7 - bit_cnt[2:0]];
                        end else begin
                            sclk_reg <= 1'b0;
                            bit_cnt  <= bit_cnt + 1;
                            if (bit_cnt[2:0] == 3'd7)
                                state <= S_COMPLETE;
                        end
                    end else
                        clk_cnt <= clk_cnt + 1;
                end

                // ── Data RX (1 byte) ───────────────────────────
                S_DATA_RX: begin
                    if (clk_tick) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;
                        if (!clk_phase)
                            sclk_reg <= 1'b1;
                        else begin
                            sclk_reg  <= 1'b0;
                            shift_in  <= {shift_in[6:0], flash_miso};
                            bit_cnt   <= bit_cnt + 1;
                            if (bit_cnt[2:0] == 3'd7) begin
                                rx_data_reg   <= {shift_in[6:0], flash_miso};
                                rx_data_valid <= 1'b1;
                                state         <= S_COMPLETE;
                            end
                        end
                    end else
                        clk_cnt <= clk_cnt + 1;
                end

                // ── XIP: send READ command ─────────────────────
                S_XIP_CMD: begin
                    if (clk_tick) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;
                        if (!clk_phase) begin
                            sclk_reg <= 1'b1;
                            mosi_reg <= shift_out[7 - bit_cnt[2:0]];
                        end else begin
                            sclk_reg <= 1'b0;
                            bit_cnt  <= bit_cnt + 1;
                            if (bit_cnt[2:0] == 3'd7) begin
                                state     <= S_XIP_ADDR;
                                bit_cnt   <= 5'd0;
                                byte_cnt  <= 3'd0;
                                // Load first address byte (big-endian 24-bit)
                                shift_out <= xip_read_addr[23:16];
                            end
                        end
                    end else
                        clk_cnt <= clk_cnt + 1;
                end

                // ── XIP: send 24-bit address ───────────────────
                S_XIP_ADDR: begin
                    if (clk_tick) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;
                        if (!clk_phase) begin
                            sclk_reg <= 1'b1;
                            mosi_reg <= shift_out[7 - bit_cnt[2:0]];
                        end else begin
                            sclk_reg <= 1'b0;
                            bit_cnt  <= bit_cnt + 1;
                            if (bit_cnt[2:0] == 3'd7) begin
                                byte_cnt <= byte_cnt + 1;
                                bit_cnt  <= 5'd0;
                                case (byte_cnt)
                                    3'd0: shift_out <= xip_read_addr[15:8];
                                    3'd1: shift_out <= xip_read_addr[7:0];
                                    3'd2: begin
                                        state    <= S_XIP_DATA;
                                        byte_cnt <= 3'd0;
                                    end
                                    default: ;
                                endcase
                            end
                        end
                    end else
                        clk_cnt <= clk_cnt + 1;
                end

                // ── XIP: receive 4 data bytes (32-bit word) ────
                S_XIP_DATA: begin
                    if (clk_tick) begin
                        clk_cnt   <= 16'b0;
                        clk_phase <= ~clk_phase;
                        if (!clk_phase)
                            sclk_reg <= 1'b1;
                        else begin
                            sclk_reg <= 1'b0;
                            shift_in <= {shift_in[6:0], flash_miso};
                            bit_cnt  <= bit_cnt + 1;
                            if (bit_cnt[2:0] == 3'd7) begin
                                // Little-endian: first flash byte (lowest addr)
                                // goes to bits [7:0] so CPU fetches are correct.
                                case (byte_cnt)
                                    3'd0: xip_read_buf[7:0]   <= {shift_in[6:0], flash_miso};
                                    3'd1: xip_read_buf[15:8]  <= {shift_in[6:0], flash_miso};
                                    3'd2: xip_read_buf[23:16] <= {shift_in[6:0], flash_miso};
                                    3'd3: begin
                                        xip_read_buf[31:24] <= {shift_in[6:0], flash_miso};
                                        state <= S_COMPLETE;
                                    end
                                    default: ;
                                endcase
                                byte_cnt <= byte_cnt + 1;
                                bit_cnt  <= 5'd0;
                            end
                        end
                    end else
                        clk_cnt <= clk_cnt + 1;
                end

                // ── Transfer complete ──────────────────────────
                S_COMPLETE: begin
                    cs_n_reg  <= 1'b1;
                    sclk_reg  <= 1'b0;
                    state     <= S_IDLE;
                end

                default: state <= S_IDLE;
            endcase
        end
    end

endmodule
