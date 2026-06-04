// =============================================================================
// soc_uvm_pkg.sv - Top-level UVM package for the RISC-V SoC environment
// Purpose : Imports uvm_pkg and includes the register model, APB agent,
//           scoreboard, coverage, environment, sequences and tests in
//           dependency order. Compile with +incdir+<uvm root>.
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================
`ifndef SOC_UVM_PKG_SV
`define SOC_UVM_PKG_SV

package soc_uvm_pkg;

    `include "uvm_macros.svh"
    import uvm_pkg::*;

    // Shared address macros
    `include "env/soc_addr.svh"

    // Register model
    `include "env/reg_model.sv"

    // Agent building blocks
    `include "env/apb_seq_item.sv"
    `include "env/apb_coverage.sv"
    `include "env/apb_sequencer.sv"
    `include "env/apb_driver.sv"
    `include "env/apb_monitor.sv"
    `include "env/apb_agent.sv"
    `include "env/apb_scoreboard.sv"
    `include "env/soc_env.sv"

    // Sequences
    `include "seq/apb_base_seq.sv"
    `include "seq/uart_seq.sv"
    `include "seq/gpio_seq.sv"
    `include "seq/timer_seq.sv"
    `include "seq/spi_seq.sv"
    `include "seq/soc_smoke_seq.sv"
    `include "seq/soc_stress_seq.sv"

    // Tests
    `include "tests/soc_base_test.sv"
    `include "tests/uart_test.sv"
    `include "tests/gpio_test.sv"
    `include "tests/timer_test.sv"
    `include "tests/spi_test.sv"
    `include "tests/soc_smoke_test.sv"
    `include "tests/soc_stress_test.sv"

endpackage

`endif // SOC_UVM_PKG_SV
