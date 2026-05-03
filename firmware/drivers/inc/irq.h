#ifndef IRQ_H
#define IRQ_H

#include "common.h"

/* PicoRV32 IRQ Mapping — matches irq_aggregator.sv */
#define IRQ_TIMER     3u
#define IRQ_UART      4u
#define IRQ_GPIO      5u
#define IRQ_SPI       6u
#define IRQ_DEBUG     7u

void irq_init(void);
void irq_dispatch(uint32_t irqs);

/* Peripheral ISRs (to be implemented by app or provided by driver) */
void timer_irq_handler(void);
void uart_irq_handler(void);
void gpio_irq_handler(void);
void spi_irq_handler(void);
void debug_irq_handler(void);

extern volatile uint32_t irq_count[32];

#endif /* IRQ_H */
