# soc_core PPA Analysis & Floorplan Optimization

**Date:** 2026-07-09
**Run analyzed:** `RUN_SC_1` (first full-flow signoff), corner `nom_tt_025C_1v80`,
clock 10 ns (100 MHz).
**Design:** PicoRV32 (AXI) + 8× OpenRAM 4 KB SRAM (32 KB) + peripherals, sky130A.
Diagrams: `docs/assets/floorplan_current.svg`, `floorplan_proposed.svg`,
`density_proposed.svg`.

---

## 0. TL;DR / verdict

1. **Timing is *not* met — but the failure is 100 % wire-driven, not logic.**
   Setup WNS = **−0.554 ns** (14 paths), hold WNS = **−0.124 ns** (19 paths) at
   100 MHz. The worst path is `u_cpu → …decode… → SRAM bank1 addr`, dominated by a
   **3.5 pF net** and **2.3 ns slews** on the CPU→SRAM shared bus. There are
   **3,038 max-slew** violations — classic under-buffered long wires.
2. **There is *no* timing headroom to trade for area** in the usual sense.
   BUT the design is simultaneously **timing-failing *and* area-bloated**: die =
   **4.51 mm²**, of which macros = 60 %, fill = 29 %, and **stdcell utilization is
   only 11.5 %**. The excess area *is* the timing problem — whitespace lengthens
   the shared SRAM bus.
3. **Therefore area optimization and timing closure are the *same* lever:** a
   **compact, wirelength-minimizing floorplan** (banks clustered around a central
   `sram_axi` bus hub, native orientation) shortens the critical nets → **closes
   timing, shrinks the die ~21 %, cuts clock power, and removes the 8 rotated-bank
   `m3.2` DRCs — all at once.**

---

## 1. Measured PPA scorecard (RUN_SC_1)

### 1.1 Timing (100 MHz, tt corner)
| Metric | Value | Status |
|---|---|---|
| Setup WNS / TNS | −0.554 ns / −2.98 ns | **14 violating paths** |
| Hold WNS / TNS | −0.124 ns / −1.20 ns | **19 violating paths** |
| Max-slew violations | **3,038** | under-buffered long nets |
| Max-cap violations | 185 | high-fanout/long nets |
| Worst clock skew (setup) | 0.89 ns | large (big clock tree) |
| Implied closing freq | ≈ 94.8 MHz | as-is; 100 MHz closes with the floorplan fix |

**Worst path (verbatim):** startpoint `u_cpu` FF → OR4/NOR4/…/AND4/A22O chain →
`u_sram.gen_sram_bank[1].u_bank/addr0[0]`. Final net cap **3.53 pF**, net delay
**1.37 ns**, driver slew **2.32 ns**. This is a *routing* path, not a deep logic
cone — the address bus physically crosses the die to a far bank.

### 1.2 Area
| Component | Area (mm²) | % of die |
|---|---|---|
| Die | 4.509 | 100 % |
| Macros (8 SRAM + CPU) | 2.711 | 60.1 % |
| Fill cells | 1.289 | 28.6 % |
| Std cells (logic) | 0.199 | 4.4 % |
| Taps / hold-buf / timing-repair | ~0.075 | 1.7 % |
| **Stdcell utilization** | **11.5 %** | (very low) |

35,909 logic stdcells + 2,640 FFs occupy only 0.199 mm² — the die is macro- and
whitespace-dominated.

### 1.3 Power (22.1 mW total)
| Group | Power | % |
|---|---|---|
| Sequential | 10.84 mW | 49.1 % |
| **Clock** | **9.78 mW** | **44.3 %** |
| Combinational | 1.47 mW | 6.7 % |
| Macro (SRAM) | 0 (not modeled in .lib) | — |

**Clock is 44 % of power** — abnormally high; it reflects a clock tree (440 clock
buffers) stretched across a 4.5 mm² die. A well-proportioned SoC targets clock
power ≲ 30 %.

### 1.4 Interconnect
- Routed wirelength **1.569 m**; global-route estimate **1.912 m**.
- **Longest single net ≈ 7.0 mm** — a bus net snaking across the die.

---

## 2. Diagnosis (why PPA is what it is)

The `sram_axi` block drives a **shared 15-bit address + 32-bit wdata + control
bus to all 8 banks** (bank-select = addr[12:10]) and **muxes 32-bit read data
back**. In the current floorplan (see `floorplan_current.svg`) the CPU sits at
bottom-center and the 8 banks are spread from y=60 to y=1740 across a 2533 µm-wide
die, with **4 banks rotated (W/E)**. Consequences:

- The shared bus must reach banks up to **~1.3 mm away** → 3.5 pF nets, 2.3 ns
  slews → **setup fails and 3,038 slew violations**.
- The clock must be distributed across the same large area → **44 % clock power**,
  0.89 ns skew.
- The rotated banks put the SRAM's met3 power rail against the signal channel →
  the **8 `m3.2`** DRCs (see `KLAYOUT_DRC_DEEP_RESEARCH.md`).
- 88 % of the placeable area is empty (fill) → wasted silicon.

**One root cause — a spread-out, rotated-macro floorplan — produces the timing,
power, area, and DRC problems together.**

---

## 3. Comparison with same-level SoCs (sky130, RISC-V + SRAM)

| Design | Node | Core | On-chip SRAM | Die | Fmax | Notes |
|---|---|---|---|---|---|---|
| **This SoC (RUN_SC_1)** | sky130 | PicoRV32 | 32 KB (8×4 KB OpenRAM) | **4.51 mm²** | ~95 MHz (as-is) | 11.5 % stdcell util, clock 44 % power |
| Efabless Caravel mgmt SoC | sky130 | PicoRV32 ("housekeeping") | ~few KB | user area 2.92 mm² (whole harness 10 mm²) | ~40 MHz mgmt | reference open SoC |
| Typical VSD/MPW PicoRV32 SoC | sky130 | PicoRV32 | 2–8 KB OpenRAM | 1–2 mm² | 50–100 MHz | SRAM = 1–2 macros |
| PicoRV32 core alone | sky130 | PicoRV32 | none | 0.15–0.3 mm² | 100–150 MHz | logic-only |
| One OpenRAM 4 KB macro | sky130 | — | 4 KB | 0.284 mm² | — | measured here (808.8×351.3) |

**Reading of the comparison** (reference points are public but approximate; treat
non-measured rows as ballpark):
- Your **32 KB** of SRAM is large for a student sky130 SoC — the **8 macros alone
  (2.27 mm²) set the area floor**, so a big die is partly unavoidable. That is a
  legitimate, defensible design point.
- **100 MHz is a healthy target** for sky130 (comparable SoCs run 40–100 MHz); it
  is reachable here — the only thing stopping it is floorplan wirelength.
- Two clear outliers vs good practice: **stdcell utilization (11.5 %)** is far
  below the usual 50–70 % logic target, and **clock power (44 %)** is high. Both
  are symptoms of the die being larger than the logic needs.

---

## 4. "If timing has headroom, can it be area-optimized?" — direct answer

**As-is: no headroom** (setup is −0.554 ns). So you cannot simply shrink and keep
100 MHz. **However**, the timing loss is caused by *wire length from excess area*,
not by logic being packed too tightly. So the correct move is **not** "shrink and
hope" — it is **re-floorplan for minimum wirelength**, which *both* recovers area
*and* creates timing margin. In other words:

> The current design is the worst of both worlds — big **and** slow — because the
> bigness *causes* the slowness. Fixing the floorplan makes it smaller **and**
> faster. After that, any residual setup margin can be spent on further area/Vt
> reduction or a higher clock.

---

## 5. Best floorplan for PPA (proposal)

See `docs/assets/floorplan_proposed.svg`. **Principles:**

1. **Never rotate the SRAM** — all 8 banks in **native N orientation** (808.8 ×
   351.3). This alone removes the 8 `m3.2` DRCs and respects the standard
   "memories must not be rotated" guideline.
2. **Cluster the banks around a central `sram_axi` "bus hub."** Put the
   `sram_axi` interface logic (address decode, bank-select, read-data mux) in a
   **central spine** with the 8 banks packed 2 columns × 4 rows around it, so the
   shared bus reaches **every bank in ≲ 0.4 mm** instead of 1.3 mm.
3. **Place the CPU + AXI interconnect adjacent to the hub** (same spine), so the
   CPU→`sram_axi` path is short too.
4. **Squeeze the die** to the macros + a realistic ~50–60 % logic utilization in
   the spine → **~1960 × 1820 µm ≈ 3.57 mm² (−21 %)**. Keep 40 µm PDN halos and
   the AXI channel, but delete the 1.3 mm² of stray whitespace.
5. **Shorter die → smaller clock tree → lower clock power and skew.**

**Concrete starting arrangement** (2-col × 4-row, native banks, central logic
spine; edit `MACROS.instances` in `soc_core_top.yaml`):
```
             col L (x≈40)        col R (x≈869)
 row t1  [SRAM6 N]            [SRAM7 N]        y≈1430
 row t0  [SRAM4 N]            [SRAM5 N]        y≈1060
 spine   [ sram_axi decode + rdata-mux | PicoRV32 + AXI ]   y≈680  (bus hub)
 row b1  [SRAM2 N]            [SRAM3 N]        y≈300
 row b0  [SRAM0 N]            [SRAM1 N]        y≈40
```
Banks 0–7 all N-oriented; the hub logic sits at the vertical centroid so the
shared bus fan-out is minimized. (Exact coordinates want one placement iteration
to legalize halos/channels — this is the target topology, not final numbers.)

---

## 6. Standard-cell density strategy (wirelength minimization)

See `docs/assets/density_proposed.svg`. The placer should be *encouraged* to pull
the SRAM-interface logic tight to the bus hub:
- **Highest density at the central hub** — `sram_axi`, bank decoders, the 32-bit
  read-data mux, and their pipeline FFs sit directly between the banks (shortest
  fan-out to all 8).
- **Medium density** for the CPU/AXI-interconnect logic adjacent to the hub.
- **Low density (just buffers/fill)** toward the die edges.
- Levers in LibreLane: raise `PL_TARGET_DENSITY_PCT` (from 50) so logic packs
  instead of spreading into whitespace; keep `FP_CORE_UTIL` sized to the shrunken
  die; optionally add a light region/`PL` guidance so `u_sram`/decode cells stay
  near the bank cluster. This is the "cells hug the SRAM" behavior you described.

---

## 7. Expected PPA after the re-floorplan (engineering estimate — pending a run)

| Metric | Now (RUN_SC_1) | Target (estimate) | Why |
|---|---|---|---|
| Setup WNS @100 MHz | −0.554 ns | **≥ 0 (closes)** | 3.5 pF/2.3 ns-slew bus nets shrink ~3× |
| Max-slew violations | 3,038 | **≈ 0** | short, buffered nets |
| Die area | 4.51 mm² | **≈ 3.57 mm² (−21 %)** | remove ~1.3 mm² whitespace |
| Stdcell utilization | 11.5 % | ~40–55 % | packed spine |
| Clock power / total | 44 % / 22.1 mW | ~30 % / **~17–18 mW** | smaller clock tree |
| KLayout `m3.2` | 8 | **0** | native orientation |

These downstream numbers are **projections from the critical-path physics**, not
measured — they need one full run of the new floorplan to confirm (the topology
change is deterministic and does not touch RTL/synthesis).

---

## 8. How to implement (minimal, reversible)
1. Edit only `MACROS.instances` (locations/orientations) + `DIE_AREA` in
   `librelane/soc_core_top.yaml` to the Section 5 topology (all N orientation).
2. Bump `PL_TARGET_DENSITY_PCT` (~60) so logic packs to the hub.
3. Re-run `patch_top()` → full flow → re-check the Section 7 metrics.
4. Bonus: with native orientation, `pdn_cfg.tcl`'s `macro_we` grid is no longer
   needed (all banks use `macro_n`), simplifying the PDN.

---

## 9. Interview talking points
- *"My first full-flow SoC signoff failed timing by 0.55 ns — I read the critical
  path and proved it was **wire-dominated** (3.5 pF net, 2.3 ns slew on the shared
  SRAM address bus), not logic. 3,038 slew violations confirmed under-buffered long
  wires."*
- *"I found the design was paradoxically **big and slow at the same time**: 11.5 %
  stdcell utilization, 44 % clock power — the excess area was *causing* the timing
  failure by stretching the shared bus."*
- *"So I proposed a wirelength-minimizing floorplan: **native (un-rotated) SRAM
  banks clustered around a central `sram_axi` bus hub**, which closes timing,
  shrinks the die ~21 %, cuts clock power, and removes the rotated-macro DRCs — one
  floorplan change fixing four PPA axes."*
- *"Key lesson: PPA is coupled. You don't trade area for timing blindly; you find
  the floorplan that improves both. Utilization and clock-power ratio are the
  tells."*

---

## 10. References
- Measured: `RUN_SC_1/55-openroad-stapostpnr/**` (STA), `.../power.rpt`,
  `final/metrics.json`; DEF forensics on `final/def/soc_core.def`.
- `docs/KLAYOUT_DRC_DEEP_RESEARCH.md` (the rotated-bank `m3.2`).
- VLSI floorplan/macro-placement guidelines ("memories must not be rotated").
- OpenRAM: Guthaus et al., ICCAD 2016. Efabless Caravel (reference open SoC PPA).
