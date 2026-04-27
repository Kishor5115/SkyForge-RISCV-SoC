/*
 * UART Receiver with 16× Oversampling
 * 
 * Detects start bit via falling edge on rx, samples mid-bit using
 * 16× oversampling clock. Outputs received byte with valid pulse.
 * Detects framing errors (missing stop bit).
 */

module uart_rx (
    input  logic       clk,
    input  logic       resetn,

    // 16× baud tick (16 ticks per bit period)
    input  logic       baud_tick_16x,

    // Control
    input  logic       rx_enable,

    // Received data
    output logic [7:0] rx_data,
    output logic       rx_valid,       // Pulse when byte received
    output logic       frame_error,    // Pulse on framing error

    // Serial input
    input  logic       rx
);

    // States
    typedef enum logic [1:0] {
        IDLE    = 2'b00,
        START   = 2'b01,
        DATA    = 2'b10,
        STOP    = 2'b11
    } rx_state_t;

    rx_state_t state;
    logic [7:0] shift_reg;
    logic [2:0] bit_cnt;
    logic [3:0] sample_cnt;    // 0-15 for 16× oversampling

    //? Double-flop synchronizer for metastability
    logic rx_sync_0, rx_sync_1;

    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            rx_sync_0 <= 1'b1;
            rx_sync_1 <= 1'b1;
        end 
        else 
        begin
            rx_sync_0 <= rx;
            rx_sync_1 <= rx_sync_0;
        end
    end

    wire rx_in = rx_sync_1;

    // Main FSM
    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            state       <= IDLE;
            shift_reg   <= 8'h00;
            bit_cnt     <= 3'd0;
            sample_cnt  <= 4'd0;
            rx_data     <= 8'h00;
            rx_valid    <= 1'b0;
            frame_error <= 1'b0;
        end 
        else 
        begin
            // Default: deassert pulses
            rx_valid    <= 1'b0;
            frame_error <= 1'b0;

            case (state)
                IDLE: begin
                    if (rx_enable && !rx_in) 
                    begin
                        // Falling edge detected — potential start bit
                        state      <= START;
                        sample_cnt <= 4'd0;
                    end
                end

                START: begin
                    if (baud_tick_16x) 
                    begin
                        if (sample_cnt == 4'd7) 
                        begin
                            // Mid-point of start bit — verify it's still low
                            if (!rx_in) 
                            begin
                                // Valid start bit
                                state      <= DATA;
                                sample_cnt <= 4'd0;
                                bit_cnt    <= 3'd0;
                            end 
                            else 
                            begin
                                // False start — return to idle
                                state <= IDLE;
                            end
                        end 
                        else 
                        begin
                            sample_cnt <= sample_cnt + 1'b1;
                        end
                    end
                end

                DATA: begin
                    if (baud_tick_16x) begin
                        if (sample_cnt == 4'd15) begin
                            // Mid-point of data bit — sample
                            shift_reg  <= {rx_in, shift_reg[7:1]}; // LSB first
                            sample_cnt <= 4'd0;
                            if (bit_cnt == 3'd7) begin
                                state <= STOP;
                            end else begin
                                bit_cnt <= bit_cnt + 1'b1;
                            end
                        end else begin
                            sample_cnt <= sample_cnt + 1'b1;
                        end
                    end
                end

                STOP: begin
                    if (baud_tick_16x) begin
                        if (sample_cnt == 4'd15) begin
                            // Mid-point of stop bit — check for valid stop
                            if (rx_in) begin
                                // Valid stop bit
                                rx_data  <= shift_reg;
                                rx_valid <= 1'b1;
                            end else begin
                                // Missing stop bit — frame error
                                frame_error <= 1'b1;
                            end
                            state <= IDLE;
                        end else begin
                            sample_cnt <= sample_cnt + 1'b1;
                        end
                    end
                end
            endcase
        end
    end

endmodule
