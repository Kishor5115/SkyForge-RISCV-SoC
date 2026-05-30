/*
 * FreeRTOSConfig.h — Tuned for PicoRV32 SoC (16 KB SRAM)
 */
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* ── Core ────────────────────────────────────────────────────────── */
#define configUSE_PREEMPTION                     1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION   0
#define configUSE_TICKLESS_IDLE                   0
#define configCPU_CLOCK_HZ                       ((uint32_t)25000000) /* 25 MHz */
#define configTICK_RATE_HZ                       ((TickType_t)1000)   /* 1 kHz = 1 ms */
#define configMAX_PRIORITIES                      4
#define configMINIMAL_STACK_SIZE                 ((uint16_t)128)  /* words */
#define configMAX_TASK_NAME_LEN                   8
#define configUSE_16_BIT_TICKS                    0
#define configIDLE_SHOULD_YIELD                   1
#define configUSE_TASK_NOTIFICATIONS              1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES     1

/* ── Memory (heap_4, 6 KB of 16 KB SRAM) ─────────────────────────── */
#define configTOTAL_HEAP_SIZE                    ((size_t)(6 * 1024))
#define configSUPPORT_STATIC_ALLOCATION           0
#define configSUPPORT_DYNAMIC_ALLOCATION          1
#define configAPPLICATION_ALLOCATED_HEAP           0

/* ── Hooks ───────────────────────────────────────────────────────── */
#define configUSE_IDLE_HOOK                       0
#define configUSE_TICK_HOOK                       0
#define configUSE_MALLOC_FAILED_HOOK              1
#define configCHECK_FOR_STACK_OVERFLOW            1

/* ── Synchronisation ─────────────────────────────────────────────── */
#define configUSE_MUTEXES                         1
#define configUSE_RECURSIVE_MUTEXES               0
#define configUSE_COUNTING_SEMAPHORES             0
#define configQUEUE_REGISTRY_SIZE                 0

/* ── Timers ──────────────────────────────────────────────────────── */
#define configUSE_TIMERS                          0
#define configTIMER_TASK_PRIORITY                  2
#define configTIMER_QUEUE_LENGTH                   4
#define configTIMER_TASK_STACK_DEPTH              configMINIMAL_STACK_SIZE

/* ── Co-routines (disabled) ──────────────────────────────────────── */
#define configUSE_CO_ROUTINES                     0

/* ── PicoRV32: NO mtime/mtimecmp (uses custom APB timer instead) ── */
#define configMTIME_BASE_ADDRESS                  0
#define configMTIMECMP_BASE_ADDRESS               0

/* ── API inclusion ───────────────────────────────────────────────── */
#define INCLUDE_vTaskPrioritySet                  0
#define INCLUDE_uxTaskPriorityGet                 0
#define INCLUDE_vTaskDelete                       1
#define INCLUDE_vTaskSuspend                      1
#define INCLUDE_vTaskDelayUntil                   1
#define INCLUDE_vTaskDelay                        1
#define INCLUDE_xTaskGetSchedulerState            0
#define INCLUDE_xTaskGetCurrentTaskHandle         0

/* ── Assert ──────────────────────────────────────────────────────── */
#define configASSERT(x) do { if (!(x)) { \
    (*(volatile unsigned int *)(0x2000200CU)) = 0xABCD0000U; \
    for(;;); } } while(0)

#endif /* FREERTOS_CONFIG_H */
