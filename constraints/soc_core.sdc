# =============================================================================
# soc_core.sdc — SkyWater sky130 / OpenSTA timing constraints
# Target: 100 MHz (10 ns period), sky130B TT/1.8V/25C corner
# =============================================================================

set_units -time ns -resistance kOhm -capacitance pF -voltage V -current mA

# -----------------------------------------------------------------------------
# Primary clock
# -----------------------------------------------------------------------------
create_clock -name clk_i -period 10 [get_ports clk_i]

# 30 % clock-source uncertainty (jitter + skew on sky130)
set_clock_uncertainty 0.3 [get_clocks clk_i]

# Generated clock inside SRAM macro (same source, registered output)
create_generated_clock -name sram_clk \
  -source [get_ports clk_i] \
  -divide_by 1 \
  [get_pins -hierarchical "*/clk0"]

# -----------------------------------------------------------------------------
# I/O delays (assume external FF one hop away at the same 10 ns period)
# -----------------------------------------------------------------------------
set_input_delay  2.0 -clock clk_i [get_ports {*}]
set_output_delay 2.0 -clock clk_i [get_ports {*}]

# Async ports need no timing constraint
set_false_path -from [get_ports rst_ni]
set_false_path -from [get_ports jtag_tck_i]
set_false_path -from [get_ports jtag_tms_i]
set_false_path -from [get_ports jtag_tdi_i]
set_false_path -to   [get_ports jtag_tdo_o]

# -----------------------------------------------------------------------------
# SRAM macro constraints
# SRAM read latency = 1 cycle; write = 1 cycle.
# The AXI→SRAM bridge already inserts one pipeline stage, so the
# data path from core to SRAM din is exactly 1 cycle.
# -----------------------------------------------------------------------------

# Setup: data must arrive at SRAM din/addr/csb/web 0.5 ns before rising clock
set_input_delay 0.5 -clock sram_clk -add_delay \
  [get_pins -hierarchical "*/din0*"]
set_input_delay 0.5 -clock sram_clk -add_delay \
  [get_pins -hierarchical "*/addr0*"]
set_input_delay 0.5 -clock sram_clk -add_delay \
  [get_pins -hierarchical "*/csb0"]
set_input_delay 0.5 -clock sram_clk -add_delay \
  [get_pins -hierarchical "*/web0"]
set_input_delay 0.5 -clock sram_clk -add_delay \
  [get_pins -hierarchical "*/wmask0*"]

# SRAM output (dout) is valid 2.6 ns after rising clock edge.
# The downstream register has a 10 ns window minus 2.6 ns = 7.4 ns budget.
set_output_delay -2.6 -clock sram_clk -add_delay \
  [get_pins -hierarchical "*/dout0*"]

# Prevent false timing paths through the behavioural SRAM model
# (applies when SRAM is instantiated as a blackbox in synthesis)
set_false_path -through [get_cells -hierarchical -filter {REF_NAME =~ sky130_sram*}]

# -----------------------------------------------------------------------------
# Load / drive assumptions
# -----------------------------------------------------------------------------
set_driving_cell -lib_cell sky130_fd_sc_hd__inv_2 \
  -pin Y [all_inputs]
set_load 0.05 [all_outputs]

# -----------------------------------------------------------------------------
# Max transition / fanout
# -----------------------------------------------------------------------------
set_max_transition 0.5 [current_design]
set_max_fanout     20  [current_design]
