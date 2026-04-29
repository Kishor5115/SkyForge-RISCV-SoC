

.section .text.init

.global _start

.type _start, @function

_start:
    j _reset_entry

    .org 0x10
_irq_vector:
    j _irq_entry

_reset_entry:
    /* ── Step 1: Zero all general-purpose registers ──────────── */
    addi x1,  zero, 0
    addi x2,  zero, 0
    addi x3,  zero, 0
    addi x4,  zero, 0
    addi x5,  zero, 0
    addi x6,  zero, 0
    addi x7,  zero, 0
    addi x8,  zero, 0
    addi x9,  zero, 0
    addi x10, zero, 0
    addi x11, zero, 0
    addi x12, zero, 0
    addi x13, zero, 0
    addi x14, zero, 0
    addi x15, zero, 0
    addi x16, zero, 0
    addi x17, zero, 0
    addi x18, zero, 0
    addi x19, zero, 0
    addi x20, zero, 0
    addi x21, zero, 0
    addi x22, zero, 0
    addi x23, zero, 0
    addi x24, zero, 0
    addi x25, zero, 0
    addi x26, zero, 0
    addi x27, zero, 0
    addi x28, zero, 0
    addi x29, zero, 0
    addi x30, zero, 0
    addi x31, zero, 0    

    /* ── Step 2: Load Global Pointer ───────────────────────────── */
.option push
.option norelax
    la  gp,__global_pointer$
.option pop

    /* ── Step 3: Load Stack Pointer ─────────────────────────────── */
    la  sp, _stack_top

    /* ── Step 4: zero the .bss section ─────────────────────────────── */
    la  t0, _bss_start
    la  t1, _bss_end
bss_loop :
    bge  t0, t1, bss_done
    sw   zero, 0(t0)
    addi t0, t0, 4
    j    bss_loop
bss_done:

    /* ── Step 5: Initialize IRQ mask and peripheral IRQ enables ───────── */
    call irq_init

    /* ── Step 6: Call main() ─────────────────────────────── */
    call main

    /* If main() returns, loop indefinitely */
_halt:
    j _halt

_irq_entry:
    addi sp, sp, -64

    sw ra,  0(sp)
    sw t0,  4(sp)
    sw t1,  8(sp)
    sw t2, 12(sp)
    sw t3, 16(sp)
    sw t4, 20(sp)
    sw t5, 24(sp)
    sw t6, 28(sp)
    sw a0, 32(sp)
    sw a1, 36(sp)
    sw a2, 40(sp)
    sw a3, 44(sp)
    sw a4, 48(sp)
    sw a5, 52(sp)
    sw a6, 56(sp)
    sw a7, 60(sp)

    /* getq a0, q1: q1 contains pending IRQ mask with ENABLE_IRQ_QREGS=1 */
    .insn r 0x0B, 0, 0, a0, x1, x0
    call irq_dispatch

    lw ra,  0(sp)
    lw t0,  4(sp)
    lw t1,  8(sp)
    lw t2, 12(sp)
    lw t3, 16(sp)
    lw t4, 20(sp)
    lw t5, 24(sp)
    lw t6, 28(sp)
    lw a0, 32(sp)
    lw a1, 36(sp)
    lw a2, 40(sp)
    lw a3, 44(sp)
    lw a4, 48(sp)
    lw a5, 52(sp)
    lw a6, 56(sp)
    lw a7, 60(sp)

    addi sp, sp, 64

    .insn r 0x0B, 0, 2, x0, x0, x0