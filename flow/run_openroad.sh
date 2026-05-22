#!/usr/bin/env bash
set -euo pipefail

FLOW_ROOT="$(cd "$(dirname "$0")" && pwd)"
# shellcheck source=/dev/null
source "$FLOW_ROOT/env.sh"

# Create directory hierarchy
mkdir -p "$OUT_DIR/openroad/results" "$OUT_DIR/openroad/reports"
mkdir -p "$FLOW_ROOT/logs"

LOG_FILE="$FLOW_ROOT/logs/openroad_$(date +%Y%m%d_%H%M%S).log"

echo "╔═══════════════════════════════════════════════════════════════╗"
echo "║  OpenROAD Place-and-Route                                     ║"
echo "╠═══════════════════════════════════════════════════════════════╣"
echo "║  Design : $DESIGN_NAME"
echo "║  PDK    : $PDKPATH"
echo "║  Netlist: $YOSYS_OUT_DIR/results/${DESIGN_NAME}.synth.v"
if [ -n "${OPENROAD_STOP_AFTER:-}" ]; then
    echo "║  Stage  : stop after $OPENROAD_STOP_AFTER"
fi
echo "║  Log    : $LOG_FILE"
echo "╚═══════════════════════════════════════════════════════════════╝"

# Validate netlist exists
if [ ! -f "$YOSYS_OUT_DIR/results/${DESIGN_NAME}.synth.v" ]; then
    echo "[ERROR] Synthesized netlist not found!"
    echo "        Expected: $YOSYS_OUT_DIR/results/${DESIGN_NAME}.synth.v"
    echo "        Run 'make pd-synth' first."
    exit 1
fi

# Export SCRIPTS_DIR for TCL scripts
export SCRIPTS_DIR="$FLOW_ROOT/openroad/scripts"

openroad -exit "$FLOW_ROOT/openroad/flow.tcl" 2>&1 | tee "$LOG_FILE"

echo ""
echo "✓ OpenROAD finished. Log saved to: $LOG_FILE"
