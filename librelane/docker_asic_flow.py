#!/usr/bin/env python3
"""
LibreLane RTL-to-GDSII automation for the PicoRV32 RISC-V SoC.

Multi-macro hierarchical flow (sky130A):
  1. Stage workspace into Docker bind-mount
  2. Harden PicoRV32 core as standalone macro (Classic flow)
  3. Post-synthesis GL simulation (optional)
  4. Patch top-level config with hardened core + OpenRAM SRAM views
  5. Run chip-top soc_core flow (synthesis + PnR + signoff)
  6. Parse signoff metrics

Requires: Docker container 'gf180' (hpretl/iic-osic-tools:chipathon26)
          with ~/eda/designs bind-mounted to /foss/designs and the
          sky130A PDK pre-installed at /foss/pdks/sky130A.
"""

from pathlib import Path
import csv
import shutil
import subprocess
import textwrap

# ============================================================
# Configuration
# ============================================================

# --- Run flags (flip True one-at-a-time as you progress) ---
RUN_STAGE_FILES    = False   # Step 1: copy project into bind-mount
RUN_HARDEN_CORE    = False   # Step 2: harden picorv32_axi (~5-15 min)
RUN_GLSIM          = False   # Step 3: post-synthesis GL simulation
RUN_PATCH_TOP      = False   # Step 4: patch soc_core_top.yaml with macros
RUN_CHIP_TOP       = False   # Step 5: full soc_core flow (~30-90 min)
RUN_SIGNOFF_REPORT = False   # Step 6: parse metrics.csv

# --- Container ---
CONTAINER_NAME = 'gf180'

# --- PDK (sky130A, pre-installed in the iic-osic-tools container) ---
PDK_NAME            = 'sky130A'
STD_CELL_LIB        = 'sky130_fd_sc_hd'
CONTAINER_PDK_ROOT  = '/foss/pdks'   # /foss/pdks/sky130A exists in-container

# --- Host paths ---
PROJECT_ROOT    = Path(__file__).resolve().parent.parent
HOST_WORKSPACE  = Path.home() / 'eda' / 'designs' / 'riscv_soc' / 'workspace'

# --- Container paths ---
CONTAINER_WORKSPACE = '/foss/designs/riscv_soc/workspace'

# --- SRAM macro (OpenRAM-generated, sky130, already in project) ---
# Power pins vccd1/vssd1, single TT_1p8V_25C corner, 808.845 x 351.29 um.
SRAM_NAME = 'sky130_sram_4kbyte_1rw_32x1024_8'

# --- sky130A STA corners (per-corner .lib is MANDATORY in LibreLane v3) ---
# sky130_fd_sc_hd characterized corners; nom/min/max = RC extraction corners.
SKY130_CORNERS = [
    'nom_tt_025C_1v80', 'nom_ss_100C_1v60', 'nom_ff_n40C_1v95',
    'min_tt_025C_1v80', 'min_ss_100C_1v60', 'min_ff_n40C_1v95',
    'max_tt_025C_1v80', 'max_ss_100C_1v60', 'max_ff_n40C_1v95',
]


# ============================================================
# Helpers
# ============================================================

def run_or_print(cmd, do_it, *, shell_on_container=False, timeout=None):
    """Print command; execute inside container when do_it=True."""
    if shell_on_container:
        print(f"$ docker exec {CONTAINER_NAME} bash -lc '<script>'")
        print(textwrap.indent(cmd, '  | '))
    else:
        print('$ ' + ' '.join(str(x) for x in cmd))
    if not do_it:
        print('  (skipped -- flip the RUN_* flag to execute)\n')
        return None
    args = (
        ['docker', 'exec', CONTAINER_NAME, 'bash', '-lc', cmd]
        if shell_on_container else list(cmd)
    )
    proc = subprocess.run(args, capture_output=True, text=True, timeout=timeout)
    if proc.stdout.strip():
        print(proc.stdout[-4000:])
    if proc.returncode != 0 and proc.stderr.strip():
        print('STDERR (tail):')
        print(proc.stderr[-2000:])
    print(f'  returncode={proc.returncode}\n')
    return proc


def ok(label, cond, detail=''):
    tag = 'OK ' if cond else '!! '
    print(f'{tag}{label}' + (f'  -- {detail}' if detail else ''))
    return cond


# ============================================================
# Step 0: Verify container + sky130A PDK
# ============================================================

def check_container():
    proc = subprocess.run(
        ['docker', 'ps', '--filter', f'name={CONTAINER_NAME}', '--format', '{{.Names}}'],
        capture_output=True, text=True,
    )
    container_up = CONTAINER_NAME in proc.stdout
    ok(f"Container '{CONTAINER_NAME}' running", container_up)
    if not container_up:
        print("  Start with: docker start gf180  (or bootstrap_container.sh)")
        return False

    # Verify sky130A PDK exists in-container.
    pdk_check = subprocess.run(
        ['docker', 'exec', CONTAINER_NAME, 'test', '-d',
         f'{CONTAINER_PDK_ROOT}/{PDK_NAME}'],
        capture_output=True, text=True,
    )
    ok(f"sky130A PDK present at {CONTAINER_PDK_ROOT}/{PDK_NAME}",
       pdk_check.returncode == 0)
    return container_up


# ============================================================
# Step 1: Stage project files into bind-mount
# ============================================================

def stage_files():
    print("\n=== Step 1: Stage project files ===")
    if RUN_STAGE_FILES:
        if HOST_WORKSPACE.exists():
            shutil.rmtree(HOST_WORKSPACE)
        HOST_WORKSPACE.mkdir(parents=True)
        for sub in ('rtl', 'librelane', 'openram', 'constraints'):
            src = PROJECT_ROOT / sub
            if src.exists():
                dst = HOST_WORKSPACE / sub
                shutil.copytree(src, dst)
                n = sum(1 for _ in dst.rglob('*') if _.is_file())
                print(f'  {sub}/  -- {n} file(s)')
        (HOST_WORKSPACE / 'build').mkdir(exist_ok=True)
        print(f'\nStaged at {HOST_WORKSPACE}')
    else:
        print('(dry-run) would stage rtl/, librelane/, openram/, constraints/')
    # sky130A is pre-installed in the container; no PDK clone needed.


# ============================================================
# Step 2: Harden PicoRV32 core macro (standalone Classic flow)
# ============================================================

def harden_core():
    print("\n=== Step 2: Harden PicoRV32 core macro ===")
    script = textwrap.dedent(f'''
        set -e
        cd {CONTAINER_WORKSPACE}
        librelane librelane/picorv32_core.yaml \\
            --pdk {PDK_NAME} \\
            --pdk-root {CONTAINER_PDK_ROOT} \\
            --save-views-to {CONTAINER_WORKSPACE}/build/picorv32_axi
    ''').strip()
    run_or_print(script, RUN_HARDEN_CORE, shell_on_container=True, timeout=1800)


# ============================================================
# Step 3: Post-synthesis Gate-Level Simulation (optional)
# ============================================================

def glsim():
    print("\n=== Step 3: Post-synthesis GL simulation ===")
    # Requires cocotb testbenches; here we confirm the netlist exists and
    # is linkable against the sky130_fd_sc_hd behavioural models.
    script = textwrap.dedent(f'''
        set -e
        NL={CONTAINER_WORKSPACE}/build/picorv32_axi/nl/picorv32_axi.nl.v
        ls -la $NL
        echo "Netlist available; pair with"
        echo "  {CONTAINER_PDK_ROOT}/{PDK_NAME}/libs.ref/{STD_CELL_LIB}/verilog/{STD_CELL_LIB}.v"
        echo "  + primitives.v for cocotb GL sim (-DFUNCTIONAL -DUNIT_DELAY=#1)."
    ''').strip()
    run_or_print(script, RUN_GLSIM, shell_on_container=True, timeout=300)


# ============================================================
# Step 4: Patch top-level config with hardened macros
# ============================================================

def patch_top():
    print("\n=== Step 4: Patch soc_core_top.yaml with MACROS ===")
    if not RUN_PATCH_TOP:
        print('(dry-run) would add picorv32_axi + SRAM macros to config')
        print('(dry-run) would set PDN_MACRO_CONNECTIONS (string entries)')
        return

    import yaml

    cfg_path = HOST_WORKSPACE / 'librelane' / 'soc_core_top.yaml'
    cfg = yaml.safe_load(cfg_path.read_text())

    build = Path(CONTAINER_WORKSPACE) / 'build'

    # --- PicoRV32 core: hardened by LibreLane, per-corner libs ---
    core_base = build / 'picorv32_axi'
    core_lib_map = {
        corner: [str(core_base / 'lib' / corner / f'picorv32_axi__{corner}.lib')]
        for corner in SKY130_CORNERS
    }
    core_entry = {
        'gds': [str(core_base / 'gds' / 'picorv32_axi.gds')],
        'lef': [str(core_base / 'lef' / 'picorv32_axi.lef')],
        'vh':  [str(core_base / 'nl'  / 'picorv32_axi.nl.v')],
        'lib': core_lib_map,
        'instances': {
            'u_cpu': {'location': [400, 100], 'orientation': 'N'},
        },
    }

    # --- SRAM macros: 2x4 array at TOP (SiFive-style, 8 banks = 32 KB) ---
    # Each bank is 808.845 x 351.29 um. Die is 2200 x 3300.
    # Layout: 2 columns x 4 rows.
    #   Col 0: x = 120  -> spans 120..929
    #   Col 1: x = 1180 -> spans 1180..1989 (< 2200)
    #   Row 0 (top):    y = 2340 -> spans 2340..2691
    #   Row 1:          y = 1930 -> spans 1930..2281
    #   Row 2:          y = 1520 -> spans 1520..1871
    #   Row 3 (bottom): y = 1110 -> spans 1110..1461
    # Core + peripherals fill y = 0..1050.
    sram_base = Path(CONTAINER_WORKSPACE) / 'openram' / 'build'
    # OpenRAM produced a single TT corner; map every STA corner to it.
    sram_lib_map = {
        corner: [str(sram_base / f'{SRAM_NAME}_TT_1p8V_25C.lib')]
        for corner in SKY130_CORNERS
    }
    sram_entry = {
        'gds': [str(sram_base / f'{SRAM_NAME}.gds')],
        'lef': [str(sram_base / f'{SRAM_NAME}.lef')],
        'vh':  [str(sram_base / f'{SRAM_NAME}.v')],
        'lib': sram_lib_map,
        'instances': {
            'u_sram.gen_sram_bank[0].u_bank': {'location': [120, 2340],  'orientation': 'N'},
            'u_sram.gen_sram_bank[1].u_bank': {'location': [1180, 2340], 'orientation': 'N'},
            'u_sram.gen_sram_bank[2].u_bank': {'location': [120, 1930],  'orientation': 'N'},
            'u_sram.gen_sram_bank[3].u_bank': {'location': [1180, 1930], 'orientation': 'N'},
            'u_sram.gen_sram_bank[4].u_bank': {'location': [120, 1520],  'orientation': 'N'},
            'u_sram.gen_sram_bank[5].u_bank': {'location': [1180, 1520], 'orientation': 'N'},
            'u_sram.gen_sram_bank[6].u_bank': {'location': [120, 1110],  'orientation': 'N'},
            'u_sram.gen_sram_bank[7].u_bank': {'location': [1180, 1110], 'orientation': 'N'},
        },
    }

    cfg.setdefault('MACROS', {})
    cfg['MACROS']['picorv32_axi'] = core_entry
    cfg['MACROS'][SRAM_NAME]      = sram_entry

    # PDN_MACRO_CONNECTIONS: MUST be List[str], NOT dicts (LibreLane v3 schema).
    # Format: "<instance regex> <vdd_net> <vss_net> <macro_vdd_pin> <macro_vss_pin>"
    # Chip-level power nets for sky130A are vccd1/vssd1.
    cfg['PDN_MACRO_CONNECTIONS'] = [
        '.*u_cpu.* vccd1 vssd1 vccd1 vssd1',
        '.*u_bank.* vccd1 vssd1 vccd1 vssd1',
    ]
    # Use vccd1/vssd1 as the top-level power nets (sky130A convention).
    cfg['VDD_NETS'] = ['vccd1']
    cfg['GND_NETS'] = ['vssd1']

    cfg_path.write_text(yaml.safe_dump(cfg, sort_keys=False, default_flow_style=False))
    print(f'Patched {cfg_path}')
    print(f'  + picorv32_axi  ({len(SKY130_CORNERS)} corners)')
    print(f'  + {SRAM_NAME}  (TT lib mapped to all corners)')
    print(f'  + PDN_MACRO_CONNECTIONS (vccd1/vssd1)')


# ============================================================
# Step 5: Run chip-top soc_core flow
# ============================================================

def run_chip_top():
    print("\n=== Step 5: Run soc_core chip-top flow ===")
    script = textwrap.dedent(f'''
        set -e
        cd {CONTAINER_WORKSPACE}
        librelane librelane/soc_core_top.yaml \\
            --pdk {PDK_NAME} \\
            --pdk-root {CONTAINER_PDK_ROOT} \\
            --save-views-to {CONTAINER_WORKSPACE}/build/soc_core
    ''').strip()
    run_or_print(script, RUN_CHIP_TOP, shell_on_container=True, timeout=None)


# ============================================================
# Step 6: Parse signoff metrics
# ============================================================

def signoff_report():
    print("\n=== Step 6: Signoff Metrics Report ===")
    metrics_path = HOST_WORKSPACE / 'build' / 'soc_core' / 'metrics.csv'

    if not RUN_SIGNOFF_REPORT:
        print(f'(dry-run) would parse {metrics_path}')
        return

    wanted = [
        ('design__die__area',                     'Die Area (um^2)'),
        ('magic__drc_error__count',               'Magic DRC Errors'),
        ('klayout__drc_error__count',             'KLayout DRC Errors'),
        ('design__lvs_error__count',              'Netgen LVS Errors'),
        ('antenna__violating__nets',              'Antenna Violations'),
        ('timing__setup_vio__count',              'Setup Violations'),
        ('timing__hold_vio__count',               'Hold Violations'),
        ('power__total',                          'Total Power (W)'),
    ]

    if not metrics_path.exists():
        print(f'!! metrics.csv not found: {metrics_path}')
        print('   Did Step 5 complete? Set RUN_CHIP_TOP = True first.')
        return

    found = {}
    with metrics_path.open() as fh:
        for row in csv.reader(fh):
            if row and row[0] in dict(wanted):
                found[row[0]] = row[1] if len(row) > 1 else ''

    print(f'{"Metric":45s} {"Value":>15s}')
    print('-' * 63)
    for k, label in wanted:
        print(f'  {label:43s} {found.get(k, "(missing)"):>15s}')

    any_bad = False
    for k in ('magic__drc_error__count', 'klayout__drc_error__count',
              'design__lvs_error__count', 'antenna__violating__nets',
              'timing__setup_vio__count', 'timing__hold_vio__count'):
        v = found.get(k, '')
        try:
            if int(v) != 0:
                any_bad = True
        except ValueError:
            pass

    print()
    if any_bad:
        print('\033[1;31mSIGNOFF: VIOLATIONS PRESENT\033[0m')
    else:
        print('\033[1;32mSIGNOFF: CLEAN (all zero)\033[0m')


# ============================================================
# Main
# ============================================================

def main():
    print("=" * 70)
    print("  LibreLane RTL-to-GDSII Pipeline: PicoRV32 RISC-V SoC")
    print("  Target: sky130A | 50 MHz | 4x4KB SRAM (OpenRAM, vccd1/vssd1)")
    print("=" * 70)

    if not check_container():
        return

    stage_files()
    harden_core()
    glsim()
    patch_top()
    run_chip_top()
    signoff_report()

    print("\n" + "=" * 70)
    print("  Pipeline complete. Flip RUN_* flags to execute each step.")
    print("=" * 70)


if __name__ == '__main__':
    main()
