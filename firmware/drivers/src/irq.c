#include "irq.h"
#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "spi.h"

volatile uint32_t irq_count[32];

static inline uint32_t picorv32_maskirq(uint32_t mask) {
    uint32_t old_mask;
    asm volatile (".insn r 0x0B, 0, 3, %0, %1, x0" : "=r"(old_mask) : "r"(mask));
    return old_mask;
}

void irq_init(void) {
    for (int i = 0; i < 32; i++) irq_count[i] = 0;
    // Unmask enabled peripherals
    picorv32_maskirq(~((1 << IRQ_TIMER) | (1 << IRQ_UART) | (1 << IRQ_GPIO) | (1 << IRQ_SPI) | (1 << IRQ_DEBUG)));
}

void irq_dispatch(uint32_t irqs) {
    if (irqs & (1 << IRQ_TIMER)) timer_irq_handler();
    if (irqs & (1 << IRQ_UART))  uart_irq_handler();
    if (irqs & (1 << IRQ_GPIO))  gpio_irq_handler();
    if (irqs & (1 << IRQ_SPI))   spi_irq_handler();
    if (irqs & (1 << IRQ_DEBUG)) debug_irq_handler();
}

/* Default Weak ISR Implementations */
__attribute__((weak)) void timer_irq_handler(void) { timer_clear_irq(); irq_count[IRQ_TIMER]++; }
__attribute__((weak)) void uart_irq_handler(void)  { irq_count[IRQ_UART]++; }
__attribute__((weak)) void gpio_irq_handler(void)  { irq_count[IRQ_GPIO]++; }
__attribute__((weak)) void spi_irq_handler(void)   { irq_count[IRQ_SPI]++; }
__attribute__((weak)) void debug_irq_handler(void) { irq_count[IRQ_DEBUG]++; }
