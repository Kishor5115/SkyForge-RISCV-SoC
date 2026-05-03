#ifndef TIMER_H
#define TIMER_H

#include "common.h"

/* Timer Register Offsets */
#define TIMER_LOAD     0x00u
#define TIMER_VALUE    0x04u
#define TIMER_CTRL     0x08u
#define TIMER_INTCLR   0x0Cu
#define TIMER_RIS      0x10u

/* Timer Control Register Bits */
#define TIMER_CTRL_ONE_SHOT  (1u << 0)
#define TIMER_CTRL_32BIT     (1u << 1)
#define TIMER_CTRL_INT_EN    (1u << 5)
#define TIMER_CTRL_ENABLE    (1u << 7)

void timer_init_oneshot(uint32_t ticks, int int_en);
void timer_wait(uint32_t ticks);
void timer_clear_irq(void);

#endif /* TIMER_H */
