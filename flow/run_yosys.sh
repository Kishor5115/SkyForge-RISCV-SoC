#!/usr/bin/env bash
set -euo pipefail

FLOW_ROOT="$(cd "$(dirname "$0")" && pwd)"
# shellcheck source=/dev/null
source "$FLOW_ROOT/env.sh"

mkdir -p "$YOSYS_OUT_DIR/tmp" "$YOSYS_OUT_DIR/results" "$YOSYS_OUT_DIR/reports" "$YOSYS_OUT_DIR/logs"
mkdir -p "$FLOW_ROOT/logs"

shopt -s nullglob
verilog_files=(
	"$FLOW_ROOT/../rtl/core"/*.sv
	"$FLOW_ROOT/../rtl/boot"/*.sv
	"$FLOW_ROOT/../rtl/interconnect"/*.sv
	"$FLOW_ROOT/../rtl/peripherals"/*/*.sv
	"$FLOW_ROOT/../rtl/memory"/*.sv
	"$FLOW_ROOT/../rtl/asic/soc_core.sv"
	"$FLOW_ROOT/../rtl/soc_top.sv"
)
shopt -u nullglob

export VERILOG_FILES="${verilog_files[*]}"
export SYNTH_DEFINES="SYNTHESIS"
export SYNTH_BUFFERING="${SYNTH_BUFFERING:-1}"
export SYNTH_SIZING="${SYNTH_SIZING:-0}"
export SYNTH_SHARE_RESOURCES="${SYNTH_SHARE_RESOURCES:-1}"
export SYNTH_SPLITNETS="${SYNTH_SPLITNETS:-1}"
export SYNTH_BUFFER_DIRECT_WIRES="${SYNTH_BUFFER_DIRECT_WIRES:-1}"
export SYNTH_STRATEGY="${SYNTH_STRATEGY:-AREA 0}"
export SYNTH_ADDER_TYPE="${SYNTH_ADDER_TYPE:-YOSYS}"
export SYNTH_NO_FLAT="${SYNTH_NO_FLAT:-0}"
export SYNTH_FLAT_TOP="${SYNTH_FLAT_TOP:-0}"
export SYNTH_READ_BLACKBOX_LIB="${SYNTH_READ_BLACKBOX_LIB:-0}"
export SYNTH_EXTRA_MAPPING_FILE="${SYNTH_EXTRA_MAPPING_FILE:-}"

export synthesis_tmpfiles="$YOSYS_OUT_DIR/tmp"
export synthesis_results="$YOSYS_OUT_DIR/results"
export synth_report_prefix="$YOSYS_OUT_DIR/reports/$DESIGN_NAME"
export SAVE_NETLIST="$YOSYS_OUT_DIR/results/${DESIGN_NAME}.synth.v"

if [[ -f "$SRAM_LIB" ]]; then
	export EXTRA_LIBS="$SRAM_LIB"
fi

LOG_FILE="$FLOW_ROOT/logs/yosys_$(date +%Y%m%d_%H%M%S).log"

echo "╔═══════════════════════════════════════════════════════════════╗"
echo "║  Yosys Synthesis                                              ║"
echo "╠═══════════════════════════════════════════════════════════════╣"
echo "║  Design : $DESIGN_NAME"
echo "║  PDK    : $STD_CELL_LIBRARY"
echo "║  Files  : ${#verilog_files[@]} RTL sources"
echo "║  Strategy: $SYNTH_STRATEGY"
echo "║  Log    : $LOG_FILE"
echo "╚═══════════════════════════════════════════════════════════════╝"

yosys -c "$FLOW_ROOT/yosys/scripts/synth.tcl" 2>&1 | tee "$LOG_FILE"

echo ""
echo "✓ Synthesis finished. Netlist: $SAVE_NETLIST"
echo "✓ Log saved to: $LOG_FILE"
