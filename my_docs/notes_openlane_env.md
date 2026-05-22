# OpenLane-style env variables used by the flow

These are the key environment variables the OpenLane Yosys script expects.
They are set in flow/env.sh and flow/run_yosys.sh.

- DESIGN_NAME: top module name.
- VERILOG_FILES: space-separated RTL file list.
- LIB_SYNTH / LIB_SYNTH_NO_PG: standard cell liberty for mapping and stats.
- SYNTH_DRIVING_CELL / OUTPUT_CAP_LOAD: used to build the synthesis SDC.
- SYNTH_STRATEGY: selects one of the OpenLane ABC scripts.
- SYNTH_TIEHI_PORT / SYNTH_TIELO_PORT: tie cell ports for hilomap.
- SYNTH_SPLITNETS / SYNTH_BUFFER_DIRECT_WIRES: post-ABC netlist cleanup.
- SAVE_NETLIST: output netlist path.
