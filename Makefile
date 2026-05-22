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

.PHONY: all clean sim sim_gpio sim_uart sim_timer sim_spi sim_bootrom sim_soc \
	help firmware \
	yosys sta pnr flow \
	pd-synth pd-sta pd-floorplan pd-place pd-cts pd-route pd-pnr pd-flow \
	openlane openlane-floorplan \
	show show_netlist clean_pd

# ==============================================================================
#  ASIC FLOW — Modular Physical Design Targets
# ==============================================================================

# ── Synthesis (Yosys) ─────────────────────────────────────────────────────────
pd-synth: ## Run Yosys synthesis (OpenLane-style)
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: Synthesis (Yosys)"
	@echo "══════════════════════════════════════════════════════════════"
	./flow/run_yosys.sh

yosys: pd-synth ## Alias for pd-synth

# ── Static Timing Analysis (OpenSTA) ─────────────────────────────────────────
pd-sta: pd-synth ## Run OpenSTA timing analysis (requires synthesis)
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: Static Timing Analysis (OpenSTA)"
	@echo "══════════════════════════════════════════════════════════════"
	./flow/run_opensta.sh

sta: pd-sta ## Alias for pd-sta

# ── Floorplan Only ────────────────────────────────────────────────────────────
pd-floorplan: pd-synth ## Run OpenROAD up to floorplan
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: Floorplan (OpenROAD)"
	@echo "══════════════════════════════════════════════════════════════"
	OPENROAD_STOP_AFTER=floorplan ./flow/run_openroad.sh

# ── Placement Only ────────────────────────────────────────────────────────────
pd-place: pd-synth ## Run OpenROAD up to placement
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: Placement (OpenROAD)"
	@echo "══════════════════════════════════════════════════════════════"
	OPENROAD_STOP_AFTER=place ./flow/run_openroad.sh

# ── CTS Only ──────────────────────────────────────────────────────────────────
pd-cts: pd-synth ## Run OpenROAD up to CTS
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: Clock Tree Synthesis (OpenROAD)"
	@echo "══════════════════════════════════════════════════════════════"
	OPENROAD_STOP_AFTER=cts ./flow/run_openroad.sh

# ── Routing Only ──────────────────────────────────────────────────────────────
pd-route: pd-synth ## Run OpenROAD up to routing
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: Routing (OpenROAD)"
	@echo "══════════════════════════════════════════════════════════════"
	OPENROAD_STOP_AFTER=route ./flow/run_openroad.sh

# ── Full PnR (no stop) ───────────────────────────────────────────────────────
pd-pnr: pd-synth ## Run full OpenROAD PnR (all stages)
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: Full Place-and-Route (OpenROAD)"
	@echo "══════════════════════════════════════════════════════════════"
	./flow/run_openroad.sh

pnr: pd-pnr ## Alias for pd-pnr

# ── Master Flow (Synth → STA → Full PnR) ─────────────────────────────────────
pd-flow: pd-synth pd-sta pd-pnr ## Run complete RTL-to-GDSII pipeline
	@echo ""
	@echo "╔═══════════════════════════════════════════════════════════════╗"
	@echo "║  ✓  ASIC Flow Complete!                                       ║"
	@echo "║                                                               ║"
	@echo "║  Results: flow/out/openroad/results/                          ║"
	@echo "║  Reports: flow/out/openroad/reports/                          ║"
	@echo "║  Logs:    flow/logs/                                          ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"

flow: pd-flow ## Alias for pd-flow

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

openlane-floorplan: ## Run OpenLane until floorplan
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: OpenLane Floorplan"
	@echo "══════════════════════════════════════════════════════════════"
	$(OPENLANE_DOCKER_RUN) sh -c "OPENLANE_ROOT=/openlane tclsh $(HOME)/riscv-soc/$(OPENLANE_DESIGN)/run_floorplan.tcl"

openlane: ## Run full OpenLane flow
	@echo "══════════════════════════════════════════════════════════════"
	@echo "  STAGE: OpenLane Full Flow"
	@echo "══════════════════════════════════════════════════════════════"
	$(OPENLANE_DOCKER_RUN) sh -c "./flow.tcl -design $(HOME)/riscv-soc/$(OPENLANE_DESIGN) -overwrite"

# ── Legacy aliases (backward compatibility) ───────────────────────────────────
openroad_floorplan: pd-floorplan
openroad_place: pd-place
openroad_cts: pd-cts
openroad_route: pd-route

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
	@echo "║    make sim_bootrom — Boot ROM testbench only                 ║"
	@echo "║    make sim_soc     — Full SoC integration test (Icarus)      ║"
	@echo "║    make firmware    — Build all firmware 					   ║"
	@echo "║                                                               ║"
	@echo "║  ASIC Flow (modular):                                         ║"
	@echo "║    make pd-synth      — Yosys synthesis                       ║"
	@echo "║    make pd-sta        — OpenSTA timing analysis               ║"
	@echo "║    make pd-floorplan  — OpenROAD: stop after floorplan        ║"
	@echo "║    make pd-place      — OpenROAD: stop after placement        ║"
	@echo "║    make pd-cts        — OpenROAD: stop after CTS              ║"
	@echo "║    make pd-route      — OpenROAD: stop after routing          ║"
	@echo "║    make pd-pnr        — OpenROAD: full PnR (all stages)       ║"
	@echo "║    make pd-flow       — Complete RTL-to-GDSII pipeline        ║"
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
	@bash -c 'source flow/env.sh && export GIO_MODULE_DIR=/tmp && yosys -p "read_verilog $$YOSYS_OUT_DIR/results/$$DESIGN_NAME.synth.v; read_liberty -lib $$STD_CELL_LIB; hierarchy -top $$DESIGN_NAME; show $$DESIGN_NAME"'

# ==============================================================================
#  CLEANUP
# ==============================================================================

clean: clean_pd ## Clean all build artifacts
	rm -rf $(SIM_DIR)/*.vvp $(SIM_DIR)/*.vcd
	@echo "✓ All build artifacts cleaned"
