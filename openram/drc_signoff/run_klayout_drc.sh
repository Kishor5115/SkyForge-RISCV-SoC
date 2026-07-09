#!/usr/bin/env bash
# Standalone KLayout signoff DRC on the existing SRAM GDS (Option C).
# KLayout deep/hierarchical mode = memory-efficient (unlike Magic flat extraction).
set -u
OUT=/home/kishor/riscv-soc/openram/drc_signoff
PDK=/home/kishor/pdk/ciel/sky130/versions/0fe599b2afb6708d281543108caf8310912f54af
DECK=$PDK/sky130A/libs.tech/klayout/drc/sky130A_mr.drc
GDS=/home/kishor/riscv-soc/openram/build/sky130_sram_4kbyte_1rw_32x1024_8.gds
LOG=$OUT/klayout_drc.log
REPORT=$OUT/sram_drc.lyrdb

ts(){ date "+%Y-%m-%d %H:%M:%S"; }
{
  echo "=================================================================="
  echo "[$(ts)] START KLayout signoff DRC on SRAM GDS"
  echo "  GDS:    $GDS"
  echo "  DECK:   $DECK (sky130A mask-ready, deep/hierarchical, SRAM-aware)"
  echo "  REPORT: $REPORT"
  echo "  groups: feol+beol+offgrid enabled, 2 threads (limit peak RAM)"
  echo "=================================================================="
} | tee "$LOG"

export PDK_ROOT=/home/kishor/pdk/ciel/sky130/versions/0fe599b2afb6708d281543108caf8310912f54af
/usr/bin/time -v klayout -b \
  -rd input="$GDS" \
  -rd report="$REPORT" \
  -rd feol=true -rd beol=true -rd offgrid=true \
  -rd thr=2 \
  -r "$DECK" >>"$LOG" 2>&1
rc=$?
{
  echo "[$(ts)] klayout exit=$rc"
  echo "----- total violation count in report -----"
  if [ -f "$REPORT" ]; then
    grep -c "<item>" "$REPORT" 2>/dev/null | xargs echo "TOTAL DRC violations (item count):"
    echo "----- per-rule tally -----"
    grep -oE "<name>[^<]+</name>" "$REPORT" 2>/dev/null | sed 's/<[^>]*>//g' | sort | uniq -c | sort -rn | head -40
  else
    echo "NO REPORT PRODUCED (check log above for error/OOM)"
  fi
  echo "[$(ts)] DONE"
} | tee -a "$LOG"
