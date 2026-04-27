/*
 * UART Controller with APB Slave Interface
 *
 * This is the APB version of the UART controller. The internal UART logic is
 * (baud generator, FIFOs, TX/RX cores)
 *
 * APB Protocol:
 *   Phase 1 (SETUP):  PSEL=1, PENABLE=0  → address/data/write are sampled
 *   Phase 2 (ACCESS): PSEL=1, PENABLE=1  → peripheral executes, asserts PREADY
 *   No-transfer:      PSEL=0             → bus is idle
 *
 * Register Map (offset from base address 0x2000_0000):
 *   0x00 TX_DATA   [W]     Write byte to TX FIFO (bits [7:0])
 *   0x04 RX_DATA   [R]     Read byte from RX FIFO (bits [7:0])
 *   0x08 STATUS    [R]     Status flags
 *                          [0] tx_empty  - TX FIFO empty
 *                          [1] tx_full   - TX FIFO full
 *                          [2] rx_empty  - RX FIFO empty
 *                          [3] rx_full   - RX FIFO full
 *                          [4] rx_overrun - RX overrun error (sticky)
 *                          [5] frame_err  - Frame error (sticky)
 *                          [6] tx_busy   - TX shift register busy
 *   0x0C CTRL      [R/W]   Control register
 *                          [15:0]  baud_div  - Baud divisor (clk/(baud*16))
 *                          [16]    tx_en     - TX enable
 *                          [17]    rx_en     - RX enable
 *                          [18]    irq_en    - Interrupt enable (RX data available)
 *
 * Default baud divisor: 54 (115200 baud @ 100 MHz, 16x oversampling)
 */

module uart_ctrl_apb #(
    parameter DEFAULT_BAUD_DIV = 16'd54
) (
    input  logic        clk,
    input  logic        resetn,

    // APB Slave Interface
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] paddr,
    input  logic [31:0] pwdata,
    input  logic [3:0]  pstrb,
    input  logic [2:0]  pprot,     // APB4: Protection type (unused)
    output logic [31:0] prdata,
    output logic        pready,
    output logic        pslverr,

    // UART I/O
    output logic        uart_tx,
    input  logic        uart_rx,

    // Interrupt
    output logic        irq
);

    //==========================================================================
    //? Register addresses (offsets) - use bits [3:0] of address
    //==========================================================================
    localparam ADDR_TX_DATA = 4'h0;
    localparam ADDR_RX_DATA = 4'h4;
    localparam ADDR_STATUS  = 4'h8;
    localparam ADDR_CTRL    = 4'hC;

    //==========================================================================
    // Internal signals
    //==========================================================================

    // Control register fields
    logic [15:0] baud_div;
    logic        tx_en, rx_en, irq_en;

    // Status (sticky errors)
    logic        rx_overrun;
    logic        frame_err_sticky;
    logic        wr_ctrl_pulse;

    // Baud rate generator
    logic [15:0] baud_counter;
    logic        baud_tick;
    logic        baud_tick_16x;
    logic [3:0]  baud_sub_cnt;

    // TX FIFO
    logic        tx_fifo_wr_en;
    logic [7:0]  tx_fifo_wr_data;
    logic        tx_fifo_rd_en;
    logic [7:0]  tx_fifo_rd_data;
    logic        tx_fifo_empty;
    logic        tx_fifo_full;

    // RX FIFO
    logic        rx_fifo_wr_en;
    logic [7:0]  rx_fifo_wr_data;
    logic        rx_fifo_rd_en;
    logic [7:0]  rx_fifo_rd_data;
    logic        rx_fifo_empty;
    logic        rx_fifo_full;

    // TX core
    logic        tx_start;
    logic [7:0]  tx_data_out;
    logic        tx_busy;

    // RX core
    logic [7:0]  rx_data_in;
    logic        rx_valid;
    logic        frame_error;

    //==========================================================================
    // TODO : Baud Rate Generator 
    //==========================================================================
    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            baud_counter  <= '0;
            baud_tick_16x <= 1'b0;
            baud_sub_cnt  <= 4'd0;
            baud_tick     <= 1'b0;
        end 
        else 
        begin
            baud_tick_16x <= 1'b0;
            baud_tick     <= 1'b0;

            if (baud_counter >= baud_div - 1'b1) 
            begin
                baud_counter  <= '0;
                baud_tick_16x <= 1'b1;
                if (baud_sub_cnt == 4'd15) 
                begin
                    baud_sub_cnt <= 4'd0;
                    baud_tick    <= 1'b1;
                end 
                else 
                begin
                    baud_sub_cnt <= baud_sub_cnt + 1'b1;
                end
            end 
            else 
            begin
                baud_counter <= baud_counter + 1'b1;
            end
        end
    end

    //==========================================================================
    // Sub-module Instantiations 
    //==========================================================================

    uart_fifo #(  .DATA_WIDTH(8),  .DEPTH(8) ) 
    u_tx_fifo 
    (
        .clk(clk), 
        .resetn(resetn),
        .wr_en(tx_fifo_wr_en), 
        .wr_data(tx_fifo_wr_data),
        .rd_en(tx_fifo_rd_en), 
        .rd_data(tx_fifo_rd_data),
        .empty(tx_fifo_empty), 
        .full(tx_fifo_full), 
        .count()
    );

    uart_fifo #(  .DATA_WIDTH(8),  .DEPTH(8) ) 
    u_rx_fifo 
    (
        .clk(clk), 
        .resetn(resetn),
        .wr_en(rx_fifo_wr_en), 
        .wr_data(rx_fifo_wr_data),
        .rd_en(rx_fifo_rd_en), 
        .rd_data(rx_fifo_rd_data),
        .empty(rx_fifo_empty), 
        .full(rx_fifo_full), 
        .count()
    );

    uart_tx u_tx 
    (
        .clk(clk), 
        .resetn(resetn),
        .baud_tick(baud_tick),
        .tx_start(tx_start), 
        .tx_data(tx_data_out),
        .tx_busy(tx_busy), 
        .tx(uart_tx)
    );

    uart_rx u_rx 
    (
        .clk(clk), 
        .resetn(resetn),
        .baud_tick_16x(baud_tick_16x), 
        .rx_enable(rx_en),
        .rx_data(rx_data_in), 
        .rx_valid(rx_valid),
        .frame_error(frame_error), 
        .rx(uart_rx)
    );

    //==========================================================================
    // TODO --> TX: Drain FIFO → shift register 
    //==========================================================================
    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            tx_start    <= 1'b0;
            tx_data_out <= 8'h00;
        end 
        else 
        begin
            tx_start <= 1'b0;
            if (tx_en && !tx_fifo_empty && !tx_busy && !tx_start) 
            begin
                tx_data_out <= tx_fifo_rd_data;
                tx_start    <= 1'b1;
            end
        end
    end

    assign tx_fifo_rd_en = tx_en && !tx_fifo_empty && !tx_busy && !tx_start;

    //==========================================================================
    // TODO --> RX: Shift register → FIFO
    //==========================================================================
    assign rx_fifo_wr_en   = rx_valid && !rx_fifo_full;
    assign rx_fifo_wr_data = rx_data_in;

    // Sticky error flags
    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            rx_overrun       <= 1'b0;
            frame_err_sticky <= 1'b0;
        end 
        else 
        begin
            if (rx_valid && rx_fifo_full)
                rx_overrun <= 1'b1;
            if (frame_error)
                frame_err_sticky <= 1'b1;
            if (wr_ctrl_pulse) 
            begin
                rx_overrun       <= 1'b0;
                frame_err_sticky <= 1'b0;
            end
        end
    end

    //==========================================================================
    // Interrupt logic
    //==========================================================================
    assign irq = irq_en && !rx_fifo_empty;

    //==========================================================================
    // APB Slave Interface
    //
    // APB is much simpler than AXI! The protocol is:
    //   1. PSEL asserted, PENABLE=0  → SETUP phase (we latch address/data)
    //   2. PSEL asserted, PENABLE=1  → ACCESS phase (we execute and assert PREADY)
    //
    // For simple register access, PREADY is always 1 (no wait states).
    //==========================================================================

    //* We always respond in 1 cycle (no wait states for this peripheral)
    assign pready  = 1'b1;
    assign pslverr = 1'b0;  // No error conditions

    // APB Write: execute on ACCESS phase of a write transaction
    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            tx_fifo_wr_en   <= 1'b0;
            tx_fifo_wr_data <= 8'h0;
            baud_div        <= DEFAULT_BAUD_DIV;
            tx_en           <= 1'b1;
            rx_en           <= 1'b1;
            irq_en          <= 1'b0;
            wr_ctrl_pulse   <= 1'b0;
        end 
        else 
        begin
            tx_fifo_wr_en <= 1'b0;
            wr_ctrl_pulse <= 1'b0;

            // APB write: PSEL=1, PENABLE=1, PWRITE=1
            if (psel && penable && pwrite) 
            begin
                case (paddr[3:0])
                    ADDR_TX_DATA: begin
                        if (!tx_fifo_full) 
                        begin
                            tx_fifo_wr_en   <= 1'b1;
                            tx_fifo_wr_data <= pwdata[7:0];
                        end
                    end
                    ADDR_CTRL: begin
                        baud_div      <= pwdata[15:0];
                        tx_en         <= pwdata[16];
                        rx_en         <= pwdata[17];
                        irq_en        <= pwdata[18];
                        wr_ctrl_pulse <= 1'b1;
                    end
                    default: ; // Ignore writes to read-only registers
                endcase
            end
        end
    end

    // APB Read: drive PRDATA based on address
    // RX FIFO pop on read of RX_DATA
    assign rx_fifo_rd_en = psel && penable && !pwrite &&
                           (paddr[3:0] == ADDR_RX_DATA) && !rx_fifo_empty;

    always_comb 
    begin
        prdata = 32'h0;

        // APB read: PSEL=1, PENABLE=0 or 1 (we can drive data at SETUP)
        // But conventionally read data is valid during ACCESS phase
        if (psel)
        begin
            case (paddr[3:0])
                ADDR_TX_DATA: prdata = 32'h0;
                ADDR_RX_DATA: prdata = {24'h0, rx_fifo_rd_data};
                ADDR_STATUS:  prdata = {25'h0,
                                        tx_busy,
                                        frame_err_sticky,
                                        rx_overrun,
                                        rx_fifo_full,
                                        rx_fifo_empty,
                                        tx_fifo_full,
                                        tx_fifo_empty};
                ADDR_CTRL:    prdata = {13'h0,
                                        irq_en,
                                        rx_en,
                                        tx_en,
                                        baud_div};
                default:      prdata = 32'h0;
            endcase
        end
    end

endmodule
