/* ──────────────────────────────────────────────────────────────────
 * Linker Script — PicoRV32 SoC
 *
 * Memory Map:
 *   Boot ROM : 0x00000000 – 0x000000FF  (256 B, read-only)
 *   SRAM     : 0x00010000 – 0x00013FFF  (16 KB, code + data)
 *
 * PROGADDR_RESET = 0x00010000  (first SRAM word)
 * PROGADDR_IRQ   = 0x00010010  (IRQ vector, fixed by HW)
 * Stack pointer  = 0x00013FFC  (top of SRAM, grows down)
 * ────────────────────────────────────────────────────────────────── */

OUTPUT_FORMAT("elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
    SRAM (rwx) : ORIGIN = 0x00010000, LENGTH = 16K
}

__stack_top = 0x00013FFC;

SECTIONS
{
    /* ── Reset vector at SRAM base ──────────────────────────────── */
    .text.reset 0x00010000 :
    {
        KEEP(*(.text.reset))
    } > SRAM

    /* ── IRQ vector at fixed offset 0x10 ────────────────────────── */
    .text.irq 0x00010010 :
    {
        KEEP(*(.text.irq))
    } > SRAM

    /* ── Code ───────────────────────────────────────────────────── */
    .text : ALIGN(4)
    {
        *(.text .text.*)
    } > SRAM

    /* ── Read-only data ─────────────────────────────────────────── */
    .rodata : ALIGN(4)
    {
        *(.rodata .rodata.*)
        *(.srodata .srodata.*)
    } > SRAM

    /* ── Initialized data ───────────────────────────────────────── */
    .data : ALIGN(4)
    {
        __data_start = .;
        *(.data .data.*)
        *(.sdata .sdata.*)
        __data_end = .;
    } > SRAM

    /* RISC-V ABI global pointer for small data access */
    PROVIDE(__global_pointer$ = __data_start + 0x800);

    /* ── BSS (zero-initialized) ─────────────────────────────────── */
    .bss (NOLOAD) : ALIGN(4)
    {
        __bss_start = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)
        *(COMMON)
        __bss_end = .;
    } > SRAM

    /* ── Heap (used by FreeRTOS heap_4) ─────────────────────────── */
    .heap (NOLOAD) : ALIGN(4)
    {
        __heap_start = .;
        . = ALIGN(4);
        __heap_end = .;
    } > SRAM

    /* ── Stack guard ────────────────────────────────────────────── */
    _end = .;
    PROVIDE(end = .);

    /DISCARD/ :
    {
        *(.comment)
        *(.note.*)
        *(.eh_frame*)
    }
}
