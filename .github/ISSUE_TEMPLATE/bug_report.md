---
name: Bug Report
about: Report a simulation failure, RTL bug, or build issue
title: "[BUG] "
labels: bug
assignees: ''
---

## Describe the Bug

A clear and concise description of what the bug is.

## Environment

| Item | Version |
|---|---|
| OS | e.g. Ubuntu 22.04 |
| Verilator | e.g. 5.006 |
| Icarus Verilog | e.g. 11.0 |
| riscv32-unknown-elf-gcc | e.g. 12.2.0 |
| OpenOCD | e.g. 0.12.0 |

## Steps to Reproduce

```bash
# Exact commands to reproduce
make firmware
make sim
```

## Expected Behavior

What you expected to happen.

## Actual Behavior

What actually happened. Include error messages, assertion failures, or unexpected waveforms.

## Logs / Waveforms

Paste relevant terminal output or attach a waveform screenshot.

```
[paste log here]
```

## Additional Context

Any other relevant information (custom config, modified RTL, etc.).
