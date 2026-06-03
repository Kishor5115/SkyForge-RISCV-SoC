# ╔═══════════════════════════════════════════════════════════════════════════╗
# ║  RISC-V SoC — ASIC Build System                                           ║
# ║  Targets: Simulation (Icarus) + Synthesis (Yosys) + PnR (OpenROAD)        ║
# ╚═══════════════════════════════════════════════════════════════════════════╝

# ── Tool Paths ────────────────────────────────────────────────────────────────
IVERILOG   = iverilog
VVP        = vvp

# Tools used by helper targets
YOSYS     ?= yosys
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

.PHONY: all clean sim sim_gpio sim_uart sim_timer sim_spi sim_soc sim_soc_new_tb \
	help firmware \
	yosys sta pnr flow \
	pd-synth pd-sta pd-floorplan pd-place pd-cts pd-route pd-pnr pd-flow \
	openlane openlane-run openlane-mount openlane-view-klayout openlane-view-magic openlane-clean \
	show show_netlist clean_pd

# ==============================================================================
#  OPENLANE FLOW (wrapper-based)
# ==============================================================================

OPENLANE_ROOT ?= $(HOME)/OpenLane
OPENLANE_FLOW := $(OPENLANE_ROOT)/flow.tcl
OPENLANE_DESIGN := openlane
OPENLANE_TCLSH ?= /usr/bin/tclsh
OPENLANE_PDK_ROOT ?= $(HOME)/pdk
OPENLANE_DOCKER_TAG ?= $(shell cd $(OPENLANE_ROOT) && python3 dependencies/get_tag.py)
OPENLANE_DOCKER_ARCH ?= $(shell cd $(OPENLANE_ROOT) && python3 docker/current_platform.py)
OPENLANE_IMAGE_NAME ?= ghcr.io/the-openroad-project/openlane:$(OPENLANE_DOCKER_TAG)-$(OPENLANE_DOCKER_ARCH)
OPENLANE_DOCKER_OPTS ?= $(shell cd $(OPENLANE_ROOT) && python3 env.py docker-config)
OPENLANE_DOCKER_RUN := docker run --rm \
	-v $(OPENLANE_ROOT):/openlane \
	-v $(OPENLANE_ROOT)/designs:/openlane/install \
	-v $(HOME):$(HOME) \
	-v $(OPENLANE_PDK_ROOT):$(OPENLANE_PDK_ROOT) \
	-e PDK_ROOT=$(OPENLANE_PDK_ROOT) \
	-e PDK=sky130A \
	-e STD_CELL_LIBRARY=sky130_fd_sc_hd \
	$(OPENLANE_DOCKER_OPTS) \
	$(OPENLANE_IMAGE_NAME)

openlane: openlane-run

openlane-run: ## Run full OpenLane flow
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: OpenLane Full Flow"
	@echo "══════════════════════════════════════════════════════════════"
	$(MAKE) -C openlane run

openlane-mount: ## Mount OpenLane Docker shell
	$(MAKE) -C openlane mount

openlane-view-klayout: ## View layout in KLayout
	$(MAKE) -C openlane view-klayout

openlane-view-magic: ## View layout in Magic
	$(MAKE) -C openlane view-magic

openlane-clean: ## Clean OpenLane run directories
	$(MAKE) -C openlane clean

# ── Clean PD artifacts ────────────────────────────────────────────────────────
clean_pd: ## Clean all physical design artifacts
	rm -rf flow/out flow/yosys/out flow/logs
	@echo "✓ Physical design artifacts cleaned"

# ── Default target ────────────────────────────────────────────────────────────
all: sim

# ── Help ──────────────────────────────────────────────────────────────────────
help: ## Show available targets
	@echo "╔═══════════════════════════════════════════════════════════════╗"
	@echo "║  RISC-V SoC — ASIC Build System                               ║"
	@echo "╠═══════════════════════════════════════════════════════════════╣"
	@echo "║                                                               ║"
	@echo "║  Simulation:                                                  ║"
	@echo "║    make sim         — Run all testbenches                     ║"
	@echo "║    make sim_gpio    — GPIO testbench only                     ║"
	@echo "║    make sim_uart    — UART testbench only                     ║"
	@echo "║    make sim_timer   — Timer testbench only                    ║"
	@echo "║    make sim_spi     — SPI testbench only                      ║"
	@echo "║    make sim_soc     — Full SoC integration test (Icarus)      ║"
	@echo "║    make sim_soc_new_tb — SoC bring-up smoke test (Icarus)     ║"
	@echo "║    make firmware    — Build firmware apps (default + tests)   ║"
	@echo "║                                                               ║"
	@echo "║  OpenLane:                                                    ║"
	@echo "║    make openlane-run     — Run full OpenLane flow             ║"
	@echo "║    make openlane-mount   — Mount OpenLane Docker shell        ║"
	@echo "║    make openlane-view-klayout — View layout in KLayout        ║"
	@echo "║    make openlane-view-magic   — View layout in Magic          ║"
	@echo "║    make openlane-clean   — Clean OpenLane runs                ║"
	@echo "║                                                               ║"
	@echo "║  Visualization:                                               ║"
	@echo "║    make show          — Show RTL schematic of a module        ║"
	@echo "║    make show_netlist  — Show synthesized netlist schematic    ║"
	@echo "║                                                               ║"
	@echo "║  Utility:                                                     ║"
	@echo "║    make clean         — Clean simulation artifacts            ║"
	@echo "║    make clean_pd      — Clean physical design artifacts       ║"
	@echo "║    make help          — Show this help message                ║"
	@echo "║                                                               ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"


# ==============================================================================
#  SIMULATION (Icarus Verilog)
# ==============================================================================
# ? Peripheral unit tests + full SoC integration test
# ==============================================================================

# ── Run all testbenches ───────────────────────────────────────────────────────
sim: sim_gpio sim_uart sim_timer sim_spi sim_soc
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

# ── SoC Integration ─────────────────────────────────────────────────────────-
sim_soc: $(SIM_DIR)/soc_top_tb.vvp firmware_integration_test
	@echo "Preparing BootROM init hex for soc_top_tb..."
	cp firmware/integration_test.hex $(SIM_DIR)/integration_test.hex
	@echo "Running SoC integration simulation (Icarus)..."
	$(VVP) $(SIM_DIR)/soc_top_tb.vvp

$(SIM_DIR)/soc_top_tb.vvp: $(RTL_DIR)/core/*.sv $(RTL_DIR)/memory/*.sv $(RTL_DIR)/interconnect/*.sv $(RTL_DIR)/peripherals/*/*.sv $(RTL_DIR)/asic/*.sv $(RTL_DIR)/soc_top.sv $(TB_DIR)/soc_top_tb.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -s soc_top_tb -o $@ $^

# ── SoC Bring-Up (new lightweight TB, UART PASS/FAIL only) ───────────────────-
sim_soc_new_tb: $(SIM_DIR)/soc_top_bringup_tb.vvp firmware_integration_test
	@echo "Preparing BootROM init hex for soc_top_bringup_tb..."
	cp firmware/integration_test.hex $(SIM_DIR)/integration_test.hex
	@echo "Running SoC bring-up simulation (new TB, Icarus)..."
	$(VVP) $(SIM_DIR)/soc_top_bringup_tb.vvp

$(SIM_DIR)/soc_top_bringup_tb.vvp: $(RTL_DIR)/core/*.sv $(RTL_DIR)/memory/*.sv $(RTL_DIR)/interconnect/*.sv $(RTL_DIR)/peripherals/*/*.sv $(RTL_DIR)/asic/*.sv $(RTL_DIR)/soc_top.sv $(TB_DIR)/soc_top_bringup_tb.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -s soc_top_bringup_tb -o $@ $^

# ── Firmware Build ────────────────────────────────────────────────────────────
firmware: firmware_default firmware_integration_test firmware_test_gpio firmware_periph_test ## Build firmware apps (default + tests)

firmware_default:
	$(MAKE) -C firmware APP=firmware APP_SRC=main.c all

firmware_integration_test:
	$(MAKE) -C firmware APP=integration_test APP_SRC=tests/integration_test.c FW_MODE=bootrom all

firmware_test_gpio:
	$(MAKE) -C firmware APP=test_gpio APP_SRC=tests/test_gpio.c FW_MODE=bootrom all

firmware_periph_test:
	$(MAKE) -C firmware APP=periph_test APP_SRC=tests/periph_test.c FW_MODE=bootrom all

# ==============================================================================
#  SCHEMATIC VISUALIZATION
# ==============================================================================

MODULE ?= soc_core

VERILOG_FILES ?= $(shell find $(RTL_DIR) -type f \( -name '*.sv' -o -name '*.v' \) 2>/dev/null)

show: ## Show RTL schematic of a module (e.g. make show MODULE=axi_sram_adapter)
	@$(YOSYS) -p "read_verilog -sv $(VERILOG_FILES); hierarchy -top $(MODULE); show $(MODULE)"

show_netlist: ## Show gate-level schematic of the synthesized netlist
	@bash -c 'source flow/env.sh && export GIO_MODULE_DIR=/tmp && yosys -p "read_verilog $$YOSYS_OUT_DIR/results/$$DESIGN_NAME.synth.v; read_liberty -lib $$STD_CELL_LIB; hierarchy -top $$DESIGN_NAME; show $$DESIGN_NAME"'

# ==============================================================================
#  CLEANUP
# ==============================================================================

clean: clean_pd ## Clean all build artifacts
	rm -rf $(SIM_DIR)/*.vvp $(SIM_DIR)/*.vcd
	@echo "✓ All build artifacts cleaned"

# ==============================================================================
#  DEBUGGING & SIMULATION RUNNERS
# ==============================================================================

run: ## Run the simulation (Verilator)
	$(MAKE) -C sim run

openocd: ## Run OpenOCD
	cd openocd && openocd -f openocd.cfg

gdb: ## Run GDB
	cd firmware && gdb-multiarch -x ../openocd/gdb_init.cfg firmware.elf

killall: ## Kill all simulation and debug processes
	killall -9 Vsoc_top openocd gdb-multiarch || true
