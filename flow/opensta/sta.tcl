# OpenSTA script
# Assumes env.sh has been sourced to provide library paths.

set flow_root [file normalize [file dirname [info script]]/..]
set design_name $::env(DESIGN_NAME)
set out_dir $::env(OUT_DIR)
set yosys_out_dir $::env(YOSYS_OUT_DIR)

set std_lib $::env(STD_CELL_LIB)
set sram_lib $::env(SRAM_LIB)
set sdc_file $::env(SDC_FILE)

set netlist "$yosys_out_dir/results/${design_name}.synth.v"

read_liberty $std_lib
if {[file exists $sram_lib]} {
    read_liberty $sram_lib
}

read_verilog $netlist
link_design $design_name

read_sdc $sdc_file

report_checks -path_delay max -fields {slew cap input_pins} -format full_clock > "$out_dir/sta/${design_name}_max.rpt"
report_checks -path_delay min -fields {slew cap input_pins} -format full_clock > "$out_dir/sta/${design_name}_min.rpt"
report_tns > "$out_dir/sta/${design_name}_tns.rpt"
report_wns > "$out_dir/sta/${design_name}_wns.rpt"
