#!/usr/bin/env python3
"""
LibreLane RTL-to-GDSII automation for the PicoRV32 RISC-V SoC.

Multi-macro hierarchical flow (sky130A):
  1.  Stage workspace into Docker bind-mount
  2.  Harden PicoRV32 core as standalone macro (Classic flow)
  3.  Post-synthesis GL simulation (optional)
  4.  Patch top-level config with hardened core + OpenRAM SRAM views
  ── soc_core (3 stages) ──────────────────────────────────────────
  5a. soc_core Stage A: Synthesis → DetailedRouting  (run-tag RUN_SC_A)
  5b. soc_core Stage B: post-DRT → KLayout.Render    (run-tag RUN_SC_B)
  5c. soc_core Stage C: LEF/SPICE/DRC/LVS/signoff    (run-tag RUN_SC_C)
  ── padring (3 stages) ───────────────────────────────────────────
  6a. padring Stage A: Synthesis → DetailedRouting    (run-tag RUN_PR_A)
  6b. padring Stage B: post-DRT → KLayout.Render      (run-tag RUN_PR_B)
  6c. padring Stage C: LEF/SPICE/DRC/LVS/signoff      (run-tag RUN_PR_C)
  ─────────────────────────────────────────────────────────────────
  7.  Parse signoff metrics from the padring (final chip) run

Requires: Docker container 'riscv-soc' (hpretl/iic-osic-tools:chipathon26)
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
RUN_STAGE_FILES  = False   # Step 1: copy project into bind-mount
RUN_HARDEN_CORE  = False   # Step 2: harden picorv32_axi (~5-15 min)
RUN_GLSIM        = False   # Step 3: post-synthesis GL simulation
RUN_PATCH_TOP    = False   # Step 4: patch soc_core_top.yaml with macros

RUN_SC_A         = False   # Step 5a: soc_core  synth → detailed routing
RUN_SC_B         = False   # Step 5b: soc_core  post-DRT → streamout
RUN_SC_C         = False   # Step 5c: soc_core  LEF/SPICE/DRC/LVS/STA views

RUN_PR_A         = False   # Step 6a: padring   synth → detailed routing
RUN_PR_B         = False   # Step 6b: padring   post-DRT → streamout
RUN_PR_C         = False   # Step 6c: padring   LEF/SPICE/DRC/LVS/STA views

RUN_SIGNOFF      = False   # Step 7: parse padring metrics.csv

# --- Container ---
# Named 'riscv-soc' in this project (was stale 'gf180').
CONTAINER_NAME = 'riscv-soc'

# --- PDK ---
PDK_NAME            = 'sky130A'
STD_CELL_LIB        = 'sky130_fd_sc_hd'
CONTAINER_PDK_ROOT  = '/foss/pdks'

# --- Host paths ---
PROJECT_ROOT    = Path(__file__).resolve().parent.parent
HOST_WORKSPACE  = Path.home() / 'eda' / 'designs' / 'riscv_soc' / 'workspace'

# --- Container paths ---
CONTAINER_WORKSPACE = '/foss/designs/riscv_soc/workspace'

# --- OpenRAM SRAM macro ---
SRAM_NAME = 'sky130_sram_4kbyte_1rw_32x1024_8'

# --- sky130A STA corners (per-corner .lib mandatory in LibreLane v3) ---
SKY130_CORNERS = [
    'nom_tt_025C_1v80', 'nom_ss_100C_1v60', 'nom_ff_n40C_1v95',
    'min_tt_025C_1v80', 'min_ss_100C_1v60', 'min_ff_n40C_1v95',
    'max_tt_025C_1v80', 'max_ss_100C_1v60', 'max_ff_n40C_1v95',
]

# ── LibreLane Classic flow stage split-points ─────────────────────────────
# Stage A: first step → OpenROAD.DetailedRouting
# Stage B: Odb.RemoveRoutingObstructions → KLayout.Render
# Stage C: Magic.WriteLEF → Misc.ReportManufacturability  (saves final views)
STEP_END_A   = 'OpenROAD.DetailedRouting'
STEP_START_B = 'Odb.RemoveRoutingObstructions'
STEP_END_B   = 'KLayout.Render'
STEP_START_C = 'Magic.WriteLEF'


# ============================================================
# Helpers
# ============================================================

def run_or_print(cmd, do_it, *, shell_on_container=False, timeout=None):
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


def _librelane_stage(yaml_rel, run_tag, save_to, *,
                     from_step=None, to_step=None, run_flag):
    """Build and optionally execute a single LibreLane stage command."""
    flags = f'--run-tag {run_tag}'
    if from_step:
        flags += f' -F {from_step}'
    if to_step:
        flags += f' -T {to_step}'
    if save_to:
        flags += f' --save-views-to {save_to}'
    script = textwrap.dedent(f'''
        set -e
        cd {CONTAINER_WORKSPACE}
        librelane {yaml_rel} \\
            --pdk {PDK_NAME} \\
            --pdk-root {CONTAINER_PDK_ROOT} \\
            {flags}
    ''').strip()
    run_or_print(script, run_flag, shell_on_container=True, timeout=None)


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
        print(f"  Start with: docker start {CONTAINER_NAME}")
        return False
    pdk_check = subprocess.run(
        ['docker', 'exec', CONTAINER_NAME, 'test', '-d',
         f'{CONTAINER_PDK_ROOT}/{PDK_NAME}'],
        capture_output=True, text=True,
    )
    ok(f"sky130A PDK at {CONTAINER_PDK_ROOT}/{PDK_NAME}",
       pdk_check.returncode == 0)
    return container_up


# ============================================================
# Step 1: Stage project files
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


# ============================================================
# Step 2: Harden PicoRV32 core macro
# ============================================================

def harden_core():
    print("\n=== Step 2: Harden PicoRV32 core macro ===")
    script = textwrap.dedent(f'''
        set -e
        cd {CONTAINER_WORKSPACE}
        librelane librelane/picorv32_core.yaml \\
            --pdk {PDK_NAME} \\
            --pdk-root {CONTAINER_PDK_ROOT} \\
            --run-tag RUN_PICO_100 \\
            --save-views-to {CONTAINER_WORKSPACE}/build/picorv32_axi
    ''').strip()
    run_or_print(script, RUN_HARDEN_CORE, shell_on_container=True, timeout=1800)


# ============================================================
# Step 3: Post-synthesis GL simulation (optional)
# ============================================================

def glsim():
    print("\n=== Step 3: Post-synthesis GL simulation ===")
    script = textwrap.dedent(f'''
        set -e
        NL={CONTAINER_WORKSPACE}/build/picorv32_axi/nl/picorv32_axi.nl.v
        ls -la $NL
        echo "Pair with {CONTAINER_PDK_ROOT}/{PDK_NAME}/libs.ref/{STD_CELL_LIB}/verilog/"
        echo "for cocotb GL sim (-DFUNCTIONAL -DUNIT_DELAY=#1)."
    ''').strip()
    run_or_print(script, RUN_GLSIM, shell_on_container=True, timeout=300)


# ============================================================
# Step 4: Patch soc_core_top.yaml with hardened macros
# ============================================================

def patch_top():
    print("\n=== Step 4: Patch soc_core_top.yaml with file paths (paths only) ===")
    if not RUN_PATCH_TOP:
        print('(dry-run) would fill gds/lef/vh/lib paths in MACROS block')
        print('  NOTE: macro placement (instances.location) lives in soc_core_top.yaml')
        print('        Edit that file directly to move macros — never edit here.')
        return

    import yaml

    # Source: the canonical project YAML (placement lives here permanently)
    src_yaml = PROJECT_ROOT / 'librelane' / 'soc_core_top.yaml'
    # Destination: workspace copy that LibreLane actually reads
    dst_yaml = HOST_WORKSPACE / 'librelane' / 'soc_core_top.yaml'

    cfg = yaml.safe_load(src_yaml.read_text())

    build = Path(CONTAINER_WORKSPACE) / 'build'
    core_base = build / 'picorv32_axi'
    sram_base  = Path(CONTAINER_WORKSPACE) / 'openram' / 'build'

    # ── Helper: lib dict mapping all corners to a single .lib file ──────────
    def all_corners_lib(lib_path: str) -> dict:
        return {c: [lib_path] for c in SKY130_CORNERS}

    # ── Patch picorv32_axi paths only — keep instances untouched ────────────
    core = cfg['MACROS']['picorv32_axi']
    core['gds'] = [str(core_base / 'gds' / 'picorv32_axi.gds')]
    core['lef'] = [str(core_base / 'lef' / 'picorv32_axi.lef')]
    core['vh']  = [str(core_base / 'nl'  / 'picorv32_axi.nl.v')]
    core['lib'] = all_corners_lib(
        str(core_base / 'lib/nom_tt_025C_1v80/picorv32_axi__nom_tt_025C_1v80.lib')
    )

    # ── Patch SRAM paths only — keep instances untouched ────────────────────
    sram = cfg['MACROS'][SRAM_NAME]
    sram['gds'] = [str(sram_base / f'{SRAM_NAME}.gds')]
    sram['lef'] = [str(sram_base / f'{SRAM_NAME}.lef')]
    sram['vh']  = [str(sram_base / f'{SRAM_NAME}.v')]
    sram['lib'] = all_corners_lib(
        str(sram_base / f'{SRAM_NAME}_TT_1p8V_25C.lib')
    )

    # ── Verify no __PATCH_*__ placeholders remain (safety check) ────────────
    raw = yaml.safe_dump(cfg, sort_keys=False, default_flow_style=False)
    remaining = [line for line in raw.splitlines() if '__PATCH_' in line]
    if remaining:
        print('ERROR: unreplaced placeholders in patched YAML:')
        for l in remaining:
            print(f'  {l}')
        raise RuntimeError('patch_top: placeholders not fully resolved')

    dst_yaml.write_text(raw)
    print(f'Patched {dst_yaml}')
    print(f'  picorv32_axi  paths filled  ({len(SKY130_CORNERS)} corners)')
    print(f'  {SRAM_NAME}  paths filled  (TT lib → all corners)')
    print(f'  Macro placement (instances) preserved from {src_yaml.name}')


# ============================================================
# Steps 5a-5c: soc_core chip-top (3 stages)
# ============================================================

_SC_YAML    = 'librelane/soc_core_top.yaml'
_SC_SAVE    = f'{CONTAINER_WORKSPACE}/build/soc_core'

def run_sc_a():
    """Stage A: Verilator.Lint → OpenROAD.DetailedRouting  (synthesis + PnR)"""
    print("\n=== Step 5a: soc_core — Synthesis → DetailedRouting ===")
    _librelane_stage(_SC_YAML, 'RUN_SC_A', None,
                     to_step=STEP_END_A, run_flag=RUN_SC_A)

def run_sc_b():
    """Stage B: Odb.RemoveRoutingObstructions → KLayout.Render  (post-DRT + streamout)"""
    print("\n=== Step 5b: soc_core — post-DRT cleanup + GDS/DEF streamout ===")
    _librelane_stage(_SC_YAML, 'RUN_SC_A', None,
                     from_step=STEP_START_B, to_step=STEP_END_B,
                     run_flag=RUN_SC_B)

def run_sc_c():
    """Stage C: Magic.WriteLEF → end  (DRC, LVS, STA, final views copy)"""
    print("\n=== Step 5c: soc_core — DRC/LVS/STA/views ===")
    _librelane_stage(_SC_YAML, 'RUN_SC_A', _SC_SAVE,
                     from_step=STEP_START_C, run_flag=RUN_SC_C)


# ============================================================
# Steps 6a-6c: padring chip-top (3 stages)
# ============================================================

_PR_YAML    = 'librelane/soc_padring_top.yaml'
_PR_SAVE    = f'{CONTAINER_WORKSPACE}/build/soc_padring'

def run_pr_a():
    """Stage A: Synthesis → DetailedRouting"""
    print("\n=== Step 6a: padring — Synthesis → DetailedRouting ===")
    _librelane_stage(_PR_YAML, 'RUN_PR_A', None,
                     to_step=STEP_END_A, run_flag=RUN_PR_A)

def run_pr_b():
    """Stage B: post-DRT cleanup + GDS/DEF streamout"""
    print("\n=== Step 6b: padring — post-DRT cleanup + GDS/DEF streamout ===")
    _librelane_stage(_PR_YAML, 'RUN_PR_A', None,
                     from_step=STEP_START_B, to_step=STEP_END_B,
                     run_flag=RUN_PR_B)

def run_pr_c():
    """Stage C: DRC/LVS/STA/views copy"""
    print("\n=== Step 6c: padring — DRC/LVS/STA/views ===")
    _librelane_stage(_PR_YAML, 'RUN_PR_A', _PR_SAVE,
                     from_step=STEP_START_C, run_flag=RUN_PR_C)


# ============================================================
# Step 7: Signoff metrics (padring = final chip)
# ============================================================

def signoff_report():
    print("\n=== Step 7: Signoff Metrics (padring) ===")
    metrics_path = HOST_WORKSPACE / 'build' / 'soc_padring' / 'metrics.csv'

    if not RUN_SIGNOFF:
        print(f'(dry-run) would parse {metrics_path}')
        return

    wanted = [
        ('design__die__area',         'Die Area (um^2)'),
        ('magic__drc_error__count',   'Magic DRC Errors'),
        ('klayout__drc_error__count', 'KLayout DRC Errors'),
        ('design__lvs_error__count',  'Netgen LVS Errors'),
        ('antenna__violating__nets',  'Antenna Violations'),
        ('timing__setup_vio__count',  'Setup Violations'),
        ('timing__hold_vio__count',   'Hold Violations'),
        ('power__total',              'Total Power (W)'),
    ]

    if not metrics_path.exists():
        print(f'!! metrics.csv not found: {metrics_path}')
        print('   Complete Step 6c (RUN_PR_C) first.')
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

    any_bad = any(
        (found.get(k, '0') or '0').strip() not in ('0', '')
        for k in ('magic__drc_error__count', 'klayout__drc_error__count',
                  'design__lvs_error__count', 'antenna__violating__nets',
                  'timing__setup_vio__count', 'timing__hold_vio__count')
    )
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
    print("  Target: sky130A | 100 MHz | 8x4KB SRAM (OpenRAM, vccd1/vssd1)")
    print("=" * 70)

    if not check_container():
        return

    stage_files()
    harden_core()
    glsim()
    patch_top()

    # soc_core: 3 resumable stages
    run_sc_a()
    run_sc_b()
    run_sc_c()

    # padring: 3 resumable stages (depends on soc_core views in build/)
    run_pr_a()
    run_pr_b()
    run_pr_c()

    signoff_report()

    print("\n" + "=" * 70)
    print("  Pipeline complete. Flip RUN_* flags to execute each step.")
    print("=" * 70)


if __name__ == '__main__':
    main()
