# Contributing to PicoRV32 RISC-V SoC

Thank you for taking the time to contribute! This project welcomes bug reports, feature suggestions, RTL improvements, firmware patches, and documentation updates.

---

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How to Contribute](#how-to-contribute)
- [Development Setup](#development-setup)
- [Pull Request Guidelines](#pull-request-guidelines)
- [RTL Style Guide](#rtl-style-guide)
- [Firmware Style Guide](#firmware-style-guide)
- [Commit Message Format](#commit-message-format)

---

## Code of Conduct

This project follows the [Contributor Covenant](https://www.contributor-covenant.org/version/2/1/code_of_conduct/) Code of Conduct. Be respectful, inclusive, and constructive in all interactions.

---

## How to Contribute

### Reporting Bugs

Open an issue using the **Bug Report** template. Please include:

- A minimal reproduction (the exact `make` command and any required input files)
- Simulator version (`verilator --version`, `iverilog -V`, etc.)
- Toolchain version (`riscv32-unknown-elf-gcc --version`)
- Relevant log output or waveform screenshot

### Suggesting Features

Open an issue using the **Feature Request** template. Describe:

- What problem it solves
- How it fits the existing architecture
- Any known trade-offs

### Submitting Code

1. Fork the repository and create a feature branch from `main`:
   ```bash
   git checkout -b feat/your-feature-name
   ```
2. Make your changes, following the style guides below.
3. Run the relevant simulation / lint checks (see below).
4. Push your branch and open a Pull Request against `main`.

---

## Development Setup

```bash
# Clone your fork
git clone https://github.com/YOUR_USERNAME/riscv-soc.git
cd riscv-soc

# Install simulation dependencies (Ubuntu/Debian)
sudo apt install verilator iverilog gtkwave

# RISC-V toolchain
# See https://github.com/riscv-collab/riscv-gnu-toolchain
# Minimum: riscv32-unknown-elf-gcc 12+

# Build firmware and run unit tests
make firmware
make sim

# Run Verilator simulation
make run
```

---

## Pull Request Guidelines

- Keep PRs focused. One logical change per PR.
- All new RTL modules must have at least a basic unit testbench in `tb/`.
- All new firmware features should include a brief test in `firmware/tests/`.
- Existing `make sim` and `make sim_soc` targets must still pass.
- Update `docs/` or `README.md` if you add a new feature or change a command.
- Add your change to `CHANGELOG.md` under the `[Unreleased]` section.

---

## RTL Style Guide

- **Language:** SystemVerilog (`.sv`). Prefer synthesisable constructs.
- **Naming:** `snake_case` for signals and modules. Prefix registers with `r_`, wires with `w_` (optional but consistent within a file).
- **Clocking:** Single clock domain `clk`, active-low asynchronous reset `rst_n`. CDC crossings must be explicitly documented.
- **Parameters:** Use `parameter` / `localparam` at the top of the module. Avoid magic numbers.
- **Comments:** Explain *why*, not *what*. Block headers for each module with a brief description.
- **Formatting:** 2-space indentation, 100-column line limit.

Example module header:
```systemverilog
// uart_ctrl_apb.sv — APB UART with 8-byte TX/RX FIFO
// Baud divisor: BAUDDIV = clk_hz / baud_rate - 1
module uart_ctrl_apb #(
  parameter CLK_HZ  = 50_000_000,
  parameter BAUD    = 115_200
) (
  input  logic        clk,
  input  logic        rst_n,
  // APB slave interface
  ...
);
```

---

## Firmware Style Guide

- **Language:** C99 + GNU extensions for `start.S` (GAS assembly).
- **Naming:** `snake_case` for functions and variables. `ALL_CAPS` for macros and register addresses.
- **Headers:** Each driver must have a corresponding `.h` with all register addresses and bit definitions.
- **No dynamic allocation in drivers.** Use static buffers or caller-provided memory.
- **FreeRTOS tasks:** Keep task stack sizes in `FreeRTOSConfig.h`. Document the tick source.

---

## Commit Message Format

Use [Conventional Commits](https://www.conventionalcommits.org/):

```
<type>(<scope>): <short summary>

[optional body]

[optional footer]
```

Types: `feat`, `fix`, `rtl`, `fw`, `sim`, `docs`, `ci`, `refactor`, `test`

Scopes (optional): `uart`, `gpio`, `timer`, `spi`, `debug`, `sram`, `uvm`, `openlane`, `freertos`

Examples:
```
rtl(uart): add RX FIFO overrun status flag
fw(freertos): reduce idle task stack to 128 words
fix(sim): correct bootrom.hex path in sim Makefile
docs: add synthesis area results table to flow/README.md
```
