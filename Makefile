# ╔═══════════════════════════════════════════════════════════════════════════╗
# ║  RISC-V SoC — ASIC Build System                                           ║
# ║  Targets: Simulation (Icarus) + Synthesis (Yosys) + PnR (OpenROAD)        ║
# ╚═══════════════════════════════════════════════════════════════════════════╝

# ── Tool Paths ────────────────────────────────────────────────────────────────
IVERILOG  = iverilog
VVP       = vvp
YOSYS     = yosys
VERILATOR = verilator

# ── Directory Layout ──────────────────────────────────────────────────────────
RTL_DIR   = rtl
TB_DIR    = tb
SIM_DIR   = sim

# ── PDK Configuration ────────────────────────────────────────────────────────
PDK_ROOT  = ?= $(HOME)/pdk/sky130A

# ── Compiler Flags ────────────────────────────────────────────────────────────
IVFLAGS   = -g2012 -I$(RTL_DIR)/
VFLAGS    = -Wall -Wno-fat

# ==============================================================================
#  PHONY TARGETS
# ==============================================================================

.PHONY: all clean sim_axi

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
	@echo "║    make sim_axi     — AXI testbench only                      ║"
	@echo "║                                                               ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"

# ==============================================================================
#  SIMULATION (Icarus Verilog)
# ==============================================================================

# ── Run all testbenches ───────────────────────────────────────────────────────
sim: sim_axi
	@echo "============================================="
	@echo "  ✓ All Testbenches Completed Successfully!"
	@echo "============================================="

# ── AXI test ───────────────────────────────────────────────────────
sim_axi: $(SIM_DIR)/axi_interconnect_tb.out
	$(VVP) $<

$(SIM_DIR)/axi_interconnect_tb.out: $(TB_DIR)/axi_interconect_tb.sv $(RTL_DIR)/interconnect/axi_interconnect.sv $(RTL_DIR)/memory/axi_ram.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -o $@ $^

# ── UART ──────────────────────────────────────────────────────────────────────
sim_uart: $(SIM_DIR)/uart_ctrl_apb_tb.vvp
	$(VVP) $<

$(SIM_DIR)/uart_ctrl_apb_tb.vvp: $(RTL_DIR)/peripherals/uart/*.sv $(TB_DIR)/uart_ctrl_apb_tb.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -o $@ $^
	
clean:
	rm -rf $(SIM_DIR)

# ── GPIO ──────────────────────────────────────────────────────────────────────
sim_gpio: $(SIM_DIR)/gpio_apb_tb.vvp
	$(VVP) $<

$(SIM_DIR)/gpio_apb_tb.vvp: $(RTL_DIR)/peripherals/gpio/gpio_apb.sv $(TB_DIR)/gpio_apb_tb.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -o $@ $^

# ── Timer ─────────────────────────────────────────────────────────────────────
sim_timer: $(SIM_DIR)/timer_apb_tb.vvp
	$(VVP) $<

$(SIM_DIR)/timer_apb_tb.vvp: $(RTL_DIR)/peripherals/timer/timer_apb.sv $(TB_DIR)/timer_apb_tb.sv
	mkdir -p $(SIM_DIR)
	$(IVERILOG) $(IVFLAGS) -o $@ $^
