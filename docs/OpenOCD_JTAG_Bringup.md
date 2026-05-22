# OpenOCD + JTAG bring-up (step-by-step)

This repo contains a custom JTAG TAP + DTM in RTL:

- TAP/DTM: `rtl/peripherals/debug/jtag_dtm.sv`
- The DTM speaks **RISC-V DMI framing**, but it currently forwards DMI transactions into a **custom APB debug mailbox** (`rtl/peripherals/debug/debug_apb.sv`), not a full standard RISC-V Debug Module (DM).

That means:

- You *can* use OpenOCD to verify JTAG wiring, scan the chain, read IDCODE, and shift DTMCS/DMI.
- You **cannot** use stock `target create ... riscv` in OpenOCD for halt/step/breakpoints until you implement a standard RISC-V Debug Module (DM) (dmcontrol/dmstatus/abstractcs/etc) behind DMI.

This guide is split into two phases:

1) **Phase A (works today):** JTAG sanity + low-level DTMCS/DMI shifting using OpenOCD Tcl commands.
2) **Phase B (work to do):** What RTL you must add to enable normal OpenOCD+GDB debugging.

---

## 0) Prerequisites

### Install OpenOCD

Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install -y openocd telnet
```

Fedora:

```bash
sudo dnf install -y openocd telnet
```

Arch:

```bash
sudo pacman -S openocd inetutils
```

### Install RISC-V GCC + GDB (recommended)

If you already have `riscv64-unknown-elf-gcc` and `riscv64-unknown-elf-gdb`, you can skip.

Ubuntu/Debian packages vary by release. If your distro doesn’t provide `riscv64-unknown-elf-*`, use a prebuilt toolchain (xPack or similar) and add it to `PATH`.

Check:

```bash
riscv64-unknown-elf-gcc --version
riscv64-unknown-elf-gdb --version
```

---

## 1) Hardware wiring checklist (JTAG)

You need these signals connected between your SoC and JTAG adapter:

- `TCK`, `TMS`, `TDI`, `TDO`
- `GND`
- `Vref` (adapter must see the I/O voltage reference)
- Optional but recommended: `TRSTn` / `SRSTn` (if you have them). If you don’t, that’s ok.

Rules of thumb:

- Keep wires short.
- Start with low JTAG speed (100–1000 kHz).
- Confirm that your SoC I/O bank is powered and that `Vref` is present at the adapter.

---

## 2) Phase A: Verify JTAG scan chain and DTM access (works today)

### 2.1 Create OpenOCD interface config for your adapter

Create a folder anywhere (example uses `~/openocd_soc/`):

```bash
mkdir -p ~/openocd_soc
cd ~/openocd_soc
```

Now create `interface.cfg` for **your** adapter.

Common adapters:

#### A) FTDI FT2232H / FT232H

```tcl
# interface.cfg (FTDI example)
adapter driver ftdi

# Update these VID/PID for your board/adapter
ftdi_vid_pid 0x0403 0x6010

# Often channel 0, but can be 1 depending on wiring
ftdi_channel 0

transport select jtag
adapter speed 1000

# If you have SRST/TRST, configure here. If not, keep 'none'.
reset_config none
```

#### B) CMSIS-DAP (DAPLink)

```tcl
# interface.cfg (CMSIS-DAP)
adapter driver cmsis-dap
transport select jtag
adapter speed 1000
reset_config none
```

#### C) J-Link

```tcl
# interface.cfg (J-Link)
adapter driver jlink
transport select jtag
adapter speed 1000
reset_config none
```

If you’re unsure which adapter driver to use, run:

```bash
openocd -c "adapter list" -c "shutdown"
```

### 2.2 Create a TAP config for this SoC

Create `soc_tap.cfg`:

```tcl
# soc_tap.cfg

# Your RTL TAP has:
# - IR length = 5
# - IDCODE = 0x10005001 (see rtl/peripherals/debug/jtag_dtm.sv)

jtag newtap riscv cpu -irlen 5 -expected-id 0x10005001

# Helpful defaults
transport select jtag

# If JTAG is flaky, reduce speed to 100
# adapter speed 100
```

### 2.3 Start OpenOCD

```bash
openocd -f interface.cfg -f soc_tap.cfg
```

Keep this terminal running.

In a second terminal, connect to OpenOCD telnet:

```bash
telnet localhost 4444
```

Then run:

```tcl
init
scan_chain
```

Expected outcome:

- You should see one TAP (`riscv.cpu`) with the expected IDCODE.

If `scan_chain` fails:

- Lower speed: edit `interface.cfg` and set `adapter speed 100`.
- Verify wiring and `Vref`.

---

## 3) Read IDCODE / DTMCS / DMI from OpenOCD (low-level)

Your DTM instruction opcodes (from RTL):

- `IDCODE` instruction = `0x01`
- `DTMCS` instruction  = `0x10`
- `DMI` instruction    = `0x11`

### 3.1 Read IDCODE

In telnet:

```tcl
# Select IDCODE instruction
irscan riscv.cpu 0x01

# Shift 32-bit DR, capture output
drscan riscv.cpu 32 0x0
```

Expected: output contains `0x10005001`.

### 3.2 Read DTMCS

```tcl
irscan riscv.cpu 0x10
drscan riscv.cpu 32 0x0
```

Expected: non-zero value (DTMCS fields). In RTL, `abits=7` and `version=1` are encoded.

### 3.3 Perform a single DMI read/write shift

**Important:** This SoC’s DMI does *not* implement the standard RISC-V Debug Module registers.
Instead, DMI address/data/op are forwarded into a debug mailbox.

DMI register format in your RTL (shifted LSB-first):

- `op`   = bits `[1:0]` (0=NOP, 1=Read, 2=Write)
- `data` = bits `[33:2]`
- `addr` = bits `[40:34]` (7-bit)

A practical bring-up pattern is:

1) Write mailbox registers via DMI writes.
2) Let firmware (Boot ROM monitor) act on them.

**Note:** To make this fully usable, you’ll usually add OpenOCD Tcl procs that pack/unpack the 41-bit value.
Because OpenOCD’s bit ordering can be confusing on different setups, start by validating with simple known registers first (IDCODE/DTMCS).

---

## 4) Phase B: Enable normal OpenOCD + GDB debugging (halt/step/load)

To use OpenOCD’s standard RISC-V target (`target create ... riscv`), your RTL must expose a **RISC-V Debug Module (DM)** behind DMI (RISC-V Debug Spec v0.13).

### 4.1 What you need to implement in RTL

At minimum:

- A DMI responder that implements standard DM registers (e.g. `dmcontrol`, `dmstatus`, `hartinfo`, `abstractcs`, `command`, `data0`, `progbuf`, …)
- Control of the CPU to:
  - halt/resume
  - access GPRs/CSRs
  - access memory (system bus access or abstract command)

Right now, `rtl/peripherals/debug/debug_apb.sv` is a custom mailbox and is not compatible with OpenOCD’s RISC-V DM expectations.

### 4.2 Typical integration approach

- Replace (or sit alongside) the mailbox with a standard DM.
- Keep the JTAG TAP/DTM you already have; wire its DMI transactions into the DM.
- Once DM is in place, your OpenOCD config changes to something like:

```tcl
jtag newtap riscv cpu -irlen 5 -expected-id 0x10005001
set _TARGETNAME riscv.cpu

target create $_TARGETNAME riscv -chain-position $_TARGETNAME
riscv set_prefer_sba on
init
halt
```

Only do this after DM is implemented; otherwise OpenOCD will fail during `init`/`halt`.

---

## 5) Quick “works today” alternative: use the Boot ROM debug monitor

Your boot firmware (`firmware/boot/boot_rom.c`) contains a debug monitor loop that polls the APB debug mailbox and can read/write arbitrary memory.

That means you can:

- Boot into debug monitor (when flash boot fails or when you intentionally stay in monitor).
- Use a host tool (can be OpenOCD Tcl, a Python script, or even a custom JTAG tool) to poke debug mailbox registers.

If you want, I can add a small host-side script under `scripts/` to talk to the mailbox via JTAG using OpenOCD telnet commands.

---

## 6) Troubleshooting checklist

- `scan_chain` fails: lower `adapter speed`, verify `Vref`, check `TDO` direction and ground.
- IDCODE mismatch: confirm you used the right TAP name (`riscv.cpu`) and that no other TAPs exist in the chain.
- Unstable shifting: shorten wires, add series resistors on TCK/TMS if needed, slow clock.

