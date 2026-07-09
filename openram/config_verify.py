"""
OpenRAM SKY130 SRAM config — FULL DRC/LVS VERIFICATION build.

Purpose: regenerate the SAME 4KB (32b x 1024, byte-write, 1RW) macro that is
integrated into soc_core, but this time WITH DRC + LVS verification enabled
(check_lvsdrc=True), matching the official OpenRAM reference config
(macros/sram_configs/sky130_sram_4kbyte_1rw_32x1024_8.py -> sky130_sram_common.py).

CRITICAL — geometry is IDENTICAL to config.py so the regenerated GDS keeps the
exact same 808.845 x 351.29 um footprint. This preserves the area-optimized
soc_core floorplan (macro placement/rotation unchanged). DO NOT change
num_spare_rows / num_spare_cols / words_per_row / word_size / num_words here —
any of those changes the physical dimensions and breaks the floorplan.

Output name is kept IDENTICAL to the integrated macro so the verified views
drop straight back into the flow (no _signoff suffix).
"""

import os

# ---- SRAM organization (IDENTICAL to config.py -> same dimensions) ----
word_size = 32          # bits
num_words = 1024
write_size = 8          # bits (byte write-mask)
num_banks = 1

human_byte_size = "{:.0f}kbyte".format((word_size * num_words) / 1024 / 8)

# Port mode fixed to 1rw (the integrated macro). Spare row/col = 1 (MUST match).
num_rw_ports  = 1
num_r_ports   = 0
num_w_ports   = 0
num_spare_rows = 1
num_spare_cols = 1
words_per_row  = 8
ports_human    = "1rw"

# ---- Technology ----
tech_name = "sky130"
nominal_corner_only = True

# ---- Physical / VERIFICATION settings (the whole point of this file) ----
route_supplies = "ring"
check_lvsdrc   = True    # <<< ENABLE DRC + LVS on the top-level SRAM
inline_lvsdrc  = False   # top-level only (matches official; inline is far slower)
uniquify       = True

# ---- FIX for real failure seen in the first run ----
# OpenRAM's run_script.py wraps DRC/LVS shell scripts with:
#     source {CONDA_HOME}/bin/activate
# but write_lvs_script()/write_drc_script() in verify/magic.py generate those
# scripts with "#!/bin/sh". On this system /bin/sh -> dash, which has NO
# `source` builtin (only bash does) -> the LVS script died immediately at
# that line, netgen never ran, and sky130_sram_..._1rw_32x1024_8.lvs.report
# was never created -> "Unable to load LVS results" / FileNotFoundError.
# Fix: disable the conda-activation wrapper entirely. klayout/magic/netgen
# are already directly on PATH (confirmed), so conda activation is not
# needed for this environment.
use_conda = False

# ---- Keep characterization FAST (DRC/LVS is the goal, not timing) ----
# analytical_delay=True avoids multi-hour SPICE characterization.
analytical_delay = True
model_name = "cacti"
num_sim_threads = 1
num_threads = 1
netlist_only = False
output_extended_config = True

# ---- Output naming/path — IDENTICAL to config.py (no _signoff suffix) ----
output_name = "{tech_name}_sram_{human_byte_size}_{ports_human}_{word_size}x{num_words}_{write_size}".format(**locals())
output_path = os.path.join(os.path.dirname(__file__), "build_verify")
