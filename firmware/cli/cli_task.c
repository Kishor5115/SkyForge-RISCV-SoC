/*
 * cli_task.c — Interactive UART command-line shell for the SkyForge
 *              PicoRV32 SoC, built on FreeRTOS+CLI.
 *
 * The task reads a line from the UART, runs it through the FreeRTOS+CLI
 * interpreter (handling the multi-buffer output protocol), and echoes the
 * result. Registered commands:
 *
 *   help              - list all registered commands (built into the library)
 *   ver               - print firmware/SoC banner
 *   status            - uptime (ms) + free heap + min-ever free heap
 *   memread  <addr>   - read a 32-bit word at a hex address
 *   gpio     <hex>    - drive GPIO_OUT with a 32-bit hex value
 *
 * The UART driver (uart_getc/uart_putc/uart_puts) is polled; running it
 * inside a dedicated task is fine because FreeRTOS preemption keeps the
 * other tasks (e.g. the GPIO blinkers) running while this task waits.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_CLI.h"

#include "uart.h"
#include "common.h"
#include "cli.h"

/* ── Tunables ──────────────────────────────────────────────────────── */
#define CLI_MAX_INPUT_LEN   64
#define CLI_TASK_STACK      ((uint16_t)(configMINIMAL_STACK_SIZE * 4))  /* 512 words */
#define CLI_TASK_PRIORITY   1
#define CLI_PROMPT          "skyforge> "

/* ──────────────────────────────────────────────────────────────────
 * Small helper: parse a hex string (optional 0x prefix) into uint32_t.
 * Stops at the first non-hex character or after `maxlen` chars.
 * ────────────────────────────────────────────────────────────────── */
static uint32_t parse_hex(const char *s, BaseType_t maxlen)
{
    uint32_t v = 0;
    BaseType_t i = 0;

    if (maxlen >= 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        s += 2;
        i += 2;
    }

    for (; i < maxlen && *s; ++i, ++s) {
        char c = *s;
        uint32_t d;
        if      (c >= '0' && c <= '9') d = (uint32_t)(c - '0');
        else if (c >= 'a' && c <= 'f') d = (uint32_t)(c - 'a' + 10);
        else if (c >= 'A' && c <= 'F') d = (uint32_t)(c - 'A' + 10);
        else break;
        v = (v << 4) | d;
    }
    return v;
}

/* ──────────────────────────────────────────────────────────────────
 * Command: ver
 * ────────────────────────────────────────────────────────────────── */
static BaseType_t cmd_ver(char *out, size_t len, const char *cmd)
{
    (void)cmd;
    snprintf(out, len,
             "SkyForge PicoRV32 SoC (RV32IM)\r\n"
             "FreeRTOS+CLI interactive shell\r\n");
    return pdFALSE;
}

/* ──────────────────────────────────────────────────────────────────
 * Command: status
 * ────────────────────────────────────────────────────────────────── */
static BaseType_t cmd_status(char *out, size_t len, const char *cmd)
{
    (void)cmd;
    unsigned ms       = (unsigned)xTaskGetTickCount();   /* 1 tick = 1 ms */
    unsigned freeNow  = (unsigned)xPortGetFreeHeapSize();
    unsigned freeMin  = (unsigned)xPortGetMinimumEverFreeHeapSize();
    unsigned ntasks   = (unsigned)uxTaskGetNumberOfTasks();

    snprintf(out, len,
             "uptime    : %u ms\r\n"
             "tasks     : %u\r\n"
             "heap free : %u bytes\r\n"
             "heap min  : %u bytes\r\n",
             ms, ntasks, freeNow, freeMin);
    return pdFALSE;
}

/* ──────────────────────────────────────────────────────────────────
 * Command: memread <addr>
 * ────────────────────────────────────────────────────────────────── */
static BaseType_t cmd_memread(char *out, size_t len, const char *cmd)
{
    BaseType_t plen;
    const char *p = FreeRTOS_CLIGetParameter(cmd, 1, &plen);

    if (p == NULL) {
        snprintf(out, len, "usage: memread <hex-addr>\r\n");
        return pdFALSE;
    }

    uint32_t addr = parse_hex(p, plen) & ~0x3u;   /* word align */
    uint32_t val  = mmio_read(addr);

    snprintf(out, len, "[0x%08x] = 0x%08x\r\n", addr, val);
    return pdFALSE;
}

/* ──────────────────────────────────────────────────────────────────
 * Command: gpio <hex>  — drive GPIO_OUT (shows live peripheral control)
 * ────────────────────────────────────────────────────────────────── */
static BaseType_t cmd_gpio(char *out, size_t len, const char *cmd)
{
    BaseType_t plen;
    const char *p = FreeRTOS_CLIGetParameter(cmd, 1, &plen);

    if (p == NULL) {
        snprintf(out, len, "usage: gpio <hex-value>\r\n");
        return pdFALSE;
    }

    uint32_t val = parse_hex(p, plen);
    mmio_write(GPIO_BASE + 0x0C, val);            /* GPIO_OUT */

    snprintf(out, len, "GPIO_OUT <= 0x%08x\r\n", val);
    return pdFALSE;
}

/* ── Command definition table ──────────────────────────────────────── */
static const CLI_Command_Definition_t xVer = {
    "ver", "ver:\r\n  print SoC/firmware banner\r\n", cmd_ver, 0
};
static const CLI_Command_Definition_t xStatus = {
    "status", "status:\r\n  uptime, task count and heap usage\r\n", cmd_status, 0
};
static const CLI_Command_Definition_t xMemRead = {
    "memread", "memread <addr>:\r\n  read 32-bit word at hex address\r\n", cmd_memread, 1
};
static const CLI_Command_Definition_t xGpio = {
    "gpio", "gpio <hex>:\r\n  write 32-bit value to GPIO_OUT\r\n", cmd_gpio, 1
};

/* ──────────────────────────────────────────────────────────────────
 * The interactive CLI task.
 * ────────────────────────────────────────────────────────────────── */
static void vCliTask(void *pv)
{
    (void)pv;
    char       line[CLI_MAX_INPUT_LEN];
    uint8_t    idx = 0;
    BaseType_t more;
    char      *out = FreeRTOS_CLIGetOutputBuffer();

    uart_puts("\r\n");
    uart_puts("==============================\r\n");
    uart_puts("  SkyForge SoC — FreeRTOS CLI \r\n");
    uart_puts("==============================\r\n");
    uart_puts("Type 'help' for a command list.\r\n");
    uart_puts(CLI_PROMPT);

    for (;;) {
        char c = uart_getc();          /* blocking-polled receive */

        if (c == '\r' || c == '\n') {
            uart_puts("\r\n");
            if (idx > 0) {
                line[idx] = '\0';
                /* Multi-call output protocol: keep calling until pdFALSE. */
                do {
                    more = FreeRTOS_CLIProcessCommand(
                               line, out, configCOMMAND_INT_MAX_OUTPUT_SIZE);
                    uart_puts(out);
                } while (more != pdFALSE);
                idx = 0;
            }
            uart_puts(CLI_PROMPT);
        }
        else if (c == 0x08 || c == 0x7F) {     /* backspace / DEL */
            if (idx > 0) {
                idx--;
                uart_puts("\b \b");            /* erase on terminal */
            }
        }
        else if (c >= 0x20 && c < 0x7F && idx < (CLI_MAX_INPUT_LEN - 1)) {
            line[idx++] = c;
            uart_putc(c);                      /* echo */
        }
        /* other control chars are ignored */
    }
}

/* ──────────────────────────────────────────────────────────────────
 * Public entry point.
 * ────────────────────────────────────────────────────────────────── */
void cli_start(void)
{
    FreeRTOS_CLIRegisterCommand(&xVer);
    FreeRTOS_CLIRegisterCommand(&xStatus);
    FreeRTOS_CLIRegisterCommand(&xMemRead);
    FreeRTOS_CLIRegisterCommand(&xGpio);
    /* "help" is registered automatically by the library. */

    (void)xTaskCreate(vCliTask, "CLI", CLI_TASK_STACK,
                      NULL, CLI_TASK_PRIORITY, NULL);
}
