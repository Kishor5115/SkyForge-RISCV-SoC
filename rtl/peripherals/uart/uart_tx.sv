/*
 * UART Transmitter (8N1)
 * 
 * Shifts out 1 start bit, 8 data bits (LSB first), 1 stop bit.
 * Driven by a baud_tick input from the baud rate generator.
 */

module uart_tx (
    input  logic       clk,
    input  logic       resetn,

    // Baud rate tick (1 pulse per bit period)
    input  logic       baud_tick,

    // Control
    input  logic       tx_start,     // Pulse to begin transmission
    input  logic [7:0] tx_data,      // Data byte to transmit

    // Status
    output logic       tx_busy,      // High while transmitting

    // Serial output
    output logic       tx
);

    // States
    typedef enum logic [1:0] {
        IDLE  = 2'b00,
        START = 2'b01,
        DATA  = 2'b10,
        STOP  = 2'b11
    } tx_state_t;

    tx_state_t state;
    logic [7:0] shift_reg;
    logic [2:0] bit_cnt;    // 0-7 for 8 data bits

    assign tx_busy = (state != IDLE);

    always_ff @(posedge clk) 
    begin
        if (!resetn) 
        begin
            state     <= IDLE;
            tx        <= 1'b1;  // Idle line is high
            shift_reg <= 8'h00;
            bit_cnt   <= 3'd0;
        end 
        else 
        begin
            case (state)
                IDLE: begin
                    tx <= 1'b1;
                    if (tx_start) 
                    begin
                        shift_reg <= tx_data;
                        state     <= START;
                    end
                end

                START: begin
                    if (baud_tick) 
                    begin
                        tx      <= 1'b0;  // Start bit = low
                        bit_cnt <= 3'd0;
                        state   <= DATA;
                    end
                end

                DATA: begin
                    if (baud_tick) 
                    begin
                        tx        <= shift_reg[0];  // LSB first
                        shift_reg <= {1'b0, shift_reg[7:1]};
                        if (bit_cnt == 3'd7) 
                        begin
                            state <= STOP;
                        end 
                        else 
                        begin
                            bit_cnt <= bit_cnt + 1'b1;
                        end
                    end
                end

                STOP: begin
                    if (baud_tick) 
                    begin
                        tx    <= 1'b1;  // Stop bit = high
                        state <= IDLE;
                    end
                end
            endcase
        end
    end

endmodule
