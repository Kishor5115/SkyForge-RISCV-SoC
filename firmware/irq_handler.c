#include "irq_handler.h"

/* ═════════════════════════════════════════════════════════════════
 *  Peripheral Base Addresses (must match apb_interconnect.sv)
 * ═════════════════════════════════════════════════════════════════ */
#define UART_BASE        0x20000000u
#define UART_RX_DATA     (*(volatile unsigned int *)(UART_BASE + 0x04u))
#define UART_STATUS      (*(volatile unsigned int *)(UART_BASE + 0x08u))
#define UART_CTRL        (*(volatile unsigned int *)(UART_BASE + 0x0Cu))

#define TIMER_BASE       0x20001000u
#define TIMER_CTRL       (*(volatile unsigned int *)(TIMER_BASE + 0x08u))
#define TIMER_INTCLR     (*(volatile unsigned int *)(TIMER_BASE + 0x0Cu))

#define GPIO_BASE        0x20002000u
#define GPIO_RISE_IP     (*(volatile unsigned int *)(GPIO_BASE + 0x1Cu))
#define GPIO_FALL_IP     (*(volatile unsigned int *)(GPIO_BASE + 0x24u))
#define GPIO_HIGH_IP     (*(volatile unsigned int *)(GPIO_BASE + 0x2Cu))
#define GPIO_LOW_IP      (*(volatile unsigned int *)(GPIO_BASE + 0x34u))
#define GPIO_OUTPUT_VAL  (*(volatile unsigned int *)(GPIO_BASE + 0x0Cu))

#define SPI_BASE         0x20003000u
#define SPI_SCKDIV       (*(volatile unsigned int *)(SPI_BASE + 0x00u))
#define SPI_SCKMODE      (*(volatile unsigned int *)(SPI_BASE + 0x04u))
#define SPI_CSID         (*(volatile unsigned int *)(SPI_BASE + 0x08u))
#define SPI_CSDEF        (*(volatile unsigned int *)(SPI_BASE + 0x0Cu))
#define SPI_CSMODE       (*(volatile unsigned int *)(SPI_BASE + 0x10u))
#define SPI_FMT          (*(volatile unsigned int *)(SPI_BASE + 0x14u))
#define SPI_TXDATA       (*(volatile unsigned int *)(SPI_BASE + 0x18u))
#define SPI_RXDATA       (*(volatile unsigned int *)(SPI_BASE + 0x1Cu))
#define SPI_TXMARK       (*(volatile unsigned int *)(SPI_BASE + 0x20u))
#define SPI_RXMARK       (*(volatile unsigned int *)(SPI_BASE + 0x24u))
#define SPI_IE           (*(volatile unsigned int *)(SPI_BASE + 0x28u))
#define SPI_IP           (*(volatile unsigned int *)(SPI_BASE + 0x2Cu))
#define SPI_STATUS       (*(volatile unsigned int *)(SPI_BASE + 0x30u))
#define SPI_CTRL         (*(volatile unsigned int *)(SPI_BASE + 0x34u))

#define DEBUG_BASE       0x20004000u
#define DEBUG_CMD        (*(volatile unsigned int *)(DEBUG_BASE + 0x08u))
#define DEBUG_ADDR       (*(volatile unsigned int *)(DEBUG_BASE + 0x0Cu))
#define DEBUG_WDATA      (*(volatile unsigned int *)(DEBUG_BASE + 0x10u))
#define DEBUG_RDATA      (*(volatile unsigned int *)(DEBUG_BASE + 0x14u))
#define DEBUG_ACK        (*(volatile unsigned int *)(DEBUG_BASE + 0x1Cu))
#define DEBUG_IRQ_EN     (*(volatile unsigned int *)(DEBUG_BASE + 0x20u))
#define DEBUG_IRQ_STATUS (*(volatile unsigned int *)(DEBUG_BASE + 0x24u))

/* ═════════════════════════════════════════════════════════════════ */

static volatile unsigned int g_irq_count[32];

static inline unsigned int picorv32_maskirq(unsigned int mask)
{
    unsigned int old_mask;
    asm volatile (".insn r 0x0B, 0, 3, %0, %1, x0"
                  : "=r"(old_mask)
                  : "r"(mask));
    return old_mask;
}

void irq_init(void)
{
    /* Enable IRQs for: Timer(3), UART(4), GPIO(5), SPI(6)
     * PicoRV32 maskirq: 1=masked (blocked), 0=enabled
     * Start with all masked, then unmask desired ones */
    unsigned int mask = 0xFFFFFFFFu;

    mask &= ~(1u << IRQ_TIMER);
    mask &= ~(1u << IRQ_UART);
    mask &= ~(1u << IRQ_GPIO);
    mask &= ~(1u << IRQ_SPI);
    mask &= ~(1u << IRQ_DEBUG);

    picorv32_maskirq(mask);

    /* Enable UART RX interrupt */
    UART_CTRL |= (1u << 18);
    /* Timer: keep interrupts disabled until user configures timer */
    TIMER_CTRL &= ~(1u << 7);

    /* Debug mailbox interrupt: request + completion events */
    DEBUG_IRQ_EN = 0x3u;
}

void irq_dispatch(unsigned int irqs)
{
    if (irqs & (1u << IRQ_TIMER)) {
        g_irq_count[IRQ_TIMER]++;
        timer_irq_handler();
    }

    if (irqs & (1u << IRQ_UART)) {
        g_irq_count[IRQ_UART]++;
        uart_irq_handler();
    }

    if (irqs & (1u << IRQ_GPIO)) {
        g_irq_count[IRQ_GPIO]++;
        gpio_irq_handler();
    }

    if (irqs & (1u << IRQ_SPI)) {
        g_irq_count[IRQ_SPI]++;
        spi_irq_handler();
    }

    if (irqs & (1u << IRQ_DEBUG)) {
        g_irq_count[IRQ_DEBUG]++;
        debug_irq_handler();
    }
}

void timer_irq_handler(void)
{
    TIMER_INTCLR = 1u;
}

void uart_irq_handler(void)
{
    while (((UART_STATUS >> 2) & 1u) == 0u) {
        (void)UART_RX_DATA;
    }
}

#define BTN_CENTER_BIT  16
#define BTN_LEFT_BIT    18
#define BTN_RIGHT_BIT   19

extern volatile int btn_left_flag;
extern volatile int btn_right_flag;
extern volatile int btn_center_flag;

void gpio_irq_handler(void)
{
    unsigned int pending = GPIO_RISE_IP;

    if (pending & (1u << BTN_LEFT_BIT)) {
        btn_left_flag = 1;
    }

    if (pending & (1u << BTN_RIGHT_BIT)) {
        btn_right_flag = 1;
    }

    if (pending & (1u << BTN_CENTER_BIT)) {
        btn_center_flag = 1;
    }

    /* Toggle LED 15 to visually indicate ISR executed */
    GPIO_OUTPUT_VAL ^= (1u << 15);

    /* Clear pending interrupts (W1C) */
    GPIO_RISE_IP = pending;
    GPIO_FALL_IP = 0xFFFFFFFFu;
    GPIO_HIGH_IP = 0xFFFFFFFFu;
    GPIO_LOW_IP  = 0xFFFFFFFFu;
}

void spi_irq_handler(void)
{
    /* Read and clear SPI interrupt pending register (W1C) */
    unsigned int ip = SPI_IP;
    SPI_IP = ip;  /* Write-1-to-clear */
}

static int debug_addr_valid(unsigned int addr)
{
    if (addr >= 0x00000000u && addr <= 0x0001FFFCu)
        return 1;

    if (addr >= 0x20000000u && addr <= 0x20004FFCu)
        return 1;

    return 0;
}

void debug_irq_handler(void)
{
    unsigned int pending = DEBUG_IRQ_STATUS;

    if (pending & (1u << 1)) {
        unsigned int cmd = DEBUG_CMD & 0xFFu;
        unsigned int addr = DEBUG_ADDR;
        unsigned int wdata = DEBUG_WDATA;

        if ((addr & 0x3u) || !debug_addr_valid(addr)) {
            DEBUG_ACK = 0x2u;
        } else {
            volatile unsigned int *ptr = (volatile unsigned int *)addr;

            if (cmd == 0x01u) {
                DEBUG_RDATA = *ptr;
                DEBUG_ACK = 0x1u;
            } else if (cmd == 0x02u) {
                *ptr = wdata;
                DEBUG_ACK = 0x1u;
            } else {
                DEBUG_ACK = 0x2u;
            }
        }
    }

    if (pending & (1u << 2)) {
        DEBUG_ACK = 0x4u;
    }

    if (pending & (1u << 0)) {
        DEBUG_IRQ_STATUS = (1u << 0);
    }
}
