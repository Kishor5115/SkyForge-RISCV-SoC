#ifndef UART_H
#define UART_H

#include "common.h"

/* UART Register Offsets */
#define UART_TX_DATA   0x00u
#define UART_RX_DATA   0x04u
#define UART_STATUS    0x08u
#define UART_CTRL      0x0Cu

/* UART Status Register Bits */
#define UART_STATUS_TX_FULL  (1u << 1)
#define UART_STATUS_RX_EMPTY (1u << 2)

/* UART Control Register Bits */
#define UART_CTRL_BAUD_MASK  0x0000FFFFu
#define UART_CTRL_TX_EN      (1u << 16)
#define UART_CTRL_RX_EN      (1u << 17)

/* Driver Functions */
void uart_init(uint16_t baud_div);
void uart_putc(char c);
void uart_puts(const char *s);
char uart_getc(void);

#endif /* UART_H */
