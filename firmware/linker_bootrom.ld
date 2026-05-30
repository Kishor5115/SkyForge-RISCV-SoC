/* ──────────────────────────────────────────────────────────────────
 * Linker Script — BootROM + SRAM (PicoRV32 SoC)
 *
 * BootROM is used for .text/.rodata (CPU reset vector @0x0, IRQ vector @0x10).
 * SRAM is used for .data/.bss/heap/stack.
 *
 * Notes:
 * - BootROM size is configurable in RTL; in the integration testbench it is
 *   enlarged (BOOTROM_ADDR_WIDTH=13 -> 8KB). This script defaults to 8KB.
 * - Startup code: lib/src/crt0.S
 * ────────────────────────────────────────────────────────────────── */

OUTPUT_FORMAT("elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)

BOOTROM_SIZE = 8K;
SRAM_SIZE    = 16K;

MEMORY
{
    BOOTROM (rx)  : ORIGIN = 0x00000000, LENGTH = BOOTROM_SIZE
    SRAM    (rwx) : ORIGIN = 0x00010000, LENGTH = SRAM_SIZE
}

/* Stack at top of SRAM */
_stack_top = ORIGIN(SRAM) + LENGTH(SRAM) - 4;

SECTIONS
{
    /* ── Reset + IRQ vectors and early init ───────────────────── */
    .text.init ORIGIN(BOOTROM) :
    {
        KEEP(*(.text.init))
    } > BOOTROM

    /* ── Code in BootROM ───────────────────────────────────────── */
    .text : ALIGN(4)
    {
        *(.text .text.*)
    } > BOOTROM

    /* ── Read-only data in BootROM ─────────────────────────────── */
    .rodata : ALIGN(4)
    {
        *(.rodata .rodata.*)
        *(.srodata .srodata.*)
    } > BOOTROM

    /* ── Initialized data in SRAM (loaded from BootROM) ────────── */
    .data : ALIGN(4)
    {
        _data_start = .;
        __data_start = .;
        *(.data .data.*)
        *(.sdata .sdata.*)
        _data_end = .;
        __data_end = .;
    } > SRAM AT> BOOTROM

    /* RISC-V ABI global pointer for small data access */
    PROVIDE(__global_pointer$ = __data_start + 0x800);

    _data_lma = LOADADDR(.data);
    __data_lma = LOADADDR(.data);

    /* ── BSS in SRAM ───────────────────────────────────────────── */
    .bss (NOLOAD) : ALIGN(4)
    {
        _bss_start = .;
        __bss_start = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)
        *(COMMON)
        _bss_end = .;
        __bss_end = .;
    } > SRAM

    /* ── Heap (optional) ───────────────────────────────────────── */
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
