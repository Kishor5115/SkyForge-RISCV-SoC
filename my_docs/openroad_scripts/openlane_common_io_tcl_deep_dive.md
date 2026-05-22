# Deep Dive: flow/openroad/scripts/common/io.tcl

This document explains `flow/openroad/scripts/common/io.tcl` line by line.

What this file is:
- A shared OpenLane-style helper library for OpenROAD stage scripts.
- It defines utility procs for:
  - reading netlists (`read_netlist`),
  - reading liberty corners (`read_libs`),
  - reading databases/DEF (`read`),
  - writing views (`write`),
  - reading SPEFs (`read_spefs`),
  - and small helper functions.

Key design philosophy:
- “Flow state” is passed through environment variables (`::env(...)`).
- Stage scripts set `CURRENT_*` and `SAVE_*` variables.
- Then they call helpers like `read` / `write` to do consistent IO.

Important warning for this repo:
- This script expects OpenLane-style env vars like `CURRENT_ODB`, `MERGED_LEF`, `LIB_TYPICAL`, etc.
- If you want to execute OpenLane-derived stage scripts directly, you need a wrapper/driver that defines those variables.

-------------------------------------------------------------------------------
Line-by-line walkthrough
-------------------------------------------------------------------------------

L1: License header begins (comment).
L2: Comment line, still license.
L3: Comment line, license.
L4: Comment line, license.
L5: Comment line, license.
L6: Comment line, license.
L7: Comment line, license URL.
L8: Comment line, license.
L9: Comment line, license.
L10: Comment line, license.
L11: Comment line, license.
L12: Comment line, license.
L13: Blank/comment separation.

L14: `source $::env(SCRIPTS_DIR)/openroad/common/set_global_connections.tcl`.
- Pulls in the `set_global_connections` proc.
- The caller must set `SCRIPTS_DIR` such that this path resolves.
- This dependency is used later inside `write`.

L15: Blank line.

L16: `proc is_blackbox {file_path blackbox_wildcard} {` begins.
- Helper to detect “blackbox marker” lines in a Verilog file.
- Used when reading additional netlists under `read_netlist -all`.

L17: `set not_found [catch { exec bash -c "grep ..." }]`.
- Runs `grep` via a bash subshell.
- `catch` returns success/failure without crashing Tcl.
- If grep finds nothing, it exits non-zero, caught as an error.

L18: `return [expr !$not_found]`.
- Inverts the boolean: if grep did NOT error (found match), return true.
- So the proc returns 1 when wildcard exists in file.

L19: `}` ends `is_blackbox`.

L20: Blank line.

L21: `proc string_in_file {file_path substring} {` begins.
- Generic helper to find a substring inside a file.

L22: `set f [open $file_path r]`.
- Opens file read-only.

L23: `set data [read $f]`.
- Reads entire file content into memory.

L24: `close $f`.
- Closes the file handle.

L25: Blank line.

L26: `if { [string first $substring $data] != -1} {`.
- Searches for substring.

L27: `return 1`.
- Found.

L28: `}` closes if.

L29: `return 0`.
- Not found.

L30: `}` ends `string_in_file`.

L31: Blank line.

L32: `proc env_var_used {file var} {` begins.
- Convenience wrapper to check if a file references a specific env var.

L33: `return [string_in_file $file "\$::env($var)"]`.
- Looks for the literal token `$::env(VARNAME)`.
- Useful for conditional behavior based on whether scripts need env vars.

L34: `}` ends `env_var_used`.

L35: Blank line.

L36: `proc read_current_sdc {} {` begins.
- Reads constraints only if `CURRENT_SDC` exists.
- Also maps some synthesis env vars from higher-level constraints.

L37: `if { ![info exists ::env(CURRENT_SDC)]} {`.
- Guard: if no SDC, print info and return.

L38: `puts "[INFO] CURRENT_SDC not found..."`.

L39: `return`.

L40: `}` closes guard.

L41: Blank line.

L42: `set ::env(SYNTH_MAX_FANOUT) $::env(MAX_FANOUT_CONSTRAINT)`.
- Copies constraints into SYNTH_* variables.
- OpenLane uses the same values across tools.

L43: `set ::env(SYNTH_CAP_LOAD) $::env(OUTPUT_CAP_LOAD)`.
- Output load constraint.

L44: `if { [info exists ::env(MAX_TRANSITION_CONSTRAINT)] } {`.
- Optional transition constraint.

L45: `set ::env(SYNTH_MAX_TRAN) $::env(MAX_TRANSITION_CONSTRAINT)`.

L46: `}` closes.

L47: Blank line.

L48: `puts "Reading design constraints file at ..."`.

L49: `if {[catch {read_sdc $::env(CURRENT_SDC)} errmsg]} {`.
- Calls OpenROAD `read_sdc`.
- Uses `catch` to handle parsing errors.

L50: `puts stderr $errmsg`.

L51: `exit 1`.
- Hard-fail: constraints errors should stop the run.

L52: `}` closes.

L53: `}` ends `read_current_sdc`.

L54: Blank line.

L55: Blank line (double spacing before next proc).

L56: `proc read_netlist {args} {` begins.
- Reads a Verilog netlist defined by `CURRENT_NETLIST`.
- Supports flags `-powered` and `-all`.

L57: `sta::parse_key_args ...`.
- Uses OpenSTA argument parser.
- Declares accepted flags.

L58: `keys {}\`.
- No named keys.

L59: `flags {-powered -all}`.
- Two boolean flags.

L60: Blank line.

L61: `set netlist $::env(CURRENT_NETLIST)`.
- Default netlist path.

L62: `if { [info exists flags(-powered)] } {`.
- If caller wants powered netlist.

L63: `set netlist $::env(CURRENT_POWERED_NETLIST)`.

L64: `}`.

L65: Blank line.

L66: `puts "Reading netlist '$netlist'..."`.

L67: `if {[catch {read_verilog $netlist} errmsg]} {`.
- Reads Verilog, catch errors.

L68: `puts stderr $errmsg`.

L69: `exit 1`.

L70: `}`.

L71: Blank line.

L72: `if { [info exists flags(-all)] } {`.
- If `-all` is set, attempt to read additional verilog files.

L73: `set blackbox_wildcard {/// sta-blackbox}`.
- Marker string used by OpenLane to skip reading certain files.

L74: `if { [info exists ::env(VERILOG_FILES_BLACKBOX)] } {`.
- Optional list of extra netlists.

L75: `foreach verilog_file $::env(VERILOG_FILES_BLACKBOX) {`.

L76: `if { [is_blackbox $verilog_file $blackbox_wildcard] } {`.
- If marker found, skip.

L77: `puts "Found ... skipping..."`.

L78: `} elseif { [catch {read_verilog $verilog_file} err] } {`.
- Otherwise try to read it; if it fails, print helpful hint.

L79: `puts "Error while reading ..."`.

L80: `puts "Make sure ... gate-level netlist ..."`.

L81: `puts "You can add ... sta-blackbox ..."`.

L82: `puts $err`.

L83: `exit 1`.

L84: `}`.

L85: `}`.

L86: `}`.

L87: `}`.

L88: Blank line.

L89: `link_design $::env(DESIGN_NAME)`.
- Links the design after reading.
- Requires `DESIGN_NAME`.

L90: Blank line.

L91: `if { [info exists ::env(CURRENT_SDC)] } {`.

L92: `read_current_sdc`.

L93: `}`.

L94: Blank line.

L95: `}` ends `read_netlist`.

L96: Blank line.

L97: Blank line.

L98: `proc print_units {args} {` begins.
- Convenience to print OpenSTA unit scales.

L99: `foreach {unit} { ... } {`.
- Iterates over unit names.

L100: `set scale [sta::unit_scale $unit]`.

L101: `puts "Using ..."`.

L102: `}` closes loop.

L103: `}` ends proc.

L104: Blank line.

L105: `proc read_libs {args} {` begins.
- Reads Liberty files into STA corners.

L106: `sta::parse_key_args ...`.
- Accepts keys: -typical, -slowest, -fastest.
- Accepts flag: -no_extra.

L107: Validation: `-typical` required.

L108: If missing, print and exit.

L109: If -slowest provided, set `corner(Slowest)`.

L110: If -fastest provided, set `corner(Fastest)`.

L111: Set `corner(Typical)`.

L112: Print `define_corners ...`.

L113: `define_corners {*}[array name corner]`.
- Defines corners in OpenSTA.

L114: Loop over each corner.

L115: Loop over each lib in that corner.

L116: Print the read statement.

L117: `read_liberty -corner ...`.

L118: If not `-no_extra`, and `EXTRA_LIBS` exists, also read them.

L119: Finally `print_units`.

L120: End `read_libs`.

L121: Blank line.

L122: `proc read {args} {` begins.
- High-level reader for OpenROAD DB or DEF.

L123: Parse keys `-lib_fastest`, `-lib_typical`, `-lib_slowest`; flag `-no_spefs`.

L124: If `IO_READ_DEF` set, read merged lef and def.

L125: Else read OpenROAD database `CURRENT_ODB`.

L126: Build `read_libs_args`.

L127: Decide typical lib from key or env `LIB_TYPICAL`.

L128: Optional fastest/slowest.

L129: Call `read_libs {*}$read_libs_args`.

L130: If SDC exists, call `read_current_sdc`.

L131: If not `-no_spefs` and `CURRENT_SPEF` exists, read it.

L132: End `read`.

L133: Blank line.

L134: Blank line.

L135: `proc write {args} {` begins.
- Writes out views based on SAVE_* env vars.

L136: Comment: describes SAVE_* convention.

L137: Parse flag `-no_global_connect`.

L138: If VDD_NET exists and not disabled, call `set_global_connections`.

L139: If SAVE_ODB exists: write_db.

L140: Else warn.

L141: If SAVE_NETLIST exists: write_verilog.

L142: If SAVE_POWERED_NETLIST exists: write_verilog -include_pwr_gnd.

L143: If SAVE_DEF exists: write_def.

L144: If SAVE_SDC exists: write_sdc.

L145: If SAVE_SPEF exists: write_spef.

L146: If SAVE_GUIDE exists: write_guides.

L147: If SAVE_SDF exists: write SDF; per-corner if multiple.

L148: If SAVE_LIB exists and STA_PRE_CTS false: write timing model; per-corner if needed.

L149: End `write`.

L150: Blank line.

L151: Blank line.

L152: `proc read_spefs {} {` begins.
- Reads SPEF for all corners; also supports extra macro SPEFs.

L153: `set corners [sta::corners]`.

L154: If CURRENT_SPEF exists, read it for each corner.

L155: If EXTRA_SPEFS exists, parse tuples: module_name + min/nom/max spefs.

L156: For each tuple, try to find matching cell instance(s) by ref_name.

L157: If matched, read spef with `-path` for that instance.

L158: Select file based on PROCESS_CORNER (nom/min/max).

L159: If no match, error and exit.

L160: End `read_spefs`.

L161: End of file.

-------------------------------------------------------------------------------
Extra in-depth notes (why this helper is structured this way)
-------------------------------------------------------------------------------

1) Why environment variables?
- OpenLane runs each stage as a separate tool invocation.
- Env vars are the simplest “contract” between stages.
- This makes scripts reusable across designs.

2) Why `CURRENT_*` and `SAVE_*`?
- `CURRENT_*` describes the *input* to the stage.
- `SAVE_*` describes which *outputs* to write.
- The `write` proc is essentially a router: it writes only what’s requested.

3) Where do `sta::` procs come from?
- OpenROAD embeds OpenSTA.
- `sta::parse_key_args` and `sta::corners` are OpenSTA APIs.
- That’s why these helpers can parse args and handle multi-corner behavior.

4) Why is `read_netlist -all` dangerous?
- It can accidentally read RTL (causing weird behavior).
- The `/// sta-blackbox` marker is a safety valve.
- If you see errors here, it often means you fed a non-gate-level file.

(End of deep dive)
