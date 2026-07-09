#!/usr/bin/env python3
"""
Report-level KLayout DRC signoff waiver for soc_core.

Separates the raw KLayout DRC count into:
  (a) REAL top-level violations (in cell `soc_core`) -> MUST be 0 for signoff, and
  (b) WAIVED SkyWater foundry-primitive SRAM checks, i.e. violations that fall
      inside the OpenRAM SRAM's `WP_sky130_sram_*` / `sky130_fd_bd_sram__*`
      subcells for the specific rules the standalone SRAM signoff already
      localized to qualified foundry cells (see docs/SRAM_DRC_SIGNOFF_RESULT.md).

This is NOT a blanket suppression. A violation is waived ONLY if BOTH:
  * its owning cell matches an SRAM foundry-primitive pattern, AND
  * its rule is in the pre-qualified foundry-primitive rule set.
Anything else (any soc_core-level violation, or an unexpected rule inside the
SRAM) is reported as REAL and fails signoff — matching how the SRAM macro was
signed off standalone.

Usage:
  python3 klayout_signoff_waiver.py <drc.klayout.lyrdb>
Exit code 0 iff REAL (non-waived) violation count == 0.
"""
import re
import sys
from collections import Counter

# SkyWater-qualified SRAM primitive cells (foundry base library, not OpenRAM-drawn)
SRAM_CELL_PATTERNS = (
    re.compile(r"^WP_sky130_sram_"),
    re.compile(r"sky130_fd_bd_sram__"),
    re.compile(r"sky130_sram_\d+kbyte"),
)
# The exact rule set localized to foundry primitives by the standalone SRAM
# signoff (docs/SRAM_DRC_SIGNOFF_RESULT.md). Only these are waivable, and only
# when inside an SRAM primitive cell.
WAIVABLE_FOUNDRY_RULES = {
    "nsdm.1", "nwell.1", "nwell.2a", "psdm.1", "m1.2", "m2.2",
}


def is_sram_primitive_cell(cell: str) -> bool:
    return any(p.search(cell) for p in SRAM_CELL_PATTERNS)


def main(path: str) -> int:
    data = open(path).read()
    items = re.findall(r"<item>.*?</item>", data, re.S)

    real = Counter()      # (cell, rule) -> count  [NOT waivable -> fails signoff]
    waived = Counter()    # rule -> count
    unexpected_in_sram = Counter()  # rule inside SRAM but NOT in waivable set

    for it in items:
        cat = re.search(r"<category>'?(.*?)'?</category>", it)
        cell = re.search(r"<cell>(.*?)</cell>", it)
        rule = cat.group(1) if cat else "?"
        cellname = cell.group(1) if cell else "?"
        if is_sram_primitive_cell(cellname):
            if rule in WAIVABLE_FOUNDRY_RULES:
                waived[rule] += 1
            else:
                unexpected_in_sram[rule] += 1
                real[(cellname, rule)] += 1
        else:
            real[(cellname, rule)] += 1

    total = len(items)
    n_waived = sum(waived.values())
    n_real = sum(real.values())

    print(f"KLayout DRC signoff waiver report for: {path}")
    print(f"  raw total violations         : {total}")
    print(f"  waived (SRAM foundry prims)  : {n_waived}")
    for r, c in sorted(waived.items(), key=lambda x: -x[1]):
        print(f"        {r:<10} {c}")
    print(f"  REAL (non-waived) violations : {n_real}")
    for (cell, rule), c in sorted(real.items(), key=lambda x: -x[1]):
        print(f"        {rule:<10} x{c:<5} in {cell}")
    if unexpected_in_sram:
        print("  !! unexpected rules inside SRAM cells (NOT auto-waived):")
        for r, c in unexpected_in_sram.items():
            print(f"        {r:<10} {c}")

    if n_real == 0:
        print("\nSIGNOFF (KLayout): CLEAN — 0 real violations "
              f"({n_waived} foundry-primitive checks waived, evidenced in "
              "docs/SRAM_DRC_SIGNOFF_RESULT.md).")
        return 0
    print(f"\nSIGNOFF (KLayout): FAIL — {n_real} real violation(s) remain.")
    return 1


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(__doc__)
        sys.exit(2)
    sys.exit(main(sys.argv[1]))
