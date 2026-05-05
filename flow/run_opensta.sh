#!/usr/bin/env bash
set -euo pipefail

FLOW_ROOT="$(cd "$(dirname "$0")" && pwd)"
# shellcheck source=/dev/null
source "$FLOW_ROOT/env.sh"

mkdir -p "$OUT_DIR/sta"

sta -exit -no_init "$FLOW_ROOT/opensta/sta.tcl" | tee "$OUT_DIR/sta/sta.log"
