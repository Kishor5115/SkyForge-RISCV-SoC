#ifndef GPIO_H
#define GPIO_H

#include "common.h"

/* GPIO Register Offsets */
#define GPIO_INPUT_VAL  0x00u
#define GPIO_INPUT_EN   0x04u
#define GPIO_OUTPUT_EN  0x08u
#define GPIO_OUTPUT_VAL 0x0Cu

void gpio_set_output_en(uint32_t mask);
void gpio_write(uint32_t val);
uint32_t gpio_read(void);
void gpio_set_input_en(uint32_t mask);

#endif /* GPIO_H */
