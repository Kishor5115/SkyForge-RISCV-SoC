# Yosys scripts deep dive (from scratch)

This document explains the **OpenLane-style Yosys flow** used in this repo in depth:

- What each script does
- The order (flow) in which passes run
- Which environment variables control behavior
- What files are produced and where

The authoritative scripts live in:

- `flow/run_yosys.sh` (bash entrypoint)
- `flow/env.sh` (defaults for PDK/libs/constraints)
- `flow/yosys/scripts/synth.tcl` (main OpenLane-style synthesis)
- `flow/yosys/scripts/{elaborate.tcl,rewrite_verilog.tcl,logic_equiv_check.tcl}` (utilities)

---

## 1) What is Yosys doing in an ASIC flow?

At a high level, Yosys converts your RTL (SystemVerilog) into a **gate-level netlist** that uses cells from your standard-cell library (here: `sky130_fd_sc_hd`).

Conceptually there are three big transformations:

1. **Elaboration & lowering**
   - Parses RTL, resolves hierarchy, turns behavioral `always` blocks into an internal netlist of muxes/FFs/logic.
2. **Optimization**
   - Simplifies boolean logic, removes redundant logic, shares arithmetic resources (optional), canonicalizes state machines, etc.
3. **Technology mapping**
   - Converts generic logic into **real library gates** using ABC (`abc` pass) and maps flops (`dfflibmap`).

In OpenLane-style flows, Yosys is not just a “single synth command”; it is a controlled pipeline of passes that is parameterized by environment variables.

---

## 2) Repository layout & where outputs go

### Scripts

- Main Yosys scripts: `flow/yosys/scripts/`
  - `synth.tcl` (main)
  - `elaborate.tcl` (quick elaborate/check/stat)
  - `rewrite_verilog.tcl` (netlist normalization)
  - `logic_equiv_check.tcl` (formal equivalence check)

### Outputs

All Yosys outputs are rooted at:

- `flow/yosys/out/`
  - `logs/yosys.log`
  - `results/<design>.synth.v` (final synthesized netlist)
  - `reports/` (stat/check reports, strategy-tagged)
  - `tmp/` (temporary SDC, hierarchy DOT graphs)

The output root is controlled by `YOSYS_OUT_DIR` (set in `flow/env.sh`).

---

## 3) The top-level flow: `flow/run_yosys.sh`

This bash script is the entrypoint for synthesis. It is responsible for *preparing the environment* for the OpenLane-style Tcl.

### 3.1 What it sets up

1. Sources `flow/env.sh` so you get:
   - PDK and library paths (e.g. `LIB_SYNTH`)
   - Design name (`DESIGN_NAME`) and timing (`CLOCK_PERIOD`)
   - OpenRAM macro liberty path (`SRAM_LIB`)

2. Creates output directories under `flow/yosys/out/{tmp,results,reports,logs}`

3. Builds a deterministic RTL file list (`VERILOG_FILES`) by globbing:
   - `rtl/core/*.sv`, `rtl/boot/*.sv`, `rtl/interconnect/*.sv`, `rtl/peripherals/*/*.sv`, `rtl/memory/*.sv`, plus the top files

4. Exports key OpenLane-style knobs, for example:
   - `SYNTH_STRATEGY` (e.g. `AREA 0`)
   - `SYNTH_BUFFERING`, `SYNTH_SIZING`, `SYNTH_SHARE_RESOURCES`, `SYNTH_SPLITNETS`, `SYNTH_BUFFER_DIRECT_WIRES`
   - `SYNTH_NO_FLAT`, `SYNTH_FLAT_TOP`

5. Sets output variables consumed by Yosys Tcl:
   - `synthesis_tmpfiles` → `flow/yosys/out/tmp`
   - `synthesis_results` → `flow/yosys/out/results`
   - `synth_report_prefix` → `flow/yosys/out/reports/<design>`
   - `SAVE_NETLIST` → `flow/yosys/out/results/<design>.synth.v`

6. If the SRAM liberty exists, exports it as `EXTRA_LIBS`.

### 3.2 Why the bash script matters

OpenLane-style scripts intentionally avoid hardcoding paths. The caller (bash) sets:

- What RTL files to read
- What libraries to map against
- How to name outputs and where to write them

That makes the Tcl reusable across projects.

---

## 4) Main synthesis script flow: `flow/yosys/scripts/synth.tcl`

This is the core script. It is essentially OpenLane’s Yosys synthesis flow.

### 4.1 Phase A — bootstrap, knobs, and constraints

**Import Yosys commands**
- `yosys -import` makes Yosys commands available in Tcl.

**Read key env vars**
- `SYNTH_BUFFERING`, `SYNTH_SIZING`, `DESIGN_NAME`, `LIB_SYNTH`
- Optional `DFF_LIB_SYNTH` overrides flop mapping library.

**Apply Verilog defines**
- `verilog_defines -D<DEFINE>` for each token in `SYNTH_DEFINES`.

**Include directories**
- Builds `-I` arguments from `VERILOG_INCLUDE_DIRS` if provided.

**Read blackbox libraries**
- If `SYNTH_READ_BLACKBOX_LIB=1`, the script reads `LIB_SYNTH_COMPLETE_NO_PG` as blackboxes.
- Always reads `EXTRA_LIBS` (when set) as blackboxes.

This is how the SRAM is handled:

- Your SRAM macro is a “hard macro”: it is not synthesized into gates.
- Yosys reads the SRAM `.lib` as a **blackbox cell definition** so mapping and `stat` can account for it.

**Create a minimal SDC for ABC**
The script writes `synthesis.sdc` into `synthesis_tmpfiles` containing:

- `set_driving_cell <SYNTH_DRIVING_CELL>`
- `set_load <OUTPUT_CAP_LOAD>`

It also converts units:

- `CLOCK_PERIOD` is in ns in the environment
- ABC wants ps for `-D`, so the script computes: `clock_period_ps = CLOCK_PERIOD * 1000`

### 4.2 Phase B — define ABC “strategies”

OpenLane uses multiple pre-built ABC scripts. The idea:

- **DELAY** strategies try harder to meet timing (more retiming/buffering/choices)
- **AREA** strategies try harder to reduce area

You pick the strategy with:

- `SYNTH_STRATEGY="DELAY <idx>"` or `SYNTH_STRATEGY="AREA <idx>"`

The script validates formatting and index range, then selects the strategy script string.

### 4.3 Phase C — read RTL and build hierarchy

**Read RTL**
- Loops over `VERILOG_FILES` and calls `read_verilog -sv`.

**Apply parameter overrides** (optional)
- If `SYNTH_PARAMETERS` is set, runs `chparam -set <param> <value> <top>`.

**Hierarchy check**
- Emits a hierarchy graph (`show -format dot ...`) into `synthesis_tmpfiles`.
- Runs `hierarchy -check -top <DESIGN_NAME>`.

### 4.4 Phase D — RTL lowering to logic (the `proc_*` pipeline)

This block turns behavioral RTL into a more canonical netlist:

- `proc_clean`, `proc_rmdead`, `proc_prune`: remove dead processes
- `proc_init`, `proc_arst`: normalize init/async reset constructs
- `proc_mux`: converts control flow to muxes
- `proc_dff`, `proc_dlatch`: identifies sequential elements
- `proc_rom`, `proc_memwr`: memory-related transformations

Then it runs classic Yosys optimizations:

- `opt_expr`, `opt_clean`, `opt`, `wreduce`, `peepopt`
- `fsm`: FSM extraction/optimization
- `alumacc`: arithmetic pattern optimizations
- `share`: resource sharing (more aggressive later)

Flattening behavior:

- If `SYNTH_NO_FLAT != 1`, the script runs `flatten` during this phase.

### 4.5 Phase E — memory handling

- `memory -nomap` and later `memory_map`

This is where inferred memories are normalized/mapped into explicit structures.

Important note for this repo:

- The OpenRAM SRAM is not inferred memory; it is a macro module instance.
- Inferred memories (if any) would be handled here; macro SRAM remains a blackbox instance.

### 4.6 Phase F — early techmap + a fast ABC cleanup

- `techmap` converts some generic internal cells into techlib-friendly forms.
- `abc -fast` is a quick mapping/optimization pass (not the final, constrained mapping).

This helps reduce complexity before the “real” constrained strategy run.

### 4.7 Phase G — optional extra mapping file

If `SYNTH_EXTRA_MAPPING_FILE` is provided and exists:

- `techmap -map <file>`

This is an “escape hatch” to apply project-specific cell mappings.

### 4.8 Phase H — aggressive sharing, optional adder extraction

- If `SYNTH_SHARE_RESOURCES` is true: `share -aggressive`

Adder type controls (`SYNTH_ADDER_TYPE`):

- `YOSYS`: default behavior
- `FA`: extract full/half adders (`extract_fa`) then map with `FULL_ADDER_MAP` (if provided)
- `RCA`/`CSA`: can apply `RIPPLE_CARRY_ADDER_MAP` / `CARRY_SELECT_ADDER_MAP` via `techmap -map`

Unless you explicitly provide those mapping files, the default behavior is to let ABC map the arithmetic normally.

### 4.9 Phase I — map sequential elements: `dfflibmap`

- `dfflibmap -liberty <dfflib>`

This maps generic `$dff` cells to real flip-flops from your liberty.

### 4.10 Phase J — checkpoint and final constrained mapping: `run_strategy`

This is the most important part.

The script saves a checkpoint (`design -save checkpoint`) and then `run_strategy`:

1. Reloads the checkpoint (`design -load checkpoint`)
2. Runs ABC with constraints + liberty + selected script:

   - `abc -D <clock_ps> -constr <sdc_file> -liberty <LIB_SYNTH> -script <strategy_script> -showtmp`

3. Post-ABC cleanup / netlist hygiene:

   - `setundef -zero`: forces undriven/unknown signals to known zeros
   - `hilomap`: inserts tie-high / tie-low cells using `SYNTH_TIEHI_PORT` and `SYNTH_TIELO_PORT`
   - `splitnets` (optional via `SYNTH_SPLITNETS`): split large fanout nets and clean
   - `insbuf` (optional via `SYNTH_BUFFER_DIRECT_WIRES`): inserts minimum buffers on direct wires using `SYNTH_MIN_BUF_PORT`

4. Reports:

   - `check` report written to `synth_report_prefix.<strategy>.chk.rpt`
   - `stat` report written to `synth_report_prefix.<strategy>.stat.rpt`

   For `stat`, it uses `LIB_SYNTH_NO_PG` and also includes `EXTRA_LIBS` (SRAM) so the report accounts for macros.

5. Writes the final netlist:

   - `write_verilog ... -defparam <output>`

In your flow, `<output>` is `SAVE_NETLIST`, so the final netlist lands at:

- `flow/yosys/out/results/<design>.synth.v`

### 4.11 Phase K — explore mode and no-flat mode

**Explore mode** (`SYNTH_EXPLORE=1`):
- Runs *all* delay and area strategies and emits netlists per strategy.
- Useful for experimentation but slower.

**No-flat mode** (`SYNTH_NO_FLAT=1`):
- The script can re-run synthesis in a way that preserves hierarchy artifacts and still maps.
- This is for debugging/experiments; most flows keep `SYNTH_NO_FLAT=0`.

---

## 5) Utility scripts in `flow/yosys/scripts/`

### 5.1 `elaborate.tcl`

Purpose: quick elaboration and sanity checks.

What it does:

- Reads blackbox libs (`EXTRA_LIBS`, optionally stdcells as blackbox)
- Reads RTL (`VERILOG_FILES`)
- Runs `hierarchy -check -top <top>`
- Optionally `flatten` if `SYNTH_FLAT_TOP=1`
- Runs basic cleanup (`splitnets`, `opt_clean -purge`)
- Writes:
  - `check` + `stat`
  - the netlist to `SAVE_NETLIST`

When to use:

- Fast “does it compile/elaborate?” debugging
- Capturing a pre-mapping structural view

### 5.2 `rewrite_verilog.tcl`

Purpose: normalize a netlist by re-reading it and writing it back out.

What it does:

- `read_verilog "$::env(SAVE_NETLIST)"`
- `write_verilog ... "$::env(SAVE_NETLIST)"`

When to use:

- After a tool emits a netlist that is syntactically valid but not in the style you want (e.g., missing explicit wire declarations).

### 5.3 `logic_equiv_check.tcl`

Purpose: run logical equivalence checking (LEC) between two netlists.

Inputs (env vars):

- `LEC_LHS_NETLIST` (gold/reference)
- `LEC_RHS_NETLIST` (gate/implementation)
- `LIB_TYPICAL` (cell lib for interpreting gate netlists)

High-level steps:

1. Read libraries (`read_liberty`) so Yosys understands standard cells.
2. Read and normalize each netlist (`read_nl` proc):
   - `rmports`, `splitnets -ports`, `hierarchy -top`, optional `flatten`, `stat`
   - stash designs as `gold` and `gate`
3. Build equivalence miter:
   - `equiv_make gold gate equiv`
4. Prove equivalence:
   - `equiv_simple -seq ...`
   - `equiv_status -assert` (fails if mismatch)

When to use:

- To ensure optimizations/mapping didn’t change functionality.
- To compare pre- vs post-PnR netlists (if you export both).

---

## 6) Practical “mental model” of the flow

Think of the main synthesis as:

1. **Read inputs** (RTL + libs)
2. **Lower RTL → boolean+FF netlist** (proc/fsm/memory)
3. **Optimize** (opt/share/etc.)
4. **Map FFs** (dfflibmap)
5. **Map combinational logic** (ABC with a chosen strategy)
6. **Fix constants & nets** (hilomap, splitnets, insbuf)
7. **Report + write gate-level netlist**

This matches how OpenLane expects Yosys outputs to look when handed to STA/OpenROAD.

---

## 7) Where to look when debugging

- Full log: `flow/yosys/out/logs/yosys.log`
- Final netlist: `flow/yosys/out/results/<design>.synth.v`
- Strategy reports: `flow/yosys/out/reports/<design>.<strategy>.{chk.rpt,stat.rpt}`
- Hierarchy graph: `flow/yosys/out/tmp/hierarchy.dot` (and related files)

If a run stops mid-ABC with no explicit Tcl error, common causes are:

- Process killed (OOM / ulimit / timeout)
- ABC stuck on a huge cone due to missing constraints or unexpected design growth

In those cases, the last ~200 lines of `yosys.log` are the most useful starting point.
