# ============================================================================
# Professional RISC-V SoC Firmware Makefile
# ============================================================================

# Toolchain
PREFIX   ?= riscv64-unknown-elf
CC       = $(PREFIX)-gcc
AS       = $(PREFIX)-gcc
LD       = $(PREFIX)-ld
OBJCOPY  = $(PREFIX)-objcopy
OBJDUMP  = $(PREFIX)-objdump
SIZE     = $(PREFIX)-size

# Build Directories
BUILD_DIR = build
DRV_DIR   = drivers
LIB_DIR   = lib
SOFT_DIR  = software
TEST_DIR  = tests
BOOT_DIR  = boot

# Architecture
ARCH     = -march=rv32i -mabi=ilp32
CFLAGS   = $(ARCH) -Os -Wall -ffreestanding -nostdlib
CFLAGS  += -I$(DRV_DIR)/inc -I$(LIB_DIR)/inc
ASFLAGS  = $(ARCH) -c
LDFLAGS  = -nostdlib -m elf32lriscv

# Common Objects (HAL + Startup)
CRT0     = $(BUILD_DIR)/crt0.o
DRV_SRCS = $(wildcard $(DRV_DIR)/src/*.c)
DRV_OBJS = $(patsubst $(DRV_DIR)/src/%.c,$(BUILD_DIR)/drivers/%.o,$(DRV_SRCS))

LIBGCC   = $(shell $(CC) $(ARCH) -print-libgcc-file-name)

.PHONY: all clean software integration_test boot_rom

all: software

clean:
	rm -rf $(BUILD_DIR)

# Ensure build directories exist
$(BUILD_DIR)/%/:
	mkdir -p $@

# Rules for object files
$(BUILD_DIR)/crt0.o: $(LIB_DIR)/src/crt0.S
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/drivers/%.o: $(DRV_DIR)/src/%.c
	@mkdir -p $(BUILD_DIR)/drivers
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SOFT_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(BOOT_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Target: Main Software
software: $(BUILD_DIR)/main.hex $(BUILD_DIR)/main.lst
	@echo "Build complete: $(BUILD_DIR)/main.hex"

$(BUILD_DIR)/main.elf: $(BUILD_DIR)/main.o $(CRT0) $(DRV_OBJS)
	$(LD) $(LDFLAGS) -T $(LIB_DIR)/scripts/linker.ld -o $@ $^ $(LIBGCC)

# Target: Integration Test
integration_test: $(BUILD_DIR)/integration_test_boot.hex $(BUILD_DIR)/integration_test_boot.lst
	@echo "Integration Test Build complete."

$(BUILD_DIR)/integration_test_boot.elf: $(BUILD_DIR)/integration_test.o $(CRT0) $(DRV_OBJS)
	$(LD) $(LDFLAGS) -T $(LIB_DIR)/scripts/boot_linker.ld -o $@ $^ $(LIBGCC)

# Target: Boot ROM
boot_rom: $(BUILD_DIR)/boot_rom.hex $(BUILD_DIR)/boot_rom.lst
	@echo "Boot ROM Build complete."

$(BUILD_DIR)/boot_rom.elf: $(BUILD_DIR)/boot_rom.o $(CRT0) $(DRV_OBJS)
	$(LD) $(LDFLAGS) -T $(LIB_DIR)/scripts/boot_linker.ld -o $@ $^ $(LIBGCC)

# Generic rules for HEX and LST
%.hex: %.elf
	$(OBJCOPY) -O verilog --verilog-data-width 4 $< $@

%.lst: %.elf
	$(OBJDUMP) -d -S $< > $@
	$(SIZE) $<
