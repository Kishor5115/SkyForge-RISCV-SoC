// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vsoc_top__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vsoc_top::Vsoc_top(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vsoc_top__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , jtag_tck{vlSymsp->TOP.jtag_tck}
    , uart_tx{vlSymsp->TOP.uart_tx}
    , uart_rx{vlSymsp->TOP.uart_rx}
    , spi_sclk{vlSymsp->TOP.spi_sclk}
    , spi_mosi{vlSymsp->TOP.spi_mosi}
    , spi_miso{vlSymsp->TOP.spi_miso}
    , spi_cs_n{vlSymsp->TOP.spi_cs_n}
    , flash_sclk{vlSymsp->TOP.flash_sclk}
    , flash_cs_n{vlSymsp->TOP.flash_cs_n}
    , flash_mosi{vlSymsp->TOP.flash_mosi}
    , flash_miso{vlSymsp->TOP.flash_miso}
    , jtag_tms{vlSymsp->TOP.jtag_tms}
    , jtag_tdi{vlSymsp->TOP.jtag_tdi}
    , jtag_tdo{vlSymsp->TOP.jtag_tdo}
    , trap{vlSymsp->TOP.trap}
    , gpio_in{vlSymsp->TOP.gpio_in}
    , gpio_out{vlSymsp->TOP.gpio_out}
    , gpio_oe{vlSymsp->TOP.gpio_oe}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vsoc_top::Vsoc_top(const char* _vcname__)
    : Vsoc_top(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vsoc_top::~Vsoc_top() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vsoc_top___024root___eval_debug_assertions(Vsoc_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vsoc_top___024root___eval_static(Vsoc_top___024root* vlSelf);
void Vsoc_top___024root___eval_initial(Vsoc_top___024root* vlSelf);
void Vsoc_top___024root___eval_settle(Vsoc_top___024root* vlSelf);
void Vsoc_top___024root___eval(Vsoc_top___024root* vlSelf);

void Vsoc_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsoc_top::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vsoc_top___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vsoc_top___024root___eval_static(&(vlSymsp->TOP));
        Vsoc_top___024root___eval_initial(&(vlSymsp->TOP));
        Vsoc_top___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vsoc_top___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vsoc_top::eventsPending() { return false; }

uint64_t Vsoc_top::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vsoc_top::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vsoc_top___024root___eval_final(Vsoc_top___024root* vlSelf);

VL_ATTR_COLD void Vsoc_top::final() {
    Vsoc_top___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vsoc_top::hierName() const { return vlSymsp->name(); }
const char* Vsoc_top::modelName() const { return "Vsoc_top"; }
unsigned Vsoc_top::threads() const { return 1; }
void Vsoc_top::prepareClone() const { contextp()->prepareClone(); }
void Vsoc_top::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vsoc_top::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vsoc_top___024root__trace_decl_types(VerilatedVcd* tracep);

void Vsoc_top___024root__trace_init_top(Vsoc_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vsoc_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsoc_top___024root*>(voidSelf);
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vsoc_top___024root__trace_decl_types(tracep);
    Vsoc_top___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vsoc_top___024root__trace_register(Vsoc_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vsoc_top::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vsoc_top::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vsoc_top___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
