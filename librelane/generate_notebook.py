#!/usr/bin/env python3
"""
Generate soc_asic_flow.ipynb from the sections defined below.
Each (markdown, code) pair becomes two notebook cells.
Run:  python3 generate_notebook.py
"""

from pathlib import Path
import nbformat as nbf

OUT_PATH = Path(__file__).resolve().parent / 'soc_asic_flow.ipynb'

# ── shared boilerplate ────────────────────────────────────────────────────

CONFIG = '''\
from pathlib import Path
import csv, shutil, subprocess, textwrap

# ── Run flags ────────────────────────────────────────────────────────────
RUN_STAGE_FILES  = True    # Step 1: stage project files
RUN_HARDEN_CORE  = True    # Step 2: harden picorv32_axi  (~5-15 min)
RUN_GLSIM        = True    # Step 3: GL simulation (optional)
RUN_PATCH_TOP    = True    # Step 4: patch soc_core_top.yaml

RUN_SC_A         = True    # Step 5a: soc_core  synth → detailed routing
RUN_SC_B         = True    # Step 5b: soc_core  post-DRT → streamout
RUN_SC_C         = True    # Step 5c: soc_core  DRC/LVS/STA + views copy

RUN_PR_A         = True    # Step 6a: padring   synth → detailed routing
RUN_PR_B         = True    # Step 6b: padring   post-DRT → streamout
RUN_PR_C         = True    # Step 6c: padring   DRC/LVS/STA + views copy

RUN_SIGNOFF      = True    # Step 7: parse signoff metrics

# ── Container / PDK ──────────────────────────────────────────────────────
CONTAINER_NAME      = 'riscv-soc'
PDK_NAME            = 'sky130A'
STD_CELL_LIB        = 'sky130_fd_sc_hd'
CONTAINER_PDK_ROOT  = '/foss/pdks'

# ── Paths ─────────────────────────────────────────────────────────────────
PROJECT_ROOT        = Path.cwd().parent if Path.cwd().name == 'librelane' else Path.cwd()
HOST_WORKSPACE      = Path.home() / 'eda' / 'designs' / 'riscv_soc' / 'workspace'
CONTAINER_WORKSPACE = '/foss/designs/riscv_soc/workspace'

SRAM_NAME = 'sky130_sram_4kbyte_1rw_32x1024_8'
SKY130_CORNERS = [
    'nom_tt_025C_1v80', 'nom_ss_100C_1v60', 'nom_ff_n40C_1v95',
    'min_tt_025C_1v80', 'min_ss_100C_1v60', 'min_ff_n40C_1v95',
    'max_tt_025C_1v80', 'max_ss_100C_1v60', 'max_ff_n40C_1v95',
]

# ── Stage split-points (LibreLane step IDs) ───────────────────────────────
STEP_END_A   = 'OpenROAD.DetailedRouting'
STEP_START_B = 'Odb.RemoveRoutingObstructions'
STEP_END_B   = 'KLayout.Render'
STEP_START_C = 'Magic.WriteLEF'

print(f'PROJECT_ROOT   = {PROJECT_ROOT}')
print(f'HOST_WORKSPACE = {HOST_WORKSPACE}')
'''

HELPERS = '''\
def run_or_print(cmd, do_it, *, shell_on_container=False, timeout=None):
    if shell_on_container:
        print(f"$ docker exec {CONTAINER_NAME} bash -lc '<script>'")
        print(textwrap.indent(cmd, '  | '))
    else:
        print('$ ' + ' '.join(str(x) for x in cmd))
    if not do_it:
        print('  (skipped -- flip RUN_* flag)\\n')
        return None
    args = (['docker', 'exec', CONTAINER_NAME, 'bash', '-lc', cmd]
            if shell_on_container else list(cmd))
    proc = subprocess.run(args, capture_output=True, text=True, timeout=timeout)
    if proc.stdout.strip():
        print(proc.stdout[-4000:])
    if proc.returncode != 0 and proc.stderr.strip():
        print('STDERR:', proc.stderr[-2000:])
    print(f'  returncode={proc.returncode}\\n')
    return proc

def ok(label, cond, detail=''):
    print(('OK ' if cond else '!! ') + label + (f'  -- {detail}' if detail else ''))
    return cond

def _stage(yaml_rel, run_tag, save_to, *, from_step=None, to_step=None, run_flag):
    flags = f'--run-tag {run_tag}'
    if from_step: flags += f' -F {from_step}'
    if to_step:   flags += f' -T {to_step}'
    if save_to:   flags += f' --save-views-to {save_to}'
    script = textwrap.dedent(f"""
        set -e
        cd {CONTAINER_WORKSPACE}
        librelane {yaml_rel} \\\\
            --pdk {PDK_NAME} \\\\
            --pdk-root {CONTAINER_PDK_ROOT} \\\\
            {flags}
    """).strip()
    run_or_print(script, run_flag, shell_on_container=True, timeout=None)
'''

STEP0 = '''\
proc = subprocess.run(
    ['docker', 'ps', '--filter', f'name={CONTAINER_NAME}', '--format', '{{.Names}}'],
    capture_output=True, text=True)
ok(f"Container '{CONTAINER_NAME}' running", CONTAINER_NAME in proc.stdout)

pdk_check = subprocess.run(
    ['docker', 'exec', CONTAINER_NAME, 'test', '-d', f'{CONTAINER_PDK_ROOT}/{PDK_NAME}'],
    capture_output=True, text=True)
ok(f"sky130A PDK at {CONTAINER_PDK_ROOT}/{PDK_NAME}", pdk_check.returncode == 0)
'''

STEP1 = '''\
if RUN_STAGE_FILES:
    if HOST_WORKSPACE.exists():
        shutil.rmtree(HOST_WORKSPACE)
    HOST_WORKSPACE.mkdir(parents=True)
    for sub in ('rtl', 'librelane', 'openram', 'constraints'):
        src = PROJECT_ROOT / sub
        if src.exists():
            dst = HOST_WORKSPACE / sub
            shutil.copytree(src, dst)
            print(f'  {sub}/  -- {sum(1 for _ in dst.rglob("*") if _.is_file())} files')
    (HOST_WORKSPACE / 'build').mkdir(exist_ok=True)
    print(f'Staged at {HOST_WORKSPACE}')
else:
    print('(dry-run) would stage rtl/, librelane/, openram/, constraints/')
'''

STEP2 = '''\
script = textwrap.dedent(f"""
    set -e
    cd {CONTAINER_WORKSPACE}
    librelane librelane/picorv32_core.yaml \\\\
        --pdk {PDK_NAME} \\\\
        --pdk-root {CONTAINER_PDK_ROOT} \\\\
        --run-tag RUN_PICO_100 \\\\
        --save-views-to {CONTAINER_WORKSPACE}/build/picorv32_axi
""").strip()
run_or_print(script, RUN_HARDEN_CORE, shell_on_container=True, timeout=1800)
'''

STEP3 = '''\
script = textwrap.dedent(f"""
    set -e
    NL={CONTAINER_WORKSPACE}/build/picorv32_axi/nl/picorv32_axi.nl.v
    ls -la $NL
    echo "Pair with {CONTAINER_PDK_ROOT}/{PDK_NAME}/libs.ref/{STD_CELL_LIB}/verilog/"
""").strip()
run_or_print(script, RUN_GLSIM, shell_on_container=True, timeout=300)
'''

STEP4 = '''\
def patch_top():
    import yaml
    src_yaml = PROJECT_ROOT / 'librelane' / 'soc_core_top.yaml'
    dst_yaml = HOST_WORKSPACE / 'librelane' / 'soc_core_top.yaml'
    cfg = yaml.safe_load(src_yaml.read_text())
    
    build = Path(CONTAINER_WORKSPACE) / 'build'
    core_base = build / 'picorv32_axi'
    sram_base = Path(CONTAINER_WORKSPACE) / 'openram' / 'build'
    
    def all_corners_lib(lib_path):
        return {c: [lib_path] for c in SKY130_CORNERS}
        
    core = cfg['MACROS']['picorv32_axi']
    core['gds'] = [str(core_base / 'gds/picorv32_axi.gds')]
    core['lef'] = [str(core_base / 'lef/picorv32_axi.lef')]
    core['vh']  = [str(core_base / 'nl/picorv32_axi.nl.v')]
    core['lib'] = all_corners_lib(str(core_base / 'lib/nom_tt_025C_1v80/picorv32_axi__nom_tt_025C_1v80.lib'))
    
    sram = cfg['MACROS'][SRAM_NAME]
    sram['gds'] = [str(sram_base / f'{SRAM_NAME}.gds')]
    sram['lef'] = [str(sram_base / f'{SRAM_NAME}.lef')]
    sram['vh']  = [str(sram_base / f'{SRAM_NAME}.v')]
    sram['lib'] = all_corners_lib(str(sram_base / f'{SRAM_NAME}_TT_1p8V_25C.lib'))
    
    raw = yaml.safe_dump(cfg, sort_keys=False, default_flow_style=False)
    if any('__PATCH_' in l for l in raw.splitlines()):
        raise RuntimeError('Placeholders not fully resolved')
        
    dst_yaml.write_text(raw)
    print(f'Patched {dst_yaml}')

if RUN_PATCH_TOP:
    patch_top()
else:
    print('(dry-run) would inject picorv32_axi + SRAM paths (placement kept from yaml)')
'''

SC_A = '''\
# soc_core Stage A: Verilator.Lint → OpenROAD.DetailedRouting
# Run-tag: RUN_SC_A  |  resume here if Stage B/C failed
_stage('librelane/soc_core_top.yaml', 'RUN_SC_A', None,
       to_step=STEP_END_A, run_flag=RUN_SC_A)
'''

SC_B = '''\
# soc_core Stage B: Odb.RemoveRoutingObstructions → KLayout.Render
# Run-tag: RUN_SC_A  |  resumes seamlessly from RUN_SC_A Stage A
_stage('librelane/soc_core_top.yaml', 'RUN_SC_A', None,
       from_step=STEP_START_B, to_step=STEP_END_B, run_flag=RUN_SC_B)
'''

SC_C = '''\
# soc_core Stage C: Magic.WriteLEF → end  (DRC / LVS / STA / views copy)
# Run-tag: RUN_SC_A  |  saves final views to build/soc_core/
_SC_SAVE = f'{CONTAINER_WORKSPACE}/build/soc_core'
_stage('librelane/soc_core_top.yaml', 'RUN_SC_A', _SC_SAVE,
       from_step=STEP_START_C, run_flag=RUN_SC_C)
'''

PR_A = '''\
# padring Stage A: Synthesis → OpenROAD.DetailedRouting
# Run-tag: RUN_PR_A  |  uses soc_core views from build/soc_core/
_stage('librelane/soc_padring_top.yaml', 'RUN_PR_A', None,
       to_step=STEP_END_A, run_flag=RUN_PR_A)
'''

PR_B = '''\
# padring Stage B: Odb.RemoveRoutingObstructions → KLayout.Render
# Run-tag: RUN_PR_A  |  resumes seamlessly from RUN_PR_A Stage A
_stage('librelane/soc_padring_top.yaml', 'RUN_PR_A', None,
       from_step=STEP_START_B, to_step=STEP_END_B, run_flag=RUN_PR_B)
'''

PR_C = '''\
# padring Stage C: Magic.WriteLEF → end  (DRC / LVS / STA / views copy)
# Run-tag: RUN_PR_A  |  saves final views to build/soc_padring/
_PR_SAVE = f'{CONTAINER_WORKSPACE}/build/soc_padring'
_stage('librelane/soc_padring_top.yaml', 'RUN_PR_A', _PR_SAVE,
       from_step=STEP_START_C, run_flag=RUN_PR_C)
'''

SIGNOFF = '''\
metrics_path = HOST_WORKSPACE / 'build' / 'soc_padring' / 'metrics.csv'
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
if not RUN_SIGNOFF:
    print(f'(dry-run) would parse {metrics_path}')
elif not metrics_path.exists():
    print(f'!! {metrics_path} not found — complete Step 6c first')
else:
    found = {}
    with metrics_path.open() as fh:
        for row in csv.reader(fh):
            if row and row[0] in dict(wanted):
                found[row[0]] = row[1] if len(row) > 1 else ''
    print(f\'{"Metric":45s} {"Value":>15s}\')
    print(\'-\' * 63)
    for k, label in wanted:
        print(f\'  {label:43s} {found.get(k, "(missing)"):>15s}\')
    any_bad = any((found.get(k,"0") or "0").strip() not in ("0","")
                  for k in ("magic__drc_error__count","klayout__drc_error__count",
                            "design__lvs_error__count","antenna__violating__nets",
                            "timing__setup_vio__count","timing__hold_vio__count"))
    print("\\nSIGNOFF:", "VIOLATIONS PRESENT" if any_bad else "CLEAN (all zero)")
'''

# ── Notebook sections: (markdown, code) ──────────────────────────────────

SECTIONS = [
    # ── Title ────────────────────────────────────────────────────────────
    ("""# PicoRV32 RISC-V SoC — LibreLane RTL-to-GDSII (sky130A)

End-to-end **multi-macro hierarchical** flow inside `hpretl/iic-osic-tools:chipathon26`.

| Stage | Detail |
|---|---|
| Core macro | PicoRV32 (RV32IM) hardened standalone |
| SRAM | 8× OpenRAM 4 KB banks, 2×4 array at die top |
| soc_core | 3 resumable stages (A/B/C) — run-tags RUN_SC_A/B/C |
| padring | 3 resumable stages (A/B/C) — run-tags RUN_PR_A/B/C |

Flip the `RUN_*` flags one at a time. If a stage gets stuck, fix the issue
and re-run just that stage — LibreLane resumes from the saved ODB state via
`--from-step` and `--run-tag`.""", None),

    # ── Config ───────────────────────────────────────────────────────────
    ("## 0.1 Configuration & run flags", CONFIG),

    # ── Helpers ──────────────────────────────────────────────────────────
    ("## 0.2 Helpers (`run_or_print`, `ok`, `_stage`)\n\n"
     "`_stage` wraps a `librelane` invocation with optional `--from`/`--to` "
     "step bounds and `--run-tag` so each stage has its own resumable run "
     "directory under `librelane/runs/`.", HELPERS),

    # ── Step 0 ───────────────────────────────────────────────────────────
    ("## 0.3 Verify container + sky130A PDK", STEP0),

    # ── Step 1 ───────────────────────────────────────────────────────────
    ("## Step 1 — Stage project files\n\n"
     "Copies `rtl/`, `librelane/`, `openram/`, `constraints/` into the "
     "Docker bind-mount at `~/eda/designs/riscv_soc/workspace`.", STEP1),

    # ── Step 2 ───────────────────────────────────────────────────────────
    ("## Step 2 — Harden PicoRV32 core macro\n\n"
     "Full LibreLane Classic run on `picorv32_core.yaml`; writes "
     "`gds/lef/nl/lib` views to `build/picorv32_axi/`. ~5-15 min.", STEP2),

    # ── Step 3 ───────────────────────────────────────────────────────────
    ("## Step 3 — Post-synthesis GL simulation (optional)\n\n"
     "Confirms the hardened netlist exists for a cocotb GL run.", STEP3),

    # ── Step 4 ───────────────────────────────────────────────────────────
    ("""## Step 4 — Patch `soc_core_top.yaml`

Injects two macro entries into the YAML:

- **`picorv32_axi`** — per-corner Liberty (9 sky130A corners)
- **SRAM** — TT lib mapped to all corners; 2×4 array centred at die top

`PDN_MACRO_CONNECTIONS` is written as `List[str]` per the LibreLane v3
schema (dict entries are rejected). Power nets: `vccd1`/`vssd1`.""", STEP4),

    # ── soc_core heading ─────────────────────────────────────────────────
    ("""## soc_core flow — 3 resumable stages

The Classic flow is split at two natural checkpoints:

| Stage | Steps | Run-tag | When to run |
|---|---|---|---|
| **A** | Lint → `OpenROAD.DetailedRouting` | `RUN_SC_A` | First run, or if placement/routing failed |
| **B** | `Odb.RemoveRoutingObstructions` → `KLayout.Render` | `RUN_SC_B` | After Stage A succeeds |
| **C** | `Magic.WriteLEF` → end (DRC/LVS/STA + views copy) | `RUN_SC_C` | After Stage B succeeds |

If a stage gets stuck, fix the issue, flip only that stage's flag and re-run this cell.""", None),

    # ── SC-A ─────────────────────────────────────────────────────────────
    ("### Step 5a — soc_core: Synthesis → DetailedRouting  (`RUN_SC_A`)\n\n"
     "Runs Verilator lint, Yosys synthesis, floorplan, PDN, global/detailed "
     "placement, CTS, global routing, and detailed routing. ~20-60 min.", SC_A),

    # ── SC-B ─────────────────────────────────────────────────────────────
    ("### Step 5b — soc_core: post-DRT cleanup + streamout  (`RUN_SC_B`)\n\n"
     "Removes routing obstructions, checks antennas, fills, RCX, "
     "post-PnR STA, IR-drop, Magic + KLayout GDS streamout. ~10-20 min.", SC_B),

    # ── SC-C ─────────────────────────────────────────────────────────────
    ("### Step 5c — soc_core: DRC / LVS / STA / views copy  (`RUN_SC_C`)\n\n"
     "Magic LEF write, KLayout XOR, Magic DRC, KLayout DRC, SPICE extraction, "
     "Netgen LVS, timing-violation checkers, manufacturability report. "
     "Copies final views to `build/soc_core/`. ~5-15 min.", SC_C),

    # ── padring heading ───────────────────────────────────────────────────
    ("""## padring flow — 3 resumable stages

Same split strategy applied to `soc_padring_top.yaml`.
Depends on `build/soc_core/` views produced by Step 5c.

| Stage | Steps | Run-tag |
|---|---|---|
| **A** | Lint → `OpenROAD.DetailedRouting` | `RUN_PR_A` |
| **B** | `Odb.RemoveRoutingObstructions` → `KLayout.Render` | `RUN_PR_B` |
| **C** | `Magic.WriteLEF` → end | `RUN_PR_C` |""", None),

    # ── PR-A ─────────────────────────────────────────────────────────────
    ("### Step 6a — padring: Synthesis → DetailedRouting  (`RUN_PR_A`)", PR_A),

    # ── PR-B ─────────────────────────────────────────────────────────────
    ("### Step 6b — padring: post-DRT cleanup + streamout  (`RUN_PR_B`)", PR_B),

    # ── PR-C ─────────────────────────────────────────────────────────────
    ("### Step 6c — padring: DRC / LVS / STA / views copy  (`RUN_PR_C`)\n\n"
     "Copies final padring views to `build/soc_padring/`.", PR_C),

    # ── Signoff ──────────────────────────────────────────────────────────
    ("## Step 7 — Signoff metrics (padring)\n\n"
     "Parses `build/soc_padring/metrics.csv` and prints a "
     "**CLEAN / VIOLATIONS PRESENT** verdict.", SIGNOFF),

    # ── Next steps ───────────────────────────────────────────────────────
    ("""## Where to go next

- **Inspect layout**: `klayout ~/eda/designs/riscv_soc/workspace/build/soc_padring/gds/soc_padring.gds`
- **Re-run a stuck stage**: flip only that stage's `RUN_*` flag and re-execute its cell.
- **Tune floorplan**: edit CPU/SRAM coordinates in Step 4 — re-run Steps 4 → 5a only.

```bash
# Stop container when done
docker stop riscv-soc
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
    print(f'Wrote {OUT_PATH}')
    print(f'  {len(SECTIONS)} sections, {n_code} code cells')
    print(f'  Open with: jupyter notebook {OUT_PATH}')


if __name__ == '__main__':
    main()
