# soc_core Physical Verification: DRC/LVS Findings and OpenRAM SRAM Macro Assessment

**Date:** 2026-07-03
**Scope:** `soc_core` (hardened PicoRV32 + 8x OpenRAM 4KB SRAM banks), run tag `RUN_SC_A`,
LibreLane Classic flow, sky130A / sky130_fd_sc_hd.
**Author's role for this analysis:** treating this as a macro-integration / physical
verification review, the way a macro-generation specialist would sign off (or not) on a
macro before it is released for reuse.

This is a **separate, independent finding from the `soc_padring` investigation**
(`docs/PADRING_ROOT_CAUSE_AND_PATH_FORWARD.md`). `soc_core` itself — the actual chip macro,
not the pad-ring wrapper — has never been fully DRC/LVS-clean. This was not previously
called out explicitly in project status docs; this document does so with data.

---

## 1. Headline result

`soc_core`'s most recent complete signoff run (`RUN_SC_A`) reports:

| Check | Result |
|---|---|
| `OpenROAD.DetailedRouting` (routing DRC) | **0 errors** (converged cleanly after 10 iterations: 6726 → 3049 → … → 0) |
| `Magic.DRC` (physical/layer DRC) | **3,666 errors** |
| `KLayout.DRC` (physical/layer DRC, independent engine) | **2,737 errors** |
| `Netgen.LVS` | **FAIL** — "Top level cell failed pin matching." 8 device differences, 22 LVS errors, 1 unmatched device, 1 unmatched net, 4 unmatched pins. Device count mismatch: 13,442 vs. 13,450. Net count mismatch: 13,694 vs. 13,702. |
| Antenna | 11 violating nets / 13 violating pins (412 diodes inserted by repair) — separate, minor issue, not analyzed further here |

**Routing itself is clean.** The failures are entirely in the physical-layer DRC deck and
in LVS device/net matching — i.e., this is a **physical macro-correctness problem**, not a
routing-congestion or connectivity-at-the-netlist-level problem.

## 2. DRC violation breakdown (Magic, 3,666 total — parsed directly from `drc.magic.rpt`)

| Count | Rule |
|---|---|
| 1,958 | `All nwells must contain metal-connected N+ taps (nwell.4)` |
| 1,175 | `Can't overlap those layers` |
| 519 | `This layer can't abut or partially overlap between subcells` |
| 7 | `Metal3 minimum area < 9600 (met3.6)` |
| 2 | `Metal3 > 3um spacing to unrelated m3 < 80 (met3.3d)` |

**3,652 of 3,666 (99.6%) are nwell-tap / cross-subcell-abutment / layer-overlap
violations** — a coherent, single-family issue, not scattered noise.

### 2.1 Where the violations physically are

Cross-referencing each violation's centroid against the actual macro placement coordinates
from `librelane/soc_core_top.yaml`:

| Location | Count | % |
|---|---|---|
| Open standard-cell area (>5 µm from any macro boundary) | 2,836 | 77.4% |
| `bank2` (SRAM, **E**-rotated) boundary | 404 | 11.0% |
| `bank0` (SRAM, **W**-rotated) boundary | 337 | 9.2% |
| `bank1` (SRAM, **W**-rotated) boundary | 69 | 1.9% |
| `bank3` (SRAM, **E**-rotated) | 0 | — |
| `bank4`–`bank7` (SRAM, **N**-oriented, top row) | 7 total | 0.2% |
| `u_cpu` (picorv32_axi macro) boundary | 5 | 0.1% |

**Key pattern: violations concentrate overwhelmingly on the four *rotated* SRAM banks
(0–3, placed W/E) and are nearly absent on the four *unrotated* banks (4–7, placed N).**
This is a strong, specific signal — not "the SRAM view is generically bad," but "the SRAM
view's DRC/tap behavior breaks specifically under 90°-rotated placement."

## 3. Is this the OpenRAM SRAM macro's view quality? — Yes, but only part of the picture

### 3.1 Evidence the OpenRAM macro view IS a contributing factor
- 810 of 3,666 violations (22%) sit directly on/inside the four rotated SRAM bank
  footprints, and are absent on the identical macro used unrotated. A LEF/GDS abstract
  view's `OBS` (obstruction) layers and boundary geometry are computed for the macro's
  native (unrotated) orientation; if the view generator (`openram/generate_views.py`,
  per this project's README) did not fully account for rotation when emitting `nwell`/tap
  connectivity information in the LEF abstraction, Magic's DRC (which reads the *actual*
  rotated GDS instance, not just the LEF) will see nwell taps that appear disconnected
  relative to where the DRC deck expects them post-rotation.
- This project's OpenRAM integration is explicitly described in its own docs as generating
  a **minimal, macro-blackboxed view** (`LVS_FLATTEN_CELLS: sky130_sram_4kbyte_1rw_32x1024_8`,
  `IGNORE_DISCONNECTED_MODULES` in `soc_core_top.yaml` — the SRAM's internals are
  intentionally not LVS-checked in detail). A minimal view is a legitimate, standard
  technique to keep LVS/DRC tractable for macro reuse, but it also means: **whatever the
  view generator does NOT correctly abstract (e.g., per-orientation nwell tap density,
  guard-ring continuity) will not be caught by a fast blackbox LVS check and will only
  surface here, in whole-chip Magic/KLayout DRC** — exactly what is observed.

### 3.2 Evidence it is NOT *only* the SRAM macro
- 77.4% of violations are in open standard-cell area, far (>5 µm) from any macro edge —
  too far to be a macro-boundary/halo artifact. The dominant rule there is the same
  `nwell.4` (tap) rule, meaning **`OpenROAD.TapEndcapInsertion`'s own tap-cell placement
  across the standard-cell rows is not achieving full nwell-tap coverage** for this
  floorplan, independent of the SRAM macros.
- 21,037 tap cells were inserted (`design__instance__count__class:tap_cell` metric) — a
  very large count, so this is not "too few taps were placed"; it is more consistent with
  a **halo/pitch/row-alignment interaction** between `PDN_HORIZONTAL_HALO`/`PDN_VERTICAL_HALO`
  (currently 14 µm, per `soc_core_top.yaml`) and `FP_TAPCELL_DIST`, especially around the
  irregular floorplan shape this design uses (rotated SRAM columns flanking the CPU,
  non-uniform row lengths at different y-bands — see the floorplan diagram in
  `soc_core_top.yaml`'s header comment).

### 3.3 LVS failure is consistent with the same root cause
The LVS mismatch is entirely on **power-domain pins** (`VGND`, `VNB`, `VPB`, `VPWR` appear
in every mismatched device/pin group in `lvs.netgen.json`) — not on any functional/logic
signal. A tap-cell/nwell continuity problem that Magic's DRC deck flags as `nwell.4`
violations is exactly the kind of defect that also produces power-net LVS mismatches
(missing or extra tap-to-nwell connections change which devices netgen considers connected
to which power net). **The DRC and LVS failures are very likely the same underlying defect
observed through two different tools**, not two independent problems.

## 4. Assessment (macro-integration reviewer's judgment)

If this were a real macro-reuse sign-off:
- **Do not release `soc_core` as "DRC/LVS clean" as-is.** The routing is genuinely clean,
  but the physical/tap layer is not, and LVS does not match. This would fail signoff.
- **Root cause is most likely a `TapEndcapInsertion` configuration issue interacting with
  (a) this floorplan's irregular macro layout and (b) the OpenRAM SRAM view's rotation
  handling** — not a single simple bug, but two compounding, both fixable, issues:
  1. Re-tune `FP_TAPCELL_DIST` / `PDN_HORIZONTAL_HALO` / `PDN_VERTICAL_HALO` for this
     floorplan's actual row geometry, and re-run `OpenROAD.TapEndcapInsertion` +
     `Magic.DRC` in isolation (fast iteration loop) to confirm the open-area violations
     (77.4% of the total) clear.
  2. Inspect `openram/generate_views.py`'s LEF emission for the SRAM macro specifically for
     rotation-dependent nwell/OBS layer handling, or — faster — regenerate the SRAM view
     and re-run DRC with only banks 0–3 (the rotated ones) to confirm whether the
     macro-boundary violations (22% of the total) are eliminated by a corrected view or
     persist regardless (which would point back to placement/tap-pitch instead).
- **This is unrelated to the `soc_padring` investigation.** `soc_padring`'s blocker is a
  tooling/PDK limitation (Classic flow cannot route to sky130 bond pads). `soc_core`'s DRC/
  LVS failures are a real, fixable macro-integration defect in this project's own floorplan/
  tapcell/OpenRAM-view configuration — squarely within this project's own control to fix,
  and should be prioritized before any further padring work, since a padring wrapping a
  non-DRC-clean core doesn't produce a tapeable chip either way.

## 5. Recommended next steps (not yet executed — this document is findings only)
1. Reproduce with a fast isolated loop: `OpenROAD.Floorplan` → `OpenROAD.TapEndcapInsertion`
   → `Magic.DRC` only (skip placement/routing/CTS) to confirm whether tap-cell coverage
   alone explains the 2,836 open-area violations, without waiting for a full ~40min run.
2. Diff DRC violation count with banks 0–3 temporarily placed unrotated (N), if functionally
   possible for a quick experiment, to isolate whether rotation is truly the SRAM-view
   contributing factor identified in Section 3.1.
3. Once (1)/(2) narrow the cause, fix the higher-leverage one first (likely tap/halo tuning,
   since it explains 3x more violations than the SRAM-rotation theory) and re-run full DRC/LVS.
4. Do not consider `soc_core` tapeout-ready until `Netgen.LVS` reports a clean match.
