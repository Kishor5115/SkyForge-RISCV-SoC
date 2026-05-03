# ╔═══════════════════════════════════════════════════════════════════════════╗
# ║  RISC-V SoC — ASIC Build System                                           ║
# ║  Targets: Simulation (Icarus) + Synthesis (Yosys) + PnR (OpenROAD)        ║
# ╚═══════════════════════════════════════════════════════════════════════════╝

# ── Tool Paths ────────────────────────────────────────────────────────────────
IVERILOG   = iverilog
VVP        = vvp
# ── Directory Layout ──────────────────────────────────────────────────────────
RTL_DIR    = rtl
TB_DIR     = tb
SIM_DIR    = sim


# ── PDK Configuration ────────────────────────────────────────────────────────
PDK_ROOT  ?= $(HOME)/pdk/sky130A

# ── Compiler Flags ────────────────────────────────────────────────────────────
IVFLAGS    = -g2012 -I $(RTL_DIR)/
VFLAGS     = -Wall -Wno-fatal --trace --cc --exe --build -j $(shell nproc) \
             -I$(RTL_DIR) -Mdir verilator/obj_dir --top-module soc_top

# ==============================================================================
#  PHONY TARGETS
# ==============================================================================

.PHONY: all clean sim sim_gpio sim_uart sim_timer sim_soc help firmware

# Load design-specific PnR configuration
include $(DESIGN_CONFIG)

# ── Default target ────────────────────────────────────────────────────────────
all: sim

# ── Help ──────────────────────────────────────────────────────────────────────
help: ## Show available targets
	@echo "╔═══════════════════════════════════════════════════════════════╗"
	@echo "║  RISC-V SoC — ASIC Build System                               ║"
	@echo "╠═══════════════════════════════════════════════════════════════╣"
	@echo "║                                                               ║"
	@echo "║                                                               ║"
	@echo "║  Simulation:                                                  ║"
	@echo "║    make sim         — Run all testbenches                     ║"
	@echo "║    make sim_gpio    — GPIO testbench only                     ║"
	@echo "║    make sim_uart    — UART testbench only                     ║"
	@echo "║    make sim_timer   — Timer testbench only                    ║"
	@echo "║    make sim_soc     — Full SoC integration test (Icarus)      ║"
	@echo "║    make firmware    — Build all firmware (software, boot, test) ║"
	@echo "║                                                               ║"
	@echo "║  Utility:                                                     ║"
	@echo "║    make clean       — Clean all build artifacts               ║"
	@echo "║    make help        — Show this help message                  ║"
	@echo "║                                                               ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"


# ==============================================================================
#  SIMULATION (Icarus Verilog)
# ==============================================================================
# ? Peripheral unit tests + full SoC integration test
# ==============================================================================

# ── Run all testbenches ───────────────────────────────────────────────────────
sim: sim_gpio sim_uart sim_timer sim_spi sim_bootrom sim_integration
	@echo "============================================="
	@echo "  ✓ All Testbenches Completed Successfully!"
	@echo "============================================="

# ── GPIO ──────────────────────────────────────────────────────────────────────
sim_gpio: $(SIM_DIR)/gpio_apb_tb.vvp
	$(VVP) $<

$(SIM_DIR)/gpio_apb_tb.vvp: $(RTL_DIR)/peripherals/gpio/gpio_apb.sv $(TB_DIR)/gpio_apb_tb.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -o $@ $^

# ── UART ──────────────────────────────────────────────────────────────────────
sim_uart: $(SIM_DIR)/uart_ctrl_apb_tb.vvp
	$(VVP) $<

$(SIM_DIR)/uart_ctrl_apb_tb.vvp: $(RTL_DIR)/peripherals/uart/*.sv $(TB_DIR)/uart_ctrl_apb_tb.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -o $@ $^

# ── Timer ─────────────────────────────────────────────────────────────────────
sim_timer: $(SIM_DIR)/timer_apb_tb.vvp
	$(VVP) $<

$(SIM_DIR)/timer_apb_tb.vvp: $(RTL_DIR)/peripherals/timer/timer_apb.sv $(TB_DIR)/timer_apb_tb.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -o $@ $^

# ── SPI Master ────────────────────────────────────────────────────────────────
sim_spi: $(SIM_DIR)/tb_spi.vvp
	$(VVP) $<

$(SIM_DIR)/tb_spi.vvp: $(RTL_DIR)/peripherals/spi/spi_master_apb.sv $(TB_DIR)/tb_spi.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -o $@ $^

# ── Boot ROM ──────────────────────────────────────────────────────────────────
sim_bootrom: $(SIM_DIR)/tb_bootrom.vvp
	$(MAKE) -C firmware boot_rom
	cp firmware/build/boot_rom.hex ./bootrom.hex
	$(VVP) $<

$(SIM_DIR)/tb_bootrom.vvp: $(RTL_DIR)/memory/bootrom.sv $(TB_DIR)/tb_bootrom.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -o $@ $^

# ── SoC Integration ──────────────────────────────────────────────────────────
sim_soc: $(SIM_DIR)/soc_integration_tb.vvp
	@echo "Building integration firmware..."
	$(MAKE) -C firmware integration_test
	cp firmware/build/integration_test_boot.hex $(SIM_DIR)/integration_test.hex
	@echo "Running integration simulation..."
	$(VVP) $< +MEM_INIT_FILE=$(SIM_DIR)/integration_test.hex

$(SIM_DIR)/soc_integration_tb.vvp: $(RTL_DIR)/core/*.sv $(RTL_DIR)/memory/*.sv $(RTL_DIR)/interconnect/*.sv $(RTL_DIR)/peripherals/*/*.sv $(RTL_DIR)/asic/*.sv $(RTL_DIR)/soc_top.sv $(TB_DIR)/soc_top_tb.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -s soc_top_tb -o $@ $^

# ── Firmware Build ────────────────────────────────────────────────────────────
firmware: ## Build all firmware components
	$(MAKE) -C firmware all software boot_rom integration_test

# ==============================================================================
#  SCHEMATIC VISUALIZATION
# ==============================================================================

MODULE ?= soc_core

show: ## Show RTL schematic of a module (e.g. make show MODULE=axi_sram_adapter)
	@$(YOSYS) -p "read_verilog -sv $(VERILOG_FILES); hierarchy -top $(MODULE); show $(MODULE)"

show_netlist: ## Show gate-level schematic of the synthesized netlist
	@$(YOSYS) -p "read_verilog $(RESULTS_DIR)/$(DESIGN_NAME).netlist.v; read_liberty -lib $(LIB_FILE); hierarchy -top $(DESIGN_NAME); show $(DESIGN_NAME)"

# ==============================================================================
#  CLEANUP
# ==============================================================================

clean: clean_syn ## Clean all build artifacts
	rm -rf $(SIM_DIR)/*.vvp $(SIM_DIR)/*.vcd
	@echo "✓ All build artifacts cleaned"
