#include <stdint.h>

#include "irq.h"

volatile int btn_left_flag = 0;
volatile int btn_right_flag = 0;
volatile int btn_center_flag = 0;

#define UART_BASE   0x20000000u
#define TIMER_BASE  0x20001000u
#define GPIO_BASE   0x20002000u
#define SPI_BASE    0x20003000u
#define DEBUG_BASE  0x20004000u

#define UART_TX_DATA   0x00u
#define UART_RX_DATA   0x04u
#define UART_STATUS    0x08u
#define UART_CTRL      0x0Cu

#define UART_STATUS_TX_FULL  (1u << 1)

#define UART_CTRL_BAUD_MASK  0x0000FFFFu
#define UART_CTRL_TX_EN      (1u << 16)
#define UART_CTRL_RX_EN      (1u << 17)
#define UART_CTRL_IRQ_EN     (1u << 18)

#define TIMER_LOAD     0x00u
#define TIMER_CTRL     0x08u
#define TIMER_INTCLR   0x0Cu

#define TIMER_CTRL_ONE_SHOT  (1u << 0)
#define TIMER_CTRL_32BIT     (1u << 1)
#define TIMER_CTRL_INT_EN    (1u << 5)
#define TIMER_CTRL_ENABLE    (1u << 7)

#define GPIO_OUTPUT_EN  0x08u
#define GPIO_OUTPUT_VAL 0x0Cu

#define SPI_SCKDIV  0x00u
#define SPI_SCKMODE 0x04u
#define SPI_CSID    0x08u
#define SPI_CSDEF   0x0Cu
#define SPI_CSMODE  0x10u
#define SPI_FMT     0x14u
#define SPI_TXDATA  0x18u
#define SPI_RXDATA  0x1Cu
#define SPI_IE      0x28u
#define SPI_IP      0x2Cu
#define SPI_STATUS  0x30u
#define SPI_CTRL    0x34u

#define DEBUG_CMD        0x08u
#define DEBUG_ADDR       0x0Cu
#define DEBUG_WDATA      0x10u
#define DEBUG_RDATA      0x14u
#define DEBUG_GO         0x18u
#define DEBUG_IRQ_EN     0x20u

static inline void mmio_write(uint32_t addr, uint32_t value)
{
    *(volatile uint32_t *)addr = value;
}

static inline uint32_t mmio_read(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}

static void uart_init(uint16_t baud_div)
{
    uint32_t ctrl = (baud_div & UART_CTRL_BAUD_MASK) |
                    UART_CTRL_TX_EN | UART_CTRL_RX_EN | UART_CTRL_IRQ_EN;
    mmio_write(UART_BASE + UART_CTRL, ctrl);
}

static void uart_putc(char c)
{
    if (c == '\n') {
        uart_putc('\r');
    }

    while (mmio_read(UART_BASE + UART_STATUS) & UART_STATUS_TX_FULL) {
        ;
    }

    mmio_write(UART_BASE + UART_TX_DATA, (uint32_t)c);
}

static void uart_puts(const char *s)
{
    while (*s) {
        uart_putc(*s++);
    }
}

static void gpio_set_stage(uint32_t stage)
{
    mmio_write(GPIO_BASE + GPIO_OUTPUT_VAL, (stage & 0xFu) << 4);
}

static void timer_start_oneshot(uint32_t ticks)
{
    mmio_write(TIMER_BASE + TIMER_INTCLR, 1u);
    mmio_write(TIMER_BASE + TIMER_LOAD, ticks);
    mmio_write(TIMER_BASE + TIMER_CTRL,
               TIMER_CTRL_ONE_SHOT | TIMER_CTRL_32BIT |
               TIMER_CTRL_INT_EN | TIMER_CTRL_ENABLE);
}

static void spi_init(void)
{
    mmio_write(SPI_BASE + SPI_SCKDIV, 1u);
    mmio_write(SPI_BASE + SPI_SCKMODE, 0u);
    mmio_write(SPI_BASE + SPI_CSID, 0u);
    mmio_write(SPI_BASE + SPI_CSDEF, 0xFu);
    mmio_write(SPI_BASE + SPI_CSMODE, 0u);
    mmio_write(SPI_BASE + SPI_FMT, (8u << 16));
    mmio_write(SPI_BASE + SPI_CTRL, 1u);
}

static uint8_t spi_xfer_byte(uint8_t tx)
{
    mmio_write(SPI_BASE + SPI_TXDATA, tx);

    while ((mmio_read(SPI_BASE + SPI_STATUS) & (1u << 31)) == 0u) {
        ;
    }

    return (uint8_t)(mmio_read(SPI_BASE + SPI_RXDATA) & 0xFFu);
}

static int wait_for_irq(unsigned int irq, uint32_t timeout)
{
    unsigned int start = irq_count[irq];
    while (timeout--) {
        if (irq_count[irq] != start) {
            return 0;
        }
    }
    return -1;
}

int main(void)
{
    uint32_t fail_mask = 0u;

    mmio_write(GPIO_BASE + GPIO_OUTPUT_EN, 0x0000000Fu);
    gpio_set_stage(0u);

    uart_init(8u);
    uart_puts("[TEST] periph test start\n");

    mmio_write(DEBUG_BASE + DEBUG_IRQ_EN, 0x7u);

    timer_start_oneshot(2000u);
    if (wait_for_irq(IRQ_TIMER, 200000u) != 0) {
        fail_mask |= (1u << 0);
    }

    gpio_set_stage(1u);
    if (wait_for_irq(IRQ_UART, 500000u) != 0) {
        fail_mask |= (1u << 1);
    }

    spi_init();
    mmio_write(SPI_BASE + SPI_IP, 0xFu);
    mmio_write(SPI_BASE + SPI_IE, (1u << 2));
    if (spi_xfer_byte(0xA5u) != 0xA5u) {
        fail_mask |= (1u << 2);
    }
    if (wait_for_irq(IRQ_SPI, 200000u) != 0) {
        fail_mask |= (1u << 3);
    }

    gpio_set_stage(2u);
    if (wait_for_irq(IRQ_DEBUG, 800000u) != 0) {
        fail_mask |= (1u << 4);
    }

    if (fail_mask == 0u) {
        mmio_write(GPIO_BASE + GPIO_OUTPUT_VAL, 0x1u);
        uart_puts("[TEST] PASS\n");
    } else {
        mmio_write(GPIO_BASE + GPIO_OUTPUT_VAL, 0x2u);
        uart_puts("[TEST] FAIL\n");
    }

    while (1) {
        ;
    }
}
