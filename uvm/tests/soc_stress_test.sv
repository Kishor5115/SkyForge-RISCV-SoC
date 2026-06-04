// =============================================================================
// soc_stress_test.sv - Randomized SoC stress test (runs soc_stress_seq)
// Author : <author placeholder>   Date : <date placeholder>
// =============================================================================
class soc_stress_test extends soc_base_test;
    `uvm_component_utils(soc_stress_test)
    function new(string name, uvm_component parent);
        super.new(name, parent);
        seq_name = "soc_stress_seq";
    endfunction
endclass
