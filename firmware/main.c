#include <stdint.h>

extern uint32_t _uart_base;
extern uint32_t _timer_base;
extern uint32_t _gpio_base;

#define UART_BASE  ((uintptr_t)&_uart_base)
#define TIMER_BASE ((uintptr_t)&_timer_base)
#define GPIO_BASE  ((uintptr_t)&_gpio_base)

static inline void mmio_write(uintptr_t addr, uint32_t value)
{
    *(volatile uint32_t *)addr = value;
}

static inline uint32_t mmio_read(uintptr_t addr)
{
    return *(volatile uint32_t *)addr;
}

// UART register offsets
#define UART_TX_DATA   0x00u
#define UART_RX_DATA   0x04u
#define UART_STATUS    0x08u
#define UART_CTRL      0x0Cu

// UART STATUS bits
#define UART_STATUS_TX_EMPTY (1u << 0)
#define UART_STATUS_TX_FULL  (1u << 1)
#define UART_STATUS_RX_EMPTY (1u << 2)
#define UART_STATUS_RX_FULL  (1u << 3)
#define UART_STATUS_TX_BUSY  (1u << 6)

// UART CTRL bits
#define UART_CTRL_BAUD_MASK  0x0000FFFFu
#define UART_CTRL_TX_EN      (1u << 16)
#define UART_CTRL_RX_EN      (1u << 17)
#define UART_CTRL_IRQ_EN     (1u << 18)

// TIMER register offsets
#define TIMER_LOAD     0x00u
#define TIMER_VALUE    0x04u
#define TIMER_CTRL     0x08u
#define TIMER_INTCLR   0x0Cu
#define TIMER_RIS      0x10u
#define TIMER_MIS      0x14u
#define TIMER_BGLOAD   0x18u

// TIMER CTRL bits
#define TIMER_CTRL_ONE_SHOT  (1u << 0)
#define TIMER_CTRL_32BIT     (1u << 1)
#define TIMER_CTRL_PRESCALE0 (0u << 2)
#define TIMER_CTRL_INT_EN    (1u << 5)
#define TIMER_CTRL_MODE      (1u << 6)
#define TIMER_CTRL_ENABLE    (1u << 7)

// GPIO register offsets
#define GPIO_INPUT_VAL  0x00u
#define GPIO_INPUT_EN   0x04u
#define GPIO_OUTPUT_EN  0x08u
#define GPIO_OUTPUT_VAL 0x0Cu

static void uart_init(uint16_t baud_div)
{
    uint32_t ctrl = (baud_div & UART_CTRL_BAUD_MASK) | UART_CTRL_TX_EN | UART_CTRL_RX_EN;
    mmio_write(UART_BASE + UART_CTRL, ctrl);
}

static void uart_putc(char c)
{
    if (c == '\n') {
        uart_putc('\r');
    }

    while (mmio_read(UART_BASE + UART_STATUS) & UART_STATUS_TX_FULL) {
        // wait for space in TX FIFO
    }

    mmio_write(UART_BASE + UART_TX_DATA, (uint32_t)c);
}

static void uart_puts(const char *s)
{
    while (*s) {
        uart_putc(*s++);
    }
}

static void timer_wait(uint32_t ticks)
{
    mmio_write(TIMER_BASE + TIMER_INTCLR, 1u);
    mmio_write(TIMER_BASE + TIMER_LOAD, ticks);
    mmio_write(TIMER_BASE + TIMER_CTRL,
               TIMER_CTRL_ONE_SHOT | TIMER_CTRL_32BIT | TIMER_CTRL_PRESCALE0 | TIMER_CTRL_ENABLE);

    while ((mmio_read(TIMER_BASE + TIMER_RIS) & 1u) == 0u) {
        // wait for timer to hit zero
    }

    mmio_write(TIMER_BASE + TIMER_INTCLR, 1u);
}

int main(void)
{
    uart_init(54u);

    uart_puts("RISC-V SoC boot\n");
    uart_puts("UART ready. Blinking GPIO0.\n");

    mmio_write(GPIO_BASE + GPIO_OUTPUT_EN, 1u << 0);
    mmio_write(GPIO_BASE + GPIO_OUTPUT_VAL, 0u);

    uint32_t gpio_val = 0u;
    uint32_t count = 0u;

    while (1) {
        gpio_val ^= 1u;
        mmio_write(GPIO_BASE + GPIO_OUTPUT_VAL, gpio_val);

        if ((count++ & 0x7u) == 0u) {
            uart_puts("tick\n");
        }

        timer_wait(1000000u);
    }
}
