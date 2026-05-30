# Signoff-oriented OpenRAM configuration for the same 4KB SKY130 macro.
# This file intentionally enables slower checks after the base build succeeds.

from config import *  # reuse stable geometry/port settings

# Enable full characterization and final top-level checks.
analytical_delay = False
check_lvsdrc = True

# Keep simulator thread count modest to reduce memory pressure.
num_sim_threads = 1

# Distinguish outputs from the fast/stable run.
output_name = output_name + "_signoff"
