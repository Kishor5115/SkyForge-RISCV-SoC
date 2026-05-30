# Changelog

## Unreleased - open-source readiness

### Added
- `tb/soc_top_bringup_tb.sv`: lightweight `soc_top` bring-up testbench. It boots
  the integration firmware from BootROM and monitors APB writes to the UART TX
  register for the firmware markers `---FIRMWARE_PASS---` (PASS) and
  `---TEST_FAIL---` (FAIL). It prints the first UART APB access and a post-reset
  diagnostic, and has a simulation timeout. Waveform dumping is off by default;
  enable it with the `+vcd` plusarg or by compiling with `-DSOC_TB_VCD`.
- `make sim_soc_new_tb`: builds the integration firmware, copies the BootROM hex
  to `sim/integration_test.hex`, and runs the new bring-up testbench (Icarus).
- `archive/` directory with a README describing retained-but-inactive files.

### Changed
- `.gitignore`: also ignore `*.map`, `firmware/gdb_session.log`, and
  `*.gdb_history`.

### Removed (from git tracking only; files remain on disk)
- Build artifacts that were committed by mistake: `sim/obj_dir_firmware/`,
  `firmware/build/`, `firmware/firmware.map`, and `firmware/gdb_session.log`.
  These already matched `.gitignore` but had been committed before those rules
  existed.

### Moved
- `tb/axi_interconect_tb.sv` -> `archive/tb/axi_interconect_tb.sv`. It is a
  misspelled unit testbench not wired into any build target. The module it
  exercises (`axi_interconnect`) is still in use via `axi_interconnect_2m`, so
  the test was archived rather than deleted.

### Notes
- The existing `make sim_soc` flow and all peripheral unit-test targets are
  unchanged.
- Project layout (unchanged, documented here for contributors):

  ```text
  rtl/            SoC RTL (core, interconnect, memory, peripherals, asic top)
  firmware/       FreeRTOS kernel + PicoRV32 port + drivers + apps/tests
  tb/             Icarus testbenches (peripherals + SoC integration)
  sim/            Verilator simulation (remote-bitbang for OpenOCD)
  scripts/        Helper scripts (hex conversion, etc.)
  flow/           Yosys/OpenSTA/OpenROAD ASIC scripts
  openlane/       OpenLane design wrapper
  constraints/    Timing constraints
  docs/           How-to-run documentation
  archive/        Retained-but-inactive files
  ```

### Known issues
- The Icarus SoC integration run (`make sim_soc` and `make sim_soc_new_tb`) does
  not currently reach the firmware PASS marker: the CPU instruction-fetch
  address runs past the BootROM shortly after reset and the UART is never
  driven. This reproduces on the committed (HEAD) RTL and firmware as well, so
  it is independent of the testbench. It needs a separate bring-up debug pass.
