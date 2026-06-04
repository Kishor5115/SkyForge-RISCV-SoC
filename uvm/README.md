# RISC-V SoC — UVM Verification Environment

A self-contained UVM environment for the APB peripheral subsystem of the
PicoRV32 SoC (`rtl/`). It provides an APB master agent, a shadow-register
scoreboard, functional coverage, a UVM register model, and unit + SoC-level
tests. The RTL is **not** modified by anything in this directory.

```
uvm/
  Makefile              Compile + run (VCS / Questa / Xcelium) + lint + coverage
  soc_uvm_pkg.sv        Package: includes the whole environment in dep. order
  env/
    apb_if.sv           APB4 interface (driver + monitor clocking blocks)
    soc_if.sv           soc_top pin-level interface
    soc_addr.svh        Centralized register-address macros
    apb_seq_item.sv     APB transaction
    apb_driver.sv       APB master driver (SETUP/ACCESS phases)
    apb_monitor.sv      Passive monitor -> analysis port
    apb_sequencer.sv    uvm_sequencer typedef
    apb_agent.sv        Active agent (driver + monitor + sequencer)
    apb_scoreboard.sv   Shadow register map + read-back checking
    apb_coverage.sv     Functional coverage (addr / rw / pslverr / cross)
    reg_model.sv        uvm_reg_block for UART/Timer/GPIO/SPI (+Debug)
    soc_env.sv          Top-level env (agent + scoreboard + coverage + regmodel)
  seq/
    apb_base_seq.sv     write32() / read32() utilities
    uart_seq.sv  gpio_seq.sv  timer_seq.sv  spi_seq.sv
    soc_smoke_seq.sv    Touches all five peripherals
    soc_stress_seq.sv   200+ randomized cross-peripheral transactions
  tests/
    soc_base_test.sv    Base test (selects a sequence by name)
    uart_test.sv  gpio_test.sv  timer_test.sv  spi_test.sv
    soc_smoke_test.sv  soc_stress_test.sv
  tb/
    tb_uart.sv  tb_gpio.sv  tb_timer.sv  tb_spi.sv   Unit TBs (single DUT)
    tb_soc_top.sv                                    Full-SoC TB
```

## Prerequisites

- A SystemVerilog/UVM simulator: **Synopsys VCS**, **Siemens Questa**, or
  **Cadence Xcelium**.
- The **UVM 1.2 library**. This environment is wired to the open-source
  `uvm-core` package by default:

  ```sh
  export UVM_HOME=/home/kishor/uvm-core/src   # or your own copy
  ```

  VCS/Questa compile `$(UVM_HOME)/uvm_pkg.sv` explicitly; Xcelium uses its
  built-in UVM (`-uvmhome CDNS-1.2`).

## Compile and run

Run from inside `uvm/`. Pick the simulator with `SIM=` (default `questa`):

```sh
make uart        SIM=questa     # uart_ctrl_apb unit test
make gpio        SIM=vcs        # gpio_apb unit test
make timer       SIM=xcelium    # timer_apb unit test
make spi                        # spi_master_apb unit test
make soc_smoke                  # full SoC smoke test  (DUT = soc_top)
make soc_stress                 # full SoC stress test (DUT = soc_top)
make all                        # everything
```

Each target compiles the relevant RTL, the APB interface, the UVM package and
the testbench, then runs with `+UVM_TESTNAME=<test>`. Logs are written to
`<test>.log`.

The test to run is chosen by `+UVM_TESTNAME`; you can point any TB at a
different test, e.g.:

```sh
make soc_smoke TESTNAME=soc_stress_test    # reuse tb_soc_top, run stress
```

## Coverage

Each run records coverage. Merge and report with:

```sh
make cov SIM=questa     # vcover merge + HTML report  -> cov_report/
make cov SIM=vcs        # urg                         -> cov_report/
make cov SIM=xcelium    # imc merge + report
```

The covergroup (`apb_cg` in `apb_coverage.sv`) collects:
- `cp_addr`  — one bin per peripheral window (UART/Timer/GPIO/SPI/Debug)
- `cp_rw`    — read vs write
- `cp_pslverr` — error response observed
- `x_addr_rw` — cross of address window and direction

The **smoke test** is designed to reach 100% of these bins, including the
`pslverr` error bin via an intentional GPIO invalid-offset access.

## How the SoC-level test reaches the APB bus

`soc_top` has no external APB port — the APB master is the internal AXI-to-APB
bridge driven by the CPU. With no firmware (`MEM_INIT_FILE=""`) the CPU issues
nothing useful, so `tb/tb_soc_top.sv` binds the UVM agent to the **internal**
APB bus of `soc_core` by hierarchical reference:

```
dut.u_soc_core.apb_psel / apb_penable / apb_pwrite
dut.u_soc_core.apb_paddr / apb_pwdata / apb_pstrb / apb_pprot   <- force from agent
dut.u_soc_core.apb_prdata / apb_pready / apb_pslverr            -> assign to agent
```

The request signals are `force`d from the agent's `apb_if`; the response
signals are continuously assigned back. This lets the same APB agent, monitor,
scoreboard and coverage work at both unit and SoC level.

## Scoreboard model

`apb_scoreboard.sv` keeps a shadow map `shadow[addr]` and a `rmask[addr]` table
of read-back-checkable registers (plain R/W storage only). Writes update the
shadow; reads of a checkable register compare `PRDATA & mask` against the
shadow. Write-only, read-only, read-clear and W1C registers are excluded.
Two RTL-specific behaviors are modelled:
- Timer `BGLOAD` (0x20001018) also updates the `LOAD` storage (0x20001000).
- SPI software reset (`CTRL[1]` @ 0x20003034) clears all SPI registers, so the
  SPI shadow entries are invalidated on that write.

## Register map (from the RTL)

| Peripheral | Base        | Key registers (offset)                                  |
|------------|-------------|---------------------------------------------------------|
| UART       | 0x20000000  | TX_DATA 0x0 (WO), RX_DATA 0x4 (RO), STATUS 0x8 (RO), CTRL 0xC |
| Timer      | 0x20001000  | LOAD 0x0, VALUE 0x4 (RO), CTRL 0x8, INTCLR 0xC (WO), RIS 0x10, BGLOAD 0x18 |
| GPIO       | 0x20002000  | INPUT_VAL 0x0 (RO), INPUT_EN 0x4, OUTPUT_EN 0x8, OUTPUT_VAL 0xC, ... IOF_SEL 0x40 |
| SPI        | 0x20003000  | SCKDIV 0x0, SCKMODE 0x4, CSID 0x8, CSDEF 0xC, FMT 0x14, TXDATA 0x18 (WO), RXDATA 0x1C (RO), CTRL 0x34 |
| Debug      | 0x20004000  | ID 0x0 (RO=0x44424731), CMD 0x8, ADDR 0xC, WDATA 0x10, IRQ_EN 0x20 |

## Running without a commercial simulator (Verilator)

A full UVM run requires a commercial simulator. If you only have the
open-source flow, you can still:

1. **Lint** the APB interface and peripheral RTL:

   ```sh
   make lint        # verilator --lint-only on apb_if.sv + gpio_apb
   ```

2. Use the open-source **UVM-on-Verilator** package
   (`https://github.com/chipsalliance/uvm-systemverilog` / Verilator's
   experimental UVM support, Verilator >= 5.x). Compile the same file list the
   Makefile uses, adding `--binary --timing +incdir+$(UVM_HOME)` and the
   `uvm_pkg.sv` source. UVM-on-Verilator is experimental and not all
   constructs (clocking-block drives, `force`/`release`, some coverage) are
   fully supported, so results may differ from a commercial run.

The existing top-level `make sim`, `make sim_soc`, and `make sim_soc_new_tb`
Icarus targets are unaffected by this directory.
