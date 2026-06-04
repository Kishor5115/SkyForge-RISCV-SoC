// =============================================================================
// timer_test.sv - Timer unit test (runs timer_seq)
// Author : <author placeholder>   Date : <date placeholder>
// =============================================================================
class timer_test extends soc_base_test;
    `uvm_component_utils(timer_test)
    function new(string name, uvm_component parent);
        super.new(name, parent);
        seq_name = "timer_seq";
    endfunction
endclass
