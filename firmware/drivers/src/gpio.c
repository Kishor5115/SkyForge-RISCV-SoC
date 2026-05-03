#include "gpio.h"

void gpio_set_output_en(uint32_t mask) {
    mmio_write(GPIO_BASE + GPIO_OUTPUT_EN, mask);
}

void gpio_write(uint32_t val) {
    mmio_write(GPIO_BASE + GPIO_OUTPUT_VAL, val);
}

uint32_t gpio_read(void) {
    return mmio_read(GPIO_BASE + GPIO_INPUT_VAL);
}

void gpio_set_input_en(uint32_t mask) {
    mmio_write(GPIO_BASE + GPIO_INPUT_EN, mask);
}
