#!/usr/bin/env bash
# =============================================================================
# Regenerate the soc_core SRAM macro WITH full DRC + LVS verification.
# Runs on the HOST (OpenRAM miniconda tools: klayout / magic / netgen).
# No Docker required. No credit cost. ~2-3 hours wall-clock.
#
# Usage (from repo root /home/kishor/riscv-soc):
#     bash openram/run_verify.sh
#
# Watch live in another terminal:
#     tail -f openram/build_verify/verify_run.log
# =============================================================================
set -u

REPO=/home/kishor/riscv-soc
export OPENRAM_ROOT=/home/kishor/OpenRAM
export PDK_ROOT=/home/kishor/pdk/ciel/sky130/versions/0fe599b2afb6708d281543108caf8310912f54af
export OPENRAM_TMP=/tmp/openram_verify_$$

OUT=$REPO/openram/build_verify
mkdir -p "$OUT"
LOG=$OUT/verify_run.log

ts(){ date "+%Y-%m-%d %H:%M:%S"; }

{
  echo "=================================================================="
  echo "[$(ts)] START OpenRAM SRAM regeneration WITH DRC/LVS (check_lvsdrc=True)"
  echo "  OPENRAM_ROOT=$OPENRAM_ROOT"
  echo "  PDK_ROOT=$PDK_ROOT"
  echo "  OPENRAM_TMP=$OPENRAM_TMP  (kept on failure for diagnostics; see below)"
  echo "  config: openram/config_verify.py   (output -> build_verify/, use_conda=False)"
  echo "  tools:  klayout=$(command -v klayout)  magic=$(command -v magic)  netgen=$(command -v netgen)"
  echo "  /bin/sh -> $(readlink -f /bin/sh)  (dash has no 'source' builtin --"
  echo "             this is why the first run's LVS script died silently;"
  echo "             fixed via use_conda=False in config_verify.py)"
  echo "=================================================================="
} | tee "$LOG"

cd "$REPO" || { echo "cannot cd $REPO" | tee -a "$LOG"; exit 1; }

# Run generation. stdbuf keeps the log flushing live for tail -f.
stdbuf -oL -eL ./openram/generate_views.py openram/config_verify.py 2>&1 | tee -a "$LOG"
rc=${PIPESTATUS[0]}

{
  echo "=================================================================="
  echo "[$(ts)] generate_views.py exit code = $rc"
  echo "----- DRC / LVS RESULT SUMMARY (grepped from log) -----"
  grep -iE "DRC|LVS|error|violation|clean|pass|fail|mismatch|Total" "$LOG" | grep -viE "^\[" | tail -40
  echo "----- build_verify/ contents -----"
  ls -la "$OUT"
  if [ $rc -ne 0 ] && [ -d "$OPENRAM_TMP" ]; then
    echo "----- FAILURE: preserving $OPENRAM_TMP for diagnostics -----"
    echo "----- run_lvs.sh / run_drc.sh (as generated) -----"
    for f in "$OPENRAM_TMP"/run_lvs.sh "$OPENRAM_TMP"/run_drc.sh; do
      [ -f "$f" ] && { echo "--- $f ---"; cat "$f"; }
    done
    echo "----- any .out/.err/.report files present -----"
    find "$OPENRAM_TMP" -maxdepth 1 \( -name "*.out" -o -name "*.err" -o -name "*.report" \) -exec sh -c 'echo "--- {} ---"; cat "{}"' \;
  fi
  echo "[$(ts)] DONE"
  echo "=================================================================="
} | tee -a "$LOG"
