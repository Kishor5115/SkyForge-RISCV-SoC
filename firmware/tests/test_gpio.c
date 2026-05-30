/*
 * Minimal test — directly write GPIO to verify CPU boots correctly.
 */

#include <stdint.h>

/* GPIO register map (per gpio_apb.sv) */
#define GPIO_BASE       0x20002000U
#define GPIO_OUTPUT_EN  (*(volatile uint32_t *)(GPIO_BASE + 0x08))
#define GPIO_OUTPUT_VAL (*(volatile uint32_t *)(GPIO_BASE + 0x0C))

int main(void)
{
    /* Enable GPIO outputs for bits 0-15 */
    GPIO_OUTPUT_EN = 0x0000FFFF;

    /* Write initial pattern */
    GPIO_OUTPUT_VAL = 0x0000DEAD;

    /* Simple toggle loop */
    volatile uint32_t count = 0;
    while (1) {
        count++;
        if ((count & 0xFFF) == 0) {
            GPIO_OUTPUT_VAL ^= 0x01;
        }
    }
    return 0;
}
