# ──────────────────────────────────────────────────────────────────
# Firmware Makefile — PicoRV32 FreeRTOS
# Usage:  make            — build firmware.elf + firmware.hex
#         make clean      — remove build artifacts
# ──────────────────────────────────────────────────────────────────

PREFIX     := riscv64-unknown-elf-
CC         := $(PREFIX)gcc
AS         := $(PREFIX)gcc
LD         := $(PREFIX)gcc
OBJCOPY    := $(PREFIX)objcopy
OBJDUMP    := $(PREFIX)objdump
SIZE       := $(PREFIX)size

# ── FreeRTOS paths ───────────────────────────────────────────────
FREERTOS_DIR   := FreeRTOS-Kernel
FREERTOS_SRC   := $(FREERTOS_DIR)/
FREERTOS_MEM   := $(FREERTOS_DIR)/portable/MemMang/

# ── Custom PicoRV32 port (NOT the standard RISC-V port) ─────────
PICORV32_PORT  := port/

# ── Minimal libc (toolchain has no newlib) ───────────────────────
LIBC_DIR       := libc/

# ── Compiler / Linker flags ─────────────────────────────────────
ARCH_FLAGS := -march=rv32im -mabi=ilp32
CFLAGS     := $(ARCH_FLAGS) -Os -g -Wall -Wextra \
              -ffreestanding -ffunction-sections -fdata-sections \
              -isystem $(LIBC_DIR) \
              -I. \
              -I$(FREERTOS_SRC)/include \
              -I$(PICORV32_PORT)

ASFLAGS    := $(ARCH_FLAGS) -g

LDFLAGS    := $(ARCH_FLAGS) -nostartfiles -nostdlib -T linker.ld \
              -Wl,--gc-sections -Wl,-Map,firmware.map -lgcc

# ── Application selection ────────────────────────────────────────
# Default app:
#   APP=firmware, APP_SRC=main.c
# Example alternate app:
#   make APP=test_gpio APP_SRC=tests/test_gpio.c
APP      ?= firmware
APP_SRC  ?= main.c

# ── Sources ──────────────────────────────────────────────────────
C_SRCS := \
    $(APP_SRC) \
    $(LIBC_DIR)/libc.c \
    $(FREERTOS_SRC)/tasks.c \
    $(FREERTOS_SRC)/queue.c \
    $(FREERTOS_SRC)/list.c \
    $(FREERTOS_MEM)/heap_4.c \
    $(PICORV32_PORT)/port.c

ASM_SRCS := start.S

# ── Objects ──────────────────────────────────────────────────────
BUILD_DIR := build
C_OBJS   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(C_SRCS)))
ASM_OBJS := $(patsubst %.S,$(BUILD_DIR)/%.o,$(notdir $(ASM_SRCS)))
OBJS     := $(ASM_OBJS) $(C_OBJS)

# VPATH for finding sources in subdirectories
VPATH := . $(FREERTOS_SRC) $(FREERTOS_MEM) $(PICORV32_PORT) $(LIBC_DIR)

TARGET := $(APP)

.PHONY: all clean

all: $(TARGET).elf $(TARGET).hex $(TARGET).lst
	@$(SIZE) $(TARGET).elf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.S | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O verilog $< $@

$(TARGET).lst: $(TARGET).elf
	$(OBJDUMP) -d -S $< > $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET).lst $(TARGET).map
	@echo "Cleaned."
