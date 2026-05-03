/* ================================================================
   linker.ld — Custom RISC-V SoC
   
   Complete Memory Picture

   SRAM 0x00010000┌──────────────────────┐ ← CPU fetches first instruction from Boot ROM
                  │  .init  (_start)     │   then jumps here
                  │  .text  (code)       │
                  │  .rodata (constants) │
                  │  .data  (globals)    │ ← pre-loaded by $readmemh(), no copy
                  │  .sdata              │
                  │  .bss   (zeroed)     │ ← startup.s zeros this at boot
                  │  .sbss               │
                  │  heap ↑  (2KB)       │
                  │                      │
                  │   ~~~~ free ~~~~     │
                  │                      │
                  │  stack ↓             │ ← grows down from _stack_top
       0x00018000 └──────────────────────┘ ← _stack_top

PERIPH 0x20000000  [ UART  registers ]    ← not memory, pointer access only
       0x20001000  [ Timer registers ]
       0x20002000  [ GPIO  registers ]
       0x20003000  [ SPI   registers ]    
       0x20004000  [ Debug registers ]
       0x40000000  [ Flash registers ]    

   ================================================================ */


OUTPUT_ARCH("riscv")

ENTRY(_start)

MEMORY
{
    SRAM (rwxa) : ORIGIN = 0x00010000, LENGTH = 32K
}

PROVIDE(_uart_base   = 0x20000000);
PROVIDE(_timer_base  = 0x20001000);
PROVIDE(_gpio_base   = 0x20002000);
PROVIDE(_spi_base    = 0x20003000);
PROVIDE(_debug_base  = 0x20004000);
PROVIDE(_flash_base  = 0x40000000);


SECTIONS
{
     .init :
     {
         . = ALIGN(4);
         KEEP(*(.text.init))  
     } > SRAM

      .text :
     {

         . = ALIGN(4);
         _text_start = . ;

         *(.text*)

         . = ALIGN(4);
         _text_end = . ;
     } > SRAM

      .rodata :
      {
         . = ALIGN(4);
         *(.rodata*)
         *(.srodata*)
         . = ALIGN(4);
      } > SRAM

      PROVIDE(__global_pointer$ = . + 0x800);

      .data :
      {
         . = ALIGN(4);
         _data_start = . ;

         *(.data*)
         *(.sdata*)

         . = ALIGN(4);
         _data_end = . ;
      } > SRAM

      .bss :
      {
         . = ALIGN(4);
         _bss_start = . ;

         *(.bss*)
         *(.sbss*)
         *(COMMON)

         . = ALIGN(4);
         _bss_end = . ;
      } > SRAM

      .heap :
      {
         . = ALIGN(4);
         _heap_start = . ;
         . += 0x2000;
         _heap_end = . ;
      } > SRAM

      _stack_top = ORIGIN(SRAM) + LENGTH(SRAM);

      ASSERT(_heap_end <= _stack_top - 0x1000,
         "ERROR : SRAM overflow - reduce heap or code size (need 4KB min stack)")
      
      /DISCARD/ : 
      {
         *(.eh_frame)
         *(.eh_frame_hdr)
         *(.riscv.attributes)
         *(.comment)
      }
}  
