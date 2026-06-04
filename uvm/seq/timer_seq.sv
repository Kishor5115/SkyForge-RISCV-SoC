// =============================================================================
// timer_seq.sv - Timer exercise sequence
// Purpose : Loads the counter, configures one-shot/periodic + prescale + IRQ,
//           reads back LOAD/CTRL and polls VALUE / interrupt status.
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================

class timer_seq extends apb_base_seq;
    `uvm_object_utils(timer_seq)

    rand bit [31:0] load;
    rand bit        one_shot;
    rand bit        periodic;
    rand bit [1:0]  prescale;

    constraint c_load     { load inside {[32'd4 : 32'd64]}; }
    constraint c_prescale { prescale inside {2'b00, 2'b01, 2'b10}; }

    function new(string name = "timer_seq");
        super.new(name);
    endfunction

    task body();
        bit [31:0] rd; bit err;
        bit [31:0] ctrl;
        if (!this.randomize()) `uvm_error("TIMER_SEQ", "randomize failed")
        write32(`TMR_LOAD, load);
        read32 (`TMR_LOAD, rd, err);  // scoreboard checks vs shadow
        // CTRL: enable(7), mode(6)=periodic, int_en(5), prescale(3:2), size(1)=32b, one_shot(0)
        ctrl = {24'd0, 1'b1, periodic, 1'b1, 1'b0, prescale, 1'b1, one_shot};
        write32(`TMR_CTRL, ctrl);
        read32 (`TMR_CTRL, rd, err);  // scoreboard checks masked vs shadow
        // Let the timer run and observe interrupt status
        repeat (8) read32(`TMR_VALUE, rd, err);
        read32 (`TMR_RIS, rd, err);
        write32(`TMR_INTCLR, 32'h1);
    endtask

endclass
