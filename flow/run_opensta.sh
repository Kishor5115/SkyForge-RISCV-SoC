#!/usr/bin/env bash
set -euo pipefail

FLOW_ROOT="$(cd "$(dirname "$0")" && pwd)"
# shellcheck source=/dev/null
source "$FLOW_ROOT/env.sh"

mkdir -p "$OUT_DIR/sta"
mkdir -p "$FLOW_ROOT/logs"

LOG_FILE="$FLOW_ROOT/logs/sta_$(date +%Y%m%d_%H%M%S).log"

echo "╔═══════════════════════════════════════════════════════════════╗"
echo "║  OpenSTA Timing Analysis                                      ║"
echo "╠═══════════════════════════════════════════════════════════════╣"
echo "║  Design : $DESIGN_NAME"
echo "║  Netlist: $YOSYS_OUT_DIR/results/${DESIGN_NAME}.synth.v"
echo "║  Log    : $LOG_FILE"
echo "╚═══════════════════════════════════════════════════════════════╝"

# Validate netlist exists
if [ ! -f "$YOSYS_OUT_DIR/results/${DESIGN_NAME}.synth.v" ]; then
    echo "[ERROR] Synthesized netlist not found!"
    echo "        Expected: $YOSYS_OUT_DIR/results/${DESIGN_NAME}.synth.v"
    echo "        Run 'make pd-synth' first."
    exit 1
fi

sta -exit -no_init "$FLOW_ROOT/opensta/sta.tcl" 2>&1 | tee "$LOG_FILE"

echo ""
echo "✓ STA finished. Log saved to: $LOG_FILE"
