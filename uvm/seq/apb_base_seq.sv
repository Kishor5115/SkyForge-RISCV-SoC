// =============================================================================
// apb_base_seq.sv - Base APB sequence with utility tasks
// Purpose : Provides write32() and read32() helpers built on apb_seq_item.
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================

class apb_base_seq extends uvm_sequence #(apb_seq_item);
    `uvm_object_utils(apb_base_seq)

    function new(string name = "apb_base_seq");
        super.new(name);
    endfunction

    // Single 32-bit write
    task write32(bit [31:0] a, bit [31:0] d);
        apb_seq_item tr = apb_seq_item::type_id::create("wr");
        start_item(tr);
        if (!tr.randomize() with { addr == a; data == d; write == 1'b1; })
            `uvm_error("APB_SEQ", "write32 randomize failed")
        finish_item(tr);
    endtask

    // Single 32-bit read; returns captured data and error flag
    task read32(bit [31:0] a, output bit [31:0] d, output bit slverr);
        apb_seq_item tr = apb_seq_item::type_id::create("rd");
        start_item(tr);
        if (!tr.randomize() with { addr == a; write == 1'b0; })
            `uvm_error("APB_SEQ", "read32 randomize failed")
        finish_item(tr);
        d      = tr.data;
        slverr = tr.slverr;
    endtask

endclass
