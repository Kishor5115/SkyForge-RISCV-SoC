# soc_padring: Root Cause, Industry Precedent, and Path Forward

**Date:** 2026-07-03
**Status:** Root cause fully identified and confirmed against upstream tooling and
industry practice. This is a genuine, verifiable gap in the open-source sky130 flow —
not a config mistake. Two concrete paths forward are laid out below with trade-offs.

---

## 1. What was actually wrong (in one paragraph)

`soc_padring_top.yaml` asks LibreLane's **Classic** flow to run `OpenROAD.DetailedRouting`
(TritonRoute) to connect each top-level chip port directly onto the sky130 `gpiov2` pad's
`PAD` pin — the bond-wire pad. TritonRoute cannot do this: the `PAD` pin is a met5 shape
walled off by met5 obstruction on all four sides with met4 fully obstructed underneath, so
its pin-access engine (`FlexPA`) can never generate an access point (`DRT-0073`), and once
that is patched around, other structural artifacts appear (auto-inserted tap/fill/tie cells,
persistent low-level routing shorts) that never fully converge to zero. **No real sky130
chip is built this way.** Bond-pad connections are made by placement/abutment, never by
signal-net detailed routing. LibreLane's own documentation says exactly this: *"hardening a
macro + padframe for a top level design is too complex using the Classic flow, and may
require you to write your own custom-based flow."*

## 2. What real sky130 projects actually do (verified from source, not assumption)

### 2.1 Caravel (Efabless / now chipfoundry.io)
- Caravel's padframe (`openlane/chip_io/` in the `efabless/caravel` repo) is hardened
  **once**, using OpenLane 1's `DESIGN_IS_PADFRAME` flow flag
  (`openlane/chip_io/config.tcl`: `set ::env(DESIGN_IS_PADFRAME) 1`). This flag triggers
  special-cased handling in OpenLane 1's (Tcl-based) internals that is **not present in
  LibreLane/OpenLane 2 at all** — confirmed by a zero-match grep of the installed LibreLane
  3.0.2 package.
- Pad placement is driven by a **hand/tool-authored placement list**
  (`openlane/chip_io/padframe.cfg`), not by an RTL-to-GDS macro-placement stage — pads and
  their spacing are specified directly (`PAD <name> <side> <master> ; SPACE <gap> ;`).
- **Every current sky130 chip built on top of Caravel reuses this pre-built padframe
  macro as-is.** `caravel_user_project`, `caravel_openframe_project`, and chipfoundry.io's
  `caravel`/`caravan`/`openframe` templates all drop user RTL into a **fixed** padframe;
  nobody re-hardens or re-routes the padframe itself. This was confirmed directly from
  chipfoundry.io's "Start a Project" page, which only offers these three fixed templates.
- **Conclusion: in the current sky130 open-source ecosystem, nobody builds a custom
  padframe from scratch the way this repo's `soc_padring` flow attempts to.**

### 2.2 LibreLane 3.0's modern equivalent: the `Chip` flow
- LibreLane 3.0 (released March 2026) added a first-party `Chip` flow
  (`librelane/flows/chip.py`) specifically for top-level chip + pad-ring tapeouts,
  built on a new `OpenROAD.PadRing` step that wraps OpenROAD's ICeWall pad-ring generator
  (`make_io_sites` → `place_pad` → `place_corners` → `place_io_fill` →
  **`connect_by_abutment`**). This is architecturally identical to how OpenROAD's own docs
  say bond pads should be connected — by abutment/placement, never by TritonRoute signal
  routing. The `Chip` flow explicitly removes `OpenROAD.IOPlacement`/`Odb.CustomIOPlacement`
  ("no pin placement necessary -> pads are the BTerms"), which is exactly the mismatch that
  caused our `DRT-0073`/`DRT-0405` chain of errors.
- **Verified directly against the installed toolchain (LibreLane 3.0.2):** the `Chip` flow
  and `OpenROAD.PadRing` step both exist and are usable today.
- **The gap:** `OpenROAD.PadRing` requires the PDK to define IO placement sites
  (`SITE ... CLASS PAD` in the tech/IO LEF) via PDK config variables `PAD_SITE_NAME` /
  `PAD_CORNER_SITE_NAME`. These are defined for **IHP's sg13g2 and sg13cmos5l** PDKs
  (`/foss/pdks/ihp-sg13g2/libs.tech/librelane/sg13g2_io/config.tcl`) and for **gf180mcu**
  (via wafer.space's project template), but **sky130A's `open_pdks` build (commit
  `7b70722e33c0`, the current standard `ciel`-distributed build used everywhere, inside
  this container and out) has zero `SITE` blocks in either `sky130_fd_io.lef` or
  `sky130_ef_io.lef`.** Every `CLASS PAD` occurrence in those files is a `MACRO ... CLASS
  PAD` annotation (marking a cell as pad-type), not a placement `SITE` definition. This was
  verified directly: `grep -c "^SITE " sky130_fd_io.lef sky130_ef_io.lef` → `0 0`.
- **This means `OpenROAD.PadRing`/the `Chip` flow cannot be used for sky130 out of the box
  today.** It is a genuine, verifiable upstream PDK-support gap — confirmed against the
  actual open-source `open_pdks` sky130A build, not a Docker-image quirk.

## 3. Everything that WAS successfully fixed along the way

These fixes are real, verified, and independently useful regardless of which path is taken
next (see Section 4):
1. Pad ring placement (all 80 pads flush, no overlaps, core clears all pads) —
   `librelane/gen_padring_placement.py` / `apply_placement.py`.
2. DIE/CORE sizing from exact PDK LEF dimensions, grid-aligned to avoid `IFP-0028`.
3. `flow.log` warning suppression (extended `on_alert` silence lists).
4. Global-routing SIGSEGV workaround (`GRT_OVERFLOW_ITERS: 0`).
5. A **working** met4/met5 single-port LEF patch for `sky130_ef_io__gpiov2_pad_wrapped`
   that gives TritonRoute's `FlexPA` a legal access point on the `PAD` pin without changing
   the pin count (avoids `DRT-0405`) — confirmed to reach `DRT-0166 Complete pin access`
   and `DRT-0198 Complete detail routing` (238,932 µm wire, 4,155 vias, 0 `DRT-0073`).
6. Root cause of the post-route DRC violations: **not** the LEF patch, but ~60,000
   auto-inserted tap/fill/tie cells that Classic's `OpenROAD.TapEndcapInsertion` /
   `FillInsertion` / `RepairDesignPost*` steps place unconditionally across the *entire*
   empty floorplan (this wrapper has no free-standing standard-cell logic of its own).
   Skipping these steps (`-S OpenROAD.TapEndcapInsertion -S OpenROAD.FillInsertion -S
   OpenROAD.RepairDesignPostGPL -S OpenROAD.RepairDesignPostGRT`) cut the design from
   60,855 cells to 765 and made DRT converge faster and to a much lower violation floor —
   but did **not** reach zero, because the underlying architecture (TritonRoute routing
   signal nets onto bond pads) is still fundamentally unsupported.
7. DRT's internal antenna-repair-loop crash (`Error: drt.tcl, 122 map::at`) — fixed with
   `DRT_ANTENNA_REPAIR_ITERS: 0`.

None of these fixes were wasted: items 1–4 and 7 are needed by *any* future approach
(including Path B below); item 5 is the reference implementation for "how to patch a
sky130 IO LEF to add a pin-access point," useful documentation in its own right; item 6
is the reason tap/fill must stay disabled for any macro-only LibreLane wrapper.

## 4. Path Forward — Three Real Choices

### Path A: Contribute the missing sky130 PDK support upstream
Write the missing `SITE CLASS PAD` LEF entries + `PAD_SITE_NAME`/`PAD_CORNER_SITE_NAME`/
`PAD_EDGE_SPACING`/`PAD_FILLERS`/`PAD_CORNER` config for sky130A (mirroring IHP's
`sg13g2_io/config.tcl` structure), submit as a PDK-config patch, then run this project
through LibreLane's `Chip` flow + `OpenROAD.PadRing` (abutment-based, no TritonRoute-to-PAD).

- **Pros:** Solves the problem the *architecturally correct* way; matches where the
  tooling is heading; a genuine, citable open-source contribution (not just "I used a
  tool" but "I found and fixed a gap in it") — this is a strong, differentiated resume/
  interview story.
- **Cons:** Requires deriving correct site geometry from the sky130 IO cell's physical
  pitch/abutment rules (real PDK-engineering work, not a quick patch), then verifying it
  against `make_io_sites`'s assumptions (site width/height, corner site behavior). Realistic
  effort: multiple sessions, possibly needs Skywater/open_pdks maintainer input to confirm
  correctness before it can be trusted for tapeout-quality work. Highest risk, highest reward.

### Path B: Follow Caravel's actual precedent — treat the padframe as authored placement, not synthesized routing
Stop using Classic's macro-placement + TritonRoute for the padring. Instead, directly author
the padring geometry (a DEF, generated by a script — much like Caravel's `padframe.cfg` and
this repo's own `gen_padring_placement.py`), with **pad-to-core-signal connections made by
routing only the pad's `IN`/`OUT`/`OE_N` (met2, fully routable) pins to `soc_core`**, and the
`PAD` (bond) pin left as a deliberately unrouted top-level boundary net — exactly matching
how the physical chip works after wire-bonding. This can be done as a **custom LibreLane
sequential flow** (documented and supported today: `meta.flow: [...]` in the config, per
LibreLane's "Writing Custom Flows" guide), selecting only the steps needed (floorplan, macro
placement, PDN, `OpenROAD.GlobalRouting`/`DetailedRouting` restricted to `soc_core`↔pad
`IN`/`OUT`/`OE_N` nets only, `Magic.StreamOut`), skipping IO placement and any step that
tries to route to `PAD`.
- **Pros:** Uses only currently-working sky130 tooling (LEF patch from Section 3 item 5
  becomes unnecessary — `PAD` is never a routing target at all, so `DRT-0073` cannot occur).
  Directly mirrors Caravel's own proven methodology. Faster to a working, DRC-clean result
  than Path A.
- **Cons:** Requires writing a genuine custom LibreLane flow (Python `Flow` subclass or a
  step-list) rather than a config file — more implementation work than a YAML change, but
  substantially less than Path A's PDK-engineering effort. Less "novel" for a resume bullet
  than Path A, but still a legitimate demonstration of understanding LibreLane's
  architecture deeply enough to route around a Classic-flow limitation.

### Path C: Reuse an existing, silicon-proven sky130 padframe macro (OpenFrame) — recommended for area/schedule
Instead of hardening any padframe at all, drop `soc_core` (or a thin wrapper) into
**Efabless/chipfoundry.io's `OpenFrame` harness** — a pre-built, already-taped-out-many-times
sky130 padframe macro that is specifically designed for "implement your own custom
processor" (confirmed from chipfoundry.io's SoC Platforms page and the
`caravel_openframe_project` reference design, which itself replaces Caravel's default
VexRiscv/PicoRV32 management SoC with a user core at the same hierarchy level — exactly
this project's situation).

- **What it provides:** a fixed, pre-hardened GDS/LEF padframe (same `sky130_ef_io__gpiov2_pad_wrapped`
  cells, but already wire-bonded/abutted correctly by Efabless — the exact problem in
  Sections 1–2 is already solved *inside* this macro) with **44 configurable GPIOs**, no
  integrated CPU (unlike Caravel/Caravan — a good fit since this SoC already has its own
  PicoRV32), and **15 mm² of user project area** (larger than this project's current
  ~4.5 mm² `soc_padring` die, so area is not a constraint).
- **How the connection works (verified from `caravel_openframe_project`):** the padframe's
  GPIO pads expose **already-routable** `gpio_in`/`gpio_out`/`gpio_oeb` (+ `gpio_ieb`)
  pins — ordinary met2 signal pins, not the `PAD` bond pin — at a fixed hierarchy boundary
  (`openframe_project_wrapper.v`). The user design (this project's `soc_core`) is
  instantiated *inside* that wrapper and wired to those pins directly, e.g.:
  `.gpio_out(uart_tx), .gpio_oeb(1'b0)` for the UART TX pin, `.gpio_in(uart_rx_val)` for
  UART RX, and so on for JTAG/SPI/clock/reset/GPIO — a straightforward, mechanical mapping
  from this project's current `pad_*` ports. **The entire `soc_padring` custom-padframe
  problem (Sections 1–3 of this doc) disappears by construction** — TritonRoute never
  routes to a bond pad because the bond-pad connection was already solved once by Efabless
  inside the OpenFrame macro; this project only ever routes to the macro's ordinary
  digital I/O pins, same as routing to any other macro.
- **Pros:** By far the lowest engineering risk and fastest path to a complete, submittable
  GDSII — reuses a macro that has already taped out on real, verified sky130 shuttles.
  Directly matches the project's stated goal of "a production-quality, fully open-source
  RV32IM SoC" (README) — production sky130 tapeouts go through exactly this kind of harness,
  not a from-scratch padframe. Also a legitimate, complete resume story: "integrated a
  custom RV32IM SoC into the industry-standard OpenFrame harness for sky130 tapeout,"
  which is closer to what a real chip-design job actually looks like day-to-day than either
  A or B.
  Area headroom (15 mm² available vs. ~2.43 mm² for `soc_core` per this project's own
  ASIC_IMPLEMENTATION.md) is generous — no area-driven redesign needed.
- **Cons:** Requires re-mapping this project's top-level port list (`pad_clk`, `pad_gpio[31:0]`,
  `pad_uart_*`, `pad_spi_*`, `pad_jtag_*`, `pad_flash_*`, `pad_trap`) onto OpenFrame's fixed
  44-GPIO numbering/pinout (some GPIOs are reserved for housekeeping SPI / flash / a status
  LED on the Efabless dev board per the project's README — need to avoid or accept those
  overlaps). Ties the project's final chip boundary to Efabless/chipfoundry.io's harness
  conventions (die size, power domain names `vccd1`/`vssd1`/`vddio`/`vssio`, pin order)
  rather than the project's own free-form `soc_padring.sv`. This is "less from-scratch,"
  which is a pro for schedule/risk and a (minor) con if the goal is specifically to
  demonstrate from-scratch pad-ring hardening skills.

## 5. Recommendation for resume/interview purposes

All three paths produce a legitimate, technically accurate story — pick based on what you
want to demonstrate and how much time is available:

- **Path C (OpenFrame reuse)** is the **recommended default** if the goal is a finished,
  working, submittable chip in the shortest time with the least risk — this is genuinely
  how most real sky130 projects (including many production ones) are built. It is also the
  most "senior engineer" answer in an interview: recognizing when to reuse a proven macro
  instead of re-deriving solved infrastructure is exactly the judgment call a real
  physical-design role rewards.
- **Path A (PDK contribution)** is the strongest, most differentiated story *if* you have
  the time to finish it: "found and fixed a missing PDK support gap in LibreLane 3.0's
  pad-ring flow for sky130" is unusual and verifiable.
- **Path B (custom flow)** is a solid middle ground: demonstrates deep LibreLane flow
  understanding without requiring PDK-level LEF/site engineering, and finishes faster than A.

Either way, the important, honest fact to lead with: **the original `soc_padring` blocker
is a documented, upstream tool/PDK limitation, not a mistake in this project's RTL,
floorplan, or configuration** — verified against LibreLane's own source and documentation,
against the actual `open_pdks` sky130A build, and against Caravel's own real source files.

---

## 5. Files relevant to this investigation
- `docs/PADRING_FLOW_DEBUG.md` — earlier, narrower debug log (pad-LEF patch attempts, DRT-0073
  first diagnosis). Superseded in scope by this document but still accurate for its content.
- `librelane/soc_padring_top.yaml` — current (Classic-flow) config; contains the working
  met4/met5 LEF-patch reference (Section 3 item 5) and the tap/fill-skip fix (item 6),
  both still valid inputs for Path B's custom flow.
- `librelane/sky130_ef_io_padring_patched.lef` — the working single-port PAD-pin patch.
