# ============================================================================
# SDC Constraints — soc_top (Sky130 @ 100 MHz / 10ns)
# ============================================================================

# ── Clock Definition ────────────────────────────────────────────────────────
set clk_period 10.0
create_clock -name clk -period $clk_period [get_ports clk]

# Clock uncertainty (jitter + skew margin)
set_clock_uncertainty 0.25 [get_clocks clk]

# Clock transition
set_clock_transition 0.15 [get_clocks clk]

# ── Input/Output Delays ────────────────────────────────────────────────────
# Assume 30% of clock period for I/O setup
set input_delay  [expr {$clk_period * 0.30}]
set output_delay [expr {$clk_period * 0.30}]

set_input_delay  $input_delay  -clock clk [all_inputs]
set_output_delay $output_delay -clock clk [all_outputs]

# Don't constrain clock pin itself as input
set_false_path -from [get_ports clk]

# ── Reset is async — false-path it ──────────────────────────────────────────
set_false_path -from [get_ports rst_n]

# ── JTAG clock domain is async to system clock ──────────────────────────────
set_false_path -from [get_ports jtag_tck]
set_false_path -from [get_ports jtag_tms]
set_false_path -from [get_ports jtag_tdi]

# ── Max Transition / Max Fanout ─────────────────────────────────────────────
set_max_transition 0.75 [current_design]
set_max_fanout     10   [current_design]

# ── Driving Cell / Load ────────────────────────────────────────────────────
set_driving_cell -lib_cell sky130_fd_sc_hd__inv_2 -pin Y [all_inputs]
set_load -pin_load 0.033442 [all_outputs]
