module irq_aggregator (
    input  logic        clk,
    input  logic        resetn,

    input  logic        uart_irq,
    input  logic        gpio_irq,
    input  logic        timer_irq,
    input  logic        spi_irq,
    input  logic        debug_irq,

    input  logic [31:0] eoi,
    output logic [31:0] irq
);

    // PicoRV32 reserves IRQ[1] (EBREAK/illegal) and IRQ[2] (bus error),
    // so external peripheral IRQs are mapped from bit 3 onward.
    localparam int IRQ_TIMER    = 3;
    localparam int IRQ_UART     = 4;
    localparam int IRQ_GPIO     = 5;
    localparam int IRQ_SPI      = 6;
    localparam int IRQ_DEBUG    = 7;


    logic [31:0] level_irq;

    always_comb begin
        level_irq = 32'b0;
        level_irq[IRQ_TIMER]    = timer_irq;
        level_irq[IRQ_UART]     = uart_irq;
        level_irq[IRQ_GPIO]     = gpio_irq;
        level_irq[IRQ_SPI]      = spi_irq;
        level_irq[IRQ_DEBUG]    = debug_irq;
    end

    // APB Peripherals generate level-sensitive interrupts that remain high
    // until explicitly cleared by software in their respective ISRs.
    // Therefore, we pass them directly without latching.
    assign irq = level_irq;

endmodule
