# ASIC flow scripts (Yosys + OpenSTA + OpenROAD)

This folder provides a minimal standalone flow for synthesis, STA, and PnR
without relying on OpenLane wrappers. It is intended as a starting point for
local iteration. The scripts borrow structure from the OpenLane defaults but
remain lightweight and explicit.

## Quick start

1) Review and edit the variables in `flow/env.sh`.
2) Run synthesis:
   - `flow/run_yosys.sh` (or `scripts/run_yosys.sh`)
3) Run STA on the synthesized netlist:
   - `flow/run_opensta.sh` (or `scripts/run_opensta.sh`)
4) Run OpenROAD place-and-route:
   - `flow/run_openroad.sh` (or `scripts/run_openroad.sh`)

Outputs are written under `flow/out`.

## Notes

- The flow assumes SKY130 HD standard cells by default.
- The OpenRAM 4KB macro is included via LEF/LIB in `flow/env.sh`.
- Yosys outputs are written under `flow/yosys/out`.
- The OpenROAD flow here is minimal and does not include full signoff steps
   (PDN, DRC, LVS). Add those if needed.
