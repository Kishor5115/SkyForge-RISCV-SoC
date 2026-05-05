OpenLane-based Yosys scripts used by the standalone flow.

Scripts live under `flow/yosys/scripts/`:
- synth.tcl: main synthesis script (mirrors OpenLane flow).
- elaborate.tcl: hierarchy + basic checks (used by OpenLane during elaborate-only runs).
- rewrite_verilog.tcl: rewrite netlist with explicit wires.
- logic_equiv_check.tcl: LEC between pre/post netlists.
