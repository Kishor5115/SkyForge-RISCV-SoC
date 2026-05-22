# Deep Dive: flow/openroad/scripts/floorplan.tcl (OpenLane-derived)

This document explains `flow/openroad/scripts/floorplan.tcl` line by line.

What this script is:
- An OpenLane-style OpenROAD floorplanning stage.
- It assumes a large set of OpenLane environment variables are defined.
- In this repo, it’s primarily a reference / learning artifact unless you wire a wrapper that defines those variables.

What it does:
- Reads libraries + merged LEF + netlist.
- Computes margins.
- Runs `initialize_floorplan` either in “absolute die/core” or “utilization/aspect ratio” mode.
- Inserts tie cells.
- Extracts die/core area from the database and writes reports.
- Loads tracks info.
- Writes the database (and any enabled SAVE_* views) via the helper `write` proc.

-------------------------------------------------------------------------------
Environment variables this script expects (conceptual)
-------------------------------------------------------------------------------

These are *not* exhaustive, but they’re the big ones you see referenced:
- `SCRIPTS_DIR`: base path used for `source` statements.
- `LIB_SYNTH_COMPLETE`: liberty list used by `read_libs`.
- `MERGED_LEF`: a merged LEF that includes tech + std cells + macros.
- `DESIGN_NAME`: top module.
- `PLACE_SITE`: site name (e.g., `unithd`).
- `PLACE_SITE_WIDTH`, `PLACE_SITE_HEIGHT`: used to compute margins.
- `BOTTOM_MARGIN_MULT`, `TOP_MARGIN_MULT`, `LEFT_MARGIN_MULT`, `RIGHT_MARGIN_MULT`.
- `FP_SIZING`: either `absolute` or `relative`.
- If `absolute`: `DIE_AREA` and optionally `CORE_AREA`.
- If `relative`: `FP_CORE_UTIL`, `FP_ASPECT_RATIO`.
- `SYNTH_TIEHI_PORT`, `SYNTH_TIELO_PORT`: tie cell/pin definition.
- `TRACKS_INFO_FILE_PROCESSED`: tracks definition Tcl.
- `fp_report_prefix`: output prefix for reports.
- `SAVE_ODB` (and other `SAVE_*`) to control what `write` emits.

-------------------------------------------------------------------------------
Line-by-line walkthrough
-------------------------------------------------------------------------------

Line 1:
- Comment block begins (license header).
- This is legal metadata; OpenROAD ignores it.
- It tells you where the script originated.

Line 2:
- Copyright line.
- No functional effect.
- Useful for tracking upstream changes.

Line 3:
- Blank in the header.
- No effect.
- Separates sections.

Line 4:
- License text continues.
- No effect.
- Indicates Apache 2.0 licensing.

Line 5:
- Continues license statement.
- No effect.

Line 6:
- Continues license statement.
- No effect.

Line 7:
- License URL.
- No effect.

Line 8:
- Blank line.
- No effect.

Line 9:
- Disclaimer: distributed on an “AS IS” basis.
- No functional effect.

Line 10:
- Ends the license header block.
- No functional effect.

Line 11:
- `source $::env(SCRIPTS_DIR)/openroad/common/io.tcl`.
- Pulls in helper procs: `read_libs`, `read_netlist`, `write`, etc.
- This is critical: without it, later commands are undefined.
- It also indirectly sources global-connection helpers.
- The path layout assumes OpenLane-like script organization.

Line 12:
- `read_libs -typical "$::env(LIB_SYNTH_COMPLETE)"`.
- Calls the helper proc `read_libs`.
- “Typical” corner is mandatory here.
- `LIB_SYNTH_COMPLETE` is usually a list of standard-cell libs.
- `read_libs` also optionally reads `EXTRA_LIBS` (macros) if enabled.

Line 13:
- `read_lef $::env(MERGED_LEF)`.
- Loads a merged LEF.
- OpenLane typically produces `merged.lef` from tech + std + macro LEFs.
- This simplifies downstream scripts: you just read one LEF.
- If `MERGED_LEF` is wrong, *everything* downstream breaks.

Line 14:
- `read_netlist`.
- Calls helper proc to read and link the design.
- In OpenLane this reads `$CURRENT_NETLIST` and does `link_design`.
- It also reads SDC if `CURRENT_SDC` exists.
- The “OpenLane way” is to set stage-specific `CURRENT_*` paths.

Line 15:
- Blank line.
- Separates “read inputs” from “compute margins”.
- No effect.

Line 16:
- `set bottom_margin ...`.
- Computes margin in microns using site height and a multiplier.
- This gives consistent row-aligned core offsets.
- Using site metrics avoids fractional placement row issues.
- Margins influence how much whitespace around the core boundary you reserve.

Line 17:
- `set top_margin ...`.
- Same concept for the top boundary.
- Often set equal to bottom margin.
- Can be larger if you plan special routing/pads.
- Keeps the core away from the die edge.

Line 18:
- `set left_margin ...`.
- Computes left core spacing using site width.
- Again, site-grid alignment.
- Important because row sites define legal placement.
- Non-integer multiples can cause rounding errors.

Line 19:
- `set right_margin ...`.
- Computes right core spacing.
- Often symmetric with left.
- Might differ depending on IO planning.
- Reserved for pin access, straps, etc.

Line 20:
- Blank line.
- Separates margin calculations from argument building.
- No effect.

Line 21:
- `set arg_list [list]`.
- Starts building a list of options.
- Tcl best practice: accumulate args into a list, then splat with `{*}`.
- This avoids quoting pitfalls.
- Also makes conditional arg addition cleaner.

Line 22:
- `lappend arg_list -site $::env(PLACE_SITE)`.
- Adds the site used by `initialize_floorplan`.
- Must match the technology site.
- In sky130_hd this is commonly `unithd`.
- If you use a different standard-cell library, site may change.

Line 23:
- Blank line.
- No effect.
- Visual separation before sizing mode selection.

Line 24:
- `if {$::env(FP_SIZING) == "absolute"} { ... }`.
- Branches based on sizing method.
- “absolute” means you provide explicit die/core rectangles.
- “relative” means you provide utilization and aspect ratio.
- This is a major knob in floorplanning.

Line 25:
- First validation: `DIE_AREA` length must be 4.
- DIE_AREA is expected to be `{llx lly urx ury}`.
- If it’s not 4 values, it errors and exits.
- This is a good defensive check.
- Prevents silent wrong floorplans.

Line 26:
- If invalid, print to stderr.
- Then `exit -1`.
- This indicates failure.
- In make-based flows, it stops the pipeline.
- Helps catch misconfigured env early.

Line 27:
- Checks if `CORE_AREA` exists.
- If it does not, the script computes it from DIE_AREA + margins.
- This gives a “default core inset” behavior.
- Core area is where std cells can be placed.
- Macros can also be placed in core depending on settings.

Line 28:
- Extracts `die_ll_x`.
- Reads from DIE_AREA list index 0.
- These are in microns.
- You must ensure consistent units across env.
- OpenLane generally uses microns at this stage.

Line 29:
- Extracts `die_ll_y`.
- Same idea.
- Lower-left y coordinate.
- Defines die origin.
- Often (0,0) but not required.

Line 30:
- Extracts `die_ur_x`.
- Upper-right x coordinate.
- Defines die width.
- Die size affects routing resources and final area.
- Must be large enough to fit macros + core utilization.

Line 31:
- Extracts `die_ur_y`.
- Upper-right y coordinate.
- Defines die height.
- Combined with aspect ratio determines shape.
- Too skinny shapes can cause congestion.

Line 32:
- Computes `core_ll_x = die_ll_x + left_margin`.
- Offsets core boundary from die boundary.
- Ensures core begins inside die with some clearance.
- Clearance is used for IO routing, power ring, etc.
- If too small, pin access/routing becomes hard.

Line 33:
- Computes `core_ll_y` similarly.
- Bottom clearance.
- Often used for IO ring and corner keepouts.
- Aligning to site height is good.
- If margins are zero, core touches die edge.

Line 34:
- Computes `core_ur_x = die_ur_x - right_margin`.
- Right inset.
- Keeps core away from die edge.
- Helps avoid boundary DRC issues.
- Also allows more routing/pin resources.

Line 35:
- Computes `core_ur_y = die_ur_y - top_margin`.
- Top inset.
- Same reasons.
- Ensures a consistent halo.
- In OpenLane, margins are multipliers of site.

Line 36:
- Sets `::env(CORE_AREA)` to the computed list.
- This makes core area available to downstream scripts.
- “Environment variable as state” is an OpenLane pattern.
- Later, the script writes CORE_AREA back out from the database.
- That helps maintain consistency.

Line 37:
- Else branch: CORE_AREA already exists.
- Validates CORE_AREA has 4 values.
- If not, error.
- This avoids subtle geometry bugs.
- Using a provided CORE_AREA overrides margin multipliers.

Line 38:
- Prints info: using set CORE_AREA, ignoring core margin parameters.
- This is important because it explains why your margin multipliers have no effect.
- Debugging floorplan often involves these knobs.
- An explicit log line is valuable.
- No functional effect.

Line 39:
- Adds `-die_area $::env(DIE_AREA)` to arg list.
- Adds `-core_area $::env(CORE_AREA)` to arg list.
- Adds `-site $::env(PLACE_SITE)` again (harmless redundancy).
- The final arg list fully specifies geometry.
- This becomes a deterministic floorplan.

Line 40:
- Else branch: FP_SIZING not absolute.
- Uses utilization/aspect ratio mode.
- Adds `-utilization $::env(FP_CORE_UTIL)`.
- Adds `-aspect_ratio $::env(FP_ASPECT_RATIO)`.
- Adds `-core_space` with margins.

Line 41:
- Calls `initialize_floorplan {*}$arg_list`.
- `{*}` “splats” the list into separate arguments.
- This is the key floorplanning command.
- It creates rows, tracks core, and sets die/core boundaries.
- If `PLACE_SITE` is wrong, this fails.

Line 42:
- Reads tie cell definitions.
- `set tielo_cell ...` and `set tielo_port ...`.
- `SYNTH_TIELO_PORT` is typically `cell pin`.
- Tie cells provide constant 0/1 nets without creating floating logic.
- Many flows insert tie cells early.

Line 43:
- Reads tiehi definitions similarly.
- `tiehi_cell` / `tiehi_port`.
- Must exist in the standard-cell library.
- If tie cell doesn’t exist, insert fails.
- The goal: avoid long constant nets and reduce leakage.

Line 44:
- `insert_tiecells "$tielo_cell/$tielo_port" -prefix "TIE_ZERO_"`.
- Inserts tie-low cells wherever needed.
- Prefix helps identification in netlist/layout.
- Tie insertion ensures constant nets are physically driven.
- Some flows do it later; OpenLane does it early.

Line 45:
- Inserts tie-high similarly.
- Prefix `TIE_ONE_`.
- Same purpose.
- Helps keep constants local.
- Also prevents optimization tools from creating illegal constant sources.

Line 46:
- Reads OpenDB handles: chip, tech, block.
- `::ord::get_db` gets the OpenROAD database.
- These objects allow querying die/core from the DB.
- This is an OpenROAD-specific introspection step.
- Used to extract real geometry after initialization.

Line 47:
- Logs: extracting DIE_AREA and CORE_AREA.
- Clears env variables to prepare for re-population.
- This ensures the env values reflect the *actual* floorplan.
- Floorplan commands may snap to grid.
- This makes subsequent scripts consistent.

Line 48:
- Gets die/core from block: `getDieArea`, `getCoreArea`.
- These are in DBU units (database units).
- DBU are integer “internal units”.
- Must convert to microns.
- Next lines handle conversion.

Line 49:
- Converts bounding boxes to min/max list form.
- Extracts xMin/yMin/xMax/yMax.
- In OpenDB, `Rect` provides these.
- Prepares for conversion.
- Still in DBU.

Line 50:
- `set dbu [$tech getDbUnitsPerMicron]`.
- Reads conversion factor.
- Example: 1000 DBU/um.
- Dividing DBU by dbu gives microns.
- Critical for correct reporting.

Line 51:
- Clears env DIE_AREA/CORE_AREA.
- Rebuilds them in microns.
- Uses `foreach coord ...` loops.
- Appends `expr {1.0 * $coord / $dbu}`.
- `1.0 *` ensures float division.

Line 52:
- Logs die/core area and where reports are saved.
- Writes two report files: `_die_area.rpt` and `_core_area.rpt`.
- Uses `fp_report_prefix`.
- These reports are simple: they contain four numbers.
- Useful for downstream scripts.

Line 53:
- Sources `TRACKS_INFO_FILE_PROCESSED`.
- Tracks are routing grid definitions.
- OpenROAD needs tracks to place wires on legal routing tracks.
- In OpenLane, this is generated per PDK/library.
- Without correct tracks, routing quality and legality suffer.

Line 54:
- Opens the die/core area report files.
- Writes the list content without newline (`puts -nonewline`).
- Closes files.
- This produces compact files consumed by later scripts.
- If directory doesn’t exist, open fails.

Line 55:
- Calls `write` (helper proc) to save stage results.
- In OpenLane, `write` respects `SAVE_ODB`, `SAVE_DEF`, etc.
- This is why the script doesn’t hardcode output paths.
- You control outputs by setting environment variables.
- This approach is flexible but requires careful env setup.

Lines 56-109 (rest of file):
- The remaining lines are mostly structural braces and the final `write` call already described.
- In an OpenLane checkout, this exact script is usually paired with a driver that sets CURRENT_* and SAVE_* paths.
- In this repo, to *execute* it, you’d add a wrapper that defines:
  - `SCRIPTS_DIR` so `source` works,
  - `MERGED_LEF` (you can build it by concatenating tech + std + macro LEFs),
  - `CURRENT_NETLIST`, `CURRENT_SDC`, `SAVE_DEF`, `SAVE_ODB`, and `fp_report_prefix`.
- If you don’t define these, the script will error (missing env vars).
- Treat it as a learning reference unless you intentionally wire it.
- The value in learning it: it demonstrates how OpenLane structures floorplan stages and how it persists state via env vars.

-------------------------------------------------------------------------------
Practical notes (how you’d wire it in this repo)
-------------------------------------------------------------------------------

To make this runnable here, you typically create a small “driver” Tcl that:
- Reads `TECH_LEF`, `STD_CELL_LEF`, `SRAM_LEF` and merges them into `MERGED_LEF`.
- Sets `CURRENT_NETLIST` to the Yosys netlist.
- Sets `LIB_SYNTH_COMPLETE` to the standard-cell liberty.
- Sets `PLACE_SITE`, sizing knobs, and tie cell settings.
- Sets `SAVE_DEF`/`SAVE_ODB` outputs.
Then it `source`s this script.

(End of deep dive)
