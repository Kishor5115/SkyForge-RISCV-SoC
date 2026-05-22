# OpenLane Yosys vs my_tpu Yosys

This compares the OpenLane-style Yosys flow used in this repo to the
standalone Yosys flow used in my_tpu.

For a from-scratch, pass-by-pass explanation of the OpenLane-style scripts in
this repo, see: `my_docs/yosys_scripts_deep_dive.md`.

## High-level differences

1) Configuration model
- OpenLane: uses environment variables (LIB_SYNTH, SYNTH_STRATEGY, etc.) and
  expects the caller to prepare temp/report/output directories.
- my_tpu: uses Tcl variables inside the script (DESIGN, RTL_DIR, CLK_PERIOD,
  PDK paths) and creates output directories itself.

2) Library handling
- OpenLane: separates libraries into typical/complete/no-pg and can read
  extra macro libs as blackboxes (EXTRA_LIBS). This is used to keep SRAMs
  as blackboxes while still mapping logic to standard cells.
- my_tpu: reads all standard cell, SRAM, and IO libs up front, then explicitly
  marks SRAM macros with keep_hierarchy/blackbox to preserve them.

3) Constraints and optimization
- OpenLane: builds an SDC with set_driving_cell and set_load and runs ABC with
  multi-strategy scripts (AREA/DELAY) and optional buffering/sizing. It uses
  a large suite of optimization passes before and after techmap.
- my_tpu: uses a simpler flow (synth -noabc, dfflibmap, then a short ABC
  script) and relies on a single CLK_PERIOD for timing (no SDC file).

4) Output structure
- OpenLane: produces multiple reports for each strategy under
  synth_report_prefix, and writes the selected netlist to SAVE_NETLIST.
- my_tpu: writes explicit report files (area, check, width) and a post-ABC
  netlist, then does splitnets + hilomap for tie cells.

5) Macro handling
- OpenLane: macro libs can be read as blackboxes via EXTRA_LIBS. The RTL
  macro wrapper is still compiled so the top-level hierarchy is preserved.
- my_tpu: explicitly sets keep_hierarchy and keep on SRAM macro instances
  and enforces blackbox with the blackbox command.

## What this means in practice

- The OpenLane flow is more parameterized and tuned for multi-corner, multi-
  strategy synthesis with strong alignment to OpenROAD usage.
- The my_tpu flow is a focused, single-purpose script optimized for a specific
  TPU macro design and the IHP SG13G2 PDK layout style.

## When to use which

- Use the OpenLane-style flow when you want behavior consistent with
  OpenLane/OpenROAD expectations, or if you need to compare results with
  OpenLane runs.
- Use the my_tpu flow when you want a compact, single-script synthesis and
  you are staying inside the IHP SG13G2 setup with fixed libraries.
