// =============================================================================
// soc_smoke_seq.sv - SoC smoke sequence
// Purpose : Touches all five peripherals (UART, Timer, GPIO, SPI, Debug) with
//           reads and writes to achieve full functional coverage including the
//           PSLVERR error path (via the GPIO invalid-offset access).
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================

class soc_smoke_seq extends apb_base_seq;
    `uvm_object_utils(soc_smoke_seq)

    rand bit [31:0] dbg_cmd;

    function new(string name = "soc_smoke_seq");
        super.new(name);
    endfunction

    task body();
        bit [31:0] rd; bit err;
        uart_seq  us;
        timer_seq ts;
        gpio_seq  gs;
        spi_seq   ss;

        if (!this.randomize()) `uvm_error("SMOKE", "randomize failed")

        us = uart_seq::type_id::create("us");   us.start(m_sequencer);
        ts = timer_seq::type_id::create("ts");  ts.start(m_sequencer);
        gs = gpio_seq::type_id::create("gs");   gs.start(m_sequencer);
        ss = spi_seq::type_id::create("ss");    ss.start(m_sequencer);

        // ---- Debug mailbox ----
        read32(`DBG_ID, rd, err);
        if (rd !== 32'h4442_4731)
            `uvm_error("SMOKE", $sformatf("debug ID mismatch: 0x%08h", rd))
        write32(`DBG_CMD, dbg_cmd);
        read32 (`DBG_CMD, rd, err);  // scoreboard checks vs shadow

        `uvm_info("SMOKE", "SoC smoke sequence complete", UVM_LOW)
    endtask

endclass
