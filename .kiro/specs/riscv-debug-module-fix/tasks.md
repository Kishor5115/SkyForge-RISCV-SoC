# Implementation Plan

## Overview

This implementation plan follows the exploratory bugfix workflow using the bug condition methodology. The tasks are ordered to:
1. **Explore** - Write tests BEFORE fix to understand the bug (Bug Condition)
2. **Preserve** - Write tests for non-buggy behavior (Preservation Requirements)
3. **Implement** - Apply the fix with understanding (Expected Behavior)
4. **Validate** - Verify fix works and doesn't break anything

## Tasks

- [x] 1. Write bug condition exploration test
  - **Property 1: Bug Condition** - DMI Write Transaction Failure Due to Missing CDC
  - **CRITICAL**: This test MUST FAIL on unfixed code - failure confirms the bug exists
  - **DO NOT attempt to fix the test or the code when it fails**
  - **NOTE**: This test encodes the expected behavior - it will validate the fix when it passes after implementation
  - **GOAL**: Surface counterexamples that demonstrate the bug exists
  - **Scoped PBT Approach**: Scope the property to concrete failing cases: JTAG DMI write to dmcontrol with dmactive=1
  - Create SystemVerilog testbench `tb_debug_dm_cdc_bug.sv` in `rtl/peripherals/debug/`
  - Test implementation details from Bug Condition in design:
    - Instantiate `debug_dm` module with JTAG clock (TCK at 1 MHz) and system clock (clk_i at 50 MHz)
    - Drive `jtag_valid=1`, `jtag_write=1`, `jtag_addr=7'h10` (dmcontrol), `jtag_wdata=32'h00000001` (dmactive=1)
    - Wait for `jtag_ready` assertion in JTAG clock domain
    - Read back dmcontrol register via JTAG: drive `jtag_valid=1`, `jtag_write=0`, `jtag_addr=7'h10`
    - Assert that `jtag_rdata[0]` (dmactive bit) equals 1
  - The test assertions should match the Expected Behavior Properties from design:
    - Register shall be updated with correct write data
    - No metastability shall occur
    - Transaction shall complete within bounded time
  - Run test on UNFIXED code with various clock ratios (1:10, 1:50, 1:100) and random phase offsets
  - **EXPECTED OUTCOME**: Test FAILS (this is correct - it proves the bug exists)
  - Document counterexamples found:
    - dmactive reads back as 0 after writing 1
    - Intermittent failures depending on clock phase
    - Possible metastability or setup/hold violations
  - Mark task complete when test is written, run, and failure is documented
  - _Requirements: 1.1, 1.2, 1.3, 2.1, 2.3_

- [ ] 2. Write preservation property tests (BEFORE implementing fix)
  - **Property 2: Preservation** - Non-JTAG Interface Behavior Unchanged
  - **IMPORTANT**: Follow observation-first methodology
  - Observe behavior on UNFIXED code for non-buggy inputs (APB transactions, debug core signals)
  - Create SystemVerilog testbench `tb_debug_dm_preservation.sv` in `rtl/peripherals/debug/`
  - Write property-based tests capturing observed behavior patterns from Preservation Requirements:
    - **APB Write Preservation**: For all APB write transactions (psel=1, penable=1, pwrite=1) to any Debug Module register, observe that register is updated correctly on unfixed code. Write property asserting this behavior continues.
    - **APB Read Preservation**: For all APB read transactions (psel=1, penable=1, pwrite=0) from any Debug Module register, observe that correct data is returned on unfixed code. Write property asserting this behavior continues.
    - **Abstract Command Preservation**: Observe that Access Register commands via APB work correctly on unfixed code (write command register, read data0). Write property asserting this behavior continues.
    - **Debug Core Interface Preservation**: Observe that dbg_halt_req, dbg_resume_req, dbg_reg_write, dbg_reg_read signals respond correctly to APB writes on unfixed code. Write property asserting this behavior continues.
    - **System Bus Access Preservation**: Observe that SBA operations via APB work correctly on unfixed code (write sbaddress0, observe AXI transaction). Write property asserting this behavior continues.
  - Property-based testing generates many test cases for stronger guarantees
  - Run tests on UNFIXED code
  - **EXPECTED OUTCOME**: Tests PASS (this confirms baseline behavior to preserve)
  - Mark task complete when tests are written, run, and passing on unfixed code
  - _Requirements: 1.5, 3.1, 3.2, 3.3, 4.1, 4.2, 4.3, 4.4, 5.1, 5.2, 5.3, 6.1, 6.2, 6.3, 7.1, 7.2, 7.3_

- [ ] 3. Implement CDC logic for JTAG DMI transactions

  - [~] 3.1 Add CDC state machine in JTAG clock domain
    - Add state machine clocked by JTAG TCK to capture DMI transactions
    - States: IDLE, REQ_PENDING, WAIT_ACK
    - In IDLE state: when `jtag_valid` asserts, latch `jtag_addr`, `jtag_wdata`, `jtag_wstrb`, `jtag_write` into registers
    - Transition to REQ_PENDING: assert `jtag_req` signal to initiate handshake
    - In WAIT_ACK state: wait for synchronized `sys_ack_sync` signal
    - When `sys_ack_sync` asserts: clear `jtag_req`, assert `jtag_ready`, transition to IDLE
    - Add registers: `jtag_addr_latched[6:0]`, `jtag_wdata_latched[31:0]`, `jtag_wstrb_latched[3:0]`, `jtag_write_latched`
    - Add control signals: `jtag_req` (output to synchronizer), `sys_ack_sync` (input from synchronizer)
    - _Bug_Condition: isBugCondition(input) where input.source == JTAG_DTM AND input.operation == WRITE_
    - _Expected_Behavior: DMI write transactions shall be reliably transferred across clock domains_
    - _Preservation: APB transactions and debug core signals shall remain unchanged_
    - _Requirements: 1.1, 1.2, 2.1, 2.4_

  - [~] 3.2 Add multi-stage synchronizers for control signals
    - Implement 3-stage synchronizer for `jtag_req` signal (JTAG clock domain → system clock domain)
    - Create registers: `jtag_req_sync1`, `jtag_req_sync2`, `jtag_req_sync` (all clocked by clk_i)
    - Add `(* ASYNC_REG = "TRUE" *)` attribute to prevent optimization
    - Implement 3-stage synchronizer for `sys_ack` signal (system clock domain → JTAG clock domain)
    - Create registers: `sys_ack_sync1`, `sys_ack_sync2`, `sys_ack_sync` (all clocked by JTAG TCK)
    - Add `(* ASYNC_REG = "TRUE" *)` attribute to prevent optimization
    - Ensure synchronizer flip-flops have no combinational logic in data path
    - _Bug_Condition: Missing synchronization causes metastability_
    - _Expected_Behavior: Multi-stage synchronizers prevent metastability_
    - _Preservation: No impact on APB path (already in system clock domain)_
    - _Requirements: 2.3, 2.4_

  - [~] 3.3 Add CDC state machine in system clock domain
    - Add state machine clocked by system clock (clk_i) to detect `jtag_req_sync` assertion
    - States: IDLE, PROCESS_REQ, ACK_PENDING
    - In IDLE state: when `jtag_req_sync` asserts, transition to PROCESS_REQ
    - In PROCESS_REQ state: latch synchronized transaction data into system clock domain registers
    - Latch `jtag_addr_sync`, `jtag_wdata_sync`, `jtag_wstrb_sync`, `jtag_write_sync` from JTAG domain latches (use direct assignment since data is stable during handshake)
    - Perform register write using latched data
    - Assert `sys_ack` signal, transition to ACK_PENDING
    - In ACK_PENDING state: wait for `jtag_req_sync` to deassert
    - When `jtag_req_sync` deasserts: clear `sys_ack`, transition to IDLE
    - Add registers: `jtag_addr_sync[6:0]`, `jtag_wdata_sync[31:0]`, `jtag_wstrb_sync[3:0]`, `jtag_write_sync`
    - Add control signals: `jtag_req_sync` (input from synchronizer), `sys_ack` (output to synchronizer)
    - _Bug_Condition: Direct use of JTAG signals in system clock domain causes corruption_
    - _Expected_Behavior: System clock domain processes stable, synchronized data_
    - _Preservation: APB path continues to work unchanged_
    - _Requirements: 1.1, 1.2, 1.3, 2.1, 2.2, 2.4_

  - [~] 3.4 Modify bus decode logic to use CDC-synchronized signals
    - Update `bus_write` assignment (line 95):
      - Old: `assign bus_write = (psel && penable && pwrite) || (jtag_valid && jtag_write);`
      - New: `assign bus_write = (psel && penable && pwrite) || (jtag_write_sync && sys_state == PROCESS_REQ);`
    - Update `bus_read` assignment (line 96):
      - Old: `assign bus_read = (psel && penable && !pwrite) || (jtag_valid && !jtag_write);`
      - New: `assign bus_read = (psel && penable && !pwrite) || (!jtag_write_sync && sys_state == PROCESS_REQ);`
    - Update `bus_addr` assignment (line 97):
      - Old: `assign bus_addr = (psel && penable) ? paddr[8:2] : jtag_addr[6:0];`
      - New: `assign bus_addr = (psel && penable) ? paddr[8:2] : jtag_addr_sync[6:0];`
    - Update `bus_wdata` assignment (line 98):
      - Old: `assign bus_wdata = (psel && penable) ? pwdata : jtag_wdata;`
      - New: `assign bus_wdata = (psel && penable) ? pwdata : jtag_wdata_sync;`
    - Ensure APB path logic remains unchanged (first part of ternary operators)
    - _Bug_Condition: Direct use of unsynchronized JTAG signals_
    - _Expected_Behavior: Bus decode uses stable, synchronized signals for JTAG path_
    - _Preservation: APB path unchanged (psel && penable conditions)_
    - _Requirements: 1.1, 1.2, 2.1, 2.2_

  - [~] 3.5 Implement JTAG read transaction handling
    - Extend JTAG clock domain state machine to handle read transactions
    - When `jtag_valid=1` and `jtag_write=0`: latch `jtag_addr`, assert `jtag_req` for read
    - System clock domain state machine: when processing read request, perform register read and latch result in `sys_rdata_latched[31:0]`
    - Add reverse data path: transfer `sys_rdata_latched` back to JTAG clock domain
    - Use same handshake protocol: system clock domain asserts `sys_ack` when read data is ready
    - JTAG clock domain: when `sys_ack_sync` asserts, latch `sys_rdata_latched` into `jtag_rdata` register
    - Assert `jtag_ready` with valid `jtag_rdata` in JTAG clock domain
    - Add registers: `sys_rdata_latched[31:0]` (system clock domain), `jtag_rdata[31:0]` (JTAG clock domain)
    - _Bug_Condition: Read transactions also require CDC for response path_
    - _Expected_Behavior: Read data reliably transferred from system to JTAG clock domain_
    - _Preservation: APB read path unchanged_
    - _Requirements: 2.2, 2.4, 6.1_

  - [~] 3.6 Update jtag_ready signal generation
    - `jtag_ready` should be asserted in JTAG clock domain only after transaction completes
    - For write transactions: assert `jtag_ready` when `sys_ack_sync` is received and state returns to IDLE
    - For read transactions: assert `jtag_ready` when `sys_ack_sync` is received and `jtag_rdata` is valid
    - Ensure `jtag_ready` is deasserted when new transaction starts (`jtag_valid` asserts)
    - Add logic to pulse `jtag_ready` for one JTAG clock cycle after transaction completion
    - _Bug_Condition: Premature jtag_ready assertion causes data corruption_
    - _Expected_Behavior: jtag_ready asserts only when transaction fully completes_
    - _Preservation: No impact on APB path_
    - _Requirements: 2.4, 2.5_

  - [~] 3.7 Verify bug condition exploration test now passes
    - **Property 1: Expected Behavior** - DMI Write Transaction Reliable Transfer
    - **IMPORTANT**: Re-run the SAME test from task 1 - do NOT write a new test
    - The test from task 1 encodes the expected behavior
    - When this test passes, it confirms the expected behavior is satisfied
    - Run bug condition exploration test `tb_debug_dm_cdc_bug.sv` from step 1
    - Verify dmactive=1 write via JTAG succeeds and reads back as 1
    - Verify test passes with all clock ratios (1:10, 1:50, 1:100) and random phase offsets
    - Verify no metastability or data corruption occurs
    - Verify CDC handshake completes within expected latency (5-10 system clock cycles)
    - **EXPECTED OUTCOME**: Test PASSES (confirms bug is fixed)
    - _Requirements: 1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 2.4_

  - [~] 3.8 Verify preservation tests still pass
    - **Property 2: Preservation** - Non-JTAG Interface Behavior Unchanged
    - **IMPORTANT**: Re-run the SAME tests from task 2 - do NOT write new tests
    - Run preservation property tests `tb_debug_dm_preservation.sv` from step 2
    - Verify all APB write transactions continue to work correctly
    - Verify all APB read transactions continue to work correctly
    - Verify abstract commands via APB continue to work correctly
    - Verify debug core interface signals continue to work correctly
    - Verify System Bus Access via APB continues to work correctly
    - **EXPECTED OUTCOME**: Tests PASS (confirms no regressions)
    - Confirm all tests still pass after fix (no regressions)
    - _Requirements: 1.5, 3.1, 3.2, 3.3, 4.1, 4.2, 4.3, 4.4, 5.1, 5.2, 5.3, 6.1, 6.2, 6.3, 7.1, 7.2, 7.3_

- [ ] 4. Integration testing with OpenOCD and GDB

  - [~] 4.1 Test OpenOCD connection and dmactive activation
    - Build FPGA bitstream with fixed debug_dm module
    - Program FPGA and connect OpenOCD via JTAG
    - Run OpenOCD with configuration: `openocd -f interface/ftdi/digilent-hs1.cfg -f target/riscv-custom.cfg`
    - Verify OpenOCD successfully reads IDCODE
    - Verify OpenOCD writes dmactive=1 and reads back dmactive=1
    - Verify OpenOCD reports "Debug Module became active"
    - Verify dmstatus register reports correct version and hart status
    - _Requirements: 1.1, 1.2, 1.3, 8.1, 8.2_

  - [~] 4.2 Test OpenOCD halt and resume operations
    - With OpenOCD connected and dmactive=1, issue halt command: `halt`
    - Verify OpenOCD reports "hart 0 halted"
    - Verify dmstatus register reports allhalted=1
    - Issue resume command: `resume`
    - Verify OpenOCD reports "hart 0 resumed"
    - Verify dmstatus register reports allrunning=1
    - _Requirements: 4.1, 4.2, 4.3, 4.4, 6.1, 6.2, 6.3_

  - [~] 4.3 Test OpenOCD register read and write
    - Halt the core via OpenOCD
    - Read general-purpose registers: `reg x1`, `reg x2`, etc.
    - Verify OpenOCD returns correct register values
    - Write to a register: `reg x1 0xDEADBEEF`
    - Read back the register: `reg x1`
    - Verify the written value is returned
    - _Requirements: 5.1, 5.2, 5.3, 8.3_

  - [~] 4.4 Test OpenOCD System Bus Access
    - With OpenOCD connected, read memory via SBA: `mdw 0x20000000`
    - Verify OpenOCD returns correct memory contents
    - Write memory via SBA: `mww 0x20000000 0x12345678`
    - Read back memory: `mdw 0x20000000`
    - Verify the written value is returned
    - _Requirements: 7.1, 7.2, 7.3, 7.4_

  - [~] 4.5 Test GDB breakpoint on FreeRTOS vTaskA
    - Load FreeRTOS firmware with vTaskA and vTaskB tasks
    - Connect GDB to OpenOCD: `riscv32-unknown-elf-gdb firmware.elf -ex "target remote :3333"`
    - Set breakpoint on vTaskA: `break vTaskA`
    - Continue execution: `continue`
    - Verify GDB halts at breakpoint in vTaskA
    - Inspect task state: `info registers`, `backtrace`
    - Verify register values and stack trace are correct
    - Continue execution: `continue`
    - Verify FreeRTOS continues normal operation and vTaskA executes again
    - _Requirements: 8.4, 8.5_

- [~] 5. Checkpoint - Ensure all tests pass
  - Run all unit tests (bug condition exploration, preservation tests)
  - Run all integration tests (OpenOCD connection, halt/resume, register access, SBA, GDB breakpoint)
  - Verify no regressions in existing functionality
  - Verify CDC logic works correctly with all clock ratios and phase offsets
  - Verify OpenOCD and GDB can successfully debug FreeRTOS applications
  - Document any issues or edge cases discovered
  - If any tests fail, investigate root cause and iterate on fix
  - Ask the user if questions arise

## Task Dependency Graph

```json
{
  "waves": [
    {
      "name": "Exploration Phase",
      "tasks": ["1", "2"]
    },
    {
      "name": "Implementation Phase",
      "tasks": ["3"]
    },
    {
      "name": "Integration Phase",
      "tasks": ["4"]
    },
    {
      "name": "Validation Phase",
      "tasks": ["5"]
    }
  ],
  "dependencies": {
    "3": ["1", "2"],
    "4": ["3"],
    "5": ["4"]
  }
}
```

## Notes

- The bug condition exploration test (task 1) is expected to FAIL on unfixed code - this confirms the bug exists
- The preservation tests (task 2) are expected to PASS on unfixed code - this establishes the baseline behavior to preserve
- After implementing the CDC fix (task 3), the bug condition test should PASS and preservation tests should still PASS
- Integration testing (task 4) validates the fix in the real system with OpenOCD and GDB
- The checkpoint (task 5) ensures all tests pass before considering the fix complete
