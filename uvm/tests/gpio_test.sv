// =============================================================================
// gpio_test.sv - GPIO unit test (runs gpio_seq)
// Author : <author placeholder>   Date : <date placeholder>
// =============================================================================
class gpio_test extends soc_base_test;
    `uvm_component_utils(gpio_test)
    function new(string name, uvm_component parent);
        super.new(name, parent);
        seq_name = "gpio_seq";
    endfunction
endclass
