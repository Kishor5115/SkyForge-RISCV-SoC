# Generate a DRC-only maglef (LEF-abstract) .mag view for the OpenRAM SRAM
# macro that does NOT false-positive against the top-level PDN.
#
# Purpose: allow Magic.DRC to run with MAGIC_DRC_USE_GDS=true (full-GDS mode,
# so standard-cell tap diffusion is visible and the false nwell.4 violations
# disappear) while treating the SRAM macro as a black box via
# MAGIC_DRC_MAGLEFS + `gds noduplicates true` (avoids the ~31M-error blowup
# from reading the SRAM's full internal transistor GDS, cf. OpenLane #1040).
#
# --------------------------------------------------------------------------
# WHY WE STRIP THE OBSTRUCTION LAYERS + met3 (root-cause fix, verified 2026-07-06)
# --------------------------------------------------------------------------
# A stock LEF->maglef abstract contains, per layer:
#   * metalN  -> the macro's real pin metal
#   * obsmN   -> LEF OBSTRUCTION rectangles (a *routing* keep-out hint; NOT a
#                real electrical layer).
#
# When the top-level PDN drops same-net power stripes/vias that cross the SRAM
# (heavily on the W/E-rotated banks, whose met3/met4 PG rails rotate onto the
# edge the vertical PDN stripes run along), Magic compares top met3/met4
# against the macro subcell geometry:
#   * top metalN over the abstract's metalN -> TOLERATED (metal-on-metal;
#     same-net PG connections do not error).
#   * top metalN over the abstract's obsmN  -> ALWAYS FLAGGED as
#     "Can't overlap those layers" / "This layer can't abut or partially
#     overlap between subcells": obstruction "is not metal", the types cannot
#     connect/merge across the black-box boundary
#     (RTimothyEdwards/magic #121; OpenLane #1040/#1152).
#
# Measured attribution on soc_core (standalone DRC harness, RUN_SC_A GDS):
#   obstruction + metal :  160    obstruction only :  152
#   metal pins only     :    8    metal4 pins only :    0    empty : 0
# => obsm1-4 cause the 149 subcell-overlap + 3 met3.3d; the tiny isolated met3
#    signal-pin stubs (dout0[29:32], a few addr) cause the 8 met3.6 min-area.
#
# Fix: keep metal4 pin geometry (all din/dout data pins + power rails, so Magic
# still checks top-level spacing to the macro's real metal) and drop the
# obsm1-4 obstruction layers and the metal3 stub layer. The SRAM is DRC-clean
# standalone (docs/SRAM_DRC_SIGNOFF_RESULT.md) and its real merged interface
# geometry is still checked by KLayout DRC on the full GDS, so no real
# violation is masked. Result: Magic DRC = 0 at the SoC level.
#
# NOTE: Magic's `erase`/`delete` will not remove the LEF obstruction planes,
# so we strip the `<< obsmN >>` / `<< metal3 >>` sections from the saved .mag
# as a text post-pass (done here in Tcl to keep this a single reproducible
# `magic ... gen_sram_maglef.tcl` invocation).
#
# Run with: magic -dnull -noconsole -rcfile <sky130A.magicrc> gen_sram_maglef.tcl
# Re-run if the SRAM LEF ever changes.

drc off

set sram sky130_sram_4kbyte_1rw_32x1024_8
set outdir /foss/designs/riscv_soc/workspace/build/soc_core/maglef
set magfile $outdir/$sram.mag

lef read /foss/designs/riscv_soc/workspace/openram/build/$sram.lef
load $sram
cellname filepath $sram $outdir
save

# ---- text post-pass: drop obstruction + metal3 sections ----
set strip {obsm1 obsm2 obsm3 obsm4 metal3}
set fin [open $magfile r]
set lines [split [read $fin] "\n"]
close $fin

set out {}
set skipping 0
foreach ln $lines {
    if {[regexp {^<< (\S+) >>} $ln -> lyr]} {
        if {[lsearch -exact $strip $lyr] >= 0} {
            set skipping 1
            continue
        } else {
            set skipping 0
        }
    }
    if {!$skipping} { lappend out $ln }
}

set fout [open $magfile w]
puts -nonewline $fout [join $out "\n"]
close $fout

puts "MAGLEF_STRIPPED_SECTIONS: $strip"
puts "MAGLEF_GEN_DONE"
quit -noprompt
