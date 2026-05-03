/* ================================================================
   boot_linker.ld — ASIC Boot ROM Linker Script

   Memory Layout for Boot ROM:
   
   Boot ROM  0x00000000┌──────────────────────┐ ← CPU reset vector
                       │  .init  (_start)     │   first instruction
                       │  .text  (boot code)  │
                       │  .rodata (strings)   │
                       │  .data  (globals)    │
                       │  .bss   (zeroed)     │
            0x00001FFF └──────────────────────┘ ← 8KB ROM limit

   SRAM     0x00010000 ┌──────────────────────┐ ← Application target
                       │  (loaded from flash) │
            0x00017FFF └──────────────────────┘ ← 32KB SRAM limit

   Peripherals:
     0x20000000  UART
     0x20001000  Timer
     0x20002000  GPIO
     0x20003000  SPI Master
     0x20004000  Debug Mailbox
     0x40000000  Flash Controller
   ================================================================ */

OUTPUT_ARCH("riscv")

ENTRY(_start)

MEMORY
{
    /* Boot ROM: 8KB read-only (initialized via $readmemh in simulation) */
    ROM  (rx)  : ORIGIN = 0x00000000, LENGTH = 8K
    
    /* Stack in SRAM (boot firmware uses minimal stack) */
    SRAM (rwx) : ORIGIN = 0x00010000, LENGTH = 32K
}

SECTIONS
{
    /* Boot entry point — must be at exactly 0x00000000 */
    .init : ALIGN(4)
    {
        KEEP(*(.text.init))
    } > ROM

    /* Boot code */
    .text : ALIGN(4)
    {
        _text_start = .;
        *(.text*)
        _text_end = .;
    } > ROM

    /* Read-only data (strings, lookup tables) */
    .rodata : ALIGN(4)
    {
        *(.rodata*)
        *(.srodata*)
    } > ROM

    /* Global pointer for GP-relative addressing */
    PROVIDE(__global_pointer$ = . + 0x800);

    /* Initialized data — stays in ROM for boot firmware */
    .data : ALIGN(4)
    {
        _data_start = .;
        *(.data*)
        *(.sdata*)
        _data_end = .;
    } > ROM

    /* BSS in SRAM (zeroed by startup) */
    .bss (NOLOAD) : ALIGN(4)
    {
        _bss_start = .;
        *(.bss*)
        *(.sbss*)
        *(COMMON)
        _bss_end = .;
    } > SRAM

    /* Stack at top of SRAM (1KB for boot firmware) */
    _stack_top = ORIGIN(SRAM) + LENGTH(SRAM);

    /* ROM size check */
    ASSERT(_data_end <= ORIGIN(ROM) + LENGTH(ROM),
        "ERROR: Boot firmware exceeds 8KB ROM limit!")

    /DISCARD/ :
    {
        *(.eh_frame)
        *(.eh_frame_hdr)
        *(.riscv.attributes)
        *(.comment)
    }
}
