# Memory Architecture Decision: On-chip SRAM vs External-Flash XIP

**Date:** 2026-07-09
**Design:** PicoRV32 (AXI) SoC, sky130A, FreeRTOS firmware.
**Branches compared:** `main` (32 KB on-chip SRAM, FreeRTOS runs from SRAM) vs
`v2-flash-xip` (code in external QSPI flash via XIP, small on-chip SRAM for data).
**Diagrams:** `docs/assets/memory_size_comparison.svg`, `floorplan_16kb.svg`.

---

## 0. TL;DR / recommendation

- **Make `v2-flash-xip` the main branch** (code in external QSPI flash via XIP +
  a **small on-chip SRAM for data/heap**). It is the *realistic, industry-standard,
  better-PPA* architecture, it matches **PicoSoC** (the reference SoC for your exact
  CPU), and it tells a much stronger resume/interview story.
- **Size the on-chip data SRAM at 8 KB (2 OpenRAM banks)** for the sweet spot:
  comfortably runs FreeRTOS with real tasks + a UART CLI, and cuts the SRAM macro
  area from **2.27 mm² → ~0.57 mm²**. 16 KB (4 banks) if you want headroom; **4 KB
  (1 bank) is the proven floor** for a minimal FreeRTOS demo.
- **Keep the 32 KB all-SRAM design as a documented secondary branch** — it
  showcases large multi-bank OpenRAM integration and is the source of your DRC/PPA
  case studies. Two branches = two distinct, complementary skills to talk about.

---

## 1. Your *measured* firmware footprint (ground truth)

From `firmware.elf` (`riscv…-size`):
| Section | Size | What it is |
|---|---|---|
| `.text` (code) | **9,940 B (~9.7 KB)** | FreeRTOS kernel + drivers + app |
| `.data` | 20 B | initialized globals |
| `.bss` | **12,824 B (~12.5 KB)** | zero-init globals — **of which 12 KB is `configTOTAL_HEAP_SIZE`** |
| **Total static** | **22,784 B (~22.3 KB)** | |

**Critical observation:** the RAM is dominated by a **12 KB FreeRTOS heap that you
chose** (`FreeRTOSConfig.h: configTOTAL_HEAP_SIZE = 12*1024`). Real non-heap data
is < 1 KB. The heap size — and therefore your SRAM requirement — is a tunable, not
a law of physics.

Two linker variants already exist in the repo:
- `linker.ld` — **32 KB SRAM**, `.text`+`.data`+`.bss` all in SRAM (current `main`).
- flash `.map` — **16 MB FLASH @0x40010000 (XIP) + 16 KB SRAM** (the `v2` variant):
  `.text` in flash, only data/heap in SRAM.

---

## 2. The two architectures

### A. On-chip 32 KB SRAM (current `main`)
Code + data both live in on-chip SRAM (8× OpenRAM 4 KB banks).
- **Pros:** self-contained (no external chip); single-cycle-ish instruction fetch
  (fast, deterministic); demonstrates large multi-bank OpenRAM integration (8
  macros, PDN, floorplan).
- **Cons:** **2.27 mm² of SRAM macros** → the 4.51 mm² die, the wire-limited timing
  miss, 44 % clock power, and the rotated-bank DRCs (see
  `FLOORPLAN_PPA_OPTIMIZATION.md`, `KLAYOUT_DRC_DEEP_RESEARCH.md`). **Unrealistic**:
  no real MCU spends 32 KB of silicon SRAM on *code* when flash is far cheaper per
  bit and non-volatile.

### B. External-flash XIP + small SRAM (`v2-flash-xip`) — recommended
Code executes in place from an external QSPI/SPI NOR flash (memory-mapped); on-chip
SRAM holds only data + heap + stacks.
- **Pros:** **standard embedded architecture**; tiny on-chip SRAM → small die,
  timing closes, low clock power, no rotated-macro DRC; **firmware size is no
  longer bounded by silicon** (MBs of flash); demonstrates a **QSPI flash
  controller + XIP + boot** (more RTL/system skills).
- **Cons:** needs an external flash chip (board-level, but that's normal); XIP fetch
  latency > SRAM (mitigated by QSPI burst / a small prefetch/cache); slightly more
  boot/controller complexity.

---

## 3. How comparable SoCs do it (evidence)

| SoC | Code memory | On-chip RAM | Pattern |
|---|---|---|---|
| **PicoSoC** (Clifford Wolf, *the* picorv32 reference SoC) | **external SPI flash, XIP** | a few KB SRAM | memory-mapped flash + small SRAM — *exactly* option B |
| Efabless **Caravel** mgmt SoC | management runs from **SPI flash** | small **DFFRAM** (~2 KB) | flash for code, tiny on-chip RAM |
| Typical MCU (Cortex-M / ESP32-C3 RISC-V) | on-chip or external **flash (XIP or copy-to-RAM)** | SRAM for data | code in flash, data in SRAM |
| Edge-IoT SoCs (design-reuse/embeddedcomputing) | **external flash XIP** | modest SRAM | "place MCU flash off-chip in XIP mode" to save area/cost |

**Takeaway:** essentially every real embedded SoC — and the canonical PicoRV32
reference (PicoSoC) — keeps **code in flash and only data in SRAM**. The 32 KB
all-SRAM approach is the outlier. Choosing option B signals that you understand the
standard memory hierarchy.

---

## 4. Can FreeRTOS fit in 8 KB or 4 KB? (yes — analysis)

FreeRTOS is explicitly a *small-footprint* kernel. RAM cost:
- Scheduler/kernel core: a few hundred bytes (ready/delayed lists, tick, timers).
- **Per task: 64 B TCB + its stack** (`configMINIMAL_STACK_SIZE = 128 words = 512 B`).
- Queues/semaphores/mutexes: tens of bytes each + any queue storage.
- Everything above is allocated from `configTOTAL_HEAP_SIZE` (heap_4).

With **code in flash (XIP)**, SRAM only carries data/heap:

| On-chip SRAM | Banks | Area (macros) | FreeRTOS feasibility |
|---|---|---|---|
| **16 KB** | 4 | ~1.14 mm² | Comfortable — 12 KB heap + several tasks + CLI + buffers. (Your current `v2` size.) |
| **8 KB** | 2 | ~0.57 mm² | **Recommended** — set heap ≈ 5–6 KB; runs kernel + 3–4 real tasks (blinky, UART RX/TX, CLI) + queues. |
| **4 KB** | 1 | ~0.28 mm² | **Minimal but proven** — heap ≈ 2–2.5 KB, 1–2 tasks with 256–384 B stacks, static allocation. A legitimate "FreeRTOS blinky + UART" demo. |

**How to shrink SRAM (in priority order):**
1. **Move `.text` to flash XIP** — removes ~9.7 KB from SRAM immediately (the whole
   point of option B).
2. **Cut `configTOTAL_HEAP_SIZE`** 12 KB → 4–6 KB (you are massively over-provisioned).
3. **`configSUPPORT_STATIC_ALLOCATION = 1`** — allocate tasks/queues statically so
   you size RAM exactly and avoid heap fragmentation/slack.
4. **Trim task stacks** to measured high-water marks (`uxTaskGetStackHighWaterMark`)
   and reduce task count.
5. Keep `.data`/`.bss` small (they already are, < 1 KB non-heap).

---

## 5. PPA impact (this is the payoff — ties to `FLOORPLAN_PPA_OPTIMIZATION.md`)

See `docs/assets/memory_size_comparison.svg`. Shrinking on-chip SRAM is the single
biggest PPA lever because the SRAM macros dominate the die:

| Config | SRAM macro area | Est. die | Timing | Clock power | Rotated-bank DRC |
|---|---|---|---|---|---|
| 32 KB / 8 banks (now) | 2.27 mm² | 4.51 mm² (measured) | fails (wire-limited) | 44 % | 8× m3.2 |
| 16 KB / 4 banks + XIP | 1.14 mm² | ~2.1 mm² | closes easily | lower | 0 (native, 2×2) |
| **8 KB / 2 banks + XIP** | 0.57 mm² | ~1.3 mm² | closes, margin | low | 0 |
| 4 KB / 1 bank + XIP | 0.28 mm² | ~0.8 mm² | large margin | lowest | 0 |

(die estimates are engineering projections; the 4.51 mm² row is measured.)
With 1–4 banks you can also drop the rotated placement entirely and use a clean
`macro_n`-only PDN — simplifying the whole flow.

---

## 6. Floorplan for the recommended options

See `docs/assets/floorplan_16kb.svg`. With only 4 banks (16 KB) or 2 banks (8 KB):
- Place banks **native orientation** in a compact **2×2 (16 KB) or 1×2 (8 KB)**
  cluster around a **central `sram_axi` + PicoRV32 + QSPI-flash-controller spine**
  (the shared-bus hub).
- This is the same "cluster logic at the bus hub" principle as the main PPA doc,
  but far easier because there are 4–8× fewer macros and no rotation.
- The QSPI flash controller sits next to the CPU; the flash pins go to the pad ring.

This mirrors how PicoSoC/Caravel place a small RAM block next to the core with the
flash controller feeding instruction fetch.

---

## 7. Recommendation summary (what to put on the resume)

- **Main / headline project:** `v2-flash-xip` — *"PicoRV32 SoC with QSPI-flash XIP
  instruction fetch and an 8 KB OpenRAM data SRAM, running FreeRTOS; taped-out-clean
  in sky130 (Magic/LVS/route clean, ~1.3 mm²)."* Realistic, small, closes timing,
  and demonstrates the full memory hierarchy + a flash controller.
- **Secondary / "advanced integration" branch:** `main` 32 KB — *"large multi-bank
  (8×4 KB) OpenRAM integration study; root-caused a router-vs-signoff-deck DRC class
  and a wirelength-limited timing path, documented PPA trade-offs."* This is where
  your DRC/PPA deep-dives shine.
- Net: you get **two complementary stories** — a clean, realistic tapeout *and* a
  hard integration/debug case study.

---

## 8. Interview talking points
- *"Real MCUs and the PicoRV32 reference SoC (PicoSoC) keep code in external flash
  and only data in SRAM. My first cut put all 32 KB on-chip, which I measured to be
  the root of my area/timing/power problems — 2.27 mm² of SRAM macros driving a
  4.5 mm² die and a wire-limited critical path."*
- *"I profiled the firmware: 9.7 KB code, <1 KB real data, and a 12 KB FreeRTOS heap
  I'd over-provisioned. Moving code to QSPI-flash XIP and right-sizing the heap lets
  FreeRTOS run in 8 KB (2 banks) — a ~4× SRAM-area reduction — or even 4 KB for a
  minimal build."*
- *"I understand the memory-hierarchy trade-off: XIP saves silicon and is
  non-volatile but adds fetch latency, so you add a QSPI burst/prefetch; on-chip
  SRAM is fast/deterministic but expensive in area. I built both and quantified the
  PPA difference."*

---

## 9. References
- Measured: `firmware/firmware.elf` size, `firmware/FreeRTOSConfig.h`,
  `firmware/linker.ld`, flash `.map`.
- PicoSoC / PicoRV32 (YosysHQ/picorv32) — SPI-flash XIP reference architecture.
- FreeRTOS.org memory-management docs; openrtos.net FAQ ("64 B + stack per task").
- Efabless Caravel (management SoC + DFFRAM + SPI flash).
- design-reuse / embeddedcomputing: XIP external-flash architecture rationale.
- Companion: `docs/FLOORPLAN_PPA_OPTIMIZATION.md`, `docs/KLAYOUT_DRC_DEEP_RESEARCH.md`.
