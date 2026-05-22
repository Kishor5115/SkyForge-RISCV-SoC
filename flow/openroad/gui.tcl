source $::env(SCRIPTS_DIR)/common/io.tcl
read_all_lefs
if { [info exists ::env(DEF_FILE)] && [file exists $::env(DEF_FILE)] } {
    puts "\[INFO\] Reading DEF: $::env(DEF_FILE)"
    read_def $::env(DEF_FILE)
} else {
    puts "\[WARN\] DEF file not found or not specified."
}
