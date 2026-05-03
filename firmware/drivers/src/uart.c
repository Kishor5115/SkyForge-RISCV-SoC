#include "uart.h"

void uart_init(uint16_t baud_div) {
    uint32_t ctrl = (baud_div & UART_CTRL_BAUD_MASK) | UART_CTRL_TX_EN | UART_CTRL_RX_EN;
    mmio_write(UART_BASE + UART_CTRL, ctrl);
}

void uart_putc(char c) {
    if (c == '\n') uart_putc('\r');
    while (mmio_read(UART_BASE + UART_STATUS) & UART_STATUS_TX_FULL);
    mmio_write(UART_BASE + UART_TX_DATA, (uint32_t)c);
}

void uart_puts(const char *s) {
    while (*s) uart_putc(*s++);
}

char uart_getc(void) {
    while (mmio_read(UART_BASE + UART_STATUS) & UART_STATUS_RX_EMPTY);
    return (char)(mmio_read(UART_BASE + UART_RX_DATA) & 0xFF);
}
