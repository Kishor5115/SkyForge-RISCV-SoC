# ──────────────────────────────────────────────────────────────────
# Firmware Makefile — PicoRV32 SoC Firmware
# Usage:  make            — build firmware.elf + firmware.hex (default: FW_MODE=freertos)
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

# ── Bare-metal drivers (UART/GPIO/SPI/TIMER/IRQ) ───────────────
DRIVERS_DIR    := drivers

# ── Common helper headers (shared types/defs) ──────────────────
LIB_DIR        := lib

# ── Custom PicoRV32 port (NOT the standard RISC-V port) ─────────
PICORV32_PORT  := port/

# ── Minimal libc (toolchain has no newlib) ───────────────────────
LIBC_DIR       := libc/

# ── Compiler / Linker flags ─────────────────────────────────────
ARCH_FLAGS := -march=rv32im -mabi=ilp32
CFLAGS_BASE := $(ARCH_FLAGS) -Os -g -Wall -Wextra \
              -ffreestanding -ffunction-sections -fdata-sections \
              -isystem $(LIBC_DIR) \
              -I. \
              -I$(LIB_DIR)/inc \
              -I$(DRIVERS_DIR)/inc \
                            -I$(PICORV32_PORT) \
              -Icli

# Firmware build mode:
# - freertos: runs from SRAM @0x10000 with FreeRTOS context-switch IRQ wrapper (start.S)
# - bootrom : runs from BootROM @0x0 with a generic IRQ dispatcher (lib/src/crt0.S)
FW_MODE ?= freertos

ifeq ($(FW_MODE),freertos)
    CFLAGS := $(CFLAGS_BASE) -I$(FREERTOS_SRC)/include
    LINKER_SCRIPT := linker.ld
    ASM_SRCS := start.S
    # v2: emit an external-flash image (XIP sections) for the flash model
    FLASH_IMG = $(APP).flash.bin $(APP).flash.hex
else ifeq ($(FW_MODE),bootrom)
    CFLAGS := $(CFLAGS_BASE)
    LINKER_SCRIPT := linker_bootrom.ld
    ASM_SRCS := $(LIB_DIR)/src/crt0.S
    FLASH_IMG :=
else
    $(error Unsupported FW_MODE='$(FW_MODE)'; use FW_MODE=freertos or FW_MODE=bootrom)
endif

# Flash XIP sections (LMA in flash): laid out by load address in the binary.
# Lowest LMA is 0x40010000 (.text.reset) -> binary byte 0 = flash offset 0x10000.
FLASH_SECTIONS := -j .text.reset -j .text.irq -j .text -j .rodata -j .data

ASFLAGS    := $(ARCH_FLAGS) -g

LDFLAGS    := $(ARCH_FLAGS) -nostartfiles -nostdlib -T $(LINKER_SCRIPT) \
              -Wl,--gc-sections -Wl,-Map,$(APP).map -lgcc

# ── Application selection ────────────────────────────────────────
# Default app:
#   APP=firmware, APP_SRC=main.c
# Example alternate app:
#   make APP=test_gpio APP_SRC=tests/test_gpio.c
APP      ?= firmware
APP_SRC  ?= main.c

# ── Sources ──────────────────────────────────────────────────────
DRIVER_SRCS := \
    $(DRIVERS_DIR)/src/uart.c \
    $(DRIVERS_DIR)/src/gpio.c \
    $(DRIVERS_DIR)/src/spi.c \
    $(DRIVERS_DIR)/src/timer.c \
    $(DRIVERS_DIR)/src/irq.c

FREERTOS_SRCS := \
    $(FREERTOS_SRC)/tasks.c \
    $(FREERTOS_SRC)/queue.c \
    $(FREERTOS_SRC)/list.c \
    $(FREERTOS_MEM)/heap_4.c \
    $(PICORV32_PORT)/port.c \
    cli/FreeRTOS_CLI.c \
    cli/cli_task.c

C_SRCS := \
    $(APP_SRC) \
    $(LIBC_DIR)/libc.c \
    $(DRIVER_SRCS)

ifeq ($(FW_MODE),freertos)
  C_SRCS += $(FREERTOS_SRCS)
endif

# ── Objects ──────────────────────────────────────────────────────
BUILD_DIR := build
C_OBJS   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(C_SRCS)))
ASM_OBJS := $(patsubst %.S,$(BUILD_DIR)/%.o,$(notdir $(ASM_SRCS)))
OBJS     := $(ASM_OBJS) $(C_OBJS)

# VPATH for finding sources in subdirectories
# Allows selecting APP_SRC from firmware/, firmware/tests/, firmware/boot/, etc.
VPATH := . tests boot $(LIB_DIR)/src $(DRIVERS_DIR)/src $(FREERTOS_SRC) $(FREERTOS_MEM) $(PICORV32_PORT) $(LIBC_DIR) cli

TARGET := $(APP)

.PHONY: all clean

all: $(TARGET).elf $(TARGET).hex $(TARGET).lst $(FLASH_IMG)
	@$(SIZE) $(TARGET).elf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.S | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(TARGET).hex: $(TARGET).elf ; $(OBJCOPY) --verilog-data-width=4 -O verilog $< $@

$(TARGET).lst: $(TARGET).elf
	$(OBJDUMP) -d -S $< > $@

# ── External-flash XIP image (v2) ────────────────────────────────
# .flash.bin : raw image, byte 0 == flash offset 0x10000 (XIP base 0x40010000)
# .flash.hex : one byte (hex) per line for $readmemh into the TB flash model
$(TARGET).flash.bin: $(TARGET).elf
	$(OBJCOPY) -O binary $(FLASH_SECTIONS) $< $@

$(TARGET).flash.hex: $(TARGET).flash.bin
	od -An -v -tx1 $< | tr -s ' ' '\n' | sed '/^$$/d' > $@

clean: ; rm -rf $(BUILD_DIR); rm -f $(TARGET).elf $(TARGET).hex $(TARGET).lst $(TARGET).map $(TARGET).flash.bin $(TARGET).flash.hex; echo "Cleaned."
