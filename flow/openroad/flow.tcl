# ============================================================================
# OpenROAD Master Flow — RISC-V SoC (Sky130)
#
# Orchestrates the full RTL-to-DEF physical design flow by sourcing
# each stage script in sequence.  Mirrors the OpenLane stage pipeline:
#
#   1. Floorplan       — Die/core area, tie cells, macro placement
#   2. I/O Placement   — Pin assignment on die boundary
#   3. Tap Cells       — Well-tap and endcap insertion
#   4. PDN             — Power distribution network
#   5. Global Place    — Analytical global placement
#   6. Resizer         — Pre-CTS design optimization
#   7. Resizer Timing  — Pre-CTS timing repair
#   8. Detailed Place  — Legalization
#   9. CTS             — Clock tree synthesis
#  10. Resizer (post)  — Post-CTS timing repair
#  11. Global Route    — Congestion-aware global routing
#  12. Detailed Route  — TritonRoute detailed routing
#  13. Fill            — Filler/decap cell insertion
#  14. Antenna Check   — Antenna rule verification
#  15. Write Views     — Export final DEF, netlist, SDC
#
# Controlled by OPENROAD_STOP_AFTER env var:
#   floorplan | place | cts | route
# ============================================================================

proc log_step {stage msg} {
    puts ""
    puts "╔══════════════════════════════════════════════════════════════════════════╗"
    puts "  \[$stage\] $msg"
    puts "╚══════════════════════════════════════════════════════════════════════════╝"
}

# ── Resolve paths ────────────────────────────────────────────────────────────
set flow_root [file normalize [file dirname [info script]]/..]
set ::env(SCRIPTS_DIR) [file normalize [file dirname [info script]]/scripts]

set or_dir "$::env(OUT_DIR)/openroad"
file mkdir "$or_dir/results"
file mkdir "$or_dir/reports"

# Optional stop-after stage
set stop_after ""
if { [info exists ::env(OPENROAD_STOP_AFTER)] } {
    set stop_after $::env(OPENROAD_STOP_AFTER)
}

# ============================================================================
# STAGE 1: Floorplan
# ============================================================================
log_step "1/15" "Floorplan"
source $::env(SCRIPTS_DIR)/floorplan.tcl

if { $stop_after == "floorplan" } {
    log_step "DONE" "Stopping after floorplan (as requested)"
    exit 0
}

# ============================================================================
# STAGE 2: I/O Pin Placement
# ============================================================================
log_step "2/15" "I/O Pin Placement"
source $::env(SCRIPTS_DIR)/ioplacer.tcl

# ============================================================================
# STAGE 3: Tap Cell & Endcap Insertion
# ============================================================================
log_step "3/15" "Tap Cell & Endcap Insertion"
source $::env(SCRIPTS_DIR)/tapcell.tcl

# ============================================================================
# STAGE 4: Power Distribution Network
# ============================================================================
log_step "4/15" "Power Distribution Network"
source $::env(SCRIPTS_DIR)/pdn.tcl

# ============================================================================
# STAGE 5: Global Placement
# ============================================================================
log_step "5/15" "Global Placement"
source $::env(SCRIPTS_DIR)/gpl.tcl

# ============================================================================
# STAGE 6: Design Optimization (Pre-CTS Resizer)
# ============================================================================
log_step "6/15" "Pre-CTS Design Optimization"
source $::env(SCRIPTS_DIR)/resizer.tcl

# ============================================================================
# STAGE 7: Timing Optimization (Pre-CTS)
# ============================================================================
log_step "7/15" "Pre-CTS Timing Optimization"
source $::env(SCRIPTS_DIR)/resizer_timing.tcl

# ============================================================================
# STAGE 8: Detailed Placement
# ============================================================================
log_step "8/15" "Detailed Placement"
source $::env(SCRIPTS_DIR)/dpl.tcl

# Save placement checkpoint
source $::env(SCRIPTS_DIR)/common/io.tcl
write_checkpoint "place"
write_timing_reports "place"

if { $stop_after == "place" } {
    log_step "DONE" "Stopping after placement (as requested)"
    exit 0
}

# ============================================================================
# STAGE 9: Clock Tree Synthesis
# ============================================================================
log_step "9/15" "Clock Tree Synthesis"
source $::env(SCRIPTS_DIR)/cts.tcl

# ============================================================================
# STAGE 10: Post-CTS Timing Optimization
# ============================================================================
log_step "10/15" "Post-CTS Timing Optimization"
source $::env(SCRIPTS_DIR)/resizer_routing_timing.tcl

# Save CTS checkpoint
write_checkpoint "cts"
write_timing_reports "cts"

if { $stop_after == "cts" } {
    log_step "DONE" "Stopping after CTS (as requested)"
    exit 0
}

# ============================================================================
# STAGE 11: Global Routing
# ============================================================================
log_step "11/15" "Global Routing"
source $::env(SCRIPTS_DIR)/groute.tcl

# ============================================================================
# STAGE 12: Detailed Routing
# ============================================================================
log_step "12/15" "Detailed Routing"
source $::env(SCRIPTS_DIR)/droute.tcl

# Save routing checkpoint
write_checkpoint "route"

if { $stop_after == "route" } {
    log_step "DONE" "Stopping after routing (as requested)"
    write_timing_reports "route"
    exit 0
}

# ============================================================================
# STAGE 13: Filler Cell Insertion
# ============================================================================
log_step "13/15" "Filler Cell Insertion"
source $::env(SCRIPTS_DIR)/fill.tcl

# ============================================================================
# STAGE 14: Antenna Check
# ============================================================================
log_step "14/15" "Antenna Rule Check"
source $::env(SCRIPTS_DIR)/antenna_check.tcl

# ============================================================================
# STAGE 15: Write Final Views
# ============================================================================
log_step "15/15" "Writing Final Views"
source $::env(SCRIPTS_DIR)/write_views.tcl

# ── Final Signoff Reports ──────────────────────────────────────────────────
# Re-estimate parasitics with global routing for final timing
estimate_parasitics -global_routing
write_timing_reports "final"

# Power report
report_power > "$or_dir/reports/$::env(DESIGN_NAME).final.power.rpt"

# TNS/WNS reports
report_tns > "$or_dir/reports/$::env(DESIGN_NAME).final.tns.rpt"
report_wns > "$or_dir/reports/$::env(DESIGN_NAME).final.wns.rpt"

log_step "DONE" "RTL-to-DEF flow complete!"
puts ""
puts "  Results:  $or_dir/results/"
puts "  Reports:  $or_dir/reports/"
puts ""
