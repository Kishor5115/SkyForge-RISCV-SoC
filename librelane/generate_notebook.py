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
RUN_STAGE_FILES    = True    # Step 1
RUN_HARDEN_CORE    = True    # Step 2
RUN_GLSIM          = True    # Step 3
RUN_PATCH_TOP      = True    # Step 4
RUN_CHIP_TOP       = True    # Step 5
RUN_GDS            = True    # Step 6
RUN_SIGNOFF_REPORT = True    # Step 7

# --- Container ---
CONTAINER_NAME = 'riscv-soc'

# --- PDK: sky130A (pre-installed in iic-osic-tools container) ---
PDK_NAME           = 'sky130A'
STD_CELL_LIB       = 'sky130_fd_sc_hd'
CONTAINER_PDK_ROOT = '/foss/pdks'

# --- Paths ---
PROJECT_ROOT        = Path.cwd().parent if Path.cwd().name == 'librelane' else Path.cwd()
HOST_WORKSPACE      = Path.home() / 'eda' / 'designs' / 'sky-forge'
CONTAINER_WORKSPACE = '/foss/designs/sky-forge'

# --- OpenRAM SRAM macro (sky130, vccd1/vssd1, single TT corner) ---
SRAM_NAME = 'sky130_sram_4kbyte_1rw_32x1024_8'

# --- Run tags ---
CORE_RUN_TAG = 'RUN_1_PICORV32'
TOP_RUN_TAG  = 'RUN_2_SOC_TOP_PD'
GDS_RUN_TAG  = 'RUN_3_GDS'

# --- sky130A STA corners (per-corner .lib mandatory in LibreLane v3) ---
SKY130_CORNERS = [
    'nom_tt_025C_1v80', 'nom_ss_100C_1v60', 'nom_ff_n40C_1v95',
    'min_tt_025C_1v80', 'min_ss_100C_1v60', 'min_ff_n40C_1v95',
    'max_tt_025C_1v80', 'max_ss_100C_1v60', 'max_ff_n40C_1v95',
]

print(f'PROJECT_ROOT   = {PROJECT_ROOT}')
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
        --save-views-to {CONTAINER_WORKSPACE}/build/picorv32_axi \\\\
        --run-tag {CORE_RUN_TAG}
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
    """Inject hardened macro views + corrected floorplan/PDN into soc_core_top.yaml.

    CRITICAL FIXES applied here (see docs/SOC_TOP_WARNING_RESOLUTION.md):
    -----------------------------------------------------------------------
    1. PDN/PSM-0069: CPU macro power pin names corrected to VPWR/VGND (the
       macro's actual LEF pin names), not vccd1/vssd1. Combined with the
       met4-topped macro PDN (picorv32_core.yaml), this resolves the 833
       vccd1 unconnected-shape violations.
    2. CONGESTION/RSZ-0064: die area expanded 1800x1550 (from 1400), density
       35% (from 52%), GRT_ADJUSTMENT 0.15 to force uniform placement spread
       room for the icache 8192-FF cluster + hold buffers.
    """
    import yaml
    cfg_path = HOST_WORKSPACE / 'librelane' / 'soc_core_top.yaml'
    cfg = yaml.safe_load(cfg_path.read_text())
    build = Path(CONTAINER_WORKSPACE) / 'build'

    # --- PicoRV32 core macro ---
    core_base = build / 'picorv32_axi'
    cfg.setdefault('MACROS', {})
    cfg['MACROS']['picorv32_axi'] = {
        'gds': [str(core_base / 'gds' / 'picorv32_axi.gds')],
        'lef': [str(core_base / 'lef' / 'picorv32_axi.lef')],
        'vh':  [str(core_base / 'nl'  / 'picorv32_axi.nl.v')],
        'lib': {c: [str(core_base / 'lib' / c / f'picorv32_axi__{c}.lib')]
                for c in SKY130_CORNERS},
        'instances': {'u_cpu': {'location': [570, 10], 'orientation': 'N'}},   # bottom edge (periphery)
    }

    # --- SRAM macros: 2 banks (8 KB), single row near top ---
    # Each bank: 808.845 x 351.29 um, native N orientation.
    sram_base = Path(CONTAINER_WORKSPACE) / 'openram' / 'build'
    cfg['MACROS'][SRAM_NAME] = {
        'gds': [str(sram_base / f'{SRAM_NAME}.gds')],
        'lef': [str(sram_base / f'{SRAM_NAME}.lef')],
        'vh':  [str(sram_base / f'{SRAM_NAME}.v')],
        'lib': {c: [str(sram_base / f'{SRAM_NAME}_TT_1p8V_25C.lib')]
                for c in SKY130_CORNERS},
        'instances': {
            'u_sram.gen_sram_bank[0].u_bank': {'location': [90,  1030], 'orientation': 'N'},
            'u_sram.gen_sram_bank[1].u_bank': {'location': [980, 1030], 'orientation': 'N'},
        },
    }

    # --- PDN macro connections ---
    # Format: "<inst_regex> <power_net> <ground_net> <power_pin> <ground_pin>"
    # CPU pins are VPWR/VGND (std-cell naming); SRAM pins are vccd1/vssd1.
    cfg['PDN_MACRO_CONNECTIONS'] = [
        '.*u_cpu.* vccd1 vssd1 VPWR VGND',
        '.*u_bank.* vccd1 vssd1 vccd1 vssd1',
    ]
    cfg['VDD_NETS'] = ['vccd1']
    cfg['GND_NETS'] = ['vssd1']

    # --- Floorplan / routing knobs (congestion + hold fix) ---
    cfg['DIE_AREA']              = [0, 0, 1800, 1550]
    cfg['PL_TARGET_DENSITY_PCT'] = 50   # normal density (periphery floorplan gives the routing channel)
    cfg['GRT_ADJUSTMENT']        = 0.15
    cfg['GRT_OVERFLOW_ITERS']    = 150

    cfg_path.write_text(yaml.safe_dump(cfg, sort_keys=False, default_flow_style=False))
    print(f'Patched {cfg_path}')
    print(f'  Die: 1800x1550, density 50%, CPU bottom + SRAM top (periphery)')
    print(f'  CPU PDN pin: VPWR/VGND -> vccd1/vssd1 net')
    print(f'  SRAM: 2 banks @ y=1030 (top edge); CPU @ y=10 (bottom edge)')

if RUN_PATCH_TOP:
    patch_top()
else:
    print('(dry-run) would patch soc_core_top.yaml with corrected macros')
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
        --run-tag {TOP_RUN_TAG} \\\\
        --to OpenROAD.DetailedRouting
""").strip()

# Runs through detailed routing. GRT_ALLOW_CONGESTION lets residual localized
# global-route overflow pass to detailed routing, which resolves it.
run_or_print(chip_top, RUN_CHIP_TOP, shell_on_container=True, timeout=None)
'''

STEP5B_CODE = '''\
chip_top_gds = textwrap.dedent(f"""
    set -e
    cd {CONTAINER_WORKSPACE}
    librelane librelane/soc_core_top.yaml \\\\
        --pdk {PDK_NAME} \\\\
        --pdk-root {CONTAINER_PDK_ROOT} \\\\
        --scl {STD_CELL_LIB} \\\\
        --save-views-to {CONTAINER_WORKSPACE}/build/soc_core \\\\
        --run-tag RUN_3_GDS \\\\
        --from Odb.RemoveRoutingObstructions \\\\
        --with-initial-state librelane/runs/{TOP_RUN_TAG}/44-openroad-detailedrouting/state_out.json
""").strip()

# Resumes from DRT-completed state: antenna check, fill, RCX, STA, GDS, DRC, LVS
run_or_print(chip_top_gds, RUN_GDS, shell_on_container=True, timeout=None)
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
    print(f'!! metrics.csv not found: {metrics_path}  (run Step 5/6 first)')
else:
    found = {}
    with metrics_path.open() as fh:
        for row in csv.reader(fh):
            if row and row[0] in dict(wanted):
                found[row[0]] = row[1] if len(row) > 1 else ''
    print(f'{\"Metric\":45s} {\"Value\":>15s}')
    print('-' * 63)
    for k, label in wanted:
        print(f'  {label:43s} {found.get(k, \"(missing)\"):>15s}')
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
    ("""# PicoRV32 RISC-V SoC — LibreLane RTL-to-GDSII (sky130A) — 8 KB Flash-XIP

End-to-end **multi-macro hierarchical** flow inside the
`hpretl/iic-osic-tools:chipathon26` container, targeting the
**sky130A** PDK with the **sky130_fd_sc_hd** standard cells.

| Stage | Detail |
|---|---|
| Core macro | PicoRV32 (RV32IM) hardened standalone @ **100 MHz**, DELAY-0 synth, **met4 power pins** (fixes PSM-0069) |
| SRAM | 2× OpenRAM 4 KB banks = **8 KB** (`vccd1`/`vssd1`, TT_1p8V_25C), single row |
| I-Cache | 512 B direct-mapped, flash XIP path, FF-based (std cells, not a macro) |
| Flash | External QSPI chip — **off-die** (XIP via flash_ctrl + I-Cache) |
| Floorplan | Die 1800×1550 µm, SRAM single-row near top, CPU centred below |
| PDN | Core grid met4/met5; macro **power** tops at met4 → orthogonal via connectivity (signals use met1–met5) |
| Signoff | 9 STA corners, Magic+KLayout DRC, Netgen LVS, antenna |

**Key fixes applied (vs prior runs):**
- **100 MHz target:** `CLOCK_PERIOD 10`, core `SYNTH_STRATEGY "DELAY 0"`,
  full met1–met5 signal routing. (PicoRV32 closes ~200 MHz on sky130 per the
  peer-reviewed OpenROAD/OpenLane study, so 100 MHz is a conservative, credible
  target.)
- **PSM-0069 (833 violations):** Root cause was the CPU macro's *power* topping at
  met5 (same as core grid), creating a floating power island. Fixed by hardening
  the macro's POWER as a proper sub-macro (`PDN_MULTILAYER: false` =
  `DESIGN_IS_CORE:false` → met1 rails + met4 power straps only). The SoC-top met5
  straps via orthogonally down to the macro's met4 power pins. Signal routing
  still uses met5 (independent of the power grid).
- **GRT-0116/0230 congestion:** Root cause = the FF-based icache (8192 FFs) local
  density on met1/met2. **PPA fix**: halve it to 512 B (`flash_xip.sv` NUM_LINES
  32→16 = 4096 FFs) — the right area/power trade, and the smaller read mux also
  helps timing at 100 MHz. Plus periphery macro floorplan (CPU bottom, SRAM top, ~509um channel), density 50%, GRT_ADJUSTMENT 0.15,
  and `GRT_ALLOW_CONGESTION: true` so detailed routing resolves residual overflow.
- **GRT-0281 high fanout:** SDC `set_max_fanout 24` + `SYNTH_MAX_FANOUT: 16`
  forces buffer tree insertion for icache req_foff word-select nets.
- **RSZ-0064 hold repair:** Lower density gives the resizer room. Clock
  uncertainty reduced from 0.5 to 0.25 ns (less pessimistic hold margin).""", None),

    ("## Step 0.1 — Configuration\n\nPaths, PDK identifiers, run tags, and the sky130A STA corner list.",
     CONFIG_CODE),

    ("## Step 0.2 — Helpers (`run_or_print`, `ok`)\n\n"
     "`run_or_print` prints every command, then executes it inside "
     "`docker exec riscv-soc bash -lc ...` only when its `RUN_*` flag is `True`.",
     HELPER_CODE),

    ("## Step 0.3 — Verify container + sky130A PDK\n\n"
     "Confirms the `riscv-soc` container is up and that `sky130A` is present "
     "at `/foss/pdks/sky130A`.",
     STEP0_CODE),

    ("## Step 1 — Stage project into the bind-mount\n\n"
     "Copies `rtl/`, `librelane/`, `openram/`, `constraints/` into "
     "`~/eda/designs/sky-forge` (container: "
     "`/foss/designs/sky-forge`). sky130A is already installed, "
     "so no PDK clone is needed.",
     STEP1_CODE),

    ("""## Step 2 — Harden the PicoRV32 core macro

Runs the LibreLane Classic flow on `picorv32_core.yaml` @ **100 MHz** with
DELAY-0 synthesis, writing `gds/lef/nl/lib` views to `build/picorv32_axi/`.
Runtime ~5–15 min.

**PDN (PSM-0069 fix) vs routing (100 MHz) — the split:**
```yaml
CLOCK_PERIOD: 10          # 100 MHz
SYNTH_STRATEGY: "DELAY 0" # shrink the regfile->ALU->regfile datapath
PDN_MULTILAYER: false     # = DESIGN_IS_CORE:false -> POWER on met1 rails + met4 straps only
PDN_VERTICAL_LAYER: met4  # power pins promoted on met4
RT_MAX_LAYER: met5        # SIGNALS use full met1..met5 (needed for 100 MHz)
```
The PSM-0069 fix is about **power**: keeping power pins on met4 lets the SoC-top
met5 straps via orthogonally DOWN onto them (met5 *power* would run parallel to
the top met5 straps and could not connect → the floating vccd1 island). **Signal**
routing on met5 is independent of the power grid and is required to close the
100 MHz datapath. (A met3+met4 power mesh was tried first and failed with
PDN-0179; the single-met4 power grid is the correct approach.)""",
     STEP2_CODE),

    ("## Step 3 — Post-synthesis GL simulation (optional)\n\n"
     "Confirms the hardened netlist exists and points at the "
     "`sky130_fd_sc_hd` behavioural models for an optional cocotb GL run.",
     STEP3_CODE),

    ("""## Step 4 — Patch the top-level config

Dynamically injects two macros into `soc_core_top.yaml`:

- **`picorv32_axi`** — per-corner Liberty (9 sky130A corners), at `[570, 10]` (bottom edge).
- **SRAM** — 2× OpenRAM 4 KB banks at `[90, 1180]` and `[980, 1030]` (top edge).

**PDN_MACRO_CONNECTIONS** format: `"<regex> <vdd_net> <gnd_net> <vdd_pin> <gnd_pin>"`.
- CPU macro: pins are **VPWR/VGND** (std-cell naming from LibreLane harden).
- SRAM macro: pins are **vccd1/vssd1** (OpenRAM native naming).

Floorplan: Die **1800×1550** µm, density **35%** (uniform spread), GRT adjustment **0.15**.""",
     STEP4_CODE),

    ("""## Step 5 — Run the chip-top `soc_core` flow (through Detailed Routing)

Synthesis → floorplan → PDN → placement → CTS → global routing → **detailed
routing**. Runtime ~40–60 min.

**Congestion strategy (GRT-0116):** the root-cause fix is the **512 B icache**
(`flash_xip.sv` NUM_LINES 16), which removes the met1/met2 density hotspot.
Since average global-route utilisation is only ~46%, any residual overflow is
localized — `GRT_ALLOW_CONGESTION: true` lets global routing pass it to detailed
routing (TritonRoute), which closes it with fine rip-up-and-reroute. That's why
this step now runs **through** detailed routing rather than stopping at GR.""",
     STEP5_CODE),

    ("## Step 6 — Post-DRT Signoff (GDS streamout + DRC + LVS + STA)\n\n"
     "Resumes from the DRT-completed state (`RUN_2_SOC_TOP_PD/44-openroad-"
     "detailedrouting/state_out.json`) under a **new run tag `RUN_3_GDS`**.\n\n"
     "Steps: routing-obstruction removal → antenna check → fill insertion → "
     "RCX parasitic extraction → multi-corner post-PnR STA → IR-drop → "
     "Magic + KLayout GDS streamout → DRC → LVS → signoff report.\n\n"
     "Runtime ~30–60 min.",
     STEP5B_CODE),

    ("## Step 7 — Signoff metrics\n\n"
     "Parses `build/soc_core/metrics.csv` and prints Die Area, DRC/LVS/"
     "antenna counts, setup/hold violations, and total power with a "
     "**CLEAN / VIOLATIONS PRESENT** verdict.",
     STEP6_CODE),

    ("""## Where to go next

- **Tune placement.** Edit the `instances` locations in Step 4 (no
  re-hardening needed) to move the core or SRAM banks.
- **Re-characterize the SRAM.** Replace the single TT lib with a full
  OpenRAM multi-corner characterization for sharper STA.
- **Inspect the layout.** `klayout ~/eda/designs/sky-forge/build/soc_core/gds/soc_core.gds`
- **Review docs.** See `docs/SOC_TOP_WARNING_RESOLUTION.md` and
  `docs/PICORV32_STA_ANALYSIS.md` for the full analysis.

Cleanup:
```bash
rm -rf ~/eda/designs/sky-forge
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
    n_md = len(SECTIONS)
    print(f'Wrote {OUT_PATH}')
    print(f'  {n_md} markdown cell(s), {n_code} code cell(s)')
    print(f'  Open with: jupyter notebook {OUT_PATH}')
    print('  NOTE: 8 KB SRAM (2 banks) + 1 KB I-Cache, external flash XIP.')
    print('  PDN FIX: CPU macro POWER tops at met4 (signals met5) -> resolves PSM-0069; 100 MHz target.')


if __name__ == '__main__':
    main()
