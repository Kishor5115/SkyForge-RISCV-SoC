#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "spi.h"
#include "irq.h"

static void fail(const char *reason) {
    uart_puts("FAIL: ");
    uart_puts(reason);
    uart_puts("\n---TEST_FAIL---\n");
    while(1);
}

int main(void) {
    uart_init(54);
    irq_init();
    uart_puts("Starting SoC Integration Test (Refactored)...\n");

    // 1. GPIO Loopback
    uart_puts("Testing GPIO Loopback...\n");
    gpio_set_output_en(0xFFFFFFFFu);
    gpio_set_input_en(0xFFFFFFFFu);
    gpio_write(0xDEADBEEFu);
    for(volatile int i=0; i<10; i++); 
    if (gpio_read() != 0xDEADBEEFu) fail("GPIO loopback mismatch");

    // 2. SPI Loopback
    uart_puts("Testing SPI Loopback...\n");
    spi_init(4);
    spi_set_cs(0);
    uint32_t rx = spi_transfer(0xA5);
    if (rx != 0xA5) fail("SPI loopback mismatch");

    // 3. Timer IRQ
    uart_puts("Testing Timer IRQ...\n");
    uint32_t start_cnt = irq_count[IRQ_TIMER];
    timer_init_oneshot(100, 1);
    
    uint32_t timeout = 10000;
    while (irq_count[IRQ_TIMER] == start_cnt) {
        if (--timeout == 0) fail("Timer IRQ Timeout");
    }

    uart_puts("All tests passed from firmware.\n");
    uart_puts("Waiting for JTAG Master (Testbench) to complete...\n");
    uart_puts("---FIRMWARE_PASS---\n");

    while(1);
    return 0;
}
