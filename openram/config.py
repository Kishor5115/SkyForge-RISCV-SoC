"""
OpenRAM SKY130 SRAM macro config.

Default target:
  4KB (32-bit x 1024 words), byte-write (write_size=8), single-port 1RW.

The core dimensions match the public VLSIDA/OpenRAM SKY130 4KB SRAM configs.
Set OPENRAM_PORT_MODE=1rw1r to generate the alternate 1RW + 1R macro.
"""

import os

# SRAM organization
word_size = 32  # bits
num_words = 1024
write_size = 8  # bits (byte write-mask capable)
num_banks = 1

human_byte_size = "{:.0f}kbyte".format((word_size * num_words) / 1024 / 8)

# Port mode:
#   "1rw"   -> 1 read/write port
#   "1rw1r" -> 1 read/write + 1 read-only port
port_mode = os.environ.get("OPENRAM_PORT_MODE", "1rw").lower()

if port_mode == "1rw":
    num_rw_ports = 1
    num_r_ports = 0
    num_w_ports = 0
    num_spare_rows = 1
    num_spare_cols = 1
    words_per_row = 8
    ports_human = "1rw"
elif port_mode == "1rw1r":
    num_rw_ports = 1
    num_r_ports = 1
    num_w_ports = 0
    # Sky130/OpenRAM parity rule in this branch:
    # keep effective row count even for replica-column mirroring.
    num_spare_rows = 0
    num_spare_cols = 1
    words_per_row = 4
    ports_human = "1rw1r"
else:
    raise ValueError("Unsupported port_mode: {}".format(port_mode))

# Technology setup
tech_name = "sky130"
nominal_corner_only = True

# Physical/signoff defaults
route_supplies = "ring"
check_lvsdrc = False
uniquify = True

# Stable runtime defaults
analytical_delay = True
model_name = "cacti"
num_sim_threads = 1
num_threads = 1
netlist_only = False
output_extended_config = True

# Output naming/path (professional macro-style naming)
output_name = "{tech_name}_sram_{human_byte_size}_{ports_human}_{word_size}x{num_words}_{write_size}".format(**locals())
output_path = os.path.join(os.path.dirname(__file__), "build")
