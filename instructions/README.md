# SkyForge — Docker Setup Instructions

SkyForge's ASIC implementation flow runs **entirely inside the IIC-OSIC-TOOLS Docker
container** (`hpretl/iic-osic-tools:chipathon26`). This is the **only supported
environment** — it bundles every EDA tool the flow needs at known-good versions.

> **New to Docker?** Follow the OS-specific setup first:
> - Linux → [`linux/install_docker_desktop.md`](linux/install_docker_desktop.md)
> - Windows → [`windows/install_docker_desktop.md`](windows/install_docker_desktop.md)

---

## What's inside the container

| Tool | Role in the SkyForge flow |
|------|---------------------------|
| **Yosys** | RTL synthesis (Verilog → gate netlist) |
| **OpenROAD** | Floorplan, placement, CTS, global + detailed routing, STA |
| **Magic** | Layout extraction, GDS streamout, DRC |
| **Netgen** | LVS (layout vs. schematic) |
| **KLayout** | Signoff DRC, GDS viewing/streamout |
| **OpenSTA** | Static timing analysis |
| **Verilator / Icarus** | RTL simulation |
| **OpenROAD/OpenLane → LibreLane** | The RTL-to-GDS flow orchestrator |

PDK: **`sky130A`** at `/foss/pdks/sky130A` (standard cell library `sky130_fd_sc_hd`).

---

## 1. Start the container

The SkyForge scripts expect a container named **`riscv-soc`** with the project
workspace bind-mounted at `/foss/designs/sky-forge`.

**Linux (X11/Wayland mode, for GUI tools like KLayout):**
```bash
docker run -d \
  --name riscv-soc \
  -v ~/eda/designs/sky-forge:/foss/designs/sky-forge \
  -v /foss/pdks:/foss/pdks \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  hpretl/iic-osic-tools:chipathon26 \
  tail -f /dev/null
```

**Attach a shell:**
```bash
docker exec -it riscv-soc bash
```

> The container's `/foss/designs` maps to `~/eda/designs` on the host — this is the
> **only** persistent directory across container updates. Clone/place the SkyForge repo
> under `~/eda/designs/sky-forge` on the host so it appears at
> `/foss/designs/sky-forge` inside the container.

---

## 2. Run the ASIC flow

From inside the container:
```bash
cd /foss/designs/sky-forge
python3 librelane/docker_asic_flow.py
```

This orchestrates the full hierarchical flow:
1. **Harden the PicoRV32 core** as a reusable macro (`picorv32_axi`).
2. **Patch** `soc_core_top.yaml` with the macro placements, PDN connections, and die area.
3. **SoC-top P&R** (synthesis → floorplan → placement → CTS → routing).
4. **Signoff** — Magic DRC, KLayout DRC, Netgen LVS, STA.

See [`../docs/WAIVED_CHECKS.md`](../docs/WAIVED_CHECKS.md) for the signoff results and
waiver documentation.

---

## 3. Troubleshooting

| Symptom | Fix |
|---------|-----|
| Docker OOM / daemon hang during a heavy step | `systemctl --user restart docker-desktop`, wait ~30 s, then `docker start riscv-soc` |
| `PDK path not found` | Ensure `/foss/pdks/sky130A` is accessible inside the container |
| Container not running | `docker start riscv-soc` |
| GUI tool (KLayout) won't open | Confirm `DISPLAY` is exported and `/tmp/.X11-unix` is mounted; install `socat` on the host (Linux) |
| Long EDA runs | Run one EDA job at a time — overlapping runs can corrupt state files |
