# Script reference (basic)

This describes the bash and Yosys scripts used by the standalone flow.

For an in-depth explanation of the Yosys pass flow and how the OpenLane-style
strategy mapping works, see: `my_docs/yosys_scripts_deep_dive.md`.

## Bash scripts

1) flow/env.sh
- Purpose: set PDK paths, standard cell library, macro LEF/LIB locations, and
  OpenLane-style synthesis defaults (tie cells, loads, fanout limits).
- Used by: all flow entry scripts.

2) flow/run_yosys.sh
- Purpose: build a deterministic RTL file list, set OpenLane env variables,
  then run the OpenLane-style Yosys synth script.
- Key outputs:
  - flow/yosys/out/results/<design>.synth.v
  - flow/yosys/out/reports/
  - flow/yosys/out/logs/yosys.log

3) flow/run_opensta.sh
- Purpose: run OpenSTA on the synthesized netlist using flow/opensta/sta.tcl.
- Key outputs: timing reports under out/sta/.

4) flow/run_openroad.sh
- Purpose: run a minimal OpenROAD PnR flow using flow/openroad/flow.tcl.
- Key outputs: DEF/PNR netlist/SDC under out/openroad/.

5) scripts/env.sh
- Purpose: wrapper that sources flow/env.sh for convenience.

6) scripts/run_yosys.sh, scripts/run_opensta.sh, scripts/run_openroad.sh
- Purpose: wrappers that call the corresponding flow/run_*.sh scripts.

## Yosys scripts (OpenLane style)

1) flow/yosys/scripts/synth.tcl
- Main synthesis script used by OpenLane.
- Reads RTL from VERILOG_FILES, applies optimization passes, performs techmap
  and ABC with a strategy (SYNTH_STRATEGY), then emits SAVE_NETLIST.
- Uses OpenLane env variables for buffering, sizing, tie cell insertion, and
  splitnets.

2) flow/yosys/scripts/elaborate.tcl
- Loads RTL and performs early hierarchy checks, splitnets, and a quick stat.
- Used by OpenLane when running an elaborate-only step.

3) flow/yosys/scripts/rewrite_verilog.tcl
- Rewrites a netlist from SAVE_NETLIST to ensure explicit wire declarations.
- Helpful after OpenROAD writes out a netlist.

4) flow/yosys/scripts/logic_equiv_check.tcl
- Loads a "gold" and "gate" netlist, then runs Yosys LEC to confirm
  equivalence. This mirrors OpenLane's optional LEC step.
