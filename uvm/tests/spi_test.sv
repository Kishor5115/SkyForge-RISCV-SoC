// =============================================================================
// spi_test.sv - SPI unit test (runs spi_seq)
// Author : <author placeholder>   Date : <date placeholder>
// =============================================================================
class spi_test extends soc_base_test;
    `uvm_component_utils(spi_test)
    function new(string name, uvm_component parent);
        super.new(name, parent);
        seq_name = "spi_seq";
    endfunction
endclass
