// =============================================================================
// gpio_seq.sv - GPIO exercise sequence
// Purpose : Configures direction, drives outputs, reads back, exercises
//           loopback (gpio_in = gpio_out) and an invalid offset (PSLVERR).
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================

class gpio_seq extends apb_base_seq;
    `uvm_object_utils(gpio_seq)

    rand bit [31:0] out_val;
    rand bit [31:0] out_xor;

    function new(string name = "gpio_seq");
        super.new(name);
    endfunction

    task body();
        bit [31:0] rd; bit err;
        if (!this.randomize()) `uvm_error("GPIO_SEQ", "randomize failed")
        write32(`GP_OUTPUT_EN,  32'hFFFF_FFFF);  // all outputs
        write32(`GP_INPUT_EN,   32'hFFFF_FFFF);  // all inputs enabled (loopback)
        write32(`GP_OUTPUT_VAL, out_val);
        read32 (`GP_OUTPUT_VAL, rd, err);        // scoreboard checks vs shadow
        write32(`GP_OUT_XOR,    out_xor);
        read32 (`GP_INPUT_VAL,  rd, err);         // loopback observation
        `uvm_info("GPIO_SEQ", $sformatf("loopback INPUT_VAL=0x%08h", rd), UVM_MEDIUM)
        // Invalid offset access exercises the PSLVERR error path
        read32 (`GP_INVALID, rd, err);
        if (!err) `uvm_warning("GPIO_SEQ", "expected PSLVERR on invalid offset")
    endtask

endclass
