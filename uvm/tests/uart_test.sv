// =============================================================================
// uart_test.sv - UART unit test (runs uart_seq)
// Author : <author placeholder>   Date : <date placeholder>
// =============================================================================
class uart_test extends soc_base_test;
    `uvm_component_utils(uart_test)
    function new(string name, uvm_component parent);
        super.new(name, parent);
        seq_name = "uart_seq";
    endfunction
endclass
