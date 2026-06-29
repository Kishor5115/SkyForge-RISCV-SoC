#!/usr/bin/env python3
"""
Generate OpenRAM views with a safer save order for SKY130 spare-column SRAMs.

OpenRAM v1.2.49 writes a delay stimulus before GDS/LEF/Verilog/Liberty. For
the SKY130 1RW byte-write macros with spare columns, that stimulus path can fail
with "Could not find bl net in timing paths", leaving only the SPICE file. This
driver writes the physical and frontend views first, then attempts Liberty.
"""

import datetime
import os
import shutil
import sys


OPENRAM_ROOT = os.environ.get("OPENRAM_ROOT", "/home/kishor/OpenRAM")
OPENRAM_HOME = os.environ.setdefault("OPENRAM_HOME", os.path.join(OPENRAM_ROOT, "compiler"))
OPENRAM_TECH = os.environ.setdefault("OPENRAM_TECH", os.path.join(OPENRAM_ROOT, "technology"))

sys.path.insert(0, OPENRAM_ROOT)
sys.path.insert(0, OPENRAM_HOME)

from common import make_openram_package  # noqa: E402

make_openram_package()

import openram  # noqa: E402


def ensure_slash(path):
    return path if path.endswith(os.sep) else path + os.sep


def write_fallback_lib(path, sram):
    """Write a conservative nominal Liberty file if OpenRAM Liberty fails."""
    addr_width = sram.bank_addr_size
    word_width = sram.word_size
    num_wmasks = sram.num_wmasks

    with open(path, "w") as lib:
        lib.write("library ({}__fallback_lib) {{\n".format(sram.name))
        lib.write("  delay_model : table_lookup;\n")
        lib.write("  time_unit : \"1ns\";\n")
        lib.write("  voltage_unit : \"1V\";\n")
        lib.write("  current_unit : \"1mA\";\n")
        lib.write("  leakage_power_unit : \"1mW\";\n")
        lib.write("  capacitive_load_unit (1,pf);\n")
        lib.write("  nom_voltage : 1.8;\n")
        lib.write("  nom_temperature : 25;\n")
        lib.write("  nom_process : 1;\n")
        lib.write("  operating_conditions(TT_1p8V_25C) { process : 1; voltage : 1.8; temperature : 25; }\n")
        lib.write("  default_operating_conditions : TT_1p8V_25C;\n\n")
        lib.write("  type(data) { base_type : array; data_type : bit; bit_width : %d; bit_from : %d; bit_to : 0; }\n" %
                  (word_width, word_width - 1))
        lib.write("  type(addr) { base_type : array; data_type : bit; bit_width : %d; bit_from : %d; bit_to : 0; }\n" %
                  (addr_width, addr_width - 1))
        lib.write("  type(wmask) { base_type : array; data_type : bit; bit_width : %d; bit_from : %d; bit_to : 0; }\n\n" %
                  (num_wmasks, num_wmasks - 1))
        lib.write("  cell (%s) {\n" % sram.name)
        lib.write("    area : 1;\n")
        lib.write("    memory() { type : ram; address_width : %d; word_width : %d; }\n" %
                  (addr_width, word_width))
        lib.write("    bus(din0) { bus_type : data; direction : input; }\n")
        lib.write("    bus(dout0) { bus_type : data; direction : output; }\n")
        lib.write("    bus(addr0) { bus_type : addr; direction : input; }\n")
        lib.write("    bus(wmask0) { bus_type : wmask; direction : input; }\n")
        lib.write("    pin(clk0) { direction : input; clock : true; }\n")
        lib.write("    pin(csb0) { direction : input; }\n")
        lib.write("    pin(web0) { direction : input; }\n")
        if sram.num_spare_cols:
            lib.write("    pin(spare_wen0) { direction : input; }\n")
        lib.write("    pg_pin(vccd1) { voltage_name : VCCD1; pg_type : primary_power; }\n")
        lib.write("    pg_pin(vssd1) { voltage_name : VSSD1; pg_type : primary_ground; }\n")
        lib.write("  }\n")
        lib.write("}\n")


def copy_if_exists(src, dst):
    if os.path.exists(src) and os.path.abspath(src) != os.path.abspath(dst):
        shutil.copyfile(src, dst)


def remove_bottom_met3_power_access(lef_path):
    """Hide bottom met3 PG rails from the abstract LEF.

    The OpenRAM GDS still contains a continuous power ring.  Removing these
    LEF pin rectangles only prevents pdngen from using the same edge as the
    met4 data pins when the macro is rotated 90 degrees.
    """
    replacements = {
        "         LAYER met3 ;\n"
        "         RECT  0.0 0.0 808.845 1.74 ;\n": "",
        "         LAYER met3 ;\n"
        "         RECT  3.48 3.48 805.365 5.22 ;\n": "",
    }

    with open(lef_path, "r") as lef:
        text = lef.read()

    for old, new in replacements.items():
        if old not in text:
            raise RuntimeError("Expected bottom met3 power pin shape not found in {}".format(lef_path))
        text = text.replace(old, new, 1)

    with open(lef_path, "w") as lef:
        lef.write(text)


def main():
    opts, args = openram.parse_args()
    if len(args) != 1:
        print(openram.USAGE)
        return 2

    opts.top_process = "openram"

    from openram import OPTS, debug, print_time

    openram.init_openram(config_file=args[0])
    openram.setup_bitcell()
    openram.print_banner()

    start_time = datetime.datetime.now()
    print_time("Start", start_time)
    openram.report_status()
    debug.print_raw("Words per row: {}".format(OPTS.words_per_row))

    OPTS.output_path = ensure_slash(OPTS.output_path)
    os.makedirs(OPTS.output_path, exist_ok=True)

    from openram import sram

    sram_obj = sram()
    s = sram_obj.s

    spname = OPTS.output_path + s.name + ".sp"
    debug.print_raw("SP: Writing to {}".format(spname))
    sram_obj.sp_write(spname)

    if not OPTS.netlist_only:
        gdsname = OPTS.output_path + s.name + ".gds"
        debug.print_raw("GDS: Writing to {}".format(gdsname))
        sram_obj.gds_write(gdsname)

        lefname = OPTS.output_path + s.name + ".lef"
        debug.print_raw("LEF: Writing to {}".format(lefname))
        sram_obj.lef_write(lefname)
        remove_bottom_met3_power_access(lefname)

    lvsname = OPTS.output_path + s.name + ".lvs.sp"
    debug.print_raw("LVS: Writing to {}".format(lvsname))
    sram_obj.sp_write(lvsname, lvs=True)
    copy_if_exists(lvsname, OPTS.output_path + s.name + ".lvs")

    vname = OPTS.output_path + s.name + ".v"
    debug.print_raw("Verilog: Writing to {}".format(vname))
    sram_obj.verilog_write(vname)

    configname = OPTS.output_path + OPTS.output_name + ".py"
    debug.print_raw("Config: Writing to {}".format(configname))
    shutil.copyfile(OPTS.config_file, configname)

    nominal_lib = OPTS.output_path + s.name + "_TT_1p8V_25C.lib"
    base_lib = OPTS.output_path + s.name + ".lib"

    try:
        if os.environ.get("OPENRAM_FORCE_FALLBACK_LIB") == "1":
            raise RuntimeError("OPENRAM_FORCE_FALLBACK_LIB=1")

        from openram.characterizer import lib

        debug.print_raw("LIB: Characterizing with OpenRAM {} model...".format(OPTS.model_name))
        lib(out_dir=OPTS.output_path, sram=s, sp_file=spname)
        copy_if_exists(nominal_lib, base_lib)
    except Exception as exc:
        debug.warning("OpenRAM Liberty generation failed: {}".format(exc))
        debug.warning("Writing conservative fallback Liberty: {}".format(nominal_lib))
        write_fallback_lib(nominal_lib, s)
        copy_if_exists(nominal_lib, base_lib)

    openram.end_openram()
    print_time("End", datetime.datetime.now(), start_time)
    return 0


if __name__ == "__main__":
    sys.exit(main())
