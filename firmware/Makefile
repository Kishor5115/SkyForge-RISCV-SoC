# Select which "game" (firmware app) to build.
# 
# - Default is the current Breakout implementation in main.c
# - To add another game: create firmware/games/<name>.c with its own main()
#   and build with: make GAME=<name>
GAME    ?= breakout

# ============================================================================
# Firmware Makefile for RISC-V SoC 
# ============================================================================

# Toolchain prefix
PREFIX   = riscv64-unknown-elf

# Tool Variables
CC 		 = $(PREFIX)-gcc
AS 		 = $(PREFIX)-as
LD 		 = $(PREFIX)-ld
OBJCOPY  = $(PREFIX)-objcopy
OBJDUMP  = $(PREFIX)-objdump	
SIZE 	 = $(PREFIX)-size

# Architecture flags - must match the core configuration
# march - Machine Architecture (ISA - Instruction Set Architecture)
# mabi - Machine ABI (Application Binary Interface)
ARCH     = -march=rv32i -mabi=ilp32 

# Compiler flags

CFLAGS   = $(ARCH) -Os -Wall -ffreestanding -nostdlib -c
ASFLAGS  = $(ARCH) 
# Link flags
LIBGCC   = $(shell $(CC) $(ARCH) -print-libgcc-file-name)
LDFLAGS  = -T linker.ld -nostdlib -m elf32lriscv

# Source files
SRCS_S   = start.S
ifeq ($(GAME),breakout)
SRCS_C  = main.c irq_handler.c
else
SRCS_C  = games/$(GAME).c irq_handler.c
endif
OBJS     = start.o $(patsubst %.c,%.o,$(SRCS_C))

# Output files
TARGET   = firmware

# ============================================================================
# Build Rules
# ============================================================================

all: $(TARGET).hex $(TARGET).lst
		@echo "Build complete!"
		@$(SIZE) $(TARGET).elf

# Assemble the startup code
start.o: start.S
		$(AS) $(ASFLAGS) -o $@ $<

# Compile the C source files
%.o: %.c
		$(CC) $(CFLAGS) -o $@ $<

# Link the object files into an executable
$(TARGET).elf: $(OBJS)
		$(LD) $(LDFLAGS) -o $@ $^ $(LIBGCC)			 

# Generate HEX for $readmemh()
$(TARGET).hex: $(TARGET).elf
		$(OBJCOPY) -O verilog --verilog-data-width 4 $< $@

# Generate disassembly listing for debugging
$(TARGET).lst: $(TARGET).elf
		$(OBJDUMP) -d -S $< > $@


# ============================================================================
# Utility Targets
# ============================================================================

# Show memory usage
size: $(TARGET).elf
		$(SIZE) $<

# Verify _start is at address 0
check: $(TARGET).elf
		@echo "=== Entry point check ==="
		@$(OBJDUMP) -d $< | head -20
		@echo ""
		@echo "=== Symbol table ==="
		@$(OBJDUMP) -t $< | grep -E "(_start|main|_stack_top|_bss|__global)"

clean: 
		rm -f *.o games/*.o $(TARGET).elf $(TARGET).hex $(TARGET).lst

.PHONY: all clean size check


