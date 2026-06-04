// =============================================================================
// uart_seq.sv - UART exercise sequence
// Purpose : Randomized baud-rate / control configuration, TX byte push and
//           CTRL/STATUS readback.
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================

class uart_seq extends apb_base_seq;
    `uvm_object_utils(uart_seq)

    rand bit [15:0] baud;
    rand bit        tx_en;
    rand bit        rx_en;
    rand bit        irq_en;
    rand bit [7:0]  tx_byte;

    constraint c_baud { baud inside {[16'd1 : 16'd2000]}; }

    function new(string name = "uart_seq");
        super.new(name);
    endfunction

    task body();
        bit [31:0] rd; bit err;
        bit [31:0] ctrl;
        if (!this.randomize()) `uvm_error("UART_SEQ", "randomize failed")
        ctrl = {13'h0, irq_en, rx_en, tx_en, baud};
        `uvm_info("UART_SEQ", $sformatf("config CTRL=0x%08h", ctrl), UVM_MEDIUM)
        write32(`UART_CTRL, ctrl);
        read32 (`UART_CTRL, rd, err);   // checked vs shadow by scoreboard
        write32(`UART_TX, {24'h0, tx_byte});
        read32 (`UART_STATUS, rd, err); // observe status (read-only)
    endtask

endclass
