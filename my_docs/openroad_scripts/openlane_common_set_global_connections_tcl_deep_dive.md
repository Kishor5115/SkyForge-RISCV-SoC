# Deep Dive: flow/openroad/scripts/common/set_global_connections.tcl

This document explains `flow/openroad/scripts/common/set_global_connections.tcl` line by line.

What this script is for:
- Defines a single procedure: `set_global_connections`.
- That procedure registers “global power/ground connections” in OpenROAD.
- It supports two use-cases:
  1) Standard-cell global connections (VDD/GND for every instance).
  2) Macro hook connections (connect macro pins to specific nets by instance pattern).

Why global connections matter:
- Many LEFs/DEFs do not explicitly connect power pins in the netlist.
- Instead, the physical tool uses a “global connection” mechanism:
  - “All pins matching pattern X connect to net Y.”
- This is essential when writing powered netlists, doing PDN, IR drop, etc.

How it’s used here:
- `flow/openroad/scripts/common/io.tcl` calls `set_global_connections` inside its `write` proc.
- That means: whenever you write views (DEF/netlist/etc) after inserting new cells,
  you can ensure new instances get the expected power/ground wiring.

-------------------------------------------------------------------------------
Line-by-line walkthrough
-------------------------------------------------------------------------------

L1:
- License header line.
- No tool effect.
- Identifies upstream.
- Keep it intact.

L2:
- Blank line in license block.
- No effect.
- Visual separation.
- Not executed.

L3:
- Apache license statement continues.
- No effect.
- Legal.
- Not executed.

L4:
- License continues.
- No effect.
- Not executed.
- Keep as-is.

L5:
- License continues.
- No effect.
- Not executed.
- Keep as-is.

L6:
- License URL.
- No effect.
- Not executed.
- Informational.

L7:
- Blank line.
- No effect.
- Not executed.
- Separates license sections.

L8:
- Disclaimer line.
- No effect.
- Not executed.
- Informational.

L9:
- Disclaimer continues.
- No effect.
- Not executed.
- Informational.

L10:
- End of license block region.
- No effect.
- Not executed.
- Next: real code.

L11:
- Blank line.
- No effect.
- Visual separation.
- Helps readability.

L12:
- Comment: “Power nets”.
- Documents that the following proc is about power/ground.
- No functional effect.
- Signals intended usage.

L13:
- `proc set_global_connections {} {` begins procedure definition.
- The proc takes no arguments.
- It relies entirely on environment variables.
- OpenLane style: env-driven configuration.

L14:
- `if { [info exists ::env(FP_PDN_ENABLE_GLOBAL_CONNECTIONS) ] } {`.
- Guard: only do standard-cell global connection if the knob exists.
- This avoids errors when the variable is missing.
- It also allows scripts to run in flows that don’t define PDN variables.

L15:
- Nested `if { $::env(FP_PDN_ENABLE_GLOBAL_CONNECTIONS) == 1 } {`.
- Actual enable check.
- Uses numeric comparison.
- A value of `1` means “do it”, others mean “skip”.

L16:
- `foreach power_pin $::env(STD_CELL_POWER_PINS) {`.
- Iterates over a list of power pin names in the std-cell library.
- Example: `VPWR`, `VDD`, etc (depends on library/LEF naming).
- Using a list supports libraries with multiple power pins.

L17:
- `add_global_connection \` starts an OpenROAD command call.
- The backslash escapes newline for readability.
- This command defines a global connect rule.
- It is evaluated/registered in the OpenDB.

L18:
- `-net $::env(VDD_NET) \`.
- Selects the net name to connect to (e.g., `vccd1` or `VDD`).
- Must match the PDN net naming convention.
- If you mismatch names, your power net will be split/missing.

L19:
- `-inst_pattern .* \`.
- Regex for instance names.
- `.*` means “all instances”.
- That is appropriate for standard cells.
- If you want to exclude blocks, you would tighten this pattern.

L20:
- `-pin_pattern $power_pin \`.
- Pin name pattern for power pins.
- Uses the current entry from `STD_CELL_POWER_PINS`.
- This connects every matching pin to the VDD net.
- Pin names must match the LEF.

L21:
- `-power`.
- Marks this global connection as a power connection.
- OpenROAD tracks power/ground types.
- This can affect analysis commands.
- Not just a string label.

L22:
- End of `add_global_connection` statement.
- Close the command.
- Next iteration repeats for each power pin.
- Ensures all power pins are handled.

L23:
- Close of the `foreach power_pin` loop.
- All standard-cell power pins now have global connects.
- This is global: applies across the whole design.
- Still no physical wires are created; it’s connectivity intent.

L24:
- `foreach ground_pin $::env(STD_CELL_GROUND_PINS) {`.
- Similar loop for ground pins.
- Again, supports multiple ground pins.
- Names depend on library naming.

L25:
- Another `add_global_connection \`.
- Same structure.
- Now for ground.
- Uses GND net name.

L26:
- `-net $::env(GND_NET) \`.
- Selects ground net.
- Example: `vssd1`.
- Must match PDN naming.
- Consistency is crucial.

L27:
- `-inst_pattern .* \`.
- Applies to all instances.
- Same rationale.
- Standard cells everywhere.
- If you have analog blocks, you may need special handling.

L28:
- `-pin_pattern $ground_pin \`.
- Current ground pin.
- Must match LEF pin names.
- Connects all those pins to ground.
- Combined with power, this defines P/G connectivity.

L29:
- `-ground`.
- Marks rule as ground.
- OpenROAD uses this for classifying nets.
- Helps PDN and powered netlist writing.
- Ensures correct semantics.

L30:
- Close command.
- End of the per-ground-pin command.
- Loop continues.
- All ground pins get rules.

L31:
- Close `foreach ground_pin`.
- Standard-cell power/ground global connections now defined.
- This is the common “connect VPWR/VGND everywhere” step.
- Without it, powered netlist export can miss supplies.

L32:
- Close the nested enable `if`.
- If knob disabled, no standard-cell connects are added.
- That might be desired in non-powered flows.
- But for PDN it’s typically required.

L33:
- Close the outer “exists” `if`.
- Again: avoids referencing an undefined env var.
- Makes the proc safer in multiple contexts.
- This is defensive scripting.

L34:
- Blank line.
- Visual separation between standard-cell behavior and macro-hook behavior.
- No effect.
- Helps readability.

L35:
- `if { $::env(FP_PDN_ENABLE_MACROS_GRID) == 1 &&`.
- Starts macro PDN hook block.
- This one does *not* guard with `info exists` for the enable variable.
- It assumes `FP_PDN_ENABLE_MACROS_GRID` exists in OpenLane PDN flows.

L36:
- Continuation line: `[info exists ::env(FP_PDN_MACRO_HOOKS)]} {`.
- Requires the macro hooks variable to exist.
- That variable encodes mapping from instance pattern to power/ground pins.
- Guard prevents missing hooks from causing errors.

L37:
- `set pdn_hooks [split $::env(FP_PDN_MACRO_HOOKS) ","]`.
- Splits the hooks string by commas.
- Each comma-separated chunk is one “hook entry”.
- Each entry itself is expected to have multiple fields.
- The parsing convention is upstream OpenLane’s.

L38:
- `foreach pdn_hook $pdn_hooks {`.
- Loops over each hook entry.
- Each entry is then indexed into pieces.
- Assumes each entry is list-like.
- If formatting is wrong, indexes may be empty.

L39:
- `set instance_name [lindex $pdn_hook 0]`.
- Instance pattern/regex.
- Used to match macro instances.
- Could be `u_sram.*` or specific instance name.
- Must match OpenDB instance names.

L40:
- `set power_net [lindex $pdn_hook 1]`.
- Power net name to connect.
- Could be same as global VDD or a dedicated macro supply.
- Useful when macros have separate supplies.
- Must match your PDN strategy.

L41:
- `set ground_net [lindex $pdn_hook 2]`.
- Ground net name.
- Similar logic.
- Could be same global GND.
- Ensures macro ground is connected properly.

L42:
- `set power_pin [lindex $pdn_hook 3]`.
- Macro pin name for power.
- Must match macro LEF pin.
- Example: `vccd1`.
- If wrong, connection won’t happen.

L43:
- `set ground_pin [lindex $pdn_hook 4]`.
- Macro ground pin.
- Must match LEF.
- Example: `vssd1`.
- Must be correct per macro.

L44:
- `if { $power_pin == "" || $ground_pin == "" } {`.
- Basic validation.
- If pin names are empty, the hook entry is malformed.
- Better to fail fast.
- Prevents silent missing power connection.

L45:
- `puts "FP_PDN_MACRO_HOOKS missing power and ground pin names"`.
- Prints clear error message.
- Debugging macro power issues is painful; explicit logs help.
- Message describes exact variable.
- Points you to config mistake.

L46:
- `exit 1`.
- Abort flow.
- This is correct: wrong macro power pins makes the run meaningless.
- In build automation, you want a hard failure.
- Encourages early fix.

L47:
- End of validation `if`.
- Flow continues only if pins are present.
- Next: verify instance name matches something.
- This is extra safety.

L48:
- `set matched 0`.
- Initializes a flag.
- Will be set to 1 if any instance matches.
- Helps catch typos in instance regex.
- Without this, you might silently add a rule that matches nothing.

L49:
- `foreach cell [[ord::get_db_block] getInsts] {`.
- Iterates over all instances in the OpenDB block.
- This is an OpenROAD/OpenDB API usage.
- Used to check if regex matches any instance names.
- Can be expensive in huge designs, but fine for typical sizes.

L50:
- `if { [regexp "\^$instance_name" [$cell getName]] } {`.
- Uses regex to match.
- Anchors with `^` so it matches from beginning.
- Important: if `instance_name` is a regex itself, this forms a combined regex.
- This logic assumes `instance_name` is intended as a regex prefix.

L51:
- `set matched 1`.
- Sets flag if any match found.
- Doesn’t break; continues scanning.
- Only cares that at least one exists.
- Could be optimized but okay.

L52:
- Close inner `if`.
- Continue scanning instances.
- Still in verification loop.
- This is purely a sanity check.

L53:
- Close instance loop.
- Now `matched` indicates whether any instance name matched.
- Next: error if not.
- Again: fail fast rather than silently skip.

L54:
- `if { $matched != 1 } {`.
- Tests the flag.
- If not matched, hook likely wrong.
- Better to stop rather than produce incorrect PDN connectivity.
- Prevents debugging headaches later.

L55:
- `puts "No regex match found for $instance_name defined in FP_PDN_MACRO_HOOKS"`.
- Emits error message including the pattern.
- Helps you confirm if regex is correct.
- Often instance names differ after synthesis (hierarchy changes).
- This message points you to that mismatch.

L56:
- `exit 1`.
- Abort the run.
- Again: appropriate for PDN macro hookups.
- Without macro power, extraction/timing/IR drop are invalid.
- Strong correctness guarantee.

L57:
- Close the “no match” check.
- Continue with adding global connections.
- Now we have validated both pins and instance match.
- This reduces silent misconfiguration.

L58:
- `add_global_connection \` (macro power).
- Adds a *macro-specific* global connection.
- Unlike std cells, inst_pattern is restricted.
- Pin_pattern is macro power pin.
- Marks connection as power.

L59:
- `-net $power_net \`.
- The net to connect.
- Could be VDD.
- Or a dedicated net.
- Up to your PDN design.

L60:
- `-inst_pattern $instance_name \`.
- Restricts to matching macro instances.
- Important: don’t connect every pin called `vccd1` globally if some blocks share name.
- Instance scoping prevents accidental cross-block power merges.
- This is why macro hooks exist.

L61:
- `-pin_pattern $power_pin \`.
- Macro pin name.
- Must match macro LEF.
- If not, connection rule matches nothing.
- But we validated pin not empty, not correctness.

L62:
- `-power`.
- Marks connection as power.
- Important for powered netlist semantics.
- Also used in analysis.
- Classifies the net.

L63:
- Blank line.
- Visual separation between power and ground hook.
- No effect.
- Helps readability.
- Keeps pairs obvious.

L64:
- Second `add_global_connection \` (macro ground).
- Same structure.
- Connects macro ground pins.
- Uses `-ground`.
- Ensures macro has both supplies.

L65:
- `-net $ground_net \`.
- Ground net name.
- Could be global GND.
- Or separate analog ground.
- Naming must match PDN plan.

L66:
- `-inst_pattern $instance_name \`.
- Same instance scope.
- Applies to same macro instance(s).
- Consistent scoping avoids connecting other instances.
- Good practice.

L67:
- `-pin_pattern $ground_pin \`.
- Macro ground pin.
- Must match LEF.
- Connects correct pin.
- If macro has multiple grounds, hooks would need multiple entries.

L68:
- `-ground`.
- Ground classification.
- Helps tooling understand this is not a signal.
- Used by some checks.
- Required for PDN semantics.

L69:
- Close of hook loop body.
- End of one macro hook entry.
- Next hook entry repeats.
- Ensures each macro type/instance is handled.

L70:
- Close `foreach pdn_hook`.
- All macro hooks processed.
- Global connections registered.
- Next: end of macro block.

L71:
- Close macro `if` block.
- If macros grid disabled or no hooks defined, macro connections are skipped.
- That might be okay for cell-only designs.
- For SRAM macros, you usually want explicit hooks.

L72:
- Close `proc set_global_connections`.
- End of procedure definition.
- No execution happens just by defining.
- It runs only when called.

L73:
- End-of-file newline.
- No effect.
- But helps POSIX text file conventions.

L74:
- (If present) blank/EOF.
- No effect.
- The file ends.
- When sourced, Tcl returns to caller.

-------------------------------------------------------------------------------
Practical takeaway
-------------------------------------------------------------------------------

- Standard-cell global connections are a broad “connect power pins everywhere” rule.
- Macro hooks are a scoped “connect these specific macro pins to these nets” rule.
- Both are essential to keep power connectivity consistent when the netlist itself is not explicit about supplies.

(End of deep dive)
