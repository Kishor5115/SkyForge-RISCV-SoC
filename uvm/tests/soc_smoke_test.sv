// =============================================================================
// soc_smoke_test.sv - Full SoC smoke test (runs soc_smoke_seq)
// Author : <author placeholder>   Date : <date placeholder>
// =============================================================================
class soc_smoke_test extends soc_base_test;
    `uvm_component_utils(soc_smoke_test)
    function new(string name, uvm_component parent);
        super.new(name, parent);
        seq_name = "soc_smoke_seq";
    endfunction
endclass
