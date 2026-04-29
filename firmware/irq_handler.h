#ifndef IRQ_HANDLER_H
#define IRQ_HANDLER_H

/* PicoRV32 IRQ Mapping — matches irq_aggregator.sv
 *   IRQ 0-2: reserved (EBREAK, bus error, timer)
 *   IRQ 3:   Timer peripheral
 *   IRQ 4:   UART
 *   IRQ 5:   GPIO
 *   IRQ 6:   SPI Master
 *   IRQ 7:   JTAG Debug mailbox
 */
#define IRQ_TIMER     3u
#define IRQ_UART      4u
#define IRQ_GPIO      5u
#define IRQ_SPI       6u
#define IRQ_DEBUG     7u

void irq_init(void);
void irq_dispatch(unsigned int irqs);

void timer_irq_handler(void);
void uart_irq_handler(void);
void gpio_irq_handler(void);
void spi_irq_handler(void);
void debug_irq_handler(void);

#endif
