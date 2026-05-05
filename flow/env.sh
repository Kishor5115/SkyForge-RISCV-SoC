#!/usr/bin/env bash

# Flow root (this directory)
FLOW_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# PDK setup
export PDK_ROOT="${PDK_ROOT:-/home/kishor/pdk}"
export PDK="${PDK:-sky130A}"
export PDKPATH="${PDKPATH:-$PDK_ROOT/$PDK}"
export STD_CELL_LIBRARY="${STD_CELL_LIBRARY:-sky130_fd_sc_hd}"

# Standard cell views
export TECH_LEF="${TECH_LEF:-$PDKPATH/libs.ref/sky130_fd_sc_hd/techlef/sky130_fd_sc_hd__nom.tlef}"
export STD_CELL_LEF="${STD_CELL_LEF:-$PDKPATH/libs.ref/sky130_fd_sc_hd/lef/sky130_fd_sc_hd.lef}"
export STD_CELL_LIB="${STD_CELL_LIB:-$PDKPATH/libs.ref/sky130_fd_sc_hd/lib/sky130_fd_sc_hd__tt_025C_1v80.lib}"

# OpenLane-style synthesis defaults (Sky130 HD)
export LIB_SYNTH="${LIB_SYNTH:-$STD_CELL_LIB}"
export LIB_TYPICAL="${LIB_TYPICAL:-$STD_CELL_LIB}"
export LIB_SYNTH_NO_PG="${LIB_SYNTH_NO_PG:-$STD_CELL_LIB}"
export LIB_SYNTH_COMPLETE_NO_PG="${LIB_SYNTH_COMPLETE_NO_PG:-$STD_CELL_LIB}"
export SYNTH_DRIVING_CELL="${SYNTH_DRIVING_CELL:-sky130_fd_sc_hd__inv_2}"
export SYNTH_DRIVING_CELL_PIN="${SYNTH_DRIVING_CELL_PIN:-Y}"
export OUTPUT_CAP_LOAD="${OUTPUT_CAP_LOAD:-33.442}"
export SYNTH_MIN_BUF_PORT="${SYNTH_MIN_BUF_PORT:-sky130_fd_sc_hd__buf_2 A X}"
export SYNTH_TIEHI_PORT="${SYNTH_TIEHI_PORT:-sky130_fd_sc_hd__conb_1 HI}"
export SYNTH_TIELO_PORT="${SYNTH_TIELO_PORT:-sky130_fd_sc_hd__conb_1 LO}"
export MAX_FANOUT_CONSTRAINT="${MAX_FANOUT_CONSTRAINT:-10}"
export MAX_TRANSITION_CONSTRAINT="${MAX_TRANSITION_CONSTRAINT:-0.75}"

# OpenRAM macro views
export SRAM_LEF="${SRAM_LEF:-$FLOW_ROOT/../openram/build/sky130_sram_4kbyte_1rw_32x1024_8.lef}"
export SRAM_LIB="${SRAM_LIB:-$FLOW_ROOT/../openram/build/sky130_sram_4kbyte_1rw_32x1024_8_TT_1p8V_25C.lib}"

# Design configuration
export DESIGN_NAME="${DESIGN_NAME:-soc_top}"
export CLOCK_PERIOD="${CLOCK_PERIOD:-10.0}"
export SDC_FILE="${SDC_FILE:-$FLOW_ROOT/constraints/soc_top.sdc}"
export OUT_DIR="${OUT_DIR:-$FLOW_ROOT/out}"

# Yosys-specific output root
export YOSYS_DIR="${YOSYS_DIR:-$FLOW_ROOT/yosys}"
export YOSYS_OUT_DIR="${YOSYS_OUT_DIR:-$YOSYS_DIR/out}"
