# SDC Timing Constraints for PicoRV32 RISC-V SoC
# Target: 50 MHz (20 ns period) on sky130A
# Used by both picorv32_core.yaml and soc_core_top.yaml

# --- Primary clock ---
set clk_period $::env(CLOCK_PERIOD)
set clk_name   $::env(CLOCK_PORT)
set clk_port   [get_ports $clk_name]

create_clock -name $clk_name -period $clk_period $clk_port

# --- Clock uncertainty ---
# 0.25 ns is still conservative for sky130 at 50 MHz (20 ns period, 1.25% of the
# cycle). The previous 0.5 ns was doubly-pessimistic and, combined with slow
# (ss_100C_1v60) derating, was the dominant contributor to the PicoRV32 core's
# marginal SS-corner setup slack (see docs/PICORV32_STA_ANALYSIS.md). The
# nominal-corner slack (+5.2 ns) is unaffected.
set_clock_uncertainty 0.25 [get_clocks $clk_name]

# --- Max fanout / transition (buffer high-fanout logic nets) ---
# The FF-based icache_512b read/write mux fans req_foff[2:4] out to thousands of
# terminals (GRT-0281). Bounding fanout lets the resizer build a buffer tree
# instead of one enormous net, easing routing congestion. Clock/reset trees are
# built separately by CTS and are not affected by this constraint.
set_max_fanout 24 [current_design]

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
