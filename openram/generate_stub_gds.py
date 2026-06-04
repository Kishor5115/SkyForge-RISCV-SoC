#!/usr/bin/env python3
"""
generate_stub_gds.py — create a minimal stub GDS for the sky130 SRAM macro
so OpenLane LVS/Magic extraction can proceed without a full OpenRAM compile.

The stub contains:
  - A top-level cell with the correct name
  - The correct bounding box (from LEF)
  - Power / ground label text on met4 (so LVS_CONNECT_BY_LABEL works)
  - Port labels matching the SPICE netlist

Usage:
    pip install gdspy
    python3 generate_stub_gds.py
    # Outputs: sky130_sram_4kbyte_1rw_32x1024_8.gds
"""

import sys

try:
    import gdspy
except ImportError:
    sys.exit("Install gdspy first:  pip install gdspy")

CELL_NAME = "sky130_sram_4kbyte_1rw_32x1024_8"

# From the LEF MACRO SIZE line (units: µm)
WIDTH  = 479.22
HEIGHT = 479.22

lib = gdspy.GdsLibrary()
cell = lib.new_cell(CELL_NAME)

# Boundary rectangle on layer 235 (prBoundary in sky130)
cell.add(gdspy.Rectangle((0, 0), (WIDTH, HEIGHT), layer=235, datatype=4))

# met4 power straps (layer 71) — horizontal stripes for vccd1 / vssd1
stripe_h = 1.6   # µm wide
for y_center in [4.0, HEIGHT - 4.0]:
    cell.add(gdspy.Rectangle(
        (0, y_center - stripe_h / 2),
        (WIDTH, y_center + stripe_h / 2),
        layer=71, datatype=0
    ))

# met4 text labels for power nets (layer 71, texttype 5)
cell.add(gdspy.Label("vccd1", (WIDTH / 2, HEIGHT - 4.0), layer=71, texttype=5))
cell.add(gdspy.Label("vssd1", (WIDTH / 2, 4.0),          layer=71, texttype=5))

# Port labels on met3 (layer 68) at left edge
signal_ports = [
    "clk0", "csb0", "web0", "spare_wen0",
    "addr0[0]",  "addr0[1]",  "addr0[2]",  "addr0[3]",
    "addr0[4]",  "addr0[5]",  "addr0[6]",  "addr0[7]",
    "addr0[8]",  "addr0[9]",  "addr0[10]",
    "wmask0[0]", "wmask0[1]", "wmask0[2]", "wmask0[3]",
] + [f"din0[{i}]"  for i in range(32)] \
  + [f"dout0[{i}]" for i in range(32)]

pitch = (HEIGHT - 20) / max(len(signal_ports), 1)
for idx, name in enumerate(signal_ports):
    y = 10 + idx * pitch
    cell.add(gdspy.Label(name, (2.0, y), layer=68, texttype=5))

out_file = "sky130_sram_4kbyte_1rw_32x1024_8.gds"
lib.write_gds(out_file)
print(f"Wrote stub GDS → {out_file}  ({WIDTH} × {HEIGHT} µm)")
print("NOTE: This is a STUB for LVS flow only — not a physical implementation.")
