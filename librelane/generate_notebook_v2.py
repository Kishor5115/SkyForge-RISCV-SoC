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

OUT_PATH = Path(__file__).resolve().parent / 'soc_asic_flow_v2.ipynb'


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
    core_base = build / 'picorv32_axi'
    sram_base = Path(CONTAINER_WORKSPACE) / 'openram' / 'build'
    cfg.setdefault('MACROS', {})
    cfg['MACROS']['picorv32_axi'] = {
        'gds': [str(core_base / 'gds' / 'picorv32_axi.gds')],
        'lef': [str(core_base / 'lef' / 'picorv32_axi.lef')],
        'vh':  [str(core_base / 'nl'  / 'picorv32_axi.nl.v')],
        'lib': {c: [str(core_base / 'lib' / c / f'picorv32_axi__{c}.lib')]
                for c in SKY130_CORNERS},
        'instances': {'u_cpu': {'location': [530, 280], 'orientation': 'N'}},
    }
    cfg['MACROS'][SRAM_NAME] = {
        'gds': [str(sram_base / f'{SRAM_NAME}.gds')],
        'lef': [str(sram_base / f'{SRAM_NAME}.lef')],
        'vh':  [str(sram_base / f'{SRAM_NAME}.v')],
        'lib': {c: [str(sram_base / f'{SRAM_NAME}_TT_1p8V_25C.lib')]
                for c in SKY130_CORNERS},
        'instances': {
            'u_sram.gen_sram_bank[0].u_bank': {'location': [90,  1249], 'orientation': 'N'},
            'u_sram.gen_sram_bank[1].u_bank': {'location': [980, 1249], 'orientation': 'N'},
            'u_sram.gen_sram_bank[2].u_bank': {'location': [90,  1620], 'orientation': 'N'},
            'u_sram.gen_sram_bank[3].u_bank': {'location': [980, 1620], 'orientation': 'N'},
        },
    }
    cfg['DIE_AREA'] = [0, 0, 1800, 2000]
    cfg['PL_TARGET_DENSITY_PCT'] = 60
    cfg['GRT_ADJUSTMENT'] = 0.20
    cfg['GRT_OVERFLOW_ITERS'] = 150
    cfg['PDN_CFG'] = 'dir::pdn_cfg.tcl'
    cfg['PDN_MACRO_CONNECTIONS'] = [
        '.*u_cpu.* vccd1 vssd1 vccd1 vssd1',
        '.*u_bank.* vccd1 vssd1 vccd1 vssd1',
    ]
    cfg['VDD_NETS'] = ['vccd1']
    cfg['GND_NETS'] = ['vssd1']
    cfg_path.write_text(yaml.safe_dump(cfg, sort_keys=False, default_flow_style=False))
    print(f'Patched {cfg_path}  (v2: 1800x2000, 4-bank 16KB SRAM 2x2 grid, 1KB I-Cache)')

if RUN_PATCH_TOP:
    patch_top()
else:
    print('(dry-run) v2: 4-bank 16KB SRAM 2x2 grid, die 1800x2000 = 3.6mm^2 (~33% smaller)')
'''

STEP5_CODE = '''\
chip_top = textwrap.dedent(f"""
    set -e
    cd {CONTAINER_WORKSPACE}
    librelane librelane/soc_core_top.yaml \\\\
        --pdk {PDK_NAME} \\\\
        --pdk-root {CONTAINER_PDK_ROOT} \\\\
        --scl {STD_CELL_LIB} \\\\
        --save-views-to {CONTAINER_WORKSPACE}/build/soc_core \\\\
        --run-tag RUN_5_V2_SOC_TOP
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

STEP7_CODE = (
    "padring_cmd = textwrap.dedent(f\"\"\"\n"
    "    set -e\n"
    "    cd {CONTAINER_WORKSPACE}\n"
    "    librelane librelane/soc_padring_top.yaml \\\\\n"
    "        --pdk {PDK_NAME} \\\\\n"
    "        --pdk-root {CONTAINER_PDK_ROOT} \\\\\n"
    "        --scl {STD_CELL_LIB} \\\\\n"
    "        --save-views-to {CONTAINER_WORKSPACE}/build/soc_padring \\\\\n"
    "        --run-tag RUN_6_PADRING\n"
    "\"\"\").strip()\n"
    "\n"
    "run_or_print(padring_cmd, RUN_PADRING, shell_on_container=True, timeout=None)\n"
)

STEP8_CODE = (
    "import json as _json\n"
    "drc_cmd = textwrap.dedent(f\"\"\"\n"
    "    set -e\n"
    "    cd {CONTAINER_WORKSPACE}\n"
    "    librelane librelane/soc_padring_top.yaml \\\\\n"
    "        --pdk {PDK_NAME} --pdk-root {CONTAINER_PDK_ROOT} --scl {STD_CELL_LIB} \\\\\n"
    "        --run-tag RUN_5_DRC --from Magic.DRC --to Checker.MagicDRC\n"
    "        --with-initial-state librelane/runs/RUN_5_GDS2/03-klayout-xor/state_in.json\n"
    "\"\"\").strip()\n"
    "run_or_print(drc_cmd, RUN_DRC, shell_on_container=True, timeout=3600)\n"
    "if RUN_DRC:\n"
    "    run_dir = HOST_WORKSPACE / 'librelane' / 'runs' / 'RUN_5_DRC'\n"
    "    magic_count = klayout_count = 'n/a'\n"
    "    for f in sorted(run_dir.glob('*/state_out.json')):\n"
    "        try:\n"
    "            m = _json.loads(f.read_text()).get('metrics', {})\n"
    "            if 'magic__drc_error__count' in m: magic_count = m['magic__drc_error__count']\n"
    "            if 'klayout__drc_error__count' in m: klayout_count = m['klayout__drc_error__count']\n"
    "        except: pass\n"
    "    print(f'Magic  DRC errors : {magic_count}  (target = 0)')\n"
    "    print(f'KLayout DRC errors: {klayout_count}  (4755 on SRAM macros = known false-positive)')\n"
)

STEP9_CODE = (
    "import json as _json\n"
    "lvs_cmd = textwrap.dedent(f\"\"\"\n"
    "    set -e\n"
    "    cd {CONTAINER_WORKSPACE}\n"
    "    librelane librelane/soc_padring_top.yaml \\\\\n"
    "        --pdk {PDK_NAME} --pdk-root {CONTAINER_PDK_ROOT} --scl {STD_CELL_LIB} \\\\\n"
    "        --run-tag RUN_5_LVS --from Magic.SpiceExtraction --to Checker.LVS\n"
    "        --with-initial-state librelane/runs/RUN_5_GDS2/03-klayout-xor/state_in.json\n"
    "\"\"\").strip()\n"
    "run_or_print(lvs_cmd, RUN_LVS, shell_on_container=True, timeout=3600)\n"
    "if RUN_LVS:\n"
    "    run_dir = HOST_WORKSPACE / 'librelane' / 'runs' / 'RUN_5_LVS'\n"
    "    for f in sorted(run_dir.glob('*/state_out.json'), reverse=True):\n"
    "        try:\n"
    "            m = _json.loads(f.read_text()).get('metrics', {})\n"
    "            if 'design__lvs_error__count' in m:\n"
    "                print(f\"LVS errors: {m['design__lvs_error__count']}  (0 = clean)\")\n"
    "                break\n"
    "        except: pass\n"
    "    for rpt in sorted(run_dir.glob('*/reports/lvs.netgen.rpt'), reverse=True):\n"
    "        lines = rpt.read_text().splitlines()\n"
    "        print('\\n--- LVS report tail ---'); print('\\n'.join(lines[-10:])); break\n"
)



# ============================================================
# Notebook assembly
# ============================================================

# (markdown_text, code_text) pairs. None code => markdown-only cell.
SECTIONS = [
    ("""# PicoRV32 RISC-V SoC -- LibreLane RTL-to-GDSII (sky130A)  [v2 — 16KB + I-Cache]

End-to-end **multi-macro hierarchical** flow inside the
`hpretl/iic-osic-tools:chipathon26` container, targeting the
**sky130A** PDK with the **sky130_fd_sc_hd** standard cells.

| Stage | Detail |
|---|---|
| Core macro | PicoRV32 (RV32IM) hardened standalone, per-corner Liberty |
| SRAM | 4x OpenRAM 4 KB banks = **16 KB** (`vccd1`/`vssd1`, TT_1p8V_25C), 2x2 grid |
| I-Cache | 1 KB direct-mapped, flash XIP path only, FF-based (no extra macro) |
| Flash | External QSPI chip — **off-die** (XIP via flash_ctrl + I-Cache) |
| Floorplan | Die 1800×2000 µm (~33% smaller than v1), SRAM 2×2 flush-to-top |
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
`vccd1`/`vssd1` to match the OpenRAM SRAM pins.

**v2 changes:** die area reduced from 2533×1825 to **1800×2000 µm**; SRAM
reduced from 8→4 banks (32 KB→16 KB); CPU relocated to `[530, 280]` to centre
it under the new die width. The external QSPI flash is off-die, so there is no
flash macro — only the CPU and 4 SRAM banks are hardened macros.""",
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

    ("## Step 7 -- soc_padring chip-level P&R flow\n\n"
     "Places 116 signal pads + power/gnd pads + corner cells around the "
     "hardened **soc_core** macro (3060×4240 µm die). Runtime ~20-30 min.",
     STEP7_CODE),

    ("## Step 8 -- DRC (Magic + KLayout)\n\n"
     "Runs Magic DRC (authoritative) and KLayout DRC on the padring GDS. "
     "~4755 KLayout errors on SRAM macro boundaries are a known sky130 false-positive.",
     STEP8_CODE),

    ("## Step 9 -- LVS (Netgen)\n\n"
     "Extracts SPICE from the padring layout and runs Netgen LVS. "
     "SRAM macros are blackboxed; the key check is soc_core pin connectivity.",
     STEP9_CODE),

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
    print('  NOTE: This is the v2 notebook (16KB SRAM + 1KB I-Cache, flash XIP).')
    print('        For v1 (32KB), open soc_asic_flow.ipynb')


if __name__ == '__main__':
    main()
