#!/usr/bin/env python3
"""
Generate a structured Jupyter Notebook (.ipynb) for the LibreLane sky130A
RTL-to-GDSII flow.

Each major step of `docker_asic_flow.py` becomes its own code cell with a
markdown cell above it explaining the step. Run:

    python3 generate_notebook.py

Output: librelane/soc_asic_flow.ipynb  (open in Jupyter / VS Code).

Requires: pip install nbformat
"""

from pathlib import Path
import nbformat as nbf

OUT_PATH = Path(__file__).resolve().parent / 'soc_asic_flow.ipynb'


# ============================================================
# Reusable code blocks (kept in sync with docker_asic_flow.py)
# ============================================================

CONFIG_CODE = '''\
from pathlib import Path
import csv, shutil, subprocess, textwrap

# --- Run flags (flip True one-at-a-time as you progress) ---
RUN_STAGE_FILES    = False   # Step 1
RUN_HARDEN_CORE    = False   # Step 2
RUN_GLSIM          = False   # Step 3
RUN_PATCH_TOP      = False   # Step 4
RUN_CHIP_TOP       = False   # Step 5
RUN_SIGNOFF_REPORT = False   # Step 6

# --- Container ---
CONTAINER_NAME = 'riscv-soc'

# --- PDK: sky130A (pre-installed in iic-osic-tools container) ---
PDK_NAME           = 'sky130A'
STD_CELL_LIB       = 'sky130_fd_sc_hd'
CONTAINER_PDK_ROOT = '/foss/pdks'

# --- Paths ---
PROJECT_ROOT        = Path.cwd().parent if Path.cwd().name == 'librelane' else Path.cwd()
HOST_WORKSPACE      = Path.home() / 'eda' / 'designs' / 'riscv_soc' / 'workspace'
CONTAINER_WORKSPACE = '/foss/designs/riscv_soc/workspace'

# --- OpenRAM SRAM macro (sky130, vccd1/vssd1, single TT corner) ---
SRAM_NAME = 'sky130_sram_4kbyte_1rw_32x1024_8'

# --- sky130A STA corners (per-corner .lib mandatory in LibreLane v3) ---
SKY130_CORNERS = [
    'nom_tt_025C_1v80', 'nom_ss_100C_1v60', 'nom_ff_n40C_1v95',
    'min_tt_025C_1v80', 'min_ss_100C_1v60', 'min_ff_n40C_1v95',
    'max_tt_025C_1v80', 'max_ss_100C_1v60', 'max_ff_n40C_1v95',
]

print(f'PROJECT_ROOT  = {PROJECT_ROOT}')
print(f'HOST_WORKSPACE = {HOST_WORKSPACE}')
'''

HELPER_CODE = '''\
def run_or_print(cmd, do_it, *, shell_on_container=False, timeout=None):
    """Print command; execute inside container when do_it=True."""
    if shell_on_container:
        print(f"$ docker exec {CONTAINER_NAME} bash -lc '<script>'")
        print(textwrap.indent(cmd, '  | '))
    else:
        print('$ ' + ' '.join(str(x) for x in cmd))
    if not do_it:
        print('  (skipped -- flip the RUN_* flag to execute)\\n')
        return None
    args = (['docker', 'exec', CONTAINER_NAME, 'bash', '-lc', cmd]
            if shell_on_container else list(cmd))
    proc = subprocess.run(args, capture_output=True, text=True, timeout=timeout)
    if proc.stdout.strip():
        print(proc.stdout[-4000:])
    if proc.returncode != 0 and proc.stderr.strip():
        print('STDERR (tail):')
        print(proc.stderr[-2000:])
    print(f'  returncode={proc.returncode}\\n')
    return proc

def ok(label, cond, detail=''):
    tag = 'OK ' if cond else '!! '
    print(f'{tag}{label}' + (f'  -- {detail}' if detail else ''))
    return cond
'''

STEP0_CODE = '''\
proc = subprocess.run(
    ['docker', 'ps', '--filter', f'name={CONTAINER_NAME}', '--format', '{{.Names}}'],
    capture_output=True, text=True)
container_up = CONTAINER_NAME in proc.stdout
ok(f"Container '{CONTAINER_NAME}' running", container_up)

if container_up:
    pdk_check = subprocess.run(
        ['docker', 'exec', CONTAINER_NAME, 'test', '-d',
         f'{CONTAINER_PDK_ROOT}/{PDK_NAME}'], capture_output=True, text=True)
    ok(f"sky130A PDK at {CONTAINER_PDK_ROOT}/{PDK_NAME}", pdk_check.returncode == 0)
'''

STEP1_CODE = '''\
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
    print(f'\\nStaged at {HOST_WORKSPACE}')
else:
    print('(dry-run) would stage rtl/, librelane/, openram/, constraints/')
'''

STEP2_CODE = '''\
harden_core = textwrap.dedent(f"""
    set -e
    cd {CONTAINER_WORKSPACE}
    librelane librelane/picorv32_core.yaml \\\\
        --pdk {PDK_NAME} \\\\
        --pdk-root {CONTAINER_PDK_ROOT} \\\\
        --scl {STD_CELL_LIB} \\\\
        --save-views-to {CONTAINER_WORKSPACE}/build/picorv32_axi
""").strip()

run_or_print(harden_core, RUN_HARDEN_CORE, shell_on_container=True, timeout=1800)
'''

STEP3_CODE = '''\
glsim = textwrap.dedent(f"""
    set -e
    NL={CONTAINER_WORKSPACE}/build/picorv32_axi/nl/picorv32_axi.nl.v
    ls -la $NL
    echo "Pair with {CONTAINER_PDK_ROOT}/{PDK_NAME}/libs.ref/{STD_CELL_LIB}/verilog/"
    echo "for cocotb GL sim (-DFUNCTIONAL -DUNIT_DELAY=#1)."
""").strip()

run_or_print(glsim, RUN_GLSIM, shell_on_container=True, timeout=300)
'''

STEP4_CODE = '''\
def patch_top():
    import yaml
    cfg_path = HOST_WORKSPACE / 'librelane' / 'soc_core_top.yaml'
    cfg = yaml.safe_load(cfg_path.read_text())
    build = Path(CONTAINER_WORKSPACE) / 'build'

    # PicoRV32 core: per-corner libs from LibreLane build
    core_base = build / 'picorv32_axi'
    cfg.setdefault('MACROS', {})
    cfg['MACROS']['picorv32_axi'] = {
        'gds': [str(core_base / 'gds' / 'picorv32_axi.gds')],
        'lef': [str(core_base / 'lef' / 'picorv32_axi.lef')],
        'vh':  [str(core_base / 'nl'  / 'picorv32_axi.nl.v')],
        'lib': {c: [str(core_base / 'lib' / c / f'picorv32_axi__{c}.lib')]
                for c in SKY130_CORNERS},
        'instances': {'u_core': {'location': [400, 100], 'orientation': 'N'}},
    }

    # SRAM 4x2 array at TOP (each bank 808.845 x 351.29 um, die 2200x2600)
    sram_base = Path(CONTAINER_WORKSPACE) / 'openram' / 'build'
    cfg['MACROS'][SRAM_NAME] = {
        'gds': [str(sram_base / f'{SRAM_NAME}.gds')],
        'lef': [str(sram_base / f'{SRAM_NAME}.lef')],
        'vh':  [str(sram_base / f'{SRAM_NAME}.v')],
        'lib': {c: [str(sram_base / f'{SRAM_NAME}_TT_1p8V_25C.lib')]
                for c in SKY130_CORNERS},
        'instances': {
            'u_sram.gen_sram_bank[0].u_bank': {'location': [120, 900],   'orientation': 'N'},
            'u_sram.gen_sram_bank[1].u_bank': {'location': [1180, 900],  'orientation': 'N'},
            'u_sram.gen_sram_bank[2].u_bank': {'location': [120, 1300],  'orientation': 'N'},
            'u_sram.gen_sram_bank[3].u_bank': {'location': [1180, 1300], 'orientation': 'N'},
            'u_sram.gen_sram_bank[4].u_bank': {'location': [120, 1700],  'orientation': 'N'},
            'u_sram.gen_sram_bank[5].u_bank': {'location': [1180, 1700], 'orientation': 'N'},
            'u_sram.gen_sram_bank[6].u_bank': {'location': [120, 2100],  'orientation': 'N'},
            'u_sram.gen_sram_bank[7].u_bank': {'location': [1180, 2100], 'orientation': 'N'},
        },
    }

    # PDN_MACRO_CONNECTIONS must be List[str] (LibreLane v3). sky130A nets vccd1/vssd1.
    cfg['PDN_MACRO_CONNECTIONS'] = [
        '.*u_core.* vccd1 vssd1 vccd1 vssd1',
        '.*u_bank.* vccd1 vssd1 vccd1 vssd1',
    ]
    cfg['VDD_NETS'] = ['vccd1']
    cfg['GND_NETS'] = ['vssd1']

    cfg_path.write_text(yaml.safe_dump(cfg, sort_keys=False, default_flow_style=False))
    print(f'Patched {cfg_path}')

if RUN_PATCH_TOP:
    patch_top()
else:
    print('(dry-run) would add picorv32_axi + SRAM macros and PDN connections')
'''

STEP5_CODE = '''\
chip_top = textwrap.dedent(f"""
    set -e
    cd {CONTAINER_WORKSPACE}
    librelane librelane/soc_core_top.yaml \\\\
        --pdk {PDK_NAME} \\\\
        --pdk-root {CONTAINER_PDK_ROOT} \\\\
        --scl {STD_CELL_LIB} \\\\
        --save-views-to {CONTAINER_WORKSPACE}/build/soc_core
""").strip()

# No timeout: chip-top + multi-macro signoff can run 30-90 min.
run_or_print(chip_top, RUN_CHIP_TOP, shell_on_container=True, timeout=None)
'''

STEP6_CODE = '''\
metrics_path = HOST_WORKSPACE / 'build' / 'soc_core' / 'metrics.csv'
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

if not RUN_SIGNOFF_REPORT:
    print(f'(dry-run) would parse {metrics_path}')
elif not metrics_path.exists():
    print(f'!! metrics.csv not found: {metrics_path}  (run Step 5 first)')
else:
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
                  'timing__setup_vio__count', 'timing__hold_vio__count'))
    print('\\nSIGNOFF:', 'VIOLATIONS PRESENT' if any_bad else 'CLEAN (all zero)')
'''


# ============================================================
# Notebook assembly
# ============================================================

# (markdown_text, code_text) pairs. None code => markdown-only cell.
SECTIONS = [
    ("""# PicoRV32 RISC-V SoC -- LibreLane RTL-to-GDSII (sky130A)

End-to-end **multi-macro hierarchical** flow inside the
`hpretl/iic-osic-tools:chipathon26` container, targeting the
**sky130A** PDK with the **sky130_fd_sc_hd** standard cells.

| Stage | Detail |
|---|---|
| Core macro | PicoRV32 (RV32IM) hardened standalone, per-corner Liberty |
| SRAM | 4x OpenRAM 4 KB banks (`vccd1`/`vssd1`, TT_1p8V_25C), 2x2 array |
| Floorplan | SiFive-style: SRAM at top, core+peripherals at bottom |
| Signoff | 9 STA corners, Magic+KLayout DRC, Netgen LVS, antenna |

Every long step is gated by a `RUN_*` flag (all default `False`).
Flip them on one at a time as you progress.""", None),

    ("## Step 0.1 -- Configuration\n\nPaths, PDK identifiers, run flags, and the sky130A STA corner list.",
     CONFIG_CODE),

    ("## Step 0.2 -- Helpers (`run_or_print`, `ok`)\n\n"
     "`run_or_print` prints every command, then executes it inside "
     "`docker exec gf180 bash -lc ...` only when its `RUN_*` flag is `True`.",
     HELPER_CODE),

    ("## Step 0.3 -- Verify container + sky130A PDK\n\n"
     "Confirms the `gf180` container is up and that `sky130A` is present "
     "at `/foss/pdks/sky130A`.",
     STEP0_CODE),

    ("## Step 1 -- Stage project into the bind-mount\n\n"
     "Copies `rtl/`, `librelane/`, `openram/`, `constraints/` into "
     "`~/eda/designs/riscv_soc/workspace` (container: "
     "`/foss/designs/riscv_soc/workspace`). sky130A is already installed, "
     "so no PDK clone is needed.",
     STEP1_CODE),

    ("## Step 2 -- Harden the PicoRV32 core macro\n\n"
     "Runs the LibreLane Classic flow on `picorv32_core.yaml`, writing "
     "`gds/lef/nl/lib` views to `build/picorv32_axi/`. Runtime ~5-15 min.",
     STEP2_CODE),

    ("## Step 3 -- Post-synthesis GL simulation (optional)\n\n"
     "Confirms the hardened netlist exists and points at the "
     "`sky130_fd_sc_hd` behavioural models for an optional cocotb GL run.",
     STEP3_CODE),

    ("""## Step 4 -- Patch the top-level config

Dynamically injects two macros into `soc_core_top.yaml`:

- **`picorv32_axi`** -- per-corner Liberty (9 sky130A corners).
- **SRAM** -- single TT lib mapped to all corners; placed as a 2x2 array
  at the top of the die.

`PDN_MACRO_CONNECTIONS` is written as a **list of strings**
(`"<regex> <vdd> <vss> <macro_vdd_pin> <macro_vss_pin>"`) per the
LibreLane v3 schema -- dict-shaped entries are rejected. Power nets are
`vccd1`/`vssd1` to match the OpenRAM SRAM pins.""",
     STEP4_CODE),

    ("## Step 5 -- Run the chip-top `soc_core` flow\n\n"
     "Full synthesis -> floorplan -> PDN -> placement -> CTS -> routing -> "
     "Magic+KLayout DRC -> Netgen LVS -> antenna -> multi-corner STA. "
     "Runtime ~30-90 min (DRC dominates).",
     STEP5_CODE),

    ("## Step 6 -- Signoff metrics\n\n"
     "Parses `build/soc_core/metrics.csv` and prints Die Area, DRC/LVS/"
     "antenna counts, setup/hold violations, and total power with a "
     "**CLEAN / VIOLATIONS PRESENT** verdict.",
     STEP6_CODE),

    ("""## Where to go next

- **Tune placement.** Edit the `instances` locations in Step 4 (no
  re-hardening needed) to move the core or SRAM banks.
- **Re-characterize the SRAM.** Replace the single TT lib with a full
  OpenRAM multi-corner characterization for sharper STA.
- **Inspect the layout.** `klayout ~/eda/designs/riscv_soc/workspace/build/soc_core/gds/soc_core.gds`

Cleanup:
```bash
rm -rf ~/eda/designs/riscv_soc/workspace
docker stop gf180
```""", None),
]


def build_notebook():
    nb = nbf.v4.new_notebook()
    cells = []
    for md, code in SECTIONS:
        cells.append(nbf.v4.new_markdown_cell(md))
        if code is not None:
            cells.append(nbf.v4.new_code_cell(code.rstrip()))
    nb['cells'] = cells
    nb['metadata'] = {
        'kernelspec': {'display_name': 'Python 3', 'language': 'python', 'name': 'python3'},
        'language_info': {'name': 'python', 'version': '3'},
    }
    return nb


def main():
    nb = build_notebook()
    with OUT_PATH.open('w') as fh:
        nbf.write(nb, fh)
    n_code = sum(1 for _, c in SECTIONS if c is not None)
    n_md = len(SECTIONS)
    print(f'Wrote {OUT_PATH}')
    print(f'  {n_md} markdown cell(s), {n_code} code cell(s)')
    print(f'  Open with: jupyter notebook {OUT_PATH}')


if __name__ == '__main__':
    main()
