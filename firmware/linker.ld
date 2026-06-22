/* ──────────────────────────────────────────────────────────────────
 * Linker Script — PicoRV32 SoC  (v2: Execute-In-Place from external flash)
 *
 * Memory Map:
 *   Flash XIP : 0x40010000 – 0x40FFFFFF  (~16 MB, code + rodata, read-only)
 *   SRAM      : 0x00010000 – 0x00013FFF  (16 KB, data + bss + heap + stack)
 *
 * .text/.rodata execute in place from external QSPI flash (cached by the
 * 1 KB I-Cache). .data is stored in flash (LMA) and copied to SRAM (VMA) by
 * start.S at boot. .bss/heap/stack live in SRAM.
 *
 * Boot path: CPU resets to Boot ROM @0x0 -> Boot ROM enables flash XIP and
 * jumps to 0x40010000 (this image's reset vector).
 *
 * PROGADDR_RESET (effective) = 0x40010000   (Boot ROM jump target)
 * PROGADDR_IRQ               = 0x40010010   (IRQ vector, fixed by HW param)
 * Stack pointer              = 0x00013FFC   (top of 16 KB SRAM, grows down)
 * ────────────────────────────────────────────────────────────────── */

OUTPUT_FORMAT("elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)

FLASH_ORIGIN = 0x40010000;
FLASH_LENGTH = 16M - 64K;          /* 0x40010000 .. 0x40FFFFFF */
SRAM_ORIGIN  = 0x00010000;
SRAM_LENGTH  = 16K;

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x40010000, LENGTH = 16M - 64K
    SRAM  (rwx) : ORIGIN = 0x00010000, LENGTH = 16K
}

__stack_top = ORIGIN(SRAM) + LENGTH(SRAM) - 4;   /* 0x00013FFC */

SECTIONS
{
    /* ── Reset vector at flash XIP base ─────────────────────────── */
    .text.reset 0x40010000 :
    {
        KEEP(*(.text.reset))
    } > FLASH

    /* ── IRQ vector at fixed offset 0x10 ────────────────────────── */
    .text.irq 0x40010010 :
    {
        KEEP(*(.text.irq))
    } > FLASH

    /* ── Code (execute-in-place from flash) ─────────────────────── */
    .text : ALIGN(4)
    {
        *(.text .text.*)
    } > FLASH

    /* ── Read-only data (in flash) ──────────────────────────────── */
    .rodata : ALIGN(4)
    {
        *(.rodata .rodata.*)
        *(.srodata .srodata.*)
    } > FLASH

    /* ── Initialized data: VMA in SRAM, LMA in flash ────────────── */
    .data : ALIGN(4)
    {
        __data_start = .;
        *(.data .data.*)
        *(.sdata .sdata.*)
        . = ALIGN(4);
        __data_end = .;
    } > SRAM AT> FLASH

    /* LMA of .data in flash — source for the start.S copy loop */
    __data_lma = LOADADDR(.data);

    /* RISC-V ABI global pointer for small data access */
    PROVIDE(__global_pointer$ = __data_start + 0x800);

    /* ── BSS (zero-initialized, in SRAM) ────────────────────────── */
    .bss (NOLOAD) : ALIGN(4)
    {
        __bss_start = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > SRAM

    /* ── Heap (used by FreeRTOS heap_4) ─────────────────────────── */
    .heap (NOLOAD) : ALIGN(4)
    {
        __heap_start = .;
        . = ALIGN(4);
        __heap_end = .;
    } > SRAM

    _end = .;
    PROVIDE(end = .);

    /DISCARD/ :
    {
        *(.comment)
        *(.note.*)
        *(.eh_frame*)
    }
}
