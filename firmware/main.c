/*
 * main.c — PicoRV32 FreeRTOS Demo
 *
 * Initialises the APB timer for 1 ms periodic IRQ[3],
 * creates two demo tasks, and starts the FreeRTOS scheduler.
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

/* ── APB Timer Registers (base 0x20001000) ───────────────────────── */
#define TIMER_BASE      0x20001000U
#define TIMER_LOAD      (*(volatile uint32_t *)(TIMER_BASE + 0x00))
#define TIMER_CTRL      (*(volatile uint32_t *)(TIMER_BASE + 0x08))
#define TIMER_INTCLR    (*(volatile uint32_t *)(TIMER_BASE + 0x0C))

/* CTRL bits */
#define TIMER_CTRL_EN       (1U << 7)
#define TIMER_CTRL_PERIODIC (1U << 6)
#define TIMER_CTRL_IRQ_EN   (1U << 5)

/* ── GPIO (base 0x20002000) per apb_interconnect.sv address map ──── */
#define GPIO_BASE       0x20002000U
#define GPIO_OUTPUT_EN  (*(volatile uint32_t *)(GPIO_BASE + 0x08))
#define GPIO_OUT        (*(volatile uint32_t *)(GPIO_BASE + 0x0C))

/* ── Clock ───────────────────────────────────────────────────────── */
#define CPU_CLOCK_HZ    25000000U
#define TICK_RATE_HZ    1000U
#define TIMER_RELOAD    (CPU_CLOCK_HZ / TICK_RATE_HZ)  /* 25000 */

/* ── Diagnostic: write unique pattern to GPIO to trace execution ── */
#define DIAG(val) do { GPIO_OUT = (uint32_t)(val); } while(0)

/* ──────────────────────────────────────────────────────────────────
 * Timer initialisation
 * ────────────────────────────────────────────────────────────────── */
static void timer_init(void)
{
    TIMER_CTRL   = 0;                   /* disable first */
    TIMER_INTCLR = 1;                   /* clear any pending IRQ */
    TIMER_LOAD   = TIMER_RELOAD;        /* 1 ms period at 25 MHz */
    TIMER_CTRL   = TIMER_CTRL_EN
                 | TIMER_CTRL_PERIODIC
                 | TIMER_CTRL_IRQ_EN;
}

/* ── FreeRTOS tick handler (called from start.S IRQ wrapper) ─────── */
BaseType_t xPortSysTickHandler(void)
{
    /* Clear the timer interrupt */
    TIMER_INTCLR = 1;

    /* Inform FreeRTOS of the tick */
    BaseType_t xHigherPriorityTaskWoken = xTaskIncrementTick();

    return xHigherPriorityTaskWoken;
}

/* ── vApplicationStackOverflowHook ───────────────────────────────── */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    GPIO_OUT = 0xDEAD0001U;
    for (;;);  /* hang on stack overflow */
}

/* ── vApplicationMallocFailedHook ────────────────────────────────── */
void vApplicationMallocFailedHook(void)
{
    GPIO_OUT = 0xDEAD0002U;
    for (;;);  /* hang on malloc failure */
}

/* ──────────────────────────────────────────────────────────────────
 * Demo Task A — toggles GPIO bit 0 every 500 ms
 * ────────────────────────────────────────────────────────────────── */
static void vTaskA(void *pvParams)
{
    (void)pvParams;
    for (;;) {
        GPIO_OUT ^= 0x01;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/* ──────────────────────────────────────────────────────────────────
 * Demo Task B — toggles GPIO bit 1 every 1000 ms
 * ────────────────────────────────────────────────────────────────── */
static void vTaskB(void *pvParams)
{
    (void)pvParams;
    for (;;) {
        GPIO_OUT ^= 0x02;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/* ──────────────────────────────────────────────────────────────────
 * main
 * ────────────────────────────────────────────────────────────────── */
int main(void)
{
    /* Enable GPIO output drivers for ALL bits (diagnostics use upper bits) */
    GPIO_OUTPUT_EN = 0xFFFFFFFFU;
    GPIO_OUT = 0x00000000U;
    DIAG(0xA0000001U);   /* reached main */

    timer_init();
    DIAG(0xA0000002U);   /* timer init done */

    BaseType_t rcA = xTaskCreate(vTaskA, "TaskA", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    DIAG(0xA0000003U);   /* TaskA created */

    BaseType_t rcB = xTaskCreate(vTaskB, "TaskB", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    DIAG(0xA0000004U);   /* TaskB created */

    /* Diagnostic: task creation failure */
    if ((rcA != pdPASS) || (rcB != pdPASS)) {
        GPIO_OUT = 0xE0010000U | ((uint32_t)rcA << 8) | (uint32_t)rcB;
        for (;;);
    }
    DIAG(0xA0000005U);   /* about to start scheduler */

    vTaskStartScheduler();

    /* Diagnostic: scheduler returned unexpectedly */
    DIAG(0xE0020000U);
    for (;;);
    return 0;
}
