#!/usr/bin/env tclsh
# =============================================================================
# analyze_ir_drop.tcl — OpenROAD PDN IR-drop analysis for soc_core
#
# Run after detailed route inside the OpenLane Docker container:
#   openroad -exit analyze_ir_drop.tcl
#
# Or from inside the OpenLane flow directory:
#   openroad -exit flow/scripts/analyze_ir_drop.tcl
# =============================================================================

# Path to the post-route ODB (adjust to your run timestamp)
set ODB_PATH   "designs/soc_core_prod/runs/RUN_latest/results/routing/soc_core.odb"
set PDK_ROOT   $::env(PDK_ROOT)
set TECH_LEF   "$PDK_ROOT/sky130B/libs.ref/sky130_fd_sc_hd/techlef/sky130_fd_sc_hd__nom.tlef"

# Load the design
read_lef  $TECH_LEF
read_db   $ODB_PATH

# -----------------------------------------------------------------------------
# Run IR-drop on both supply nets
# -----------------------------------------------------------------------------
foreach net {vccd1 vssd1} {
    puts "\n[string repeat = 60]"
    puts "  PDN IR-Drop Analysis — net: $net"
    puts "[string repeat = 60]"

    # analyze_power_grid is OpenROAD's built-in EM/IR checker
    # Typical worst-case IR budget for sky130: < 50 mV (< 3% of 1.8V)
    analyze_power_grid \
        -net            $net \
        -voltage_file   "ir_drop_${net}.rpt"

    puts "  Report written to: ir_drop_${net}.rpt"
}

puts "\n=== IR Drop targets (sky130 @ 1.8V) ==="
puts "  Acceptable : < 50 mV  (< 2.8% of Vdd)"
puts "  Warning    : 50–90 mV"
puts "  Critical   : > 90 mV — widen PDN straps or add rings"
puts "==="
