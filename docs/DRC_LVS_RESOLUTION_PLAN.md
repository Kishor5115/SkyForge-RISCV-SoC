# soc_core DRC/LVS Resolution Plan — Task Order

**Status:** Planning document. No fixes applied yet. Companion to
`docs/SOC_CORE_DRC_LVS_OPENRAM_ANALYSIS.md` (findings) — this document defines
the **order of execution** to resolve those findings with minimum wasted flow
runs / credits.

**Ground rule:** DRC/LVS signoff is pass/fail, not a percentage. This plan
targets **0 DRC violations + clean LVS match**, not "mostly resolved." Partial
progress should be reported as exactly that — not as "solved" — until both
gates are actually clean.

**Floorplan constraint respected throughout:** macro positions, rotations
(banks 0–3 W/E, banks 4–7 N), and die/core area from `soc_core_top.yaml` are
NOT changed by any step below. Only (a) tapcell/halo/PDN parameters and (b)
the OpenRAM SRAM view's internal LEF/GDS geometry are touched.

---

## Task 1 — Isolated tapcell/halo fix loop (fixes ~77.4% of violations)

**Why first:** highest violation count (2,836 of 3,666), does not touch the
SRAM macro at all, fastest to iterate, zero risk of re-triggering the
SRAM-rotation issue while testing.

**Scope:** partial flow only — do **not** run full P&R.

1. Run `OpenROAD.Floorplan → OpenROAD.TapEndcapInsertion → Magic.DRC` only
   (skip global placement, detailed placement, CTS, routing, fill).
2. Retune candidates, one change at a time:
   - `FP_TAPCELL_DIST`
   - `PDN_HORIZONTAL_HALO` / `PDN_VERTICAL_HALO` (currently 14 µm each in
     `soc_core_top.yaml`)
3. Re-run the same isolated loop after each change and recount `nwell.4`
   violations in the open standard-cell area only (exclude anything within
   5 µm of a macro boundary — that's Task 2's territory, don't let it
   contaminate this measurement).
4. **Exit criterion:** open-area `nwell.4` violation count → 0 in the
   isolated loop.

**Do not proceed to a full flow run yet.** This task only validates the fix
in isolation.

---

## Task 2 — OpenRAM SRAM view rotation fix (fixes ~22.1% of violations)

**Why second:** smaller count than Task 1, but requires touching the actual
macro view (higher-risk change), so validate Task 1's cheaper fix first and
keep this isolated so a mistake here doesn't get confused with Task 1's
result.

**Scope:** macro regeneration is targeted, not a full OpenRAM recompile.

1. Inspect `openram/generate_views.py` (and, if needed, the underlying
   OpenRAM library layer it calls into) for how nwell/tap-ring geometry is
   emitted into the GDS relative to macro orientation. Confirm whether the
   defect is:
   - (a) tap density/continuity that's fine unrotated but breaks under 90°
     rotation in the **GDS** itself (real geometry bug), or
   - (b) an **abstraction gap** — LEF `OBS` never included nwell/tap layers
     (confirmed already: current LEF `OBS` only has met1–met4), which is
     normal for LEF, but means Magic's DRC (reading full GDS) is the only
     thing that ever exercises this geometry — so any latent issue in the
     GDS tap ring has never been caught before whole-chip DRC.
2. Patch the tap-ring/guard-ring geometry generation so it is verified
   correct under R90/R270 (mirrored/rotated) placement — this is a change to
   the SRAM macro's internal layout generation, not to its LEF port/pin
   layout, so pin coordinates and macro boundary size do NOT change (no
   downstream floorplan/placement impact).
3. Regenerate **only the physical views** (GDS + LEF) via
   `generate_views.py` — do not need `check_lvsdrc=True` /
   `analytical_delay=False` (the `config_signoff.py` full-characterization
   path) for this step; timing/Liberty are unaffected by a tap-ring fix.
4. Run `Magic.DRC` / `KLayout.DRC` standalone against a small test layout
   (or directly against the merged `soc_core` layout without a full
   placement/route re-run, if the existing routed DEF can be reused) focused
   on bank0–2 boundaries only.
5. **Exit criterion:** rotated-bank-boundary violation count → 0.

---

## Task 3 — Confirm the two fixes don't interact badly

**Why:** Task 1 changes tapcell/halo globally; Task 2 changes macro-boundary
geometry locally. They target disjoint violation sets per the original
analysis, but that should be confirmed, not assumed.

1. With both fixes in place, re-run the same **isolated** `Floorplan →
   TapEndcapInsertion → Magic.DRC` loop from Task 1 (now including the
   corrected SRAM macro view).
2. Confirm total violation count is 0, not just each fix's own target subset.
   Pay attention especially to the `u_cpu` boundary (5 violations) and the
   residual met3 area/spacing violations (~9) — confirm these clear as a
   side effect, or scope a small Task 3b if they don't.

**Do not spend a full flow run here either.** Still an isolated DRC-only
loop.

---

## Task 4 — Full end-to-end flow run (first point where LVS can be checked)

**Why last:** LVS requires a completed, routed netlist extracted from GDS —
it cannot be meaningfully evaluated from an isolated floorplan/tapcell-only
loop. This is also the point where tap/halo changes could shift routing
congestion or antenna behavior, so a full run is the only way to confirm
nothing downstream broke.

1. Run the complete flow: floorplan → placement → CTS → routing → fill →
   `Magic.DRC` + `KLayout.DRC` → `Netgen.LVS`, exactly as `RUN_SC_A` was run,
   with both Task 1 and Task 2 fixes applied.
2. **Exit criteria (all required):**
   - `OpenROAD.DetailedRouting`: 0 errors (already true before these fixes —
     confirm it stays true)
   - `Magic.DRC`: 0 errors
   - `KLayout.DRC`: 0 errors
   - `Netgen.LVS`: clean pin/device/net match, no FAIL
3. Only if all four are clean simultaneously: **this is the first point at
   which "DRC/LVS clean" can honestly be claimed.**
4. If LVS still fails at this point despite 0 DRC: revisit whether any
   power-domain (`VGND`/`VNB`/`VPB`/`VPWR`) connectivity issue remains
   independent of the tap/nwell defect — do not assume it's automatically
   fixed by Tasks 1–2 without checking the actual `lvs.netgen.json` diff.

---

## What NOT to do (to avoid repeating wasted runs)

- Do not run the full end-to-end flow to test Task 1 or Task 2 individually
  — both are cheaply testable in isolated loops first.
- Do not attempt a full OpenRAM recompile (`config_signoff.py`,
  `check_lvsdrc=True`, `analytical_delay=False`) to fix Task 2 — that reruns
  bitcell/decoder/sense-amp generation and full characterization, none of
  which are implicated in the tap-ring defect. Only the view-export step
  needs to re-run.
- Do not change floorplan macro placement/rotation to "work around" Task 2 —
  the analysis confirmed this is fixable in the macro view itself, and
  changing placement would give up the area-optimized floorplan for no
  reason.
- Do not report "N% of violations resolved" as "DRC/LVS solved" or
  "tapeout-ready" — only a simultaneous 0/0/0/clean result in Task 4
  qualifies.
