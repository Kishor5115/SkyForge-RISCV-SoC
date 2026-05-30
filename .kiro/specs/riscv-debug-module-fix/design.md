# RISC-V Debug Module dmactive Fix Design

## Overview

This design addresses a critical bug in the RISC-V Debug Module where the `dmactive` bit in the `dmcontrol` register fails to latch writes from OpenOCD via the JTAG Debug Transport Module (DTM). The root cause is the absence of proper Clock Domain Crossing (CDC) logic between the JTAG clock domain (TCK) and the system clock domain (clk_i).

The current implementation directly uses JTAG-domain signals (`jtag_valid`, `jtag_write`, `jtag_addr`, `jtag_wdata`) in system-clock-domain sequential logic without synchronization, leading to metastability, setup/hold violations, and unreliable register writes. This prevents OpenOCD from activating the Debug Module, blocking all debugging operations.

The fix implements a proper CDC mechanism using a request-acknowledge handshake protocol with multi-stage synchronizers to safely transfer DMI transactions from the JTAG clock domain to the system clock domain, ensuring reliable dmactive bit latching and full Debug Spec 0.13 compliance.

## Glossary

- **Bug_Condition (C)**: DMI write transactions from JTAG clock domain fail to reliably update Debug Module registers in the system clock domain due to missing CDC logic
- **Property (P)**: DMI write transactions shall be reliably transferred across clock domains and update Debug Module registers with 100% correctness
- **Preservation**: All existing Debug Module functionality (register reads, abstract commands, SBA operations, APB access) must remain unchanged
- **debug_dm.sv**: The Debug Module RTL file at `rtl/peripherals/debug/debug_dm.sv` that implements Debug Spec 0.13 registers and control logic
- **JTAG_Clock_Domain**: The clock domain running at JTAG TCK frequency (typically 1-10 MHz) where the JTAG DTM operates
- **System_Clock_Domain**: The clock domain running at system clock frequency (clk_i, typically 50-100 MHz) where the Debug Module operates
- **CDC**: Clock Domain Crossing - the mechanism for safely transferring signals between asynchronous clock domains
- **Metastability**: An unstable state when a flip-flop samples a signal during a clock edge transition, violating setup/hold timing
- **Handshake_Protocol**: A request-acknowledge mechanism ensuring data stability during clock domain crossing
- **Multi-Stage_Synchronizer**: A chain of flip-flops (typically 2-3 stages) used to synchronize control signals across clock domains

## Bug Details

### Bug Condition

The bug manifests when OpenOCD writes to any Debug Module register (particularly dmcontrol) via the JTAG DTM. The `debug_dm.sv` module directly uses JTAG-domain signals in system-clock-domain sequential logic without synchronization, causing metastability and unreliable register updates.

**Formal Specification:**
```
FUNCTION isBugCondition(input)
  INPUT: input of type DMI_Transaction
  OUTPUT: boolean
  
  RETURN input.source == JTAG_DTM
         AND input.operation == WRITE
         AND input.target_register IN [DM_DMCONTROL, DM_DATA0, DM_COMMAND, DM_SBCS, DM_SBADDRESS0, DM_SBDATA0]
         AND NOT hasCDCLogic(input.path)
END FUNCTION
```

**Current Buggy Implementation:**
```systemverilog
// Lines 95-98 in debug_dm.sv - BUGGY: Direct use of JTAG signals in system clock domain
assign bus_write = (psel && penable && pwrite) || (jtag_valid && jtag_write);
assign bus_read  = (psel && penable && !pwrite) || (jtag_valid && !jtag_write);
assign bus_addr  = (psel && penable) ? paddr[8:2] : jtag_addr[6:0];
assign bus_wdata = (psel && penable) ? pwdata : jtag_wdata;
```

The `jtag_valid`, `jtag_write`, `jtag_addr`, and `jtag_wdata` signals originate from the JTAG clock domain but are used directly in combinational logic that feeds system-clock-domain flip-flops (lines 127-220), violating fundamental CDC design rules.

### Examples

- **Example 1**: OpenOCD writes `dmcontrol = 0x00000001` (dmactive=1) via JTAG. Due to metastability, the system clock domain samples an undefined value, and dmactive remains 0. OpenOCD reads back `dmcontrol = 0x00000000` and reports "Debug Module did not become active."

- **Example 2**: OpenOCD writes `command = 0x00231000` (Access Register read x1) via JTAG. The command register in the system clock domain receives a corrupted value due to setup/hold violations, causing cmderr to be set or the command to be ignored.

- **Example 3**: OpenOCD writes `sbaddress0 = 0x20000000` with sbreadonaddr=1 to initiate a System Bus Access read. The address is corrupted during clock domain crossing, causing an AXI transaction to an incorrect address or no transaction at all.

- **Edge Case**: If JTAG TCK and system clock have a near-integer frequency ratio, the metastability window may align periodically, causing intermittent failures that are difficult to reproduce and debug.

## Expected Behavior

### Preservation Requirements

**Unchanged Behaviors:**
- APB4 slave interface access to Debug Module registers must continue to work exactly as before (APB transactions are already in the system clock domain)
- Abstract command execution for GPR access must remain unchanged in functionality and timing
- System Bus Access (SBA) AXI-lite master operations must remain unchanged in functionality and timing
- Debug core control signals (dbg_halt_req, dbg_resume_req, dbg_reg_write, dbg_reg_read) must maintain their current behavior
- Register read operations via JTAG must continue to work (reads require CDC for response path)
- All Debug Module register addresses, bit fields, and semantics must remain compliant with Debug Spec 0.13

**Scope:**
All inputs that do NOT involve JTAG DMI transactions should be completely unaffected by this fix. This includes:
- APB4 slave interface transactions (psel, penable, pwrite, paddr, pwdata)
- Debug core interface signals (dbg_halted, dbg_reg_rdata)
- AXI-lite master interface signals (dbg_axi_*)
- Reset behavior (resetn)

## Hypothesized Root Cause

Based on the bug description and RTL analysis, the root cause is:

1. **Missing CDC Logic**: The module directly uses JTAG-domain signals (`jtag_valid`, `jtag_write`, `jtag_addr`, `jtag_wdata`) in system-clock-domain sequential logic without any synchronization mechanism. This violates the fundamental rule that signals crossing clock domains must be synchronized.

2. **Metastability Risk**: When the system clock samples `jtag_valid` or other JTAG signals during a transition, the flip-flop can enter a metastable state, producing an undefined logic level that may propagate through the design, causing unpredictable behavior.

3. **Setup/Hold Violations**: The JTAG signals may change at arbitrary times relative to the system clock edge, violating setup and hold timing requirements for the system-clock-domain flip-flops that sample them.

4. **Data Corruption**: Multi-bit signals like `jtag_addr[6:0]` and `jtag_wdata[31:0]` can be corrupted if individual bits are sampled at different system clock edges while the JTAG-domain source is changing, leading to incorrect register addresses or data values.

## Correctness Properties

Property 1: Bug Condition - Reliable DMI Write Transaction Transfer

_For any_ DMI write transaction from the JTAG clock domain where the transaction is valid (jtag_valid=1, jtag_write=1) and targets a Debug Module register, the fixed debug_dm module SHALL reliably transfer the transaction to the system clock domain using proper CDC mechanisms, and the target register SHALL be updated with the correct write data within a bounded number of system clock cycles.

**Validates: Requirements 1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 2.4**

Property 2: Preservation - Non-JTAG Interface Behavior

_For any_ input transaction that does NOT originate from the JTAG DMI interface (i.e., APB4 transactions, debug core interface signals, AXI-lite responses), the fixed debug_dm module SHALL produce exactly the same behavior as the original module, preserving all register access, abstract command execution, and System Bus Access functionality.

**Validates: Requirements 1.5, 3.1, 3.2, 3.3, 3.4, 4.1, 4.2, 4.3, 4.4, 5.1, 5.2, 5.3, 6.1, 6.2, 6.3, 7.1, 7.2, 7.3**

## Fix Implementation

### Changes Required

Assuming our root cause analysis is correct:

**File**: `rtl/peripherals/debug/debug_dm.sv`

**Module**: `debug_dm`

**Specific Changes**:

1. **Add CDC State Machine in JTAG Clock Domain**:
   - Add a state machine clocked by JTAG TCK to capture DMI transactions
   - Latch `jtag_addr`, `jtag_wdata`, `jtag_wstrb`, and `jtag_write` when `jtag_valid` is asserted
   - Assert a `jtag_req` signal to initiate the handshake with the system clock domain
   - Wait for synchronized `sys_ack` signal before clearing `jtag_req` and asserting `jtag_ready`

2. **Add Multi-Stage Synchronizers for Control Signals**:
   - Implement a 2-stage or 3-stage synchronizer to transfer `jtag_req` from JTAG clock domain to system clock domain (producing `jtag_req_sync`)
   - Implement a 2-stage or 3-stage synchronizer to transfer `sys_ack` from system clock domain to JTAG clock domain (producing `sys_ack_sync`)
   - Use `(* ASYNC_REG = "TRUE" *)` attribute (for Xilinx) or equivalent to prevent optimization of synchronizer flip-flops

3. **Add CDC State Machine in System Clock Domain**:
   - Add a state machine clocked by system clock to detect `jtag_req_sync` assertion
   - When `jtag_req_sync` is detected, latch the synchronized transaction data and perform the register write
   - Assert `sys_ack` to acknowledge completion
   - Wait for `jtag_req_sync` to deassert before clearing `sys_ack`

4. **Modify Bus Decode Logic**:
   - Change `bus_write` and `bus_read` to use CDC-synchronized signals for JTAG path
   - Keep APB path unchanged (already in system clock domain)
   - Ensure `bus_addr`, `bus_wdata`, and `bus_wstrb` use latched, synchronized values for JTAG transactions

5. **Add Data Path Synchronization**:
   - Add registers in the JTAG clock domain to hold `jtag_addr_latched`, `jtag_wdata_latched`, `jtag_wstrb_latched`, `jtag_write_latched`
   - Add registers in the system clock domain to hold `jtag_addr_sync`, `jtag_wdata_sync`, `jtag_wstrb_sync`, `jtag_write_sync`
   - Transfer multi-bit data only when handshake is stable (req asserted, data stable, then ack)

6. **Handle Read Transactions**:
   - For JTAG read transactions, capture the read address in JTAG clock domain
   - Transfer read request to system clock domain via handshake
   - Perform register read in system clock domain and latch result
   - Transfer read data back to JTAG clock domain via reverse handshake or Gray-coded FIFO
   - Assert `jtag_ready` with valid `jtag_rdata` in JTAG clock domain

7. **Update jtag_ready Signal**:
   - `jtag_ready` should be asserted in the JTAG clock domain only after the transaction completes
   - For writes: assert after `sys_ack_sync` is received
   - For reads: assert after read data is available in JTAG clock domain

## Testing Strategy

### Validation Approach

The testing strategy follows a two-phase approach: first, surface counterexamples that demonstrate the bug on unfixed code by observing metastability and unreliable register writes, then verify the fix works correctly with proper CDC and preserves existing APB-based functionality.

### Exploratory Bug Condition Checking

**Goal**: Surface counterexamples that demonstrate the bug BEFORE implementing the fix. Confirm or refute the root cause analysis (missing CDC logic). If we refute, we will need to re-hypothesize.

**Test Plan**: Write SystemVerilog testbenches that simulate OpenOCD's JTAG DMI write transactions to the dmcontrol register. Run these tests on the UNFIXED code with different clock frequency ratios and phase relationships to observe metastability, setup/hold violations, and unreliable register updates.

**Test Cases**:
1. **dmcontrol Write Test**: Simulate OpenOCD writing dmactive=1 via JTAG with JTAG TCK at 1 MHz and system clock at 50 MHz. Observe that dmactive fails to latch reliably (will fail on unfixed code).
2. **Clock Ratio Sweep Test**: Repeat dmcontrol write with various TCK:clk ratios (1:10, 1:50, 1:100) and random phase offsets. Observe intermittent failures and metastability (will fail on unfixed code).
3. **Multi-Bit Data Corruption Test**: Write different values to data0 register via JTAG and read back. Observe bit corruption due to sampling different bits at different clock edges (will fail on unfixed code).
4. **Rapid Transaction Test**: Issue back-to-back JTAG writes to multiple registers. Observe lost transactions or incorrect register updates (will fail on unfixed code).

**Expected Counterexamples**:
- dmactive bit reads back as 0 after writing 1 via JTAG
- Register values are corrupted (e.g., write 0xDEADBEEF, read back 0xDEADBEEE or other corrupted value)
- Intermittent failures that depend on clock phase relationship
- Possible causes: metastability, setup/hold violations, missing CDC handshake, data path corruption

### Fix Checking

**Goal**: Verify that for all inputs where the bug condition holds (JTAG DMI write transactions), the fixed function produces the expected behavior (reliable register updates with proper CDC).

**Pseudocode:**
```
FOR ALL input WHERE isBugCondition(input) DO
  result := debug_dm_fixed.process_jtag_write(input)
  ASSERT result.register_updated == TRUE
  ASSERT result.register_value == input.write_data
  ASSERT result.no_metastability == TRUE
  ASSERT result.completion_time <= MAX_CDC_LATENCY
END FOR
```

**Test Plan**: After implementing CDC logic, run the same test cases on the FIXED code and verify:
- dmactive=1 write via JTAG always succeeds and reads back as 1
- Multi-bit register writes are never corrupted
- All JTAG write transactions complete successfully regardless of clock ratio or phase
- CDC handshake completes within expected latency (e.g., 5-10 system clock cycles)

### Preservation Checking

**Goal**: Verify that for all inputs where the bug condition does NOT hold (APB transactions, debug core signals, AXI responses), the fixed function produces the same result as the original function.

**Pseudocode:**
```
FOR ALL input WHERE NOT isBugCondition(input) DO
  ASSERT debug_dm_original(input) = debug_dm_fixed(input)
END FOR
```

**Testing Approach**: Property-based testing is recommended for preservation checking because:
- It generates many test cases automatically across the input domain
- It catches edge cases that manual unit tests might miss
- It provides strong guarantees that behavior is unchanged for all non-JTAG inputs

**Test Plan**: Observe behavior on UNFIXED code first for APB transactions and other interfaces, then write property-based tests capturing that behavior.

**Test Cases**:
1. **APB Write Preservation**: Observe that APB writes to dmcontrol, data0, command, etc. work correctly on unfixed code. Write property-based tests to verify this continues after CDC fix.
2. **Abstract Command Preservation**: Observe that abstract commands (Access Register) work correctly via APB on unfixed code. Verify this continues after fix.
3. **SBA Preservation**: Observe that System Bus Access operations work correctly via APB on unfixed code. Verify this continues after fix.
4. **Debug Core Interface Preservation**: Observe that dbg_halt_req, dbg_resume_req, dbg_reg_write, dbg_reg_read signals behave correctly on unfixed code. Verify this continues after fix.

### Unit Tests

- Test CDC handshake protocol with various clock ratios (1:10, 1:50, 1:100)
- Test CDC handshake with random phase offsets between JTAG TCK and system clock
- Test back-to-back JTAG transactions to verify handshake doesn't drop transactions
- Test JTAG write to each Debug Module register (dmcontrol, data0, command, sbcs, sbaddress0, sbdata0)
- Test JTAG read from each Debug Module register
- Test APB write and read to each register (preservation)
- Test edge cases: JTAG transaction during system reset, system transaction during JTAG reset

### Property-Based Tests

- Generate random JTAG write transactions (random addresses, random data, random timing) and verify all complete successfully with correct register updates
- Generate random APB transactions and verify behavior is identical between original and fixed modules
- Generate random sequences of mixed JTAG and APB transactions and verify correct interleaving and no interference
- Generate random clock frequency ratios and phase offsets and verify CDC always works correctly

### Integration Tests

- Test full OpenOCD connection sequence: IDCODE read, dmcontrol write (dmactive=1), dmstatus read, verify dmactive=1
- Test OpenOCD halt sequence: write haltreq=1 via JTAG, verify dbg_halt_req asserted, verify dmstatus reports halted
- Test OpenOCD register read sequence: halt core, write Access Register command via JTAG, read data0 via JTAG, verify correct GPR value
- Test OpenOCD register write sequence: halt core, write data0 via JTAG, write Access Register command via JTAG, verify GPR updated
- Test OpenOCD System Bus Access: write sbaddress0 via JTAG with sbreadonaddr=1, verify AXI read transaction, read sbdata0 via JTAG, verify correct memory value
- Test mixed APB and JTAG access: write dmcontrol via APB, write command via JTAG, verify both work correctly
- Test OpenOCD breakpoint flow: set breakpoint via SBA write, run code, halt at breakpoint, read registers, resume
