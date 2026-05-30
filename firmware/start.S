/* PicoRV32 Startup & IRQ Wrapper
 * Reset vector at 0x00010000, IRQ vector at 0x00010010
 * NO mret/mtvec/mcause — PicoRV32 custom IRQ ABI only
 *
 * PicoRV32 custom instructions use .insn r with opcode 0x0B.
 * The assembler doesn't recognise q0-q3 register names, so we
 * substitute the standard xN register whose index matches:
 *   q0 -> x0 (index 0)   q1 -> x1 (index 1)
 *   q2 -> x2 (index 2)   q3 -> x3 (index 3)
 */

#define picorv32_getq_insn(rd, qs)   .insn r 0x0B, 0, 0, rd, qs, x0
#define picorv32_setq_insn(qd, rs)   .insn r 0x0B, 0, 1, qd, rs, x0
#define picorv32_retirq_insn()       .insn r 0x0B, 0, 2, x0, x0, x0
#define picorv32_maskirq_insn(rd,rs) .insn r 0x0B, 0, 3, rd, rs, x0

    .equ CTX_SIZE, 144
    .equ CTX_RA, 0
    .equ CTX_GP, 4
    .equ CTX_TP, 8
    .equ CTX_T0, 12
    .equ CTX_T1, 16
    .equ CTX_T2, 20
    .equ CTX_S0, 24
    .equ CTX_S1, 28
    .equ CTX_A0, 32
    .equ CTX_A1, 36
    .equ CTX_A2, 40
    .equ CTX_A3, 44
    .equ CTX_A4, 48
    .equ CTX_A5, 52
    .equ CTX_A6, 56
    .equ CTX_A7, 60
    .equ CTX_S2, 64
    .equ CTX_S3, 68
    .equ CTX_S4, 72
    .equ CTX_S5, 76
    .equ CTX_S6, 80
    .equ CTX_S7, 84
    .equ CTX_S8, 88
    .equ CTX_S9, 92
    .equ CTX_S10, 96
    .equ CTX_S11, 100
    .equ CTX_T3, 104
    .equ CTX_T4, 108
    .equ CTX_T5, 112
    .equ CTX_T6, 116
    .equ CTX_Q0, 120
    .equ CTX_Q1, 124
    .equ CTX_Q2, 128
    .equ CTX_Q3, 132
    .equ CTX_XNEST, 136

    .section .text.reset, "ax"
    .global _start
    .align 2
_start:
    lui x1, 0
    lui x2, 0
    lui x3, 0
    j   _init

    .section .text.irq, "ax"
    .global _irq_handler
    .align 2
_irq_handler:
    addi sp, sp, -CTX_SIZE

    sw ra, CTX_RA(sp)
    sw gp, CTX_GP(sp)
    sw tp, CTX_TP(sp)
    sw t0, CTX_T0(sp)
    sw t1, CTX_T1(sp)
    sw t2, CTX_T2(sp)
    sw s0, CTX_S0(sp)
    sw s1, CTX_S1(sp)
    sw a0, CTX_A0(sp)
    sw a1, CTX_A1(sp)
    sw a2, CTX_A2(sp)
    sw a3, CTX_A3(sp)
    sw a4, CTX_A4(sp)
    sw a5, CTX_A5(sp)
    sw a6, CTX_A6(sp)
    sw a7, CTX_A7(sp)
    sw s2, CTX_S2(sp)
    sw s3, CTX_S3(sp)
    sw s4, CTX_S4(sp)
    sw s5, CTX_S5(sp)
    sw s6, CTX_S6(sp)
    sw s7, CTX_S7(sp)
    sw s8, CTX_S8(sp)
    sw s9, CTX_S9(sp)
    sw s10, CTX_S10(sp)
    sw s11, CTX_S11(sp)
    sw t3, CTX_T3(sp)
    sw t4, CTX_T4(sp)
    sw t5, CTX_T5(sp)
    sw t6, CTX_T6(sp)

    picorv32_getq_insn(t0, x0)
    sw t0, CTX_Q0(sp)
    picorv32_getq_insn(t0, x1)
    sw t0, CTX_Q1(sp)
    picorv32_getq_insn(t0, x2)
    sw t0, CTX_Q2(sp)
    picorv32_getq_insn(t0, x3)
    sw t0, CTX_Q3(sp)

    la  t0, xCriticalNesting
    lw  t1, 0(t0)
    sw  t1, CTX_XNEST(sp)

    la  t0, pxCurrentTCB
    lw  t1, 0(t0)
    sw  sp, 0(t1)

    /* Check if timer IRQ (bit 3) is pending. */
    lw   t0, CTX_Q1(sp)
    andi t0, t0, 0x08
    beqz t0, _irq_restore

    call xPortSysTickHandler
    mv  t0, a0

    la  t1, xPortYieldRequired
    lw  t2, 0(t1)
    or  t0, t0, t2
    sw  zero, 0(t1)

    beqz t0, _irq_restore
    call vTaskSwitchContext

_irq_restore:
    la  t0, pxCurrentTCB
    lw  t1, 0(t0)
    lw  sp, 0(t1)

    la  t0, xCriticalNesting
    lw  t1, CTX_XNEST(sp)
    sw  t1, 0(t0)

    lw t0, CTX_Q3(sp)
    picorv32_setq_insn(x3, t0)
    lw t0, CTX_Q2(sp)
    picorv32_setq_insn(x2, t0)
    lw t0, CTX_Q1(sp)
    picorv32_setq_insn(x1, t0)
    lw t0, CTX_Q0(sp)
    picorv32_setq_insn(x0, t0)

    lw ra, CTX_RA(sp)
    lw gp, CTX_GP(sp)
    lw tp, CTX_TP(sp)
    lw t0, CTX_T0(sp)
    lw t1, CTX_T1(sp)
    lw t2, CTX_T2(sp)
    lw s0, CTX_S0(sp)
    lw s1, CTX_S1(sp)
    lw a0, CTX_A0(sp)
    lw a1, CTX_A1(sp)
    lw a2, CTX_A2(sp)
    lw a3, CTX_A3(sp)
    lw a4, CTX_A4(sp)
    lw a5, CTX_A5(sp)
    lw a6, CTX_A6(sp)
    lw a7, CTX_A7(sp)
    lw s2, CTX_S2(sp)
    lw s3, CTX_S3(sp)
    lw s4, CTX_S4(sp)
    lw s5, CTX_S5(sp)
    lw s6, CTX_S6(sp)
    lw s7, CTX_S7(sp)
    lw s8, CTX_S8(sp)
    lw s9, CTX_S9(sp)
    lw s10, CTX_S10(sp)
    lw s11, CTX_S11(sp)
    lw t3, CTX_T3(sp)
    lw t4, CTX_T4(sp)
    lw t5, CTX_T5(sp)
    lw t6, CTX_T6(sp)

    addi sp, sp, CTX_SIZE
    picorv32_retirq_insn()

    .section .text
    .global vPortYield
    .align 2
vPortYield:
    addi sp, sp, -CTX_SIZE

    sw ra, CTX_RA(sp)
    sw gp, CTX_GP(sp)
    sw tp, CTX_TP(sp)
    sw t0, CTX_T0(sp)
    sw t1, CTX_T1(sp)
    sw t2, CTX_T2(sp)
    sw s0, CTX_S0(sp)
    sw s1, CTX_S1(sp)
    sw a0, CTX_A0(sp)
    sw a1, CTX_A1(sp)
    sw a2, CTX_A2(sp)
    sw a3, CTX_A3(sp)
    sw a4, CTX_A4(sp)
    sw a5, CTX_A5(sp)
    sw a6, CTX_A6(sp)
    sw a7, CTX_A7(sp)
    sw s2, CTX_S2(sp)
    sw s3, CTX_S3(sp)
    sw s4, CTX_S4(sp)
    sw s5, CTX_S5(sp)
    sw s6, CTX_S6(sp)
    sw s7, CTX_S7(sp)
    sw s8, CTX_S8(sp)
    sw s9, CTX_S9(sp)
    sw s10, CTX_S10(sp)
    sw s11, CTX_S11(sp)
    sw t3, CTX_T3(sp)
    sw t4, CTX_T4(sp)
    sw t5, CTX_T5(sp)
    sw t6, CTX_T6(sp)

    picorv32_setq_insn(x0, ra)
    picorv32_getq_insn(t0, x0)
    sw t0, CTX_Q0(sp)
    picorv32_getq_insn(t0, x1)
    sw t0, CTX_Q1(sp)
    picorv32_getq_insn(t0, x2)
    sw t0, CTX_Q2(sp)
    picorv32_getq_insn(t0, x3)
    sw t0, CTX_Q3(sp)

    la  t0, xCriticalNesting
    lw  t1, 0(t0)
    sw  t1, CTX_XNEST(sp)

    la  t0, pxCurrentTCB
    lw  t1, 0(t0)
    sw  sp, 0(t1)

    call vTaskSwitchContext

    la  t0, pxCurrentTCB
    lw  t1, 0(t0)
    lw  sp, 0(t1)

    la  t0, xCriticalNesting
    lw  t1, CTX_XNEST(sp)
    sw  t1, 0(t0)

    lw t0, CTX_Q3(sp)
    picorv32_setq_insn(x3, t0)
    lw t0, CTX_Q2(sp)
    picorv32_setq_insn(x2, t0)
    lw t0, CTX_Q1(sp)
    picorv32_setq_insn(x1, t0)
    lw t0, CTX_Q0(sp)
    picorv32_setq_insn(x0, t0)

    lw ra, CTX_RA(sp)
    lw gp, CTX_GP(sp)
    lw tp, CTX_TP(sp)
    lw t0, CTX_T0(sp)
    lw t1, CTX_T1(sp)
    lw t2, CTX_T2(sp)
    lw s0, CTX_S0(sp)
    lw s1, CTX_S1(sp)
    lw a0, CTX_A0(sp)
    lw a1, CTX_A1(sp)
    lw a2, CTX_A2(sp)
    lw a3, CTX_A3(sp)
    lw a4, CTX_A4(sp)
    lw a5, CTX_A5(sp)
    lw a6, CTX_A6(sp)
    lw a7, CTX_A7(sp)
    lw s2, CTX_S2(sp)
    lw s3, CTX_S3(sp)
    lw s4, CTX_S4(sp)
    lw s5, CTX_S5(sp)
    lw s6, CTX_S6(sp)
    lw s7, CTX_S7(sp)
    lw s8, CTX_S8(sp)
    lw s9, CTX_S9(sp)
    lw s10, CTX_S10(sp)
    lw s11, CTX_S11(sp)
    lw t3, CTX_T3(sp)
    lw t4, CTX_T4(sp)
    lw t5, CTX_T5(sp)
    lw t6, CTX_T6(sp)

    addi sp, sp, CTX_SIZE
    picorv32_retirq_insn()

    .align 2
_init:
    lui x4,0
    lui x5,0
    lui x6,0
    lui x7,0
    lui x8,0
    lui x9,0
    lui x10,0
    lui x11,0
    lui x12,0
    lui x13,0
    lui x14,0
    lui x15,0
    lui x16,0
    lui x17,0
    lui x18,0
    lui x19,0
    lui x20,0
    lui x21,0
    lui x22,0
    lui x23,0
    lui x24,0
    lui x25,0
    lui x26,0
    lui x27,0
    lui x28,0
    lui x29,0
    lui x30,0
    lui x31,0

    la  sp, __stack_top

    la  t0, __bss_start
    la  t1, __bss_end
    beq t0, t1, _bss_done
_bss_loop:
    sw  zero, 0(t0)
    addi t0, t0, 4
    blt t0, t1, _bss_loop
_bss_done:

    /* Keep all IRQ sources masked during C/RTOS initialization.
     * xPortStartFirstTask() will unmask the timer IRQ right before
     * transferring control to the first task context. */
    li  t0, 0xFFFFFFFF
    picorv32_maskirq_insn(zero, t0)

    call main
_halt:
    j _halt
