// =============================================================================
// soc_base_test.sv - Base UVM test
// Purpose : Builds soc_env and runs a sequence (selected by name) on the APB
//           sequencer, managing objections and a drain time.
// Author  : <author placeholder>
// Date    : <date placeholder>
// =============================================================================

class soc_base_test extends uvm_test;
    `uvm_component_utils(soc_base_test)

    soc_env env;
    string  seq_name = "soc_smoke_seq";

    function new(string name, uvm_component parent);
        super.new(name, parent);
    endfunction

    function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        env = soc_env::type_id::create("env", this);
    endfunction

    task run_phase(uvm_phase phase);
        uvm_coreservice_t cs = uvm_coreservice_t::get();
        uvm_factory       f  = cs.get_factory();
        uvm_object        obj;
        apb_base_seq      seq;
        phase.raise_objection(this, "running sequence");
        obj = f.create_object_by_name(seq_name, get_full_name(), seq_name);
        if (!$cast(seq, obj))
            `uvm_fatal("TEST", $sformatf("cannot create sequence '%s'", seq_name))
        seq.start(env.agent.sequencer);
        #200ns;  // drain
        phase.drop_objection(this, "sequence done");
    endtask

endclass
