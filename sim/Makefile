# ──────────────────────────────────────────────────────────────────
# Verilator Simulation Makefile for PicoRV32 SoC
# Usage:  make sim        — build the simulator binary
#         make run        — build & run
#         make clean      — remove build artifacts
# ──────────────────────────────────────────────────────────────────

TOPLEVEL   := soc_top
RTL_DIR    := ../rtl
SIM_DIR    := .
FW_DIR     := ../firmware

# Firmware hex files for simulation preload
BOOTROM_HEX := $(SIM_DIR)/bootrom.hex
FW_APP      ?= firmware
FW_APP_SRC  ?= main.c
OBJ_DIR     = obj_dir_$(FW_APP)
FW_HEX      := $(FW_DIR)/$(FW_APP).hex
SRAM_HEX    := $(SIM_DIR)/$(FW_APP)_sram.hex

# Collect all RTL source files
RTL_SRCS   := $(shell find $(RTL_DIR) -name '*.v' -o -name '*.sv' 2>/dev/null)

VERILATOR  := verilator
VERILATOR_FLAGS := \
	--cc \
	--exe \
	--build \
	-Wall \
	-Wno-fatal \
	--top-module $(TOPLEVEL) \
	-CFLAGS "-std=c++14 -O2" \
	-LDFLAGS "-lpthread" \
	--Mdir $(OBJ_DIR) \
	--trace \
	-GMEM_INIT_FILE='"bootrom.hex"' \
	-GSRAM_INIT_FILE='"$(notdir $(SRAM_HEX))"'

# Include directories for RTL
RTL_INCDIRS := $(shell find $(RTL_DIR) -type d 2>/dev/null | sed 's/^/-I/')

SIM_BINARY := $(OBJ_DIR)/V$(TOPLEVEL)

.PHONY: sim run firmware clean

# Build firmware first, then generate SRAM hex, then build sim
sim: firmware $(SRAM_HEX) $(SIM_BINARY)

firmware:
	$(MAKE) -C $(FW_DIR) APP=$(FW_APP) APP_SRC=$(FW_APP_SRC) all

$(SRAM_HEX): $(FW_HEX)
	python3 ../scripts/verilog_hex_to_memh.py $< 0x00010000 $@

$(SIM_BINARY): main.cpp $(RTL_SRCS) $(BOOTROM_HEX) $(SRAM_HEX)
	$(VERILATOR) $(VERILATOR_FLAGS) $(RTL_INCDIRS) $(RTL_SRCS) main.cpp

run: sim
	@echo "─── Launching simulation (Ctrl-C to stop) ───"
	$(SIM_BINARY)

clean:
	rm -rf obj_dir*
	rm -f soc_top.vcd *_sram.hex
	@echo "Cleaned."
