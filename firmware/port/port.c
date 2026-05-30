/*
 * port.c — PicoRV32-specific FreeRTOS port
 *
 * PicoRV32 has NO standard RISC-V CSRs (mstatus, mtvec, mepc, etc.).
 * All interrupt handling is done via the custom IRQ ABI in start.S.
 *
 * This port uses interrupt-driven preemption:
 * - Interrupts are managed via picorv32_maskirq custom instruction
 * - Context switches happen in the IRQ wrapper and vPortYield
 */

#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include <string.h>

/* ── Global state ─────────────────────────────────────────────── */

/* Saved IRQ mask for critical section nesting */
volatile uint32_t picorv32_irq_mask = 0xFFFFFFFF; /* All masked at boot */

/* Critical nesting counter */
size_t xCriticalNesting = 0xAAAAAAAA;
size_t *pxCriticalNesting = &xCriticalNesting;

/* Yield requested from ISR context. */
volatile BaseType_t xPortYieldRequired = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * pxPortInitialiseStack
 *
 * Full context frame (36 words / 144 bytes, 16-byte aligned). The frame
 * includes all integer registers except x0/x2 plus q0-q3 and nesting state.
 *
 * Word 0:  ra  (x1)   = pxCode (task entry)
 * Word 1:  gp  (x3)
 * Word 2:  tp  (x4)
 * Word 3:  t0  (x5)
 * Word 4:  t1  (x6)
 * Word 5:  t2  (x7)
 * Word 6:  s0  (x8)
 * Word 7:  s1  (x9)
 * Word 8:  a0  (x10)  = pvParameters
 * Word 9:  a1  (x11)
 * Word 10: a2  (x12)
 * Word 11: a3  (x13)
 * Word 12: a4  (x14)
 * Word 13: a5  (x15)
 * Word 14: a6  (x16)
 * Word 15: a7  (x17)
 * Word 16: s2  (x18)
 * Word 17: s3  (x19)
 * Word 18: s4  (x20)
 * Word 19: s5  (x21)
 * Word 20: s6  (x22)
 * Word 21: s7  (x23)
 * Word 22: s8  (x24)
 * Word 23: s9  (x25)
 * Word 24: s10 (x26)
 * Word 25: s11 (x27)
 * Word 26: t3  (x28)
 * Word 27: t4  (x29)
 * Word 28: t5  (x30)
 * Word 29: t6  (x31)
 * Word 30: q0        = pxCode (retirq target)
 * Word 31: q1
 * Word 32: q2
 * Word 33: q3
 * Word 34: xCriticalNesting = 0
 * Word 35: padding
 */

#define portCONTEXT_WORDS  36

#define portCTX_RA          0
#define portCTX_A0          8
#define portCTX_Q0          30
#define portCTX_XNEST       34

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack,
                                     TaskFunction_t pxCode,
                                     void *pvParameters )
{
    /* Align to 16-byte boundary */
    pxTopOfStack = (StackType_t *)((uint32_t)pxTopOfStack & ~0xFUL);

    /* Allocate the context frame */
    pxTopOfStack -= portCONTEXT_WORDS;

    /* Zero the entire frame */
    memset(pxTopOfStack, 0, portCONTEXT_WORDS * sizeof(StackType_t));

    /* Set key registers */
    pxTopOfStack[portCTX_RA]    = (StackType_t)pxCode;
    pxTopOfStack[portCTX_A0]    = (StackType_t)pvParameters;
    pxTopOfStack[portCTX_Q0]    = (StackType_t)pxCode;
    pxTopOfStack[portCTX_XNEST] = 0;
    /* xCriticalNesting = 0 (already zeroed) */

    return pxTopOfStack;
}

/*-----------------------------------------------------------*/

/*
 * xPortStartFirstTask  (pure assembly — avoids C compiler clobbering SP)
 *
 * Reads pxCurrentTCB->pxTopOfStack, restores context, jumps to task.
 */
void xPortStartFirstTask( void ) __attribute__((naked));
void xPortStartFirstTask( void )
{
    __asm__ volatile (
        /* Load pxCurrentTCB */
        "la   t0, pxCurrentTCB  \n"
        "lw   sp, 0(t0)         \n"  /* sp = pxCurrentTCB */

        /* Debug: write pxCurrentTCB value to GPIO_OUT */
        "lui  t1, 0x20002       \n"
        "sw   sp, 12(t1)        \n"  /* GPIO_OUT = pxCurrentTCB ptr */

        "lw   sp, 0(sp)         \n"  /* sp = pxCurrentTCB->pxTopOfStack */

        /* Debug: write pxTopOfStack value to GPIO_OUT */
        "lui  t1, 0x20002       \n"
        "sw   sp, 12(t1)        \n"  /* GPIO_OUT = pxTopOfStack */

        /* Restore registers from context frame */
        "lw   ra,  0*4(sp)      \n"  /* x1  */
        "lw   gp,  1*4(sp)      \n"  /* x3  */
        "lw   tp,  2*4(sp)      \n"  /* x4  */
        "lw   t0,  3*4(sp)      \n"  /* x5  */
        "lw   t1,  4*4(sp)      \n"  /* x6  */
        "lw   t2,  5*4(sp)      \n"  /* x7  */
        "lw   s0,  6*4(sp)      \n"  /* x8  */
        "lw   s1,  7*4(sp)      \n"  /* x9  */
        "lw   a0,  8*4(sp)      \n"  /* x10 */
        "lw   a1,  9*4(sp)      \n"  /* x11 */
        "lw   a2, 10*4(sp)      \n"  /* x12 */
        "lw   a3, 11*4(sp)      \n"  /* x13 */
        "lw   a4, 12*4(sp)      \n"  /* x14 */
        "lw   a5, 13*4(sp)      \n"  /* x15 */
        "lw   a6, 14*4(sp)      \n"  /* x16 */
        "lw   a7, 15*4(sp)      \n"  /* x17 */
        "lw   s2, 16*4(sp)      \n"  /* x18 */
        "lw   s3, 17*4(sp)      \n"  /* x19 */
        "lw   s4, 18*4(sp)      \n"  /* x20 */
        "lw   s5, 19*4(sp)      \n"  /* x21 */
        "lw   s6, 20*4(sp)      \n"  /* x22 */
        "lw   s7, 21*4(sp)      \n"  /* x23 */
        "lw   s8, 22*4(sp)      \n"  /* x24 */
        "lw   s9, 23*4(sp)      \n"  /* x25 */
        "lw   s10,24*4(sp)      \n"  /* x26 */
        "lw   s11,25*4(sp)      \n"  /* x27 */
        "lw   t3, 26*4(sp)      \n"  /* x28 */
        "lw   t4, 27*4(sp)      \n"  /* x29 */
        "lw   t5, 28*4(sp)      \n"  /* x30 */
        "lw   t6, 29*4(sp)      \n"  /* x31 */

        /* Debug: write 0xB0000003 before xCriticalNesting restore */
        "lui  t0, 0xB0000       \n"
        "addi t0, t0, 3         \n"
        "lui  t1, 0x20002       \n"
        "sw   t0, 12(t1)        \n"

        /* Restore xCriticalNesting */
        "la   t0, xCriticalNesting \n"
        "lw   t1, 34*4(sp)      \n"
        "sw   t1, 0(t0)         \n"

        /* Restore q-registers */
        "lw   t0, 33*4(sp)      \n"
        ".insn r 0x0B, 0, 1, x0, x3, t0 \n"
        "lw   t0, 32*4(sp)      \n"
        ".insn r 0x0B, 0, 1, x0, x2, t0 \n"
        "lw   t0, 31*4(sp)      \n"
        ".insn r 0x0B, 0, 1, x0, x1, t0 \n"
        "lw   t0, 30*4(sp)      \n"
        ".insn r 0x0B, 0, 1, x0, x0, t0 \n"

        /* Pop the context frame */
        "addi sp, sp, %0        \n"

        /* Unmask timer IRQ (bit 3) just before entering first task.
         * Timer IRQ mask register: 1=masked, 0=enabled. */
        "li   t0, 0xFFFFFFF7    \n"
        ".insn r 0x0B, 0, 3, x0, t0, x0 \n"

        /* Debug breadcrumb: publish restored return address to GPIO_OUT. */
        "lui  t1, 0x20002       \n"
        "sw   ra, 12(t1)        \n"

        /* Jump to the task via q0 */
        ".insn r 0x0B, 0, 2, x0, x0, x0 \n"

        :
        : "i"(portCONTEXT_WORDS * 4)
        : "memory"
    );
}

/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( void )
{
    /* Reset critical nesting */
    xCriticalNesting = 0;

    /* Diagnostic: reached xPortStartScheduler */
    (*(volatile uint32_t *)(0x20002000U + 0x0CU)) = 0xB0000001U;

    /* Jump to first task — does not return */
    xPortStartFirstTask();

    return pdFAIL;
}

void vPortYieldFromISR( void )
{
    xPortYieldRequired = pdTRUE;
}

/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
    for( ;; );
}

/*-----------------------------------------------------------*/

void __attribute__((weak)) vPortSetupTimerInterrupt( void )
{
    /* Timer setup done externally in main.c */
}
