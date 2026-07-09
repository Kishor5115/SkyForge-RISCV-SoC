/*
 * APB Interconnect / Address Decoder
 *
 * Routes APB transactions from the AXI-to-APB bridge to the correct
 * peripheral based on address decoding.
 *
 * This module acts as a 1-to-N APB decoder/mux:
 *   - Receives PSEL from the bridge
 *   - Decodes PADDR to select the right peripheral
 *   - Drives individual PSELx signals to each peripheral
 *   - Muxes PRDATA and PREADY back to the bridge
 *
 * Address Map (within APB region 0x20000000 - 0x2000FFFF):
 *   Peripheral 0 (UART):      0x20000000 - 0x20000FFF  (4KB)
 *   Peripheral 1 (Timer):     0x20001000 - 0x20001FFF  (4KB)
 *   Peripheral 2 (GPIO):      0x20002000 - 0x20002FFF  (4KB)
 *   Peripheral 3 (SPI):       0x20003000 - 0x20003FFF  (4KB)
 *   Peripheral 4 (Debug):     0x20004000 - 0x20004FFF  (4KB)
 */

module apb_interconnect (
    input  logic        clk,
    input  logic        resetn,

    // Interface from AXI-to-APB Bridge
    input  logic        psel_i,
    input  logic        penable_i,
    input  logic        pwrite_i,
    input  logic [31:0] paddr_i,
    input  logic [31:0] pwdata_i,
    input  logic [3:0]  pstrb_i,
    input  logic [2:0]  pprot_i,       // APB4: Protection type
    output logic [31:0] prdata_o,
    output logic        pready_o,
    output logic        pslverr_o,

    // Interface to UART
    output logic        psel_uart,
    output logic        penable_uart,
    output logic        pwrite_uart,
    output logic [31:0] paddr_uart,
    output logic [31:0] pwdata_uart,
    output logic [3:0]  pstrb_uart,
    output logic [2:0]  pprot_uart,
    input  logic [31:0] prdata_uart,
    input  logic        pready_uart,
    input  logic        pslverr_uart,

    // Interface to Timer
    output logic        psel_timer,
    output logic        penable_timer,
    output logic        pwrite_timer,
    output logic [31:0] paddr_timer,
    output logic [31:0] pwdata_timer,
    output logic [3:0]  pstrb_timer,
    output logic [2:0]  pprot_timer,
    input  logic [31:0] prdata_timer,
    input  logic        pready_timer,
    input  logic        pslverr_timer,

    // Interface to GPIO
    output logic        psel_gpio,
    output logic        penable_gpio,
    output logic        pwrite_gpio,
    output logic [31:0] paddr_gpio,
    output logic [31:0] pwdata_gpio,
    output logic [3:0]  pstrb_gpio,
    output logic [2:0]  pprot_gpio,
    input  logic [31:0] prdata_gpio,
    input  logic        pready_gpio,
    input  logic        pslverr_gpio,

    // Interface to SPI
    output logic        psel_spi,
    output logic        penable_spi,
    output logic        pwrite_spi,
    output logic [31:0] paddr_spi,
    output logic [31:0] pwdata_spi,
    output logic [3:0]  pstrb_spi,
    output logic [2:0]  pprot_spi,
    input  logic [31:0] prdata_spi,
    input  logic        pready_spi,
    input  logic        pslverr_spi,

    // Interface to Debug
    output logic        psel_debug,
    output logic        penable_debug,
    output logic        pwrite_debug,
    output logic [31:0] paddr_debug,
    output logic [31:0] pwdata_debug,
    output logic [3:0]  pstrb_debug,
    output logic [2:0]  pprot_debug,
    input  logic [31:0] prdata_debug,
    input  logic        pready_debug,
    input  logic        pslverr_debug
);

    // Address Decoding
    // UART : 0x2000_0000 - 0x2000_0FFF
    // Timer: 0x2000_1000 - 0x2000_1FFF
    // GPIO : 0x2000_2000 - 0x2000_2FFF
    // SPI  : 0x2000_3000 - 0x2000_3FFF
    // DEBUG: 0x2000_4000 - 0x2000_4FFF

    typedef enum logic [2:0] {
        SEL_UART  = 3'b000,
        SEL_TIMER = 3'b001,
        SEL_GPIO  = 3'b010,
        SEL_SPI   = 3'b011,
        SEL_DEBUG = 3'b100,
        SEL_NONE  = 3'b111
    } slave_sel_t;

    slave_sel_t slave_sel;

    always_comb begin
        if (paddr_i >= 32'h2000_0000 && paddr_i <= 32'h2000_0FFF)
            slave_sel = SEL_UART;
        else if (paddr_i >= 32'h2000_1000 && paddr_i <= 32'h2000_1FFF)
            slave_sel = SEL_TIMER;
        else if (paddr_i >= 32'h2000_2000 && paddr_i <= 32'h2000_2FFF)
            slave_sel = SEL_GPIO;
        else if (paddr_i >= 32'h2000_3000 && paddr_i <= 32'h2000_3FFF)
            slave_sel = SEL_SPI;
        else if (paddr_i >= 32'h2000_4000 && paddr_i <= 32'h2000_4FFF)
            slave_sel = SEL_DEBUG;
        else
            slave_sel = SEL_NONE;
    end

    // Direct signals to all slaves (broadcast)
    assign penable_uart  = penable_i;
    assign pwrite_uart   = pwrite_i;
    assign paddr_uart    = paddr_i;
    assign pwdata_uart   = pwdata_i;
    assign pstrb_uart    = pstrb_i;
    assign pprot_uart    = pprot_i;

    assign penable_timer = penable_i;
    assign pwrite_timer  = pwrite_i;
    assign paddr_timer   = paddr_i;
    assign pwdata_timer  = pwdata_i;
    assign pstrb_timer   = pstrb_i;
    assign pprot_timer   = pprot_i;

    assign penable_gpio  = penable_i;
    assign pwrite_gpio   = pwrite_i;
    assign paddr_gpio    = paddr_i;
    assign pwdata_gpio   = pwdata_i;
    assign pstrb_gpio    = pstrb_i;
    assign pprot_gpio    = pprot_i;

    assign penable_spi   = penable_i;
    assign pwrite_spi    = pwrite_i;
    assign paddr_spi     = paddr_i;
    assign pwdata_spi    = pwdata_i;
    assign pstrb_spi     = pstrb_i;
    assign pprot_spi     = pprot_i;

    assign penable_debug = penable_i;
    assign pwrite_debug  = pwrite_i;
    assign paddr_debug   = paddr_i;
    assign pwdata_debug  = pwdata_i;
    assign pstrb_debug   = pstrb_i;
    assign pprot_debug   = pprot_i;

    // Peripheral Selection (PSEL mux)
    always_comb begin
        psel_uart  = 1'b0;
        psel_timer = 1'b0;
        psel_gpio  = 1'b0;
        psel_spi   = 1'b0;
        psel_debug = 1'b0;
        
        if (psel_i) begin
            case (slave_sel)
                SEL_UART : psel_uart  = 1'b1;
                SEL_TIMER: psel_timer = 1'b1;
                SEL_GPIO : psel_gpio  = 1'b1;
                SEL_SPI  : psel_spi   = 1'b1;
                SEL_DEBUG: psel_debug = 1'b1;
                default: ; // Decode error handled by bridge or default pready
            endcase
        end
    end

    // Response Multiplexing
    always_comb begin
        case (slave_sel)
            SEL_UART : begin
                prdata_o  = prdata_uart;
                pready_o  = pready_uart;
                pslverr_o = pslverr_uart;
            end
            SEL_TIMER: begin
                prdata_o  = prdata_timer;
                pready_o  = pready_timer;
                pslverr_o = pslverr_timer;
            end
            SEL_GPIO : begin
                prdata_o  = prdata_gpio;
                pready_o  = pready_gpio;
                pslverr_o = pslverr_gpio;
            end
            SEL_SPI  : begin
                prdata_o  = prdata_spi;
                pready_o  = pready_spi;
                pslverr_o = pslverr_spi;
            end
            SEL_DEBUG: begin
                prdata_o  = prdata_debug;
                pready_o  = pready_debug;
                pslverr_o = pslverr_debug;
            end
            default: begin
                prdata_o  = 32'h0;
                pready_o  = 1'b1; // Don't hang the bus on invalid addr
                pslverr_o = 1'b1; // Signal error
            end
        endcase
    end

endmodule
