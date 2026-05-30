# OpenLane setup for riscv-soc

This folder mirrors the standard OpenLane `designs/<design>` structure so the
flow can be run in the same way as native OpenLane designs.

## Layout

- `designs/soc_core_prod/`
  - `config.json` OpenLane 2 config for the `soc_core` top.
  - `pin_order.cfg` I/O pin placement order.
  - `macro.sdc` hook for project constraints (sources `/project/constraints/soc_core.sdc`).
  - `src/` with a symlink to the master RTL tree.

## Usage

1. Ensure the OpenLane repo is cloned at `$(HOME)/OpenLane`.
2. Set `PDK_ROOT` if your PDK is not under `$(HOME)/.ciel`.
3. Run:

```sh
cd ~/riscv-soc/openlane
make run DESIGN=soc_core_prod
```

To enter the container interactively:

```sh
make mount
```
