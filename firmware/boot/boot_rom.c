/*
 * boot_rom.c — ASIC Boot Loader for RISC-V SoC
 *
 * This is the professional boot ROM firmware that executes from address 0x0000_0000.
 */

#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "spi.h"
#include "irq.h"

/* Application entry point in SRAM */
#define APP_ENTRY_ADDR   0x00010000u
#define APP_MAGIC        0x52534356u  /* "RSCV" — magic word at flash offset 0 */

/* Flash application image layout (at flash offset 0) */
#define FLASH_IMAGE_HDR_OFF  0x00000000u
#define FLASH_IMAGE_DATA_OFF 0x00000010u

/* ================================================================== */
/*  Helper Functions                                                    */
/* ================================================================== */

static void uart_put_hex(unsigned int val, int digits)
{
    for (int i = digits - 1; i >= 0; i--) {
        unsigned int nibble = (val >> (i * 4)) & 0xF;
        uart_putc(nibble < 10 ? '0' + nibble : 'A' + (nibble - 10));
    }
}

static void uart_put_hex32(unsigned int val)
{
    uart_puts("0x");
    uart_put_hex(val, 8);
}

static void delay(unsigned int cycles)
{
    for (volatile unsigned int i = 0; i < cycles; i++)
        ;
}

static void led_progress(unsigned int step)
{
    gpio_write((1u << step) & 0xFFFF);
}

/* ================================================================== */
/*  Flash Operations                                                    */
/* ================================================================== */

static void flash_init(void)
{
    /* Enable controller, set clock divisor for ~1 MHz SPI */
    mmio_write(FLASH_BASE + 0x18, 50);   /* 100 MHz / (2 * (50+1)) ≈ 980 KHz */
    mmio_write(FLASH_BASE + 0x00, 0x01); /* Enable */
    delay(100);
}

static int flash_read_jedec(unsigned int *jedec_out)
{
    /* Issue JEDEC ID read command (0x9F) */
    mmio_write(FLASH_BASE + 0x08, (1u << 8) | 0x9F);  /* start=1, cmd=0x9F */

    /* Wait for completion */
    unsigned int timeout = 100000;
    while ((mmio_read(FLASH_BASE + 0x04) & 0x01) && timeout > 0)
        timeout--;

    if (timeout == 0) return -1;

    *jedec_out = mmio_read(FLASH_BASE + 0x1C) & 0x00FFFFFF;
    return 0;
}

/* ================================================================== */
/*  Debug Monitor (fallback if no application found)                    */
/* ================================================================== */

static void debug_monitor(void)
{
    uart_puts("\r\n[BOOT] Entering debug monitor...\r\n");
    uart_puts("[BOOT] Waiting for JTAG commands.\r\n");
    uart_puts("[BOOT] Write to DEBUG_CMD register to interact.\r\n\r\n");

    /* Blink LED[0] slowly to indicate debug monitor active */
    unsigned int toggle = 0;
    while (1) {
        delay(5000000);
        toggle ^= 1;
        gpio_write(toggle);

        /* Check debug mailbox for any JTAG commands */
        unsigned int status = mmio_read(DEBUG_BASE + 0x00);
        if (status & 0x01) {
            unsigned int cmd = mmio_read(DEBUG_BASE + 0x08) & 0xFF;
            unsigned int addr = mmio_read(DEBUG_BASE + 0x0C);

            uart_puts("[DBG] CMD=");
            uart_put_hex(cmd, 2);
            uart_puts(" ADDR=");
            uart_put_hex32(addr);
            uart_puts("\r\n");

            if (cmd == 0x01) {
                /* Read: return memory value */
                volatile unsigned int *ptr = (volatile unsigned int *)addr;
                mmio_write(DEBUG_BASE + 0x14, *ptr);
                mmio_write(DEBUG_BASE + 0x1C, 0x1);
            } else if (cmd == 0x02) {
                /* Write */
                volatile unsigned int *ptr = (volatile unsigned int *)addr;
                unsigned int wdata = mmio_read(DEBUG_BASE + 0x10);
                *ptr = wdata;
                mmio_write(DEBUG_BASE + 0x1C, 0x1);
            } else {
                mmio_write(DEBUG_BASE + 0x1C, 0x2);  /* Error */
            }
        }
    }
}

/* ================================================================== */
/*  Main Boot Entry                                                     */
/* ================================================================== */

void main(void)
{
    /* ── Step 1: Initialize GPIO (LEDs for progress) ──────────── */
    gpio_set_output_en(0x0000FFFF);
    led_progress(0);

    /* ── Step 2: UART Banner ──────────────────────────────────── */
    uart_init(54);
    uart_puts("\r\n");
    uart_puts("╔══════════════════════════════════════════════════╗\r\n");
    uart_puts("║       RISC-V SoC — Boot ROM v1.0                ║\r\n");
    uart_puts("║       PicoRV32 @ 100 MHz  |  Sky130 ASIC        ║\r\n");
    uart_puts("╚══════════════════════════════════════════════════╝\r\n");
    uart_puts("\r\n");
    led_progress(1);

    /* ── Step 3: Probe SPI Flash ─────────────────────────────── */
    uart_puts("[BOOT] Initializing flash controller...\r\n");
    flash_init();
    led_progress(2);

    unsigned int jedec_id = 0;
    int flash_ok = flash_read_jedec(&jedec_id);

    if (flash_ok == 0 && jedec_id != 0x000000 && jedec_id != 0xFFFFFF) {
        uart_puts("[BOOT] Flash JEDEC ID: ");
        uart_put_hex32(jedec_id);

        /* Decode manufacturer */
        unsigned int mfr = (jedec_id >> 16) & 0xFF;
        if (mfr == 0xEF)      uart_puts(" (Winbond)");
        else if (mfr == 0xC8) uart_puts(" (GigaDevice)");
        else if (mfr == 0x9D) uart_puts(" (ISSI)");
        else if (mfr == 0x20) uart_puts(" (Micron)");
        else                  uart_puts(" (Unknown)");

        uart_puts("\r\n");
        led_progress(3);
    } else {
        uart_puts("[BOOT] WARNING: Flash not detected (JEDEC=");
        uart_put_hex32(jedec_id);
        uart_puts(")\r\n");
        uart_puts("[BOOT] Skipping flash boot.\r\n");
        debug_monitor();
        return;  /* Never reached */
    }

    /* ── Step 4: Enable Execute-In-Place (XIP) ───────────────── */
    /* v2: instead of copying the application into SRAM (only 16 KB),
     * we enable cached XIP so the CPU fetches .text/.rodata directly
     * from external flash via the 1 KB I-Cache. This allows firmware
     * larger than SRAM. */
    uart_puts("[BOOT] Enabling flash XIP (execute-in-place)...\r\n");

    /* CTRL: [0]=enable, [1]=xip_en, [3:2]=addr_width(0=24-bit) */
    mmio_write(FLASH_BASE + 0x00, 0x03u);   /* enable | xip_en, 24-bit addr */
    delay(100);

    if (mmio_read(FLASH_BASE + 0x04) & (1u << 1)) {
        uart_puts("[BOOT] XIP active.\r\n");
    } else {
        uart_puts("[BOOT] WARNING: xip_active not set; continuing anyway.\r\n");
    }
    led_progress(4);

    /* ── Step 5: Jump to application in flash XIP window ──────── */
    uart_puts("[BOOT] Jumping to application at ");
    uart_put_hex32(FLASH_XIP_BASE);
    uart_puts("...\r\n");
    uart_puts("════════════════════════════════════════════════════\r\n\r\n");
    led_progress(5);

    /* Flush UART */
    delay(10000);

    /* Jump to the flash XIP reset vector (FreeRTOS _start) */
    void (*app_entry)(void) = (void (*)(void))FLASH_XIP_BASE;
    app_entry();

    /* Should never return */
    uart_puts("[BOOT] ERROR: Application returned!\r\n");
    debug_monitor();
}
