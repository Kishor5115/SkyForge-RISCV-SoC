# Deep Dive: flow/openroad/flow.tcl (minimal OpenROAD driver)

This document explains `flow/openroad/flow.tcl` *line by line*.
It is intentionally verbose so you can understand what OpenROAD is doing at each step.

Assumptions / context:
- You run OpenROAD through `flow/run_openroad.sh` (which sources `flow/env.sh`).
- The synthesized netlist exists at `$YOSYS_OUT_DIR/results/$DESIGN_NAME.synth.v`.
- LEF/LIB/SDC paths are provided via environment variables from `flow/env.sh`.

Key idea:
- This file is a self-contained OpenROAD “driver” script.
- It reads tech + macro data (LEFs / Liberty), reads the gate-level netlist, applies constraints, then runs floorplan → placement → CTS → routing.
- It also supports stopping early using `OPENROAD_STOP_AFTER`.

-------------------------------------------------------------------------------
Line-by-line walkthrough
-------------------------------------------------------------------------------

Line 1:
- Comment describing that this is an OpenROAD place-and-route script.
- This is purely documentation; OpenROAD ignores it.
- The intent is: keep this script minimal and easy to tweak.
- If you later add PDN/signoff, you typically split the flow into more scripts.
- In many flows this file is analogous to OpenLane’s `openroad.tcl` stage driver.

Line 2:
- Comment: assumes `env.sh` has been sourced.
- That is true because `flow/run_openroad.sh` does `source flow/env.sh`.
- The environment variables are the “inputs” to this script.
- If you run this file directly without the env, it will fail early.
- Typical failures: missing `TECH_LEF`, `STD_CELL_LIB`, `SDC_FILE`, etc.

Line 3:
- Blank line separating header comments from code.
- Helps readability only.
- No functional effect.
- Many Tcl scripts use blank lines to group “configuration blocks”.
- Keeping these blocks readable matters because PnR debugging is iterative.

Line 4:
- `set flow_root ...` computes a path relative to the script location.
- `info script` returns the path of the currently-running Tcl script.
- `file dirname` takes its directory.
- `/..` moves one folder up.
- `file normalize` collapses `..` and makes it absolute.

Line 5:
- `set design_name $::env(DESIGN_NAME)`.
- Reads the top-level module name from environment variables.
- For this repo, default is `soc_top` (set in `flow/env.sh`).
- OpenROAD uses this name in `link_design`.
- If this doesn’t match the netlist top, `link_design` will fail.

Line 6:
- `set out_dir $::env(OUT_DIR)`.
- Chooses where all reports / intermediate views will be written.
- `flow/env.sh` defaults `OUT_DIR` to `flow/out`.
- `flow/run_openroad.sh` creates `$OUT_DIR/openroad`.
- Keeping outputs under `flow/out` makes it easy to clean and archive.

Line 7:
- `set yosys_out_dir $::env(YOSYS_OUT_DIR)`.
- Points OpenROAD to the synthesis results folder.
- `flow/run_yosys.sh` uses this same variable.
- In this repo, default is `flow/yosys/out`.
- This ensures OpenROAD is consuming the exact synthesized netlist from Yosys.

Line 8:
- Blank line; separates general paths from tech/library file variables.
- This script is structured in small “readability blocks”.
- When a flow fails, you often inspect the last successfully read artifact.
- Grouping these sets helps you spot mismatched env variables quickly.
- No functional effect.

Line 9:
- `set tech_lef $::env(TECH_LEF)`.
- The *technology LEF* describes routing layers, design rules, and site info.
- For sky130, this usually comes from `...__nom.tlef`.
- Without it, OpenROAD cannot understand metal layers or track grids.
- Mistakes here usually manifest as missing layers, invalid routing, or failed floorplan site.

Line 10:
- `set std_lef $::env(STD_CELL_LEF)`.
- The standard-cell LEF contains cell footprints, pins, and obstruction geometries.
- OpenROAD uses it for placement and routing blockages.
- Must match the Liberty file (same library variant: hd/hs/etc).
- If LEF and LIB are mismatched, timing and physical constraints diverge.

Line 11:
- `set sram_lef $::env(SRAM_LEF)`.
- This is the macro LEF for the OpenRAM SRAM.
- In this repo, `flow/env.sh` points it to `openram/build/...lef`.
- Floorplanning and routing need macro footprints to avoid overlaps.
- If this is missing, the SRAM instance will be treated as an undefined cell.

Line 12:
- Blank line.
- Separates LEF variables from Liberty variables.
- This is a common style to keep “physical views” and “timing views” distinct.
- During debugging, LEF issues are often different from Liberty issues.
- No functional effect.

Line 13:
- `set std_lib $::env(STD_CELL_LIB)`.
- This is the Liberty (.lib) for standard cells, at a chosen corner.
- In this repo, typically TT 1.8V 25C.
- OpenROAD uses it for STA-driven optimization and CTS.
- If the file is missing, `read_liberty` fails.

Line 14:
- `set sram_lib $::env(SRAM_LIB)`.
- Timing model for the SRAM macro.
- This is important for proper timing analysis of memory accesses.
- Some flows treat SRAM as a blackbox (no timing) early on; not ideal.
- Here we attempt to include it if it exists.

Line 15:
- `set sdc_file $::env(SDC_FILE)`.
- Constraint file: clocks, IO delays, false paths, etc.
- This repo keeps it under `flow/constraints/soc_top.sdc`.
- Accurate constraints matter even for floorplan; they influence repair and CTS.
- A missing SDC often results in “no clocks” warnings and meaningless timing.

Line 16:
- Blank line.
- Separates input variables from stage-control logic.
- Keeps the “flow control” concept clearly visible.
- Helpful when you add more stop points.
- No functional effect.

Line 17:
- Comment: “Optional: run only up to a given stage.”
- Explains the purpose of `OPENROAD_STOP_AFTER`.
- This pattern is extremely useful for iterative physical debugging.
- It lets you inspect intermediate DEFs.
- Example: stop after floorplan, open DEF in KLayout.

Line 18:
- Comment listing supported values.
- Declares `floorplan | place | cts | route`.
- If you set something else, the script will simply run full flow.
- You could extend this list later (e.g., “global_place”).
- Keeping it explicit helps avoid confusion.

Line 19:
- `set stop_after ""` initializes stage control.
- Empty string means “do not stop early”.
- Tcl uses strings by default; there is no special null.
- This variable is checked later with `if { $stop_after == "..." }`.
- This is safe even if the env var is absent.

Line 20:
- `if { [info exists ::env(OPENROAD_STOP_AFTER)] } { ... }`.
- `info exists` checks existence without throwing an error.
- This is better than directly reading `$::env(...)` which would error if unset.
- If the user exports `OPENROAD_STOP_AFTER`, we capture it.
- Otherwise we keep it empty.

Line 21:
- Inside the `if`: `set stop_after $::env(OPENROAD_STOP_AFTER)`.
- Reads the desired stop point.
- This value controls later early exits.
- If it’s misspelled, none of the `if` checks match.
- That means the flow continues to completion.

Line 22:
- End of the `if` block.
- Tcl uses braces to define blocks.
- No semicolons needed; newlines act as separators.
- This style is consistent with OpenROAD/OpenLane scripts.
- Understanding Tcl block structure helps when you add custom hooks.

Line 23:
- Blank line.
- Separates control variables from netlist path construction.
- Keeps “what to read” separate from “how to run”.
- No functional effect.
- Helps readability.

Line 24:
- `set netlist "$yosys_out_dir/results/${design_name}.synth.v"`.
- Constructs the expected synthesized Verilog netlist path.
- Uses the design name to pick the file.
- This matches what `flow/run_yosys.sh` writes via `SAVE_NETLIST`.
- If synthesis hasn’t been run, this file won’t exist.

Line 25:
- Blank line.
- A separation before the “read LEFs” block.
- In physical flows, ordering matters: you must load tech and LEFs before netlist.
- It’s good style to visually group the read sequence.
- No functional effect.

Line 26:
- `read_lef $tech_lef`.
- Loads the technology LEF (routing layers, sites).
- This must happen early.
- If the site name used later (`unithd`) isn’t defined, floorplan fails.
- A common debug step is to confirm the site name exists in the tech LEF.

Line 27:
- `read_lef $std_lef`.
- Loads standard-cell footprints.
- OpenROAD can now recognize cells in the netlist.
- Without this, you may see “unknown cell master” errors.
- Another common issue: wrong LEF variant (hd vs hs).

Line 28:
- `if {[file exists $sram_lef]} { ... }`.
- Guards macro LEF loading so the flow can run even if SRAM views are absent.
- This is convenient early in bring-up.
- However, if your design instantiates SRAM, you usually want this to exist.
- If it doesn’t, routing will not correctly reserve macro area.

Line 29:
- Inside the `if`: `read_lef $sram_lef`.
- Loads the macro LEF.
- This brings in macro size, pins, blockages.
- Important for floorplan and routing.
- For SRAM-heavy designs, macro placement is often the hardest part.

Line 30:
- End of macro LEF `if`.
- Tcl braces close the conditional block.
- The flow continues regardless of whether SRAM LEF existed.
- But later you might see missing cell masters if SRAM is instantiated.
- If that happens, ensure SRAM LEF path is correct.

Line 31:
- Blank line.
- Transition from LEF parsing to Liberty parsing.
- Keeping physical vs timing separate is good mental hygiene.
- No functional effect.
- Helps with quick scanning.

Line 32:
- `read_liberty $std_lib`.
- Loads the standard-cell timing library.
- OpenROAD uses this for setup/hold calculations and buffering.
- Many commands (repair_timing, CTS) depend on Liberty being loaded.
- If you load multiple corners you’d use `read_liberty -corner ...`.

Line 33:
- `if {[file exists $sram_lib]} { ... }`.
- Similar guard for SRAM Liberty.
- Timing for SRAM is not strictly necessary for floorplan, but useful for full STA.
- If the file is missing, OpenROAD will still run.
- But memory paths won’t have accurate timing.

Line 34:
- Inside the `if`: `read_liberty $sram_lib`.
- Loads SRAM macro timing.
- OpenROAD can now calculate delays for SRAM arcs.
- Depending on macro modeling, there might be multiple pins/ports.
- Ensure the Liberty matches the macro interface in the netlist.

Line 35:
- End of macro lib `if`.
- If SRAM lib doesn’t exist, you may later see warnings about missing timing arcs.
- Those warnings can be acceptable in early iterations.
- For signoff-like timing, you should include SRAM lib.
- Keep this guard until you’re ready to make it mandatory.

Line 36:
- Blank line.
- Transition from libraries to netlist read.
- No functional effect.
- This is where you’d insert netlist linting or linking checks.
- In more advanced flows, you might also set units and corner setup here.

Line 37:
- `read_verilog $netlist`.
- Loads the synthesized gate-level netlist.
- This is not RTL; it should contain standard cells (and macro instantiations).
- If you accidentally feed RTL, linking may succeed but placement and timing will be meaningless.
- Always confirm you’re reading the synthesized netlist output by Yosys.

Line 38:
- `link_design $design_name`.
- Resolves references and sets the current design block.
- If the top module name mismatches, this fails.
- If LEFs aren’t loaded, cell masters may be missing.
- Fix is usually: correct `DESIGN_NAME`, include correct LEFs, or regenerate netlist.

Line 39:
- `read_sdc $sdc_file`.
- Loads constraints.
- Defines clock(s) needed for timing repair and CTS.
- If you don’t provide an SDC, CTS may not know what nets are clocks.
- Many flows also set IO delays and path exceptions here.

Line 40:
- Blank line.
- Marks transition into the actual physical flow.
- You can think of the following sections as: Floorplan → Place → CTS → Route.
- Each stage progressively adds physical detail.
- No functional effect.

Line 41:
- Comment: “Floorplan (adjust to taste)”.
- Signals that die/core dimensions are currently hard-coded.
- You should eventually compute these based on utilization/aspect ratio and macro sizes.
- Hard-coding is okay for early experiments.
- But for robust flows, you make these parameters.

Line 42:
- `initialize_floorplan -die_area ... -core_area ... -site unithd`.
- Creates the die and core regions.
- `die_area` is the chip boundary; `core_area` is where standard cells can be placed.
- `unithd` must match the site name in the tech LEF for sky130_hd.
- Wrong site name causes a fatal error.

Line 43:
- Blank line.
- Separates floorplan from pin placement.
- In larger flows, you would also place macros before pin placement.
- Macro placement affects pin assignment strategy.
- No functional effect.

Line 44:
- `place_pins -random`.
- Assigns IO pins around the periphery randomly.
- This is okay for quick bring-up.
- For better results you define a pin order file or use ioplacer constraints.
- If you later integrate `flow/openroad/scripts/ioplacer.tcl`, you’ll get more control.

Line 45:
- Blank line.
- A staging point: floorplan + pins is a meaningful checkpoint.
- Many designers stop here to inspect geometry.
- In OpenLane, this corresponds to early floorplan outputs.
- No functional effect.

Line 46:
- `if { $stop_after == "floorplan" } { ... }`.
- Early-exit checkpoint.
- If you invoked `OPENROAD_STOP_AFTER=floorplan`, the script writes intermediate outputs.
- This is great for debugging sites, die/core areas, and pin distribution.
- You can open the DEF in a viewer to confirm everything looks reasonable.

Line 47:
- `write_def "$out_dir/openroad/${design_name}.floorplan.def"`.
- Writes a DEF representing floorplan + pin placement.
- DEF is the standard interchange for floorplan/placement geometry.
- This file does not include routing.
- It is often used as an input to subsequent steps.

Line 48:
- `write_sdc "$out_dir/openroad/${design_name}.floorplan.sdc"`.
- Dumps the constraints as seen by OpenROAD.
- Useful to confirm the clock exists and exceptions are applied.
- In many flows, SDC is carried through stages.
- If your original SDC includes relative paths, this output helps debugging.

Line 49:
- `exit 0`.
- Stops OpenROAD successfully.
- Returning success is important for automation (Makefile).
- If you want “hard stop” on unknown stage values, you would add validation earlier.
- Here we keep it simple.

Line 50:
- End of the floorplan stop block.
- Closes braces.
- Script continues to placement if not stopping.
- This pattern repeats for other stages.
- Understanding these stage boundaries helps you add custom steps.

Line 51:
- Blank line.
- Transition to placement.
- Floorplan defines geometry; placement populates the core with standard cells.
- No functional effect.
- Useful visual separation.

Line 52:
- `global_placement -density 0.52`.
- Performs coarse placement using a density target.
- Higher density packs cells tighter; lower gives more whitespace.
- This number is a knob: too high can cause congestion; too low wastes area.
- Good values depend on cell library and routing resources.

Line 53:
- Comment: “Basic timing repair before CTS”.
- Explains why `repair_timing` comes here.
- You often do early buffering/resizing to meet constraints.
- Doing it before CTS can reduce clock skew sensitivity.
- But too aggressive repair can hurt placement quality.

Line 54:
- `repair_timing -setup -hold`.
- Uses OpenROAD’s resizer to fix timing.
- Requires Liberty and constraints.
- It may insert buffers and resize gates.
- For macro-heavy designs, you may constrain buffer insertion carefully.

Line 55:
- Blank line.
- Transition to detailed placement.
- No functional effect.
- Detailed placement snaps cells to legal sites and resolves overlaps.
- In OpenLane, this corresponds to DPL.

Line 56:
- `detailed_placement`.
- Legalizes placement.
- Removes overlaps and aligns cells to rows.
- Necessary before CTS and routing.
- If this fails, global placement may have produced an illegal solution (tune density).

Line 57:
- Blank line.
- Another checkpoint; placement is meaningful to inspect.
- You can stop here using `OPENROAD_STOP_AFTER=place`.
- No functional effect.
- Useful for debugging congestion before CTS.

Line 58:
- `if { $stop_after == "place" } { ... }`.
- Placement checkpoint.
- Writes DEF, netlist, SDC.
- Allows you to inspect cell distribution and macro blockages.
- Also allows you to run external checks on placement-only results.

Line 59:
- `write_def "$out_dir/openroad/${design_name}.place.def"`.
- Writes the placed DEF.
- Includes cell locations and orientations.
- Does not include routing.
- Use it to visually check if the placer produced a reasonable layout.

Line 60:
- `write_verilog "$out_dir/openroad/${design_name}.place.v"`.
- Writes a netlist after any resizer modifications done so far.
- Useful because `repair_timing` can change the netlist.
- Downstream stages should use the modified netlist for consistency.
- In this minimal flow we don’t re-read it, but it’s useful for debug.

Line 61:
- `write_sdc "$out_dir/openroad/${design_name}.place.sdc"`.
- Writes constraints again.
- Confirms clocks and constraints survived the stage.
- Helpful when constraints are modified by scripts (not done here).
- Also useful for external STA checks.

Line 62:
- `exit 0`.
- Stops after placement.
- Make target `openroad_place` uses this.
- Keeping stage outputs stable helps automation.
- You can add `write_db` if you want OpenROAD’s internal database too.

Line 63:
- End of placement stop block.
- Closes braces.
- Flow continues to CTS if not stopping.
- This is a clean boundary.
- Good place to insert power planning later.

Line 64:
- Blank line.
- Transition to CTS (clock tree synthesis).
- No functional effect.
- CTS buffers the clock to manage skew and insertion delay.
- In full flows, CTS is often followed by timing repair again.

Line 65:
- `set cts_buf_list [list ...]`.
- Defines which buffer cells CTS is allowed to use.
- In sky130 hd, `clkbuf_*` are common choices.
- Restricting CTS buffers avoids using odd/undesirable cells.
- You can tune this list based on library availability.

Line 66:
- `clock_tree_synthesis -buf_list $cts_buf_list`.
- Runs CTS.
- Requires clock definitions from SDC.
- It inserts clock buffers and creates a clock tree.
- If no clocks are defined, CTS may do nothing or error.

Line 67:
- Blank line.
- CTS checkpoint.
- If your goal is to debug clock distribution, stopping here is useful.
- No functional effect.
- The `OPENROAD_STOP_AFTER=cts` hook is next.

Line 68:
- `if { $stop_after == "cts" } { ... }`.
- CTS stop block.
- Writes DEF, netlist, SDC.
- The netlist reflects inserted clock buffers.
- Great for analyzing skew and clock latency.

Line 69:
- `write_def "$out_dir/openroad/${design_name}.cts.def"`.
- Writes a DEF after CTS.
- You can inspect clock buffer locations.
- Also shows any changes in placement legalization.
- Useful for debugging clock congestion.

Line 70:
- `write_verilog "$out_dir/openroad/${design_name}.cts.v"`.
- Writes netlist after CTS.
- Important because CTS alters the netlist.
- If you later run external STA, use this netlist.
- Many flows also dump a post-CTS SPEF later.

Line 71:
- `write_sdc "$out_dir/openroad/${design_name}.cts.sdc"`.
- Writes constraints.
- OpenROAD may add generated clocks depending on flow; dumping SDC helps confirm.
- Useful for debug.
- Also forms a consistent artifact set.

Line 72:
- `exit 0`.
- Stops after CTS.
- The Makefile target `openroad_cts` uses this.
- Allows staged bring-up.
- Good when routing is still unstable.

Line 73:
- End CTS stop block.
- Closes braces.
- Flow continues to routing.
- No functional effect.
- Clear boundary.

Line 74:
- Blank line.
- Transition to routing.
- No functional effect.
- Routing is split into global routing (planning) and detailed routing (exact wires).
- The next commands control routing layers and run both stages.

Line 75:
- Comment: “Route”.
- Documents the next block.
- No functional effect.
- In richer flows, this section includes antenna fixes and DRC-driven iteration.
- Here it’s intentionally minimal.

Line 76:
- `set_routing_layers -signal met2-met6 -clock met2-met6`.
- Restricts routing to metals 2 through 6.
- Avoids met1 for routing (met1 is often used for local cell interconnect).
- Also sets clock routing layers.
- This is a key knob for congestion vs resistance.

Line 77:
- `global_route`.
- Runs global routing.
- Produces routing guides.
- Does not create exact geometry, but allocates capacity.
- If global route fails, the design is likely too dense or layer constraints are too strict.

Line 78:
- Blank line.
- Separation between global and detailed routing.
- No functional effect.
- Detailed routing uses the guides.
- In more advanced flows, you add antenna check and diode insertion around here.

Line 79:
- `detailed_route`.
- Runs detailed routing.
- Produces exact wire geometry.
- This is often the slowest step.
- If it fails, you may need to adjust placement density or routing layers.

Line 80:
- Blank line.
- Route checkpoint.
- No functional effect.
- The script can stop here with `OPENROAD_STOP_AFTER=route`.
- Useful if you want the routed DEF but not final renamed outputs.

Line 81:
- `if { $stop_after == "route" } { ... }`.
- Routing stop block.
- Writes DEF, netlist, SDC.
- Allows you to inspect routing without overwriting the “final” outputs.
- Useful for incremental debugging.

Line 82:
- `write_def "$out_dir/openroad/${design_name}.route.def"`.
- Writes routed DEF.
- Includes wiring.
- Can be viewed in KLayout.
- Good for quick DRC sanity checks.

Line 83:
- `write_verilog "$out_dir/openroad/${design_name}.route.v"`.
- Writes post-route netlist.
- Netlist likely unchanged by routing in this minimal flow, but kept for consistency.
- Helps with correlating final outputs.
- In some flows, routing may insert diodes/buffers which would change it.

Line 84:
- `write_sdc "$out_dir/openroad/${design_name}.route.sdc"`.
- Writes constraints.
- Again, useful for debug.
- You can compare SDC versions across stages.
- Sometimes flows add clock uncertainty or derates later.

Line 85:
- `exit 0`.
- Stops after routing.
- Make target `openroad_route` uses this.
- Leaves the “final” output filenames for full runs.
- Helps avoid confusion between stage outputs and final outputs.

Line 86:
- End route stop block.
- Closes braces.
- Script continues to final view writes.
- No functional effect.
- This is the point where signoff steps would typically start (DRC/LVS/RCX).

Line 87:
- Blank line.
- Transition to final save views.
- No functional effect.
- The following writes are “final artifacts” for the PnR run.
- They match the original script behavior.

Line 88:
- Comment: “Save views”.
- Documents the intent.
- No functional effect.
- Many flows also write OpenROAD DB, GDS, SPEF, etc.
- Here we only dump DEF, Verilog, SDC.

Line 89:
- `write_def "$out_dir/openroad/${design_name}.def"`.
- Final DEF.
- If you did not stop early, this should reflect routed design.
- This is the main physical output used for viewing and next-stage tooling.
- If you stop early, this line isn’t reached.

Line 90:
- `write_verilog "$out_dir/openroad/${design_name}.pnr.v"`.
- Final post-PnR netlist.
- Useful for gate-level simulation correlation.
- If you inserted buffers or diodes, they appear here.
- For signoff, you might also include power pins and tie cells.

Line 91:
- `write_sdc "$out_dir/openroad/${design_name}.sdc"`.
- Final SDC snapshot.
- Useful for downstream STA runs or documentation.
- In advanced flows, you might generate a cleaned SDC.
- Here it is just a dump of current constraints.

Line 92:
- Blank line.
- End of script.
- Tcl ends when the file ends.
- No explicit `exit` is required; OpenROAD exits when `-exit` was passed.
- In `flow/run_openroad.sh`, OpenROAD is invoked with `-exit`.

-------------------------------------------------------------------------------
How to use the stage targets
-------------------------------------------------------------------------------

- Full PnR (current behavior):
  - `make pnr`

- Stop after floorplan:
  - `make openroad_floorplan`
  - Output: `flow/out/openroad/soc_top.floorplan.def`

- Stop after placement:
  - `make openroad_place`
  - Output: `flow/out/openroad/soc_top.place.def`

- Stop after CTS:
  - `make openroad_cts`
  - Output: `flow/out/openroad/soc_top.cts.def`

- Stop after routing:
  - `make openroad_route`
  - Output: `flow/out/openroad/soc_top.route.def`

-------------------------------------------------------------------------------
Common failure modes (quick debug checklist)
-------------------------------------------------------------------------------

- `link_design` fails:
  - Check `DESIGN_NAME` matches the synthesized netlist top.
  - Ensure standard-cell LEF is loaded.

- `initialize_floorplan` fails with missing site:
  - The `-site unithd` must exist in the tech LEF.

- CTS does nothing:
  - Confirm your SDC defines `create_clock` on the clock port.

- Routing fails / high congestion:
  - Reduce placement density, increase die/core area, or allow more layers.

(End of deep dive)
