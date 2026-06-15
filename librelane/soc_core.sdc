# SDC Timing Constraints for PicoRV32 RISC-V SoC
# Target: 50 MHz (20 ns period) on sky130A
# Used by both picorv32_core.yaml and soc_core_top.yaml

# --- Primary clock ---
set clk_period $::env(CLOCK_PERIOD)
set clk_name   $::env(CLOCK_PORT)
set clk_port   [get_ports $clk_name]

create_clock -name $clk_name -period $clk_period $clk_port

# --- Clock uncertainty (conservative for sky130) ---
set_clock_uncertainty 0.5 [get_clocks $clk_name]

# --- Input/Output delays (assume 25% of period for I/O timing) ---
set io_delay [expr {$clk_period * 0.25}]

# Exclude the clock port itself — OpenSTA does not support remove_from_collection.
# Use lsearch/lreplace on the Tcl list returned by [all_inputs] instead.
set clk_indx [lsearch [all_inputs] $clk_port]
set non_clk_inputs [lreplace [all_inputs] $clk_indx $clk_indx ""]
set_input_delay  $io_delay -clock $clk_name $non_clk_inputs
set_output_delay $io_delay -clock $clk_name [all_outputs]

# --- False paths for reset (async assert, sync deassert) ---
if {[llength [get_ports -quiet rst_ni]] > 0} {
    set_false_path -from [get_ports rst_ni]
} elseif {[llength [get_ports -quiet resetn]] > 0} {
    set_false_path -from [get_ports resetn]
}

# --- JTAG clock domain (TCK is asynchronous to main clock) ---
if {[llength [get_ports -quiet jtag_tck_i]] > 0} {
    create_clock -name jtag_tck -period 100.0 [get_ports jtag_tck_i]
    set_clock_groups -asynchronous \
        -group [get_clocks $clk_name] \
        -group [get_clocks jtag_tck]
}
