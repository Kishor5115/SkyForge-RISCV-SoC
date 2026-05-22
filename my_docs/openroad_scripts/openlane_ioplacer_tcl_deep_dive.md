# Deep Dive: flow/openroad/scripts/ioplacer.tcl (OpenLane-derived)

This document explains `flow/openroad/scripts/ioplacer.tcl` line by line.

What this script is:
- An OpenLane-style OpenROAD stage script for IO pin placement.
- It expects OpenLane’s environment-variable convention and a pre-existing database (`CURRENT_ODB`) or DEF.
- In this repo, it’s mainly for learning unless you add a wrapper driver that defines those env vars.

What this script does:
- Reads a design database (ODB) via the `read` helper.
- Optionally reads an extra LEF for contextual IO.
- Configures pin lengths/thickness extensions.
- Calls `place_pins` with layers and options.
- Writes outputs via the `write` helper.

-------------------------------------------------------------------------------
Key OpenLane-style env variables referenced
-------------------------------------------------------------------------------

- `SCRIPTS_DIR`: used to source the IO helper file.
- `CURRENT_ODB` / `CURRENT_DEF`: input database.
- `IO_READ_DEF`: whether to read DEF instead of ODB.
- `FP_IO_MODE`: random vs non-random mode.
- `FP_IO_MIN_DISTANCE`: min spacing between pins.
- `FP_IO_HLAYER` / `FP_IO_VLAYER`: routing layers used for horizontal/vertical pins.
- `FP_IO_HLENGTH` / `FP_IO_VLENGTH`: pin lengths.
- `FP_IO_HEXTEND` / `FP_IO_VEXTEND`: pin length extensions.
- `FP_IO_HTHICKNESS_MULT` / `FP_IO_VTHICKNESS_MULT`: thickness scaling.
- `placement_tmpfiles` + `CONTEXTUAL_IO_FLAG`: advanced OpenLane feature.

-------------------------------------------------------------------------------
Line-by-line walkthrough (in depth)
-------------------------------------------------------------------------------

Line 1:
- License header begins.
- No functional effect.
- Identifies upstream source.
- Useful for updates.
- OpenROAD ignores it.

Line 2:
- Copyright line.
- No functional effect.
- Metadata.
- Not used by tools.
- Good to keep intact.

Line 3:
- License text continues.
- No functional effect.
- Legal.
- OpenROAD ignores.
- You rarely edit these lines.

Line 4:
- License text continues.
- No effect.
- States Apache 2.0.
- Allows modification and redistribution.
- Still not a flow control statement.

Line 5:
- License URL.
- No effect.
- Informational.
- Helps find license terms.
- Keep as-is.

Line 6:
- Disclaimer.
- No effect.
- Informational.
- Typical.
- End of header region soon.

Line 7:
- End of header.
- No effect.
- Now real logic begins.
- The script starts by sourcing helpers.
- This is a typical OpenLane stage structure.

Line 8:
- `source $::env(SCRIPTS_DIR)/openroad/common/io.tcl`.
- Loads the helper procs: `read`, `write`, etc.
- Without this, `read` is undefined.
- It also pulls in global connection helper.
- The `$::env(SCRIPTS_DIR)` must point to the correct scripts root.

Line 9:
- `read`.
- Calls helper proc to read the current design database.
- OpenLane either loads ODB (`read_db`) or LEF+DEF (`read_lef`, `read_def`).
- Which mode is used depends on `IO_READ_DEF`.
- Also loads libs so OpenROAD knows cell masters.

Line 10:
- Blank line.
- Visual separation.
- No effect.
- Helps you see “read stage” ends here.
- IO placement configuration begins next.

Line 11:
- `if { [info exists ::env(CONTEXTUAL_IO_FLAG)] } { ... }`.
- Checks whether OpenLane is in “contextual IO” mode.
- Contextual IO means you’re placing pins for a block relative to a larger context.
- In that mode, you might read an additional LEF describing the top-level environment.
- In this script, it reads `top_level.lef` from a tmp directory.

Line 12:
- Inside the `if`: `read_lef $::env(placement_tmpfiles)/top_level.lef`.
- Adds extra LEF so pin placement can be aware of the top-level boundary.
- This is an advanced flow feature.
- If `placement_tmpfiles` is unset, this would error, but only inside the guard.
- For this repo, you probably won’t use this unless doing hierarchical integration.

Line 13:
- End of contextual IO block.
- Closes braces.
- No further effect if not enabled.
- This is safe for non-contextual runs.
- Good example of optional advanced behavior.

Line 14:
- Blank line.
- No effect.
- Separates contextual block from pin-geometry configuration.
- Good readability.
- Next: pin length.

Line 15:
- `if {$::env(FP_IO_HLENGTH) != "" && $::env(FP_IO_VLENGTH) != ""} { ... }`.
- Checks both horizontal and vertical pin lengths are provided.
- OpenLane uses empty string as “unset”.
- If both set, it calls `set_pin_length`.
- This affects IO pin geometry (how far pins extend into the core).

Line 16:
- Inside: `set_pin_length -hor_length ... -ver_length ...`.
- Sets the pin “stub” length.
- Longer stubs can improve router access but may cause congestion near edges.
- Short stubs reduce congestion but can make DRC harder.
- This is a tradeoff knob.

Line 17:
- End length block.
- No effect when lengths are not set.
- Leaves default pin length.
- Defaults come from OpenROAD.
- In a custom flow you might always set explicit lengths.

Line 18:
- Blank line.
- No effect.
- Next: pin length extension.
- In OpenLane this is separate from base pin length.
- Helps with thick pins.

Line 19:
- `if {$::env(FP_IO_HEXTEND) != "0" && $::env(FP_IO_VEXTEND) != "0"} { ... }`.
- Checks for non-zero extension values.
- Uses string comparison; env vars are strings.
- If non-zero, calls `set_pin_length_extension`.
- Extension adds additional length beyond default stub.

Line 20:
- Inside: `set_pin_length_extension -hor_extension ... -ver_extension ...`.
- Extends pins.
- Useful when using thick pins or wanting larger landing pads.
- Can help reduce via crowding.
- Can also increase blockage/congestion.

Line 21:
- End extension block.
- No effect if extensions are zero.
- Keeps default behavior.
- OpenLane defaults often set these to 0.
- You tune only if needed.

Line 22:
- Blank line.
- No effect.
- Next: pin thickness multiplier.
- Thickness affects pin metal width.
- Wider pins can be easier to route but consume resources.

Line 23:
- `if {$::env(FP_IO_VTHICKNESS_MULT) != "" && $::env(FP_IO_HTHICKNESS_MULT) != ""} { ... }`.
- Checks both thickness multipliers are provided.
- Empty string means unset.
- If set, calls `set_pin_thick_multiplier`.
- Multiplier scales the width of pins.

Line 24:
- Inside: `set_pin_thick_multiplier -hor_multiplier ... -ver_multiplier ...`.
- Applies thickness scaling.
- If you pick too large values, pins can overlap or violate DRC.
- Useful for pads or macro pins.
- Usually left at default for small blocks.

Line 25:
- End thickness block.
- No effect if multipliers are unset.
- Default thickness remains.
- This script makes all these optional.
- That’s a flexible design.

Line 26:
- Blank line.
- No effect.
- Now it builds the `place_pins` argument list.
- Similar to how floorplan script builds arg lists.

Line 27:
- `set arg_list [list]`.
- Initializes empty list.
- Used to add optional flags.
- Avoids quoting issues.
- Clean Tcl pattern.

Line 28:
- `if { $::env(FP_IO_MODE) == 1 } { lappend arg_list -random }`.
- If FP_IO_MODE is 1, we randomize pin placement.
- If not, pins may be placed using a config file/order (not shown here).
- Random pin placement is okay for experimentation.
- For SoC-level integration, you typically want deterministic pin planning.

Line 29:
- `if { $::env(FP_IO_MIN_DISTANCE) != "" } { ... }`.
- Optional minimum distance between pins.
- Prevents pins from being placed too close.
- Helps avoid DRC and router-access issues.
- If unset, OpenROAD uses default spacing rules.

Line 30:
- Inside: `lappend arg_list -min_distance $::env(FP_IO_MIN_DISTANCE)`.
- Adds the option.
- Units typically in microns (depending on OpenROAD command expectations).
- Ensure units match track grid.
- Too large can make it impossible to place all pins.

Line 31:
- `set HMETAL $::env(FP_IO_HLAYER)`.
- Defines horizontal pin layers.
- OpenLane often uses a specific metal (e.g., met2 or met3).
- Picking layers that match your routing stack is important.
- If you pick an illegal layer, `place_pins` errors.

Line 32:
- `set VMETAL $::env(FP_IO_VLAYER)`.
- Defines vertical pin layers.
- Must exist in the tech LEF.
- Often one layer above/below HMETAL.
- Choosing layers influences pin accessibility.
- Also affects DRC near boundary.

Line 33:
- `place_pins {*}$arg_list \` continues.
- Calls OpenROAD’s pin placer.
- `-random_seed 42` ensures deterministic randomness.
- Determinism is critical for reproducible builds.
- You can change the seed to explore alternatives.

Line 34:
- `-hor_layers $HMETAL`.
- Restricts horizontal pins to specific layers.
- Improves consistency.
- Also helps router planning.
- If multiple layers, OpenLane passes a list.

Line 35:
- `-ver_layers $VMETAL`.
- Restricts vertical pins.
- Same rationale.
- Helps avoid odd layer usage.
- Supports multiple layers.

Line 36:
- Blank line.
- No effect.
- After `place_pins`, we write outputs.
- This is a stage boundary.

Line 37:
- `write`.
- Calls helper proc.
- Writes DB/DEF/SDC/netlist depending on `SAVE_*` env vars.
- This is OpenLane’s stage persistence mechanism.
- If you don’t set `SAVE_DEF` or `SAVE_ODB`, you may get warnings.

Line 38:
- End of file.
- No explicit exit required.
- In OpenLane, OpenROAD is run with `-exit`.
- So OpenROAD exits when script completes.
- That ensures automation stops.

-------------------------------------------------------------------------------
Practical wiring suggestion for this repo
-------------------------------------------------------------------------------

If you want to actually run this script in this repo:
- Create a driver that sets:
  - `SCRIPTS_DIR` to a path where `openroad/common/io.tcl` resolves,
  - `CURRENT_ODB` / `SAVE_ODB` (or DEF equivalents),
  - `LIB_TYPICAL` and other `read`-related vars,
  - `FP_IO_*` variables.
- Then invoke `openroad -exit driver.tcl`.

(End of deep dive)
