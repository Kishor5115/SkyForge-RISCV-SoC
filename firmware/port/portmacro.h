/*
 * portmacro.h — PicoRV32-specific FreeRTOS port
 *
 * PicoRV32 does NOT implement standard RISC-V CSRs (mstatus, mie, etc.).
 * Instead, it uses custom instructions for interrupt masking.
 * This port uses picorv32_maskirq to implement critical sections.
 */

#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
    extern "C" {
#endif

/* ── Type definitions ─────────────────────────────────────────── */
#define portSTACK_TYPE           uint32_t
#define portBASE_TYPE            int32_t
#define portUBASE_TYPE           uint32_t
#define portMAX_DELAY            ( (TickType_t) 0xffffffffUL )

typedef portSTACK_TYPE   StackType_t;
typedef portBASE_TYPE    BaseType_t;
typedef portUBASE_TYPE   UBaseType_t;
typedef portUBASE_TYPE   TickType_t;

/* Legacy type definitions. */
#define portCHAR                 char
#define portFLOAT                float
#define portDOUBLE               double
#define portLONG                 long
#define portSHORT                short

/* 32-bit tick type on a 32-bit architecture. */
#define portTICK_TYPE_IS_ATOMIC  1

/* ── Architecture specifics ───────────────────────────────────── */
#define portSTACK_GROWTH         ( -1 )
#define portTICK_PERIOD_MS       ( (TickType_t) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT       16

/* ── Critical section management ──────────────────────────────── */
/*
 * PicoRV32 uses a custom maskirq instruction to mask/unmask interrupts.
 * We inline-assemble .word encodings since the assembler doesn't know
 * the custom opcodes natively.
 *
 * picorv32_maskirq(rd, rs):
 *   .insn r 0x0B, 0, 3, rd, rs, x0
 *   Encoding: funct7=3, rs2=x0, rs1=rs, funct3=0, rd=rd, opcode=0x0B
 *
 * To DISABLE interrupts: mask all 32 bits (write 0xFFFFFFFF)
 * To ENABLE  interrupts: restore the previous mask
 *
 * The maskirq instruction returns the *previous* mask in rd.
 */

extern volatile uint32_t picorv32_irq_mask;

static inline uint32_t __picorv32_maskirq(uint32_t newmask)
{
    uint32_t oldmask;
    /* .insn r 0x0B, 0, 3, rd, rs, x0
     * We use inline asm with constraints:
     *   rd = %0 (output, "=r")
     *   rs = %1 (input, "r") */
    __asm__ volatile (
        ".insn r 0x0B, 0, 3, %0, %1, x0"
        : "=r"(oldmask)
        : "r"(newmask)
    );
    return oldmask;
}

#define portDISABLE_INTERRUPTS()   do { picorv32_irq_mask = __picorv32_maskirq(0xFFFFFFFF); } while(0)
#define portENABLE_INTERRUPTS()    do { __picorv32_maskirq(picorv32_irq_mask); } while(0)

extern size_t xCriticalNesting;

#define portENTER_CRITICAL()       \
    {                              \
        portDISABLE_INTERRUPTS();  \
        xCriticalNesting++;        \
    }

#define portEXIT_CRITICAL()            \
    {                                  \
        xCriticalNesting--;            \
        if( xCriticalNesting == 0 )    \
        {                              \
            portENABLE_INTERRUPTS();   \
        }                              \
    }

#define portCRITICAL_NESTING_IN_TCB    0

/* ── Scheduler utilities ──────────────────────────────────────── */
extern void vTaskSwitchContext( void );
extern void vPortYield( void );
extern void vPortYieldFromISR( void );
/* PicoRV32 does not support ecall. Context switching is done in assembly. */
#define portYIELD()                vPortYield()
#define portEND_SWITCHING_ISR( xSwitchRequired )   \
    do {                                            \
        if( (xSwitchRequired) != pdFALSE )          \
            vPortYieldFromISR();                    \
    } while(0)
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )

/* ── Task function macros ─────────────────────────────────────── */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    void vFunction( void * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          void vFunction( void * pvParameters )

/* ── Misc ─────────────────────────────────────────────────────── */
#define portNOP()              __asm__ volatile ( "nop" )
#define portINLINE             __inline
#ifndef portFORCE_INLINE
    #define portFORCE_INLINE   inline __attribute__(( always_inline ))
#endif
#define portMEMORY_BARRIER()   __asm__ volatile ( "" ::: "memory" )

#ifdef __cplusplus
    }
#endif

#endif /* PORTMACRO_H */
