#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "irq.h"

int main(void) {
    uart_init(54); // 115200 @ 100MHz (approx)
    irq_init();
    
    gpio_set_output_en(0xFFFF);
    
    uart_puts("RISC-V SoC Professional Firmware Initialized\n");
    
    uint32_t count = 0;
    while (1) {
        gpio_write(count++);
        uart_puts("Blink... ");
        timer_wait(1000000); // 10ms @ 100MHz
    }
    
    return 0;
}
