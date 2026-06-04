// =============================================================================
// soc_stress_seq.sv - Randomized cross-peripheral stress sequence
// Purpose : Fires 200+ randomized back-to-back APB transactions whose address
//           is randomized within each peripheral's valid register window.
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================

class soc_stress_seq extends apb_base_seq;
    `uvm_object_utils(soc_stress_seq)

    rand int unsigned num_trans;
    constraint c_num { num_trans inside {[200 : 300]}; }

    function new(string name = "soc_stress_seq");
        super.new(name);
    endfunction

    task body();
        apb_seq_item tr;
        if (!this.randomize()) `uvm_error("STRESS", "randomize failed")
        `uvm_info("STRESS", $sformatf("running %0d transactions", num_trans), UVM_LOW)
        repeat (num_trans) begin
            `uvm_do_with(tr, {
                tr.addr inside {
                    [`UART_BASE  : `UART_BASE  + 32'h00C],
                    [`TIMER_BASE : `TIMER_BASE + 32'h018],
                    [`GPIO_BASE  : `GPIO_BASE  + 32'h040],
                    [`SPI_BASE   : `SPI_BASE   + 32'h034],
                    [`DEBUG_BASE : `DEBUG_BASE + 32'h024] };
            })
        end
    endtask

endclass
