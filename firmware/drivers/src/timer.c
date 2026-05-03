#include "timer.h"

void timer_init_oneshot(uint32_t ticks, int int_en) {
    mmio_write(TIMER_BASE + TIMER_INTCLR, 1u);
    mmio_write(TIMER_BASE + TIMER_LOAD, ticks);
    uint32_t ctrl = TIMER_CTRL_ONE_SHOT | TIMER_CTRL_32BIT | TIMER_CTRL_ENABLE;
    if (int_en) ctrl |= TIMER_CTRL_INT_EN;
    mmio_write(TIMER_BASE + TIMER_CTRL, ctrl);
}

void timer_wait(uint32_t ticks) {
    timer_init_oneshot(ticks, 0);
    while ((mmio_read(TIMER_BASE + TIMER_RIS) & 1u) == 0u);
    mmio_write(TIMER_BASE + TIMER_INTCLR, 1u);
}

void timer_clear_irq(void) {
    mmio_write(TIMER_BASE + TIMER_INTCLR, 1u);
}
