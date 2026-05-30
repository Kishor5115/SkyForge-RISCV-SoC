// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_top.h for the primary calling header

#include "Vsoc_top__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vsoc_top___024root___eval_triggers__act(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_triggers__act\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.jtag_tck)) 
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__jtag_tck__0)) 
                                                      << 4U) 
                                                     | (((((IData)(vlSelfRef.jtag_tck) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__jtag_tck__0))) 
                                                          << 3U) 
                                                         | (((~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)) 
                                                             & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__soc_top__DOT__rst_ff2__0)) 
                                                            << 2U)) 
                                                        | ((((~ (IData)(vlSelfRef.rst_n)) 
                                                             & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0)) 
                                                            << 1U) 
                                                           | ((IData)(vlSelfRef.clk) 
                                                              & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__soc_top__DOT__rst_ff2__0 
        = vlSelfRef.soc_top__DOT__rst_ff2;
    vlSelfRef.__Vtrigprevexpr___TOP__jtag_tck__0 = vlSelfRef.jtag_tck;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsoc_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vsoc_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlUnpacked<CData/*3:0*/, 64> Vsoc_top__ConstPool__TABLE_h236b36fc_0;

void Vsoc_top___024root___nba_sequent__TOP__0(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___nba_sequent__TOP__0\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*5:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift = 0;
    // Body
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift;
    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state;
    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift;
    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift;
    if ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state))) {
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                      >> 4U)))) {
            if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                          >> 3U)))) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                              >> 2U)))) {
                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                                  >> 1U)))) {
                        if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift = 0x10005001U;
                        }
                    }
                }
            }
        }
        if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
            if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                          >> 3U)))) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                              >> 2U)))) {
                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                                  >> 1U)))) {
                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg)))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift 
                                = (0x00001071U | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_stat) 
                                                  << 0x0000000aU));
                        }
                        if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                            vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                = (((QData)((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_data)) 
                                    << 2U) | (QData)((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_op)));
                        }
                    }
                }
            }
            if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg = 0U;
            } else if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg = 0U;
            } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg = 0U;
            }
        } else if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg = 0U;
        } else if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg = 0U;
        } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg = 0U;
        } else if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg = 0U;
        }
    } else if ((4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state))) {
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                      >> 4U)))) {
            if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                          >> 3U)))) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                              >> 2U)))) {
                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                                  >> 1U)))) {
                        if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift 
                                = (((IData)(vlSelfRef.jtag_tdi) 
                                    << 0x0000001fU) 
                                   | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift 
                                      >> 1U));
                        }
                    }
                }
            }
        }
        if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
            if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                          >> 3U)))) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                              >> 2U)))) {
                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg) 
                                  >> 1U)))) {
                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg)))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift 
                                = (((IData)(vlSelfRef.jtag_tdi) 
                                    << 0x0000001fU) 
                                   | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift 
                                      >> 1U));
                        }
                        if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                            vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                = (((QData)((IData)(vlSelfRef.jtag_tdi)) 
                                    << 0x00000028U) 
                                   | (0x000000ffffffffffULL 
                                      & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                         >> 1U)));
                        }
                    }
                }
            }
            if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg 
                    = vlSelfRef.jtag_tdi;
            } else if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg 
                    = vlSelfRef.jtag_tdi;
            } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg 
                    = vlSelfRef.jtag_tdi;
            }
        } else if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg 
                = vlSelfRef.jtag_tdi;
        } else if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg 
                = vlSelfRef.jtag_tdi;
        } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg 
                = vlSelfRef.jtag_tdi;
        } else if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg 
                = vlSelfRef.jtag_tdi;
        }
    }
    __Vtableidx3 = (((IData)(vlSelfRef.jtag_tms) << 5U) 
                    | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state) 
                        << 1U) | (IData)(vlSelfRef.soc_top__DOT__rst_ff2)));
    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state 
        = Vsoc_top__ConstPool__TABLE_h236b36fc_0[__Vtableidx3];
    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           & ((((8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)) 
                & (0x11U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) 
               & (0U != (3U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift)))) 
              & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d))));
    if (((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)) 
         | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_dmireset_pulse))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_busy = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_stat = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_data = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_op = 0U;
    } else {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_busy = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_stat = 3U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_op = 3U;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tck_pulse) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_busy = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_stat 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_op_sys;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_data 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_data_sys;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_op 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_op_sys;
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_last 
        = ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)) 
           && (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync2));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync2 
        = ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)) 
           && (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync1));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tck_pulse 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_last) 
           ^ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync2));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync1 
        = ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)) 
           && (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_toggle_sys));
}

extern const VlUnpacked<VlWide<4>/*127:0*/, 256> Vsoc_top__ConstPool__TABLE_h3c1c5ec4_0;

void Vsoc_top___024root___nba_sequent__TOP__1(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___nba_sequent__TOP__1\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_1;
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_1 = 0;
    CData/*0:0*/ soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_2;
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_2 = 0;
    CData/*0:0*/ soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_3;
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_3 = 0;
    CData/*0:0*/ soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_5;
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_5 = 0;
    CData/*0:0*/ soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_6;
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_6 = 0;
    CData/*0:0*/ soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_7;
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_7 = 0;
    CData/*7:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*1:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc = 0;
    CData/*4:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out = 0;
    QData/*63:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active = 0;
    CData/*5:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr = 0;
    CData/*1:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state = 0;
    QData/*63:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr = 0;
    CData/*7:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 = 0;
    CData/*1:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state = 0;
    CData/*1:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r = 0;
    CData/*1:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase = 0;
    SData/*15:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0;
    CData/*7:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in = 0;
    CData/*4:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0;
    CData/*2:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt = 0;
    CData/*7:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out = 0;
    SData/*15:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr = 0;
    CData/*1:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state = 0;
    CData/*1:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt = 0;
    CData/*7:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr = 0;
    CData/*2:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 0;
    SData/*15:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase = 0;
    CData/*4:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt = 0;
    CData/*3:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 = 0;
    IData/*31:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 = 0;
    CData/*2:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 0;
    CData/*0:0*/ __Vdly__soc_top__DOT__u_soc_core__DOT__jdbg_valid;
    __Vdly__soc_top__DOT__u_soc_core__DOT__jdbg_valid = 0;
    IData/*31:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0 = 0;
    CData/*5:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0 = 0;
    IData/*31:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1 = 0;
    CData/*5:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1 = 0;
    CData/*7:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0 = 0;
    SData/*11:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0 = 0;
    CData/*7:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1 = 0;
    SData/*11:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1 = 0;
    CData/*7:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2 = 0;
    SData/*11:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2 = 0;
    CData/*7:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3 = 0;
    SData/*11:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3 = 0;
    CData/*7:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0 = 0;
    CData/*2:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0 = 0;
    CData/*7:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0 = 0;
    CData/*2:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0 = 0;
    CData/*2:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0 = 0;
    IData/*31:0*/ __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0;
    __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0 = 0;
    CData/*2:0*/ __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0;
    __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0 = 0;
    CData/*0:0*/ __VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0 = 0;
    // Body
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0 = 0U;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1 = 0U;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2 = 0U;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3 = 0U;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0 = 0U;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1 = 0U;
    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured;
    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured;
    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0 = 0U;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive;
    __Vdly__soc_top__DOT__u_soc_core__DOT__jdbg_valid 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_valid;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0 = 0U;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0 = 0U;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state;
    __VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0 = 0U;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1;
    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state;
    if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_csb0)))) {
        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_web0)))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0))) {
                __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0 
                    = (0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0);
                __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0;
                __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0 = 1U;
            }
            if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0))) {
                __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1 
                    = (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0 
                                      >> 8U));
                __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0;
                __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1 = 1U;
            }
            if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0))) {
                __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2 
                    = (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0 
                                      >> 0x10U));
                __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0;
                __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2 = 1U;
            }
            if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0))) {
                __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3 
                    = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0 
                       >> 0x18U);
                __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0;
                __VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3 = 1U;
            }
        }
    }
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arvalid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_arready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg = 1U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_rready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg = 0U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arvalid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_arready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg = 1U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_rready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg = 0U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_en) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__full)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr)));
            __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_data_in;
            __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0 
                = (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr));
            __VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0 = 1U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awvalid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_awready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done = 1U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wvalid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_wready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done = 1U;
        }
        if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done)) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg = 1U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_bready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done = 0U;
        }
        if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_aw_done) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_w_done)) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_bvalid_r)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_bvalid_r = 1U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awvalid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_awready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_addr_r 
                = (0x00000fffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awaddr 
                                  >> 2U));
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wvalid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_wready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_data_r 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wdata;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_strb_r 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wstrb;
        }
        if (((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)) 
              & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending = 1U;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r = 1U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_bready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured = 0U;
        }
        if ((((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart) 
                & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite))) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable)) 
              & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty))) 
             & (4U == (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr)));
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_en) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__full)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr)));
            __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_data;
            __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0 
                = (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr));
            __VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0 = 1U;
        }
        if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))) {
            if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 0U;
            } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 0U;
            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rvalid) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 0U;
            }
        } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))) {
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_arready) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 4U;
                }
            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_bvalid) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 0U;
            }
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))) {
            if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__aw_done) 
                  | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awready)) 
                 & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__w_done) 
                    | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wready)))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 2U;
            }
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awready) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__aw_done = 1U;
            }
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wready) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__w_done = 1U;
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__aw_done = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__w_done = 0U;
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_write) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 1U;
            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_read) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 3U;
            }
        }
        if ((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__empty)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_en)) 
             & (~ ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state)) 
                   | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start))))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr)));
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) 
                      & (0x10U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                              >> 6U)))) {
                    if ((0x00000020U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                        if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                            if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                              >> 2U)))) {
                                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                                  >> 1U)))) {
                                        if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                            if ((1U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
                                                    = 
                                                    ((0xffffff00U 
                                                      & __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0) 
                                                     | (0x000000ffU 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                            if ((2U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
                                                    = 
                                                    ((0xffff00ffU 
                                                      & __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0) 
                                                     | (0x0000ff00U 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                            if ((4U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
                                                    = 
                                                    ((0xff00ffffU 
                                                      & __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0) 
                                                     | (0x00ff0000U 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                            if ((8U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
                                                    = 
                                                    ((0x00ffffffU 
                                                      & __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0) 
                                                     | (0xff000000U 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                        }
                                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))) {
                                            if ((2U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadondata 
                                                    = 
                                                    (1U 
                                                     & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
                                                        >> 0x0fU));
                                            }
                                            if ((4U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadonaddr 
                                                    = 
                                                    (1U 
                                                     & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
                                                        >> 0x14U));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_write) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter 
                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                   & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size)
                       ? 0xffffffffU : 0x0000ffffU));
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped = 0U;
        } else if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_write) 
                     & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                        >> 7U)) & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_enable)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter 
                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_reg 
                   & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size)
                       ? 0xffffffffU : 0x0000ffffU));
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped = 0U;
        } else if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_enable) 
                     & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_tick)) 
                    & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped)))) {
            if ((0U == vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter_value)) {
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_one_shot) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped = 1U;
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter 
                        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_mode)
                            ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_reg 
                               & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size)
                                   ? 0xffffffffU : 0x0000ffffU))
                            : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size)
                                ? 0xffffffffU : 0x0000ffffU));
                }
            } else {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter 
                    = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter 
                        - (IData)(1U)) & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size)
                                           ? 0xffffffffU
                                           : 0x0000ffffU));
            }
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arvalid) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rdata_reg 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rom
                [(0x0000003fU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_araddr 
                                 >> 2U))];
        }
        if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state))) {
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arvalid) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_arready))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state = 1U;
            }
        } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rdata_r 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_dout0;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state = 2U;
        } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_rready) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state = 0U;
            }
        } else {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state = 0U;
        }
    } else {
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_bvalid_r = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__aw_done = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__w_done = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter = 0xffffffffU;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rdata_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadondata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadonaddr = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rdata_r = 0U;
    }
    if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_csb0)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_dout0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem
            [vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0];
    }
    if (((((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)) 
          & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_1) 
             & ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                 >> 0x00000010U) & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_3)))) 
         & (0U != (0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____Vlvbound_h6f5e494c__0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0;
        __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____Vlvbound_h6f5e494c__0;
        __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0 
            = (0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command);
        __VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0 = 1U;
    } else if ((((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_write)) 
                & (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____Vlvbound_hc83e3f8d__0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata;
        if ((0x23U >= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd))) {
            __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____Vlvbound_hc83e3f8d__0;
            __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd;
            __VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1 = 1U;
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__trace_valid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rd 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rd;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs2 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs2;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs1 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs1;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_opcode 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_opcode;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_imm 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_imm;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_ascii_instr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_instr;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word_q 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word;
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__launch_next_insn) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_addr 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_pc;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_next = 1U;
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_next = 0U;
    }
    if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__pcpi_insn = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ecall_ebreak 
            = (((0x73U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)) 
                & (~ (0U != (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                             >> 0x15U)))) & (~ (0U 
                                                != 
                                                (0x00001fffU 
                                                 & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                    >> 7U)))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycleh = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstrh = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_fence 
            = ((0x0fU == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)) 
               & (~ (0U != (7U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                  >> 0x0cU)))));
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger_q) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_ascii_instr 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_opcode 
            = ((3U == (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode))
                ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode
                : (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rd 
            = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rd));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs1 
            = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs2 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_imm 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm;
    }
    if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)) 
               | (IData)(vlSelfRef.trap)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_valid_insn = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__prefetched_high_word = 0U;
    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__launch_next_insn) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_valid_insn = 1U;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__prefetched_high_word = 0U;
    }
    if ((1U & (~ ((~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)) 
                  | (IData)(vlSelfRef.trap))))) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_write) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wdata 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wdata;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_read) 
             | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_write))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr 
                = (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch) 
                    | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst))
                    ? (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_pc)
                    : (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1));
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg;
    if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)) 
               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst)))) {
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr = 0U;
    } else {
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_pop) 
             & (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr)));
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r;
        if (((8U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_0))) {
            __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata;
            __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0 
                = (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr));
            __VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0 = 1U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr)));
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter;
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0] 
            = __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem__v0;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr;
    if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)) 
               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst)))) {
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr = 0U;
    } else {
        if (((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state)) 
             & ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)) 
                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_enable)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr)));
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count) 
             <= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_txmark))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip 
                = (1U | (IData)(__Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip));
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count) 
             >= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_rxmark))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip 
                = (2U | (IData)(__Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip));
        }
        if (((4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state)) 
             & ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt)) 
                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip 
                = (4U | (IData)(__Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip));
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_0) 
             & (8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip 
                = (8U | (IData)(__Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip));
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_write) 
             & (0x2cU == (0x0000003fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip 
                = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip) 
                   & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata));
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_push) 
             & (8U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count)))) {
            __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_in;
            __VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0 
                = (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr));
            __VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0 = 1U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr)));
        }
    }
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0] 
            = __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo__v0;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state;
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state = 0U;
                }
            } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid) 
                        & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state = 0U;
            }
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state = 2U;
            }
        } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready) 
                    & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_addr_reg 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_prot_reg = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state 
                = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_decerr)
                    ? 3U : 1U);
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state;
        if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_addr_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_prot_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state 
                    = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_decerr)
                        ? 2U : 1U);
            }
        } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state = 0U;
            }
        } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state = 0U;
            }
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state;
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_write) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_reg 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_write) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_int_en 
                = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                         >> 5U));
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) 
                      & (0x10U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                              >> 6U)))) {
                    if ((0x00000020U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                        if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                            if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                              >> 2U)))) {
                                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                                  >> 1U)))) {
                                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))) {
                                            if ((1U 
                                                 & (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb) 
                                                     >> 2U) 
                                                    & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
                                                       >> 0x16U)))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbbusyerror = 0U;
                                            }
                                            if ((IData)(
                                                        (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb) 
                                                          >> 3U) 
                                                         & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
                                                            >> 0x0000001dU)))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbbusyerror = 0U;
                                            }
                                            if ((2U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                if (
                                                    (0U 
                                                     != 
                                                     (7U 
                                                      & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
                                                         >> 0x0cU)))) {
                                                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sberror = 0U;
                                                }
                                            }
                                        }
                                    }
                                }
                                if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                                  >> 1U)))) {
                                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))) {
                                            if ((1U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0 
                                                    = 
                                                    ((0xffffff00U 
                                                      & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0) 
                                                     | (0x000000ffU 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                            if ((2U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0 
                                                    = 
                                                    ((0xffff00ffU 
                                                      & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0) 
                                                     | (0x0000ff00U 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                            if ((4U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0 
                                                    = 
                                                    ((0xff00ffffU 
                                                      & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0) 
                                                     | (0x00ff0000U 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                            if ((8U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0 
                                                    = 
                                                    ((0x00ffffffU 
                                                      & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0) 
                                                     | (0xff000000U 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))) {
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_read) 
                 | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_write))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbbusyerror = 1U;
            }
        }
        if (((0x0bU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_rdata_reg 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_rvalid_reg = 1U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending = 0U;
        }
        if (((4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rvalid))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0 
                = ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size))
                    ? ((0U == (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0))
                        ? (0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata)
                        : ((1U == (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0))
                            ? (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata 
                                              >> 8U))
                            : ((2U == (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0))
                                ? (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata 
                                                  >> 0x10U))
                                : (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata 
                                   >> 0x18U)))) : (
                                                   (1U 
                                                    == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size))
                                                    ? 
                                                   ((2U 
                                                     & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0)
                                                     ? 
                                                    (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata 
                                                     >> 0x10U)
                                                     : 
                                                    (0x0000ffffU 
                                                     & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata))
                                                    : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata));
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbautoincrement) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
                    = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
                       + ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size))
                           ? 1U : ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size))
                                    ? 2U : 4U)));
            }
        }
        if (((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_bvalid))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbautoincrement) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
                    = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
                       + ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size))
                           ? 1U : ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size))
                                    ? 2U : 4U)));
            }
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0;
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__apb_write) 
             & (0x0cU == (0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__raw_int = 0U;
        } else if (((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_enable) 
                      & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_tick)) 
                     & (0U == vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter_value)) 
                    & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__raw_int = 1U;
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped;
        if ((((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_bvalid)) 
             & (0U != ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)
                        ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp)
                        : 0U)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sberror = 2U;
        }
        if ((((4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rvalid)) 
             & (0U != ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)
                        ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp)
                        : 0U)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sberror = 2U;
        }
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state))) {
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick) {
                    vlSelfRef.uart_tx = 1U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state = 0U;
                }
            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick) {
                vlSelfRef.uart_tx = (1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__shift_reg));
                if ((7U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__bit_cnt))) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state = 3U;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__bit_cnt 
                        = (7U & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__bit_cnt)));
                }
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__shift_reg 
                    = (0x0000007fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__shift_reg) 
                                      >> 1U));
            }
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__bit_cnt = 0U;
                vlSelfRef.uart_tx = 0U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state = 2U;
            }
        } else {
            vlSelfRef.uart_tx = 1U;
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__shift_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_data_out;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state = 1U;
            }
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_error) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_err_sticky = 1U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_valid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__full))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_overrun = 1U;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__wr_ctrl_pulse) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_err_sticky = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_overrun = 0U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arvalid) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_data_reg 
                = ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                    ? ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                        ? 0U : ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                 ? 0U : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                          ? 0U : ((2U 
                                                   & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                                    ? 0U
                                                    : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_dummy_cycles))))))
                    : ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                        ? ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                            ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                             ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id))
                                : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                             ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_clkdiv))))
                            : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                             ? 0U : 
                                            (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_valid)) 
                                              << 0x0000001fU) 
                                             | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_reg))))
                                : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                             ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_txdata)))))
                        : ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                            ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                             ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr))
                                : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                             ? 0U : 
                                            (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd_start) 
                                              << 8U) 
                                             | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd)))))
                            : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                             ? 0U : 
                                            (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__timeout_err) 
                                              << 0x0000001dU) 
                                             | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state) 
                                                 << 2U) 
                                                | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_xip_en) 
                                                    << 1U) 
                                                   | (0U 
                                                      != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state)))))))
                                : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)
                                             ? 0U : 
                                            (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr_width) 
                                              << 2U) 
                                             | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_xip_en) 
                                                 << 1U) 
                                                | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_enable)))))))));
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg;
        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__last_mem_valid)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_firstword_reg = 0U;
        }
        if ((((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active)) 
                     & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid))))
               ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready)
               : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active) 
                  & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)) 
                     & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready)))) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_awvalid))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_awvalid = 1U;
        }
        if (((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active)) 
               & (3U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)))
               ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready)
               : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active) 
                  & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)) 
                     & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready)))) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_arvalid))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_arvalid = 1U;
        }
        if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active)
               ? ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready))
               : ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid)) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready))) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_wvalid))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_wvalid = 1U;
        }
        if ((1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__xfer_done) 
                   | (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid))))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_awvalid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_arvalid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_wvalid = 0U;
        }
        if ((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff3)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff2)) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_valid)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__jdbg_valid = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_write 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_write_tck;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_addr 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_addr_tck;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_wdata 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_wdata_tck;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_wstrb = 0x0fU;
        } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_valid) 
                    & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy)) 
                       & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_toggle_sys 
                = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_toggle_sys)));
            __Vdly__soc_top__DOT__u_soc_core__DOT__jdbg_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_data_sys 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_op_sys = 0U;
        }
    } else {
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_addr_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_prot_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_addr_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_prot_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_int_en = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbbusyerror = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbbusyerror = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_rvalid_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_rdata_reg = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0 = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0 = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__raw_int = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sberror = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sberror = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__shift_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__bit_cnt = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state = 0U;
        vlSelfRef.uart_tx = 1U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_err_sticky = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_overrun = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_data_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_firstword_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_awvalid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_arvalid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_wvalid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_toggle_sys = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__jdbg_valid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_write = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_addr = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_wdata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_wstrb = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_data_sys = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_op_sys = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_valid 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__jdbg_valid;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_wready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_awready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_web0 
        = (1U & (~ ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured) 
                      & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)) 
                     & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))) 
                    & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending)))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_wready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_awready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__full 
        = (((1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr) 
                   >> 3U)) != (1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr) 
                                     >> 3U))) & ((7U 
                                                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr)) 
                                                 == 
                                                 (7U 
                                                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count 
        = (0x0000000fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr) 
                          - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_arready 
        = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_arready 
        = ((~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending) 
               | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)))) 
           & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_arready 
        = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__last_mem_valid 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           && ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid) 
               & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_ready))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__xfer_done 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           && ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_ready)));
    if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)) 
               | (IData)(vlSelfRef.trap)))) {
        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state = 0U;
        }
        if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)) 
                   | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_ready)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid = 0U;
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_secondword = 0U;
    } else {
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_read) 
             | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_write))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb 
                = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wstrb) 
                   & (- (IData)((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_write))));
        }
        if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state))) {
            if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch) 
                  | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst)) 
                 | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_instr 
                    = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch) 
                       | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst));
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb = 0U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state = 1U;
            }
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_instr = 0U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state = 2U;
            }
        } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_secondword = 0U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state 
                    = (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst) 
                        | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata))
                        ? 0U : 3U);
            }
        } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid = 0U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state = 0U;
            }
        } else if ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state = 0U;
            }
        }
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__pcpi_valid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rinst = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rdata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_wdata = 0U;
        vlSelfRef.trap = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger_q 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq = 0U;
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_written))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_shadow;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_shadow;
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger;
        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__pcpi_valid = 0U;
        }
        vlSelfRef.trap = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rinst = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rdata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_wdata = 0U;
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__launch_next_insn) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val_valid = 0U;
        }
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle 
            = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2)
                ? (1ULL + vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle)
                : 0ULL);
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle 
            = (0x00000000ffffffffULL & __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle);
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger_q 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq = 0U;
        if ((0U != vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer)) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer 
                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer 
                   - (IData)(1U));
        }
        if (vlSelfRef.soc_top__DOT__rst_ff2) {
            if (((((((((0x80U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state)) 
                       | (0x40U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) 
                      | (0x20U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) 
                     | (0x10U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) 
                    | (8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) 
                   | (4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) 
                  | (2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) 
                 | (1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state)))) {
                if ((0x80U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) {
                    vlSelfRef.trap = 1U;
                } else if ((0x40U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst 
                        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger)) 
                                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq))));
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize = 0U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu = 0U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh = 0U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc;
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc 
                            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store)
                                ? (0xfffffffeU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_stalu)
                                                   ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_q
                                                   : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out))
                                : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc);
                    } else if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store) 
                                         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch)))))) {
                        if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state))) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc = 0x00010010U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 1U;
                        } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state))) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending 
                                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending 
                                   & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending_ack));
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__cpu_eoi 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending_ack;
                        }
                    }
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_stalu = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch = 0U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rd;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__compressed_instr;
                    if ((((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger) 
                            & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active))) 
                           & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_delay))) 
                          & (0U != (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending 
                                    & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_mask)))) 
                         | (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state)))) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr;
                        if ((1U & (~ (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state))))) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending_ack 
                                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending 
                                   & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_mask));
                        }
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state 
                            = ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state))
                                ? 1U : ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state))
                                         ? 2U : 0U));
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd 
                            = (0x0000003fU & (0x20U 
                                              | (1U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state))));
                    } else if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger) 
                                 | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq)) 
                                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_waitirq))) {
                        if ((0U != vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending)) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc 
                                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc 
                                   + ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__compressed_instr)
                                       ? 2U : 4U));
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 1U;
                        } else {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq = 1U;
                        }
                    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr 
                            = (1ULL + vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr);
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_delay 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc 
                            = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc 
                               + ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__compressed_instr)
                                   ? 2U : 4U));
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr 
                            = (0x00000000ffffffffULL 
                               & __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr);
                        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jal) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc 
                                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc 
                                   + vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j);
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch = 1U;
                        } else {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 0U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch 
                                = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jalr)) 
                                         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_retirq))));
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x20U;
                        }
                    }
                } else if ((0x20U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 = 0U;
                    if ((((((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh) 
                              | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal)) 
                             | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_getq)) 
                            | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_setq)) 
                           | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_retirq)) 
                          | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_maskirq)) 
                         | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_timer))) {
                        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh) {
                            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycle) {
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                    = (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle);
                            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstr) {
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                    = (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr);
                            }
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                        } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lui)
                                    ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc);
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 8U;
                        } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_getq) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 1U;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                        } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_setq) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd 
                                = (0x20U | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd));
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 1U;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                        } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_retirq) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__cpu_eoi = 0U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active = 0U;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch = 1U;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                        } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_maskirq) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_mask;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_mask 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        } else {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        }
                    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 1U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 1U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 1U;
                    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_slli_srli_srai) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 1U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 4U;
                    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 1U;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 8U;
                    } else {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = 1U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh 
                            = (0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2);
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val_valid = 1U;
                        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sb_sh_sw) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 2U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 1U;
                        } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sll_srl_sra) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 4U;
                        } else {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 8U;
                        }
                    }
                } else if ((0x10U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh 
                        = (0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2);
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val_valid = 1U;
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sb_sh_sw) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 2U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 1U;
                    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sll_srl_sra) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 4U;
                    } else {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 8U;
                    }
                } else if ((8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                        = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc 
                           + vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm);
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd = 0U;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0;
                        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                        }
                        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rinst = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger = 0U;
                        }
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jalr;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_stalu = 1U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                    }
                } else if ((4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                    if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh))) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                    } else {
                        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slli) 
                             | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sll))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                = VL_SHIFTL_III(32,32,32, vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1, 1U);
                        } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srli) 
                                    | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srl))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                = VL_SHIFTR_III(32,32,32, vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1, 1U);
                        } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srai) 
                                    | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sra))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                = VL_SHIFTRS_III(32,32,32, vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1, 1U);
                        }
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh 
                            = (0x0000001fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh) 
                                              - (IData)(1U)));
                    }
                } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) {
                    if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch)) 
                               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw)))) {
                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata)))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                   + vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm);
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_wdata = 1U;
                            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sb) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize = 2U;
                            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sh) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize = 1U;
                            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sw) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize = 0U;
                            }
                        }
                        if (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch)) 
                             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger = 1U;
                        }
                    }
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
                    if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch)) 
                               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw)))) {
                        if (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch)) 
                             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw))) {
                            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu) {
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word;
                            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh) {
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                    = VL_EXTENDS_II(32,16, 
                                                    (0x0000ffffU 
                                                     & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word));
                            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb) {
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
                                    = VL_EXTENDS_II(32,8, 
                                                    (0x000000ffU 
                                                     & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word));
                            }
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
                        }
                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata)))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                   + vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm);
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rdata = 1U;
                            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lb) 
                                 | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lbu))) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize = 2U;
                            } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lh) 
                                        | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lhu))) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize = 1U;
                            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lw) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize = 0U;
                            }
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lbu_lhu_lw;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lh;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lb;
                        }
                    }
                }
            }
        } else {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr = 0ULL;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_stalu = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_delay = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_mask = 0xffffffffU;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending_ack = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__cpu_eoi = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd = 2U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out = 0x00013ffcU;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = 0x40U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = 1U;
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending 
            = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending 
               | ((((0U != ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ie) 
                            & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip))) 
                    << 6U) | ((0U != ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip) 
                                      | ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie 
                                          & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip) 
                                         | ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie 
                                             & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip) 
                                            | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie 
                                               & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip))))) 
                              << 5U)) | ((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty)) 
                                           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__irq_en)) 
                                          << 4U) | 
                                         ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_irq_aggregator__DOT__timer_irq) 
                                          << 3U))));
        if ((0U != vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer)) {
            if ((0U == (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer 
                        - (IData)(1U)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending 
                    = (1U | vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending);
            }
        }
        if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)) 
                   | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata = 0U;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rinst) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = 1U;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rdata) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata = 1U;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_wdata) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata = 1U;
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc 
            = (0xfffffffcU & __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc);
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc 
            = (0xfffffffcU & __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc);
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc = 0U;
    }
    if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)) 
               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst)))) {
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_in = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__mosi_reg = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt = 2U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt = 2U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_push = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sckdiv = 3U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpha = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csdef = 0x0fU;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csmode = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_endian = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen = 8U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_txmark = 1U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_rxmark = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ie = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_enable = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst = 0U;
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_push = 0U;
        if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state))) {
            if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 0U;
            } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 0U;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol;
                if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_push = 1U;
                    if (((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csmode)) 
                         & (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)))) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo
                            [(7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr))];
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt = 0U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase = 0U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 2U;
                    } else {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 5U;
                    }
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt 
                        = (0x0000000fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt) 
                                          - (IData)(1U)));
                }
            }
        } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state))) {
                if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt) 
                     >= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sckdiv))) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase 
                        = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase)));
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt = 0U;
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpha) {
                        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_in 
                                = (((~ ((IData)(1U) 
                                        << (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx))) 
                                    & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_in) 
                                   | (0x00000000ffffffffULL 
                                      & ((IData)(vlSelfRef.spi_miso) 
                                         << (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx))));
                            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt) 
                                 == ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen) 
                                     - (IData)(1U)))) {
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt = 2U;
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 4U;
                            } else {
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt 
                                    = (0x0000001fU 
                                       & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt)));
                            }
                        } else {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg 
                                = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol)));
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__mosi_reg 
                                = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out 
                                         >> (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx)));
                        }
                    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol;
                        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt) 
                             == ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen) 
                                 - (IData)(1U)))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt = 2U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 4U;
                        } else {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt 
                                = (0x0000001fU & ((IData)(1U) 
                                                  + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt)));
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__mosi_reg 
                                = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out 
                                         >> (0x0000001fU 
                                             & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_endian)
                                                 ? 
                                                ((IData)(1U) 
                                                 + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt))
                                                 : 
                                                (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen) 
                                                  - (IData)(2U)) 
                                                 - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt))))));
                        }
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg 
                            = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol)));
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_in 
                            = (((~ ((IData)(1U) << (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx))) 
                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_in) 
                               | (0x00000000ffffffffULL 
                                  & ((IData)(vlSelfRef.spi_miso) 
                                     << (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx))));
                    }
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt 
                        = (0x0000ffffU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt)));
                }
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__mosi_reg 
                    = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out 
                             >> (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx)));
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpha) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 3U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt = 0U;
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 3U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt = 0U;
                }
            }
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state))) {
            if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 2U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt = 0U;
            } else {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt 
                    = (0x0000000fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt) 
                                      - (IData)(1U)));
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase = 0U;
            if (((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_enable))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo
                    [(7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr))];
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt = 2U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = 1U;
            }
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst = 0U;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_write) {
            if ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                  >> 3U)))) {
                        if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                          >> 1U)))) {
                                if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_enable 
                                        = (1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst 
                                        = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                 >> 1U));
                                }
                            }
                        }
                    }
                } else if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                  >> 2U)))) {
                        if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                      >> 1U)))) {
                            if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ie 
                                    = (0x0000000fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                            }
                        }
                    }
                } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                  >> 1U)))) {
                        if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_rxmark 
                                = (7U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                        }
                    }
                } else if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                     >> 1U)))) {
                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_txmark 
                            = (7U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                    }
                }
            } else if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                              >> 3U)))) {
                    if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                        if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                      >> 1U)))) {
                            if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_endian 
                                    = (1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen 
                                    = ((0U == (0x0000001fU 
                                               & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  >> 0x10U)))
                                        ? 8U : (0x0000001fU 
                                                & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                   >> 0x10U)));
                            }
                        }
                    } else if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                         >> 1U)))) {
                        if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csmode 
                                = (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                        }
                    }
                }
            } else if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                  >> 1U)))) {
                        if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csdef 
                                = (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                        }
                    }
                } else if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                     >> 1U)))) {
                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csid 
                            = (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                    }
                }
            } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                              >> 1U)))) {
                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpha 
                            = (1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol 
                            = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                     >> 1U));
                    }
                }
            } else if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                 >> 1U)))) {
                if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sckdiv 
                        = (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                }
            }
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_wait_2 = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_wait = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__trace_data = 0ULL;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0_q 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0;
        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__pcpi_timeout = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_trace = 0U;
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_q 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff3 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           && (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff2));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase;
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0] 
            = __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo__v0;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state;
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0] 
            = ((0xffffff00U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem
                [__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0]) 
               | (IData)(__VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v0));
    }
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1] 
            = ((0xffff00ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem
                [__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1]) 
               | ((IData)(__VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v1) 
                  << 8U));
    }
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2] 
            = ((0xff00ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem
                [__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2]) 
               | ((IData)(__VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v2) 
                  << 0x00000010U));
    }
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3] 
            = ((0x00ffffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem
                [__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3]) 
               | ((IData)(__VdlyVal__soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem__v3) 
                  << 0x00000018U));
    }
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_en = 0U;
        if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite))) {
            if ((0U == (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__full)))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_en = 1U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_data 
                        = (0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                }
            }
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_write) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_reg 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_write) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_reg 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_write) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_one_shot 
                = (1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_mode 
                = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                         >> 6U));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size 
                = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                         >> 1U));
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) 
                      & (0x10U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                              >> 6U)))) {
                    if ((0x00000020U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                        if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                            if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                              >> 2U)))) {
                                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                                  >> 1U)))) {
                                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))) {
                                            if ((4U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbautoincrement 
                                                    = 
                                                    (1U 
                                                     & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
                                                        >> 0x10U));
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size 
                                                    = 
                                                    (7U 
                                                     & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
                                                        >> 0x11U));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_tick = 0U;
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_enable) {
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter) 
                 >= ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale))
                      ? 0U : ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale))
                               ? 0x0fU : ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale))
                                           ? 0xffU : 0U))))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_tick = 1U;
            } else {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter 
                    = (0x000000ffU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter)));
            }
        } else {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter = 0U;
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start = 0U;
        if (((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_en) 
               & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__empty))) 
              & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state))) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_data_out 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem
                [(7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr))];
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start = 1U;
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_en = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_data = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_one_shot = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_mode = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbautoincrement = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size = 2U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_tick = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_data_out = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start;
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0] 
            = __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem__v0;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr;
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__wr_ctrl_pulse = 0U;
        if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite))) {
            if ((0U != (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                if ((0x0cU == (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__wr_ctrl_pulse = 1U;
                }
            }
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_valid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_error = 0U;
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state))) {
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick_16x) {
                    if ((0x0fU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt))) {
                        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_1) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_data_in 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__shift_reg;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_valid = 1U;
                        } else {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_error = 1U;
                        }
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state = 0U;
                    } else {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt 
                            = (0x0000000fU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt)));
                    }
                }
            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick_16x) {
                if ((0x0fU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__shift_reg 
                        = (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_1) 
                            << 7U) | (0x0000007fU & 
                                      ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__shift_reg) 
                                       >> 1U)));
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt = 0U;
                    if ((7U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__bit_cnt))) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state = 3U;
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__bit_cnt 
                            = (7U & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__bit_cnt)));
                    }
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt 
                        = (0x0000000fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt)));
                }
            }
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick_16x) {
                if ((7U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt))) {
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_1) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state = 0U;
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__bit_cnt = 0U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state = 2U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt = 0U;
                    }
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt 
                        = (0x0000000fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt)));
                }
            }
        } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_en) 
                    & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_1)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state = 1U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt = 0U;
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt;
        if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
            if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0U;
            } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
                if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__cs_n_reg = 1U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0U;
                } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
                        = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase)));
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in 
                            = ((0x000000feU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                               << 1U)) 
                               | (IData)(vlSelfRef.flash_miso));
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
                            = (0x0000001fU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)));
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                        if ((7U == (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))) {
                            if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt) 
                                          >> 2U)))) {
                                if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                                    if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf 
                                            = ((0xffffff00U 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf) 
                                               | ((0x000000feU 
                                                   & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                                      << 1U)) 
                                                  | (IData)(vlSelfRef.flash_miso)));
                                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0x0bU;
                                    } else {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf 
                                            = ((0xffff00ffU 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf) 
                                               | (((0x000000feU 
                                                    & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                                       << 1U)) 
                                                   | (IData)(vlSelfRef.flash_miso)) 
                                                  << 8U));
                                    }
                                } else {
                                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf 
                                        = ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))
                                            ? ((0xff00ffffU 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf) 
                                               | (((0x000000feU 
                                                    & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                                       << 1U)) 
                                                   | (IData)(vlSelfRef.flash_miso)) 
                                                  << 0x00000010U))
                                            : ((0x00ffffffU 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf) 
                                               | (((0x000000feU 
                                                    & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                                       << 1U)) 
                                                   | (IData)(vlSelfRef.flash_miso)) 
                                                  << 0x00000018U)));
                                }
                            }
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt 
                                = (7U & ((IData)(1U) 
                                         + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt)));
                        }
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 1U;
                    }
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
                        = (0x0000ffffU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt)));
                }
            } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0U;
            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
                    = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase)));
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
                        = (0x0000001fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)));
                    if ((7U == (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt 
                            = (7U & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt)));
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                        if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
                                = (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_addr 
                                                  >> 8U));
                        } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
                                = (0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_addr);
                        } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt = 0U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0x0aU;
                        }
                    }
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 1U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg 
                        = (1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out) 
                                 >> (7U & ((IData)(7U) 
                                           - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))));
                }
            } else {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
                    = (0x0000ffffU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt)));
            }
        } else if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
            if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
                if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
                            = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase)));
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
                        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
                                = (0x0000001fU & ((IData)(1U) 
                                                  + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)));
                            if ((7U == (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))) {
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt = 0U;
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 8U;
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
                                    = (0x000000ffU 
                                       & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_addr 
                                          >> 0x10U));
                            }
                        } else {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 1U;
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg 
                                = (1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out) 
                                         >> (7U & ((IData)(7U) 
                                                   - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))));
                        }
                    } else {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
                            = (0x0000ffffU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt)));
                    }
                } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
                        = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase)));
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in 
                            = ((0x000000feU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                               << 1U)) 
                               | (IData)(vlSelfRef.flash_miso));
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
                            = (0x0000001fU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)));
                        if ((7U == (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))) {
                            if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id 
                                    = ((0x0000ffffU 
                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id) 
                                       | (((0x000000feU 
                                            & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                               << 1U)) 
                                           | (IData)(vlSelfRef.flash_miso)) 
                                          << 0x00000010U));
                            } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id 
                                    = ((0x00ff00ffU 
                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id) 
                                       | (((0x000000feU 
                                            & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                               << 1U)) 
                                           | (IData)(vlSelfRef.flash_miso)) 
                                          << 8U));
                            } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id 
                                    = ((0x00ffff00U 
                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id) 
                                       | ((0x000000feU 
                                           & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                              << 1U)) 
                                          | (IData)(vlSelfRef.flash_miso)));
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0x0bU;
                            }
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt 
                                = (7U & ((IData)(1U) 
                                         + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt)));
                        }
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 1U;
                    }
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
                        = (0x0000ffffU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt)));
                }
            } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
                        = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase)));
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in 
                            = ((0x000000feU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                               << 1U)) 
                               | (IData)(vlSelfRef.flash_miso));
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
                            = (0x0000001fU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)));
                        if ((7U == (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_reg 
                                = ((0x000000feU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in) 
                                                   << 1U)) 
                                   | (IData)(vlSelfRef.flash_miso));
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_valid = 1U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0x0bU;
                        }
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 1U;
                    }
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
                        = (0x0000ffffU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt)));
                }
            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
                    = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase)));
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
                        = (0x0000001fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)));
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                    if ((7U == (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0x0bU;
                    }
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 1U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg 
                        = (1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out) 
                                 >> (7U & ((IData)(7U) 
                                           - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))));
                }
            } else {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
                    = (0x0000ffffU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt)));
            }
        } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
                        = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase)));
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
                    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
                            = (0x0000001fU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)));
                        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt) 
                             == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_dummy_cycles))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 5U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                        }
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 1U;
                    }
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
                        = (0x0000ffffU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt)));
                }
            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
                    = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase)));
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
                        = (0x0000001fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)));
                    if ((7U == (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt 
                            = (7U & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt)));
                        if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
                                = (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr 
                                                  >> 8U));
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                        } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
                                = (0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr);
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                        } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt))) {
                            if (((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd)) 
                                 | (0x0bU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd)))) {
                                if ((0x0bU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd))) {
                                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 3U;
                                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                                } else {
                                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 5U;
                                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                                }
                            } else {
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 4U;
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
                                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_txdata;
                            }
                        }
                    }
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 1U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg 
                        = (1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out) 
                                 >> (7U & ((IData)(7U) 
                                           - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))));
                }
            } else {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
                    = (0x0000ffffU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt)));
            }
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
                    = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase)));
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
                        = (0x0000001fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)));
                    if ((7U == (7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))) {
                        if ((0x9fU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt = 0U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 6U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                        } else if (((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd)) 
                                    || (0x0bU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd)))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 2U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
                                = (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr 
                                                  >> 0x10U));
                        } else if (((6U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd)) 
                                    || (0xc7U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd)))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0x0bU;
                        } else if ((5U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd))) {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 5U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                        } else {
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 2U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
                                = (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr 
                                                  >> 0x10U));
                        }
                    }
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 1U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg 
                        = (1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out) 
                                 >> (7U & ((IData)(7U) 
                                           - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt)))));
                }
            } else {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
                    = (0x0000ffffU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt)));
            }
        } else {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__cs_n_reg = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__timeout_cnt = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd_start) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_enable))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__cs_n_reg = 0U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 1U;
            } else if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending) 
                         & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_xip_en)) 
                        & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_enable))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__cs_n_reg = 0U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out = 3U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 7U;
            }
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt;
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active) {
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active = 0U;
            }
        } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid) 
                    & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active) {
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active = 0U;
            }
        } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid) 
                    & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold 
                = (3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state));
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__wr_ctrl_pulse = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__shift_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__bit_cnt = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_data_in = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_valid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_error = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__cs_n_reg = 1U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_valid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__timeout_cnt = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter_value 
        = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter 
           & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size)
               ? 0xffffffffU : 0x0000ffffU));
    vlSelfRef.spi_sclk = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg;
    vlSelfRef.spi_mosi = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__mosi_reg;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count 
        = (0x0000000fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr) 
                          - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr)));
    if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb 
            = (0x0000000fU & ((IData)(1U) << (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned 
            = VL_SHIFTL_III(32,32,32, (0x000000ffU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0), 
                            VL_SHIFTL_III(32,32,32, 
                                          (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0), 3U));
    } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size))) {
        if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb 
                = (0x0000000fU & 0x0cU);
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned 
                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0 
                   << 0x00000010U);
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb 
                = (0x0000000fU & 3U);
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned 
                = (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0);
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb 
            = (0x0000000fU & 0x0fU);
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__full 
        = (((1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr) 
                   >> 3U)) != (1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr) 
                                     >> 3U))) & ((7U 
                                                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr)) 
                                                 == 
                                                 (7U 
                                                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__empty 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr) 
           == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_en 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__full)) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_valid));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_1 
        = ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2))) 
           || (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_0));
    vlSelfRef.flash_cs_n = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__cs_n_reg;
    vlSelfRef.flash_sclk = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg;
    vlSelfRef.flash_mosi = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_opcode 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_opcode;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs1 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs1;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wvalid 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__w_done)) 
           & (1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__aw_done)) 
           & (1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff2 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           && (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff1));
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_write) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale 
                = (3U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                         >> 2U));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_enable 
                = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                         >> 7U));
        }
        if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite))) {
            if ((0U != (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                if ((0x0cU == (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_en 
                        = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                 >> 0x10U));
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_en 
                        = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                 >> 0x11U));
                }
            }
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick_16x = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick = 0U;
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter) 
             >= (0x0000ffffU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_div) 
                                - (IData)(1U))))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick_16x = 1U;
            if ((0x0fU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick = 1U;
            } else {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt 
                    = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt)));
            }
        } else {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter 
                = (0x0000ffffU & ((IData)(1U) + (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter)));
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt;
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd_start) 
             & (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd_start = 0U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awvalid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_awready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r = 1U;
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wvalid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_wready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r = 1U;
        }
        if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r)) 
             & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r)))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r = 1U;
            if ((0x00000020U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured))) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                              >> 4U)))) {
                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                  >> 3U)))) {
                        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                      >> 2U)))) {
                            if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                          >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured)))) {
                                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_dummy_cycles 
                                        = (0x0000000fU 
                                           & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata);
                                }
                            }
                        }
                    }
                }
            } else if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured))) {
                if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured))) {
                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                  >> 2U)))) {
                        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                      >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured)))) {
                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_clkdiv 
                                    = (0x0000ffffU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata);
                            }
                        }
                    }
                } else if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                     >> 2U)))) {
                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                  >> 1U)))) {
                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured)))) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_txdata 
                                = (0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata);
                        }
                    }
                }
            } else if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured))) {
                if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured))) {
                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                  >> 1U)))) {
                        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured)))) {
                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr 
                                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata;
                        }
                    }
                } else if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                     >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured)))) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd 
                            = (0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata);
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd_start 
                            = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata 
                                     >> 8U));
                    }
                }
            } else if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                                 >> 2U)))) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured) 
                              >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured)))) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_enable 
                            = (1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata);
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_xip_en 
                            = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata 
                                     >> 1U));
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr_width 
                            = (3U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata 
                                     >> 2U));
                    }
                }
            }
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_bready))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r = 0U;
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r = 0U;
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_enable = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_en = 1U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_en = 1U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick_16x = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt 
            = __Vdly__soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_enable = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_xip_en = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr_width = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd_start = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_txdata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_clkdiv = 3U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_dummy_cycles = 8U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active)
            ? ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)
                ? (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0)
                : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr)
            : ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))
                ? (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0)
                : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr));
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_5 
        = ((0x00010000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr) 
           & (0x00014000U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr));
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_6 
        = ((0x40000000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr) 
           & (0x41000000U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr));
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_7 
        = ((0x20000000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr) 
           & (0x20010000U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_0 
        = ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2))) 
           || (IData)(vlSelfRef.uart_rx));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt) 
           >= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_clkdiv));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_wready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_decerr 
        = (1U & (~ ((0x00000100U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr) 
                    | ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_5) 
                       | ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_6) 
                          | (IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_7))))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel 
        = ((0x00000100U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr)
            ? 0U : ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_5)
                     ? 1U : ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_6)
                              ? 2U : ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_7)
                                       ? 3U : 0U))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wdata = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wdata = 0U;
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr 
                = (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0);
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wdata;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr;
        }
    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr 
            = (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0);
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wdata;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr;
    }
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_1 
        = ((0x00010000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr) 
           & (0x00014000U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr));
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_2 
        = ((0x40000000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr) 
           & (0x41000000U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr));
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_3 
        = ((0x20000000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr) 
           & (0x20010000U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready 
        = ((~ (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb))) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_bready 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid) 
           & (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff1 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           && (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d));
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite))) {
            if ((0U != (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                if ((0x0cU == (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_div 
                        = (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata);
                }
            }
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awvalid) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_awready))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured 
                = (0x0000003fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awaddr);
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_div = 0x0036U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_awready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_decerr 
        = (1U & (~ ((0x00000100U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr) 
                    | ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_1) 
                       | ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_2) 
                          | (IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_3))))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel 
        = ((0x00000100U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr)
            ? 0U : ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_1)
                     ? 1U : ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_2)
                              ? 2U : ((IData)(soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_3)
                                       ? 3U : 0U))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)
            ? (4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))
            : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_arvalid 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_arvalid)) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready));
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid 
                = (3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state));
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot 
                = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_instr)
                    ? 4U : 0U);
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_arvalid;
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot 
            = ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))
                ? 0U : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_instr)
                         ? 4U : 0U));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_arvalid) 
               | (3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)
            ? (2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))
            : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_bready));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_wvalid 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_wvalid)) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_bready));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_awvalid 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_awvalid)) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_bready));
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wvalid;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_wvalid;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_awvalid;
        }
    } else {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wvalid;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_wvalid;
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_awvalid) 
               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wstrb = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wstrb = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wstrb = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr) 
           == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_irq_aggregator__DOT__timer_irq 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_int_en) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__raw_int));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_rready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_rready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_rready = 0U;
    if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_rready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready;
            }
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_rready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready;
            }
        }
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_rready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready;
            }
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_bready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_bready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_bready = 0U;
    if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_bready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready;
            }
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_bready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready;
            }
        }
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_bready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready;
            }
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_pc 
        = (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch) 
            & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store))
            ? (0xfffffffeU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out)
            : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc);
    __Vtableidx1 = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_state[0U] 
        = Vsoc_top__ConstPool__TABLE_h3c1c5ec4_0[__Vtableidx1][0U];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_state[1U] 
        = Vsoc_top__ConstPool__TABLE_h3c1c5ec4_0[__Vtableidx1][1U];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_state[2U] 
        = Vsoc_top__ConstPool__TABLE_h3c1c5ec4_0[__Vtableidx1][2U];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_state[3U] 
        = Vsoc_top__ConstPool__TABLE_h3c1c5ec4_0[__Vtableidx1][3U];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_write = 0U;
    if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wstrb = 0x0fU;
    } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wdata 
            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 
                << 0x00000010U) | (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wstrb 
            = ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1)
                ? 0x0cU : 3U);
    } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wdata 
            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 
                << 0x00000018U) | ((0x00ff0000U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 
                                                   << 0x00000010U)) 
                                   | ((0x0000ff00U 
                                       & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 
                                          << 8U)) | 
                                      (0x000000ffU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wstrb 
            = (0x0000000fU & ((IData)(1U) << (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1)));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_eq 
        = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
           == vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_lts 
        = VL_LTS_III(32, vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1, vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_ltu 
        = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
           < vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lbu_lhu_lw 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lbu) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lhu) 
              | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lw)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_araddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_araddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arvalid = 0U;
    if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state)) 
          & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid)) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_decerr)))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel))) {
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arvalid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arprot 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot;
            }
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arvalid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_araddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arprot 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot;
            }
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arprot 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_araddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arvalid = 1U;
            }
        }
    } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arprot 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_prot_reg;
            }
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arprot 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_prot_reg;
            }
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arprot 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_prot_reg;
            }
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wvalid = 0U;
    if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wstrb 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
            }
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wstrb 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
            }
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wstrb 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
            }
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awaddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awaddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awaddr = 0U;
    if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state)) 
          & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid)) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_decerr)))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel))) {
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awprot = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awvalid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awaddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr;
            }
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awprot = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awvalid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awaddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr;
            }
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awprot = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awvalid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awaddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr;
            }
        }
    }
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resume_pending_q) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_written = 0U;
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq = 0U;
        }
        if (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dbg_halted_q)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted))) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow 
                = (0x000000c0U | (0xfffffe3fU & __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow));
        }
        if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) 
             & (0x10U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))) {
            if ((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive)) 
                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive = 1U;
            } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive) {
                if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive 
                        = (1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata);
                    if ((0x40000000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata)) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__haltreq = 0U;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq = 1U;
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__haltreq 
                            = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
                               >> 0x1fU);
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq = 0U;
                    }
                }
                if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__haltreq = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__cmderr = 0U;
                }
            }
        } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) {
            if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                          >> 6U)))) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                              >> 5U)))) {
                    if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                      >> 3U)))) {
                            if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                    if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy = 1U;
                                    } else if ((1U 
                                                & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb) 
                                                   & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
                                                      >> 0x0aU)))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__cmderr = 0U;
                                    }
                                }
                            }
                        }
                    } else if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                         >> 3U)))) {
                        if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                            if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                          >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))) {
                                    if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 
                                            = ((0xffffff00U 
                                                & __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0) 
                                               | (0x000000ffU 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                    }
                                    if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 
                                            = ((0xffff00ffU 
                                                & __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0) 
                                               | (0x0000ff00U 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                    }
                                    if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 
                                            = ((0xff00ffffU 
                                                & __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0) 
                                               | (0x00ff0000U 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                    }
                                    if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 
                                            = ((0x00ffffffU 
                                                & __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0) 
                                               | (0xff000000U 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy) {
            __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy = 0U;
            if (((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                  >> 0x00000011U) & (2U != (7U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                                  >> 0x00000014U))))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__cmderr = 2U;
            } else if ((IData)((0x00021000U == (0x0002f000U 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)))) {
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted) {
                    if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                  >> 0x00000010U)))) {
                        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 
                            = ((0U != (0x0000001fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command))
                                ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs
                               [(0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)]
                                : 0U);
                    }
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__cmderr = 2U;
                }
            } else if ((IData)((0x00020301U == (0x0003ffffU 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)))) {
                __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 = 0x40000100U;
            } else if ((IData)((0x000207b1U == (0x0002ffffU 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)))) {
                if ((0x00010000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_shadow 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_written = 1U;
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_pc;
                }
            } else if ((IData)((0x000207b0U == (0x0002ffffU 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)))) {
                if ((0x00010000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0;
                } else {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow;
                }
            } else if ((IData)((0x00020000U == (0x0002f000U 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)))) {
                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                              >> 0x00000010U)))) {
                    __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 = 0U;
                }
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__cmderr = 2U;
            }
        }
    } else {
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow = 0x400001c3U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy = 0U;
        __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__haltreq = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_shadow = 0x00010000U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__cmderr = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_written = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow;
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0] 
            = __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v0;
    }
    if (__VdlySet__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs[__VdlyDim0__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1] 
            = __VdlyVal__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs__v1;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_access 
        = ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state)) 
           & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arvalid) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_arready)));
    if (((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)) 
          & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_data_r;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_strb_r;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0 
            = (0x00000fffU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_addr_r));
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0 = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0 = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0 
            = (0x00000fffU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_access)
                               ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_araddr 
                                  >> 2U) : 0U));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rd 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rd;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs2 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs2;
    if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_getq 
            = (IData)((0x0000000bU == (0xfe00007fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_setq 
            = (IData)((0x0200000bU == (0xfe00007fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_maskirq 
            = (IData)((0x0600000bU == (0xfe00007fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_timer 
            = (IData)((0x0a00000bU == (0xfe00007fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycle 
            = ((IData)((0xc0002073U == (0xfffff07fU 
                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q))) 
               | (IData)((0xc0102073U == (0xfffff07fU 
                                          & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstr 
            = (IData)((0xc0202073U == (0xfffff07fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycle) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycleh) 
              | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstr) 
                 | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstrh))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resume_pending_q 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           && (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req));
    if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst) 
         & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1 
            = (0x0000001fU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
                              >> 0x0fU));
        if ((IData)((0x0000000bU == (0xfe00007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1 
                = (0x00000020U | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1));
        }
        if ((IData)((0x0400000bU == (0xfe00007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1 = 0x20U;
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1 
        = ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1))
            ? ((0x23U >= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1))
                ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs
               [vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1]
                : 0U) : 0U);
    if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst) 
         & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__compressed_instr = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rd 
            = (0x0000001fU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
                              >> 7U));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2 
            = (0x0000001fU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
                              >> 0x14U));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2 
        = ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2))
            ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs
           [vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2]
            : 0U);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dbg_halted_q 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           && (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted));
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite))) {
            if ((0U != (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                if ((0x0cU == (0x0000000fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__irq_en 
                        = (1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                 >> 0x12U));
                }
            }
        }
        if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req)))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__ebreak_halt_trigger) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_pc 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc;
            } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_req) 
                        & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_allowed))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_pc 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc;
            }
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) 
                      & (0x10U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))))) {
            if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) {
                if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                              >> 6U)))) {
                    if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                  >> 5U)))) {
                        if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                            if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr) 
                                          >> 3U)))) {
                                if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                    if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                        if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                                            if ((1U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                                    = 
                                                    ((0xffffff00U 
                                                      & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command) 
                                                     | (0x000000ffU 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                            if ((2U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                                    = 
                                                    ((0xffff00ffU 
                                                      & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command) 
                                                     | (0x0000ff00U 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                            if ((4U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                                    = 
                                                    ((0xff00ffffU 
                                                      & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command) 
                                                     | (0x00ff0000U 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                            if ((8U 
                                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb))) {
                                                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                                    = 
                                                    ((0x00ffffffU 
                                                      & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command) 
                                                     | (0xff000000U 
                                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted = 0U;
        } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__ebreak_halt_trigger) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted = 1U;
        } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_req) 
                    & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_allowed))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted = 1U;
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__irq_en = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_pc = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx 
        = (0x0000001fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_endian)
                           ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt)
                           : (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen) 
                               - (IData)(1U)) - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt))));
    vlSelfRef.spi_cs_n = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csdef;
    if (((3U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csmode)) 
         & (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state)))) {
        vlSelfRef.spi_cs_n = (((~ ((IData)(1U) << (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csid))) 
                               & (IData)(vlSelfRef.spi_cs_n)) 
                              | (0x0fU & ((1U & (~ 
                                                 ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csdef) 
                                                  >> (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csid)))) 
                                          << (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csid))));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lui) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_auipc) 
              | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jal)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal_jalr_addi_add_sub 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lui) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_auipc) 
              | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jal) 
                 | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jalr) 
                    | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_addi) 
                       | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_add) 
                          | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sub)))))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_slti_blt_slt 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slti) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_blt) 
              | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slt)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sltiu_bltu_sltu 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltiu) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bltu) 
              | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltu)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_compare 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slti) 
              | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slt) 
                 | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltiu) 
                    | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltu)))));
    if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_beq 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bne 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00001000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_blt 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00004000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bge 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00005000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bltu 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00006000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bgeu 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00007000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lb 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lh 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0x00001000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lw 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0x00002000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lbu 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0x00004000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lhu 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0x00005000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sb 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sb_sh_sw) 
               & (0U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sh 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sb_sh_sw) 
               & (0x00001000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sw 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sb_sh_sw) 
               & (0x00002000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_addi 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & (0U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slti 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & (0x00002000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltiu 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & (0x00003000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xori 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & (0x00004000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ori 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & (0x00006000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_andi 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & (0x00007000U == (0x00007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slli 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & (0x00001000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srli 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & (0x00005000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srai 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & (0x40005000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_slli_srli_srai 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
               & ((IData)((0x00001000U == (0xfe007000U 
                                           & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q))) 
                  | ((IData)((0x00005000U == (0xfe007000U 
                                              & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q))) 
                     | (IData)((0x40005000U == (0xfe007000U 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q))))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jalr) 
               | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm) 
                  & ((0U == (7U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                   >> 0x0cU))) | ((2U 
                                                   == 
                                                   (7U 
                                                    & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                       >> 0x0cU))) 
                                                  | ((3U 
                                                      == 
                                                      (7U 
                                                       & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                          >> 0x0cU))) 
                                                     | ((4U 
                                                         == 
                                                         (7U 
                                                          & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                             >> 0x0cU))) 
                                                        | ((6U 
                                                            == 
                                                            (7U 
                                                             & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                                >> 0x0cU))) 
                                                           | (7U 
                                                              == 
                                                              (7U 
                                                               & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                                  >> 0x0cU))))))))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal_jalr_addi_add_sub = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_compare = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jal)
                ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j
                : (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lui) 
                    | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_auipc))
                    ? VL_SHIFTL_III(32,32,32, (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                               >> 0x0cU), 0x0000000cU)
                    : (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jalr) 
                        | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu) 
                           | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm)))
                        ? VL_EXTENDS_II(32,12, (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                >> 0x14U))
                        : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu)
                            ? VL_EXTENDS_II(32,13, 
                                            ((((2U 
                                                & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                   >> 0x0000001eU)) 
                                               | (1U 
                                                  & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                     >> 7U))) 
                                              << 0x0000000bU) 
                                             | ((0x000007e0U 
                                                 & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                    >> 0x00000014U)) 
                                                | (0x0000001eU 
                                                   & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                      >> 7U)))))
                            : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sb_sh_sw)
                                ? VL_EXTENDS_II(32,12, 
                                                ((0x00000fe0U 
                                                  & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                     >> 0x00000014U)) 
                                                 | (0x0000001fU 
                                                    & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
                                                       >> 7U))))
                                : 0U)))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_add 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sub 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0x40000000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sll 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0x00001000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slt 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0x00002000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltu 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0x00003000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xor 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0x00004000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srl 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0x00005000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sra 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0x40005000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_or 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0x00006000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_and 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & (0x00007000U == (0xfe007000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sll_srl_sra 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg) 
               & ((IData)((0x00001000U == (0xfe007000U 
                                           & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q))) 
                  | ((IData)((0x00005000U == (0xfe007000U 
                                              & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q))) 
                     | (IData)((0x40005000U == (0xfe007000U 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q))))));
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata;
    }
    if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst) 
         & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_waitirq 
            = (IData)((0x0800000bU == (0xfe00007fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_retirq 
            = (IData)((0x0400000bU == (0xfe00007fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm 
            = (0x13U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu 
            = (3U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sb_sh_sw 
            = (0x23U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j 
            = ((0x000fffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j) 
               | (0xfff00000U & VL_EXTENDS_II(32,21, 
                                              (0x001ffffeU 
                                               & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
                                                  >> 0x0000000bU)))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j 
            = ((0xfffff801U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j) 
               | (0x000007feU & (VL_EXTENDS_II(32,21, 
                                               (0x001ffffeU 
                                                & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
                                                   >> 0x0000000bU))) 
                                 >> 9U)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j 
            = ((0xfffff7ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j) 
               | (0x00000800U & (VL_EXTENDS_II(32,21, 
                                               (0x001ffffeU 
                                                & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
                                                   >> 0x0000000bU))) 
                                 << 2U)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j 
            = ((0xfff00fffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j) 
               | (0x000ff000U & (VL_EXTENDS_II(32,21, 
                                               (0x001ffffeU 
                                                & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
                                                   >> 0x0000000bU))) 
                                 << 0x0000000bU)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j 
            = ((0xfffffffeU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j) 
               | (1U & VL_EXTENDS_II(1,21, (0x001ffffeU 
                                            & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
                                               >> 0x0000000bU)))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_auipc 
            = (0x17U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lui 
            = (0x37U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jal 
            = (0x6fU == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jalr 
            = (IData)((0x00000067U == (0x0000707fU 
                                       & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu 
            = (0x63U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg 
            = (0x33U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle));
    }
    if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_fence = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_aw_done = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_w_done = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__timeout_err = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_addr = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_compare = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_beq = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bne = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_blt = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bge = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bltu = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bgeu = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_addi = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slti = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltiu = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xori = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ori = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_andi = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_add = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sub = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sll = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slt = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltu = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xor = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srl = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sra = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_or = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_and = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_csb0 
        = ((1U & (~ ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured) 
                       & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)) 
                      & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))) 
                     & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending))))) 
           && (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_access))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata = 0U;
    if ((0x40U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_write = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata 
                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc 
                   + ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr)
                       ? 2U : 4U));
        } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store) 
                    & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch)))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_write = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata 
                = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_stalu)
                    ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_q
                    : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out);
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_write = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata 
                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc 
                   | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr));
        } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_write = 1U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending_ack;
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_1 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy) 
           & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
              >> 0x00000011U));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_imm 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_imm;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__ebreak_halt_trigger 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger_q) 
           & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ecall_ebreak)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_3 
        = (IData)(((0x00001000U == (0x0000f000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)) 
                   & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_req 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive) 
           & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__haltreq)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__launch_next_insn 
        = ((0x40U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state)) 
           & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger) 
              & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_delay) 
                 | ((~ (0U != ((~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_mask) 
                               & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending))) 
                    | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active)))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0 = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out = 0U;
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_beq) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_eq;
    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bne) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0 
            = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_eq)));
    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bge) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0 
            = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_lts)));
    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bgeu) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0 
            = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_ltu)));
    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_slti_blt_slt) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_lts;
    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sltiu_bltu_sltu) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_ltu;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal_jalr_addi_add_sub) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sub)
                ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                   - vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2)
                : (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                   + vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2));
    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_compare) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0;
    } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xori) 
                | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xor))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out 
            = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
               ^ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2);
    } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ori) 
                | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_or))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out 
            = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
               | vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2);
    } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_andi) 
                | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_and))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out 
            = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
               & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2);
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0ULL;
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lui) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000006c7569ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_auipc) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000006175697063ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jal) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000006a616cULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jalr) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x000000006a616c72ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_beq) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000626571ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bne) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000626e65ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_blt) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000626c74ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bge) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000626765ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bltu) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000626c7475ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bgeu) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000062676575ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lb) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000006c62ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lh) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000006c68ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lw) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000006c77ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lbu) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000006c6275ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lhu) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000006c6875ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sb) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000007362ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sh) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000007368ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sw) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000007377ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_addi) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000061646469ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slti) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000736c7469ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltiu) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x000000736c746975ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xori) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000786f7269ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ori) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000006f7269ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_andi) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000616e6469ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slli) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000736c6c69ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srli) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000073726c69ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srai) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000073726169ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_add) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000616464ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sub) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000737562ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sll) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000736c6cULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slt) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000736c74ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltu) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000000736c7475ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xor) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000786f72ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srl) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x000000000073726cULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sra) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000737261ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_or) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000006f72ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_and) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000000616e64ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycle) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0072646379636c65ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycleh) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x72646379636c6568ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstr) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x007264696e737472ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstrh) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x7264696e73747268ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_fence) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000066656e6365ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_getq) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000067657471ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_setq) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000000073657471ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_retirq) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0000726574697271ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_maskirq) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x006d61736b697271ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_waitirq) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x0077616974697271ULL;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_timer) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = 0x00000074696d6572ULL;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_instr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_ascii_instr;
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_next) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_opcode 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_opcode;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs1 
                = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs1));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rd 
                = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rd));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs2 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs2;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_imm 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_imm;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_instr 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_ascii_instr;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_opcode 
                = ((3U == (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode))
                    ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode
                    : (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs1 
                = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rd 
                = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rd));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs2 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_imm 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_instr 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr;
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst 
        = __Vdly__soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____VdfgRegularize_had7d1046_0_1 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata) 
              | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_allowed 
        = ((~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch) 
               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____VdfgRegularize_had7d1046_0_1))) 
           & ((~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid) 
                  | (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state)))) 
              & (0x40U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))));
}

void Vsoc_top___024root___nba_sequent__TOP__2(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___nba_sequent__TOP__2\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__apb_write) {
            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                          >> 6U)))) {
                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                              >> 5U)))) {
                    if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                        if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                      >> 3U)))) {
                            if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_ds 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_ds 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                          >> 2U)))) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_pue 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_pue 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                        }
                        if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                          >> 2U)))) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                        }
                    }
                    if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                  >> 4U)))) {
                        if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                      >> 3U)))) {
                            if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                        }
                        if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                          >> 2U)))) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                            if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                        }
                    }
                }
                if ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                        if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                            if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_en 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_en 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                          >> 2U)))) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_out_xor 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_out_xor 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                        }
                        if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                      >> 3U)))) {
                            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                          >> 2U)))) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                        }
                    }
                    if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                  >> 4U)))) {
                        if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                      >> 3U)))) {
                            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                          >> 2U)))) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                        }
                        if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                          >> 2U)))) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if ((0x00000040U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                              >> 5U)))) {
                    if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                  >> 4U)))) {
                        if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                      >> 3U)))) {
                            if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                          >> 2U)))) {
                                if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                              >> 1U)))) {
                                    if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_sel 
                                            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_sel 
                                                & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)) 
                                               | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip 
            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip 
                | (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2)) 
               & (~ (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__apb_write) 
                      & (0x34U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)))
                      ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                         & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)
                      : 0U)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip 
            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip 
                | vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2) 
               & (~ (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__apb_write) 
                      & (0x2cU == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)))
                      ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                         & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)
                      : 0U)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip 
            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip 
                | ((~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2) 
                   & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_prev)) 
               & (~ (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__apb_write) 
                      & (0x24U == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)))
                      ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                         & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)
                      : 0U)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip 
            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip 
                | ((~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_prev) 
                   & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2)) 
               & (~ (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__apb_write) 
                      & (0x1cU == (0x0000007fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)))
                      ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                         & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask)
                      : 0U)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_prev 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage1;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage1 
            = vlSelfRef.gpio_in;
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_ds = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_pue = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_en = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_sel = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_out_xor = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_prev = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2 = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage1 = 0U;
    }
    vlSelfRef.gpio_oe = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en;
    vlSelfRef.gpio_out = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_out_xor 
                          ^ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val);
}

void Vsoc_top___024root___nba_sequent__TOP__3(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___nba_sequent__TOP__3\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.jtag_tdo = (1U & ((0x0bU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state))
                                 ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_shift)
                                 : ((4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)) 
                                    && (1U & ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))
                                               ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift
                                               : ((0x10U 
                                                   == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))
                                                   ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift
                                                   : 
                                                  ((0x11U 
                                                    == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))
                                                    ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift)
                                                    : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg))))))));
}

extern const VlUnpacked<CData/*1:0*/, 1024> Vsoc_top__ConstPool__TABLE_hff2ee94f_0;
extern const VlUnpacked<CData/*4:0*/, 1024> Vsoc_top__ConstPool__TABLE_h7cb69f99_0;
extern const VlUnpacked<CData/*4:0*/, 1024> Vsoc_top__ConstPool__TABLE_hdb48db2f_0;

void Vsoc_top___024root___nba_sequent__TOP__4(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___nba_sequent__TOP__4\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*9:0*/ __Vtableidx4;
    __Vtableidx4 = 0;
    // Body
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d 
        = vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d;
    if ((((8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)) 
          & (0x11U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg))) 
         & (0U != (3U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift))))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_write_tck 
            = (2U == (3U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_addr_tck 
            = (0x0000007fU & (IData)((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                      >> 0x22U)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_wdata_tck 
            = (IData)((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                       >> 2U));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
        = vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift_rev 
        = (((QData)((IData)((((((4U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift) 
                                       << 2U)) | ((2U 
                                                   & ((IData)(
                                                              (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                               >> 1U)) 
                                                      << 1U)) 
                                                  | (1U 
                                                     & (IData)(
                                                               (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                >> 2U))))) 
                               << 6U) | (((2U & ((IData)(
                                                         (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                          >> 3U)) 
                                                 << 1U)) 
                                          | (1U & (IData)(
                                                          (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                           >> 4U)))) 
                                         << 4U)) | 
                             ((((2U & ((IData)((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                >> 5U)) 
                                       << 1U)) | (1U 
                                                  & (IData)(
                                                            (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                             >> 6U)))) 
                               << 2U) | ((2U & ((IData)(
                                                        (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                         >> 7U)) 
                                                << 1U)) 
                                         | (1U & (IData)(
                                                         (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                          >> 8U)))))))) 
            << 0x00000020U) | (QData)((IData)((((((
                                                   (((2U 
                                                      & ((IData)(
                                                                 (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                  >> 9U)) 
                                                         << 1U)) 
                                                     | (1U 
                                                        & (IData)(
                                                                  (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                   >> 0x0000000aU)))) 
                                                    << 6U) 
                                                   | (((2U 
                                                        & ((IData)(
                                                                   (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                    >> 0x0000000bU)) 
                                                           << 1U)) 
                                                       | (1U 
                                                          & (IData)(
                                                                    (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                     >> 0x0000000cU)))) 
                                                      << 4U)) 
                                                  | ((((2U 
                                                        & ((IData)(
                                                                   (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                    >> 0x0000000dU)) 
                                                           << 1U)) 
                                                       | (1U 
                                                          & (IData)(
                                                                    (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                     >> 0x0000000eU)))) 
                                                      << 2U) 
                                                     | ((2U 
                                                         & ((IData)(
                                                                    (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                     >> 0x0000000fU)) 
                                                            << 1U)) 
                                                        | (1U 
                                                           & (IData)(
                                                                     (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                      >> 0x00000010U)))))) 
                                                 << 0x00000018U) 
                                                | ((((((2U 
                                                        & ((IData)(
                                                                   (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                    >> 0x00000011U)) 
                                                           << 1U)) 
                                                       | (1U 
                                                          & (IData)(
                                                                    (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                     >> 0x00000012U)))) 
                                                      << 6U) 
                                                     | (((2U 
                                                          & ((IData)(
                                                                     (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                      >> 0x00000013U)) 
                                                             << 1U)) 
                                                         | (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                       >> 0x00000014U)))) 
                                                        << 4U)) 
                                                    | ((((2U 
                                                          & ((IData)(
                                                                     (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                      >> 0x00000015U)) 
                                                             << 1U)) 
                                                         | (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                       >> 0x00000016U)))) 
                                                        << 2U) 
                                                       | ((2U 
                                                           & ((IData)(
                                                                      (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                       >> 0x00000017U)) 
                                                              << 1U)) 
                                                          | (1U 
                                                             & (IData)(
                                                                       (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                        >> 0x00000018U)))))) 
                                                   << 0x00000010U)) 
                                               | (((((((2U 
                                                        & ((IData)(
                                                                   (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                    >> 0x00000019U)) 
                                                           << 1U)) 
                                                       | (1U 
                                                          & (IData)(
                                                                    (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                     >> 0x0000001aU)))) 
                                                      << 6U) 
                                                     | (((2U 
                                                          & ((IData)(
                                                                     (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                      >> 0x0000001bU)) 
                                                             << 1U)) 
                                                         | (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                       >> 0x0000001cU)))) 
                                                        << 4U)) 
                                                    | ((((2U 
                                                          & ((IData)(
                                                                     (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                      >> 0x0000001dU)) 
                                                             << 1U)) 
                                                         | (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                       >> 0x0000001eU)))) 
                                                        << 2U) 
                                                       | ((2U 
                                                           & ((IData)(
                                                                      (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                       >> 0x0000001fU)) 
                                                              << 1U)) 
                                                          | (1U 
                                                             & (IData)(
                                                                       (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                        >> 0x00000020U)))))) 
                                                   << 8U) 
                                                  | (((((2U 
                                                         & ((IData)(
                                                                    (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                     >> 0x00000021U)) 
                                                            << 1U)) 
                                                        | (1U 
                                                           & (IData)(
                                                                     (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                      >> 0x00000022U)))) 
                                                       << 6U) 
                                                      | (((2U 
                                                           & ((IData)(
                                                                      (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                       >> 0x00000023U)) 
                                                              << 1U)) 
                                                          | (1U 
                                                             & (IData)(
                                                                       (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                        >> 0x00000024U)))) 
                                                         << 4U)) 
                                                     | ((((2U 
                                                           & ((IData)(
                                                                      (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                       >> 0x00000025U)) 
                                                              << 1U)) 
                                                          | (1U 
                                                             & (IData)(
                                                                       (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                        >> 0x00000026U)))) 
                                                         << 2U) 
                                                        | ((2U 
                                                            & ((IData)(
                                                                       (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                        >> 0x00000027U)) 
                                                               << 1U)) 
                                                           | (1U 
                                                              & (IData)(
                                                                        (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift 
                                                                         >> 0x00000028U)))))))))));
    __Vtableidx4 = (((IData)(vlSelfRef.jtag_tdi) << 9U) 
                    | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_shift) 
                        << 4U) | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)));
    if ((1U & Vsoc_top__ConstPool__TABLE_hff2ee94f_0
         [__Vtableidx4])) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg 
            = Vsoc_top__ConstPool__TABLE_h7cb69f99_0
            [__Vtableidx4];
    }
    if ((2U & Vsoc_top__ConstPool__TABLE_hff2ee94f_0
         [__Vtableidx4])) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_shift 
            = Vsoc_top__ConstPool__TABLE_hdb48db2f_0
            [__Vtableidx4];
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state 
        = vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_dmireset_pulse 
        = ((8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)) 
           & ((0x10U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg)) 
              & (IData)((0U != (0x00030000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift)))));
}

extern const VlUnpacked<IData/*31:0*/, 16> Vsoc_top__ConstPool__TABLE_h1e1d6789_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_h27ce561f_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_hc27dba7d_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_hc596960b_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_h88828eae_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_h9b50a213_0;

void Vsoc_top___024root___nba_sequent__TOP__5(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___nba_sequent__TOP__5\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_1;
    soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_1 = 0;
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*3:0*/ __Vtableidx5;
    __Vtableidx5 = 0;
    // Body
    if (vlSelfRef.soc_top__DOT__rst_ff2) {
        if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state))) {
            if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state))) {
                vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 0U;
            } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state))) {
                vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 0U;
            } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rready) 
                        & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rvalid))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rvalid = 0U;
                vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 0U;
            }
        } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state))) {
                if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bready) 
                     & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bvalid))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bvalid = 0U;
                    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 0U;
                }
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__apb_rdata_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_prdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__apb_slverr_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pslverr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_psel = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable = 0U;
                if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__is_write_txn) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bvalid = 1U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bresp 
                        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pslverr)
                            ? 2U : 0U);
                    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 3U;
                    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured = 0U;
                    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured = 0U;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rvalid = 1U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rdata 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_prdata;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rresp 
                        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pslverr)
                            ? 2U : 0U);
                    vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 4U;
                }
            }
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state))) {
            vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 2U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable = 1U;
        } else {
            if ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured) 
                  | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid) 
                     & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready))) 
                 & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured) 
                    | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wvalid) 
                       & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_wready))))) {
                vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__is_write_txn = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_psel = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite = 1U;
                if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid) 
                     & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awaddr;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pprot 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awprot;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_addr_reg;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pprot 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_prot_reg;
                }
                if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wvalid) 
                     & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_wready))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wdata;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pstrb 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wstrb;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_data_reg;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pstrb 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_strb_reg;
                }
            } else if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arvalid) 
                        & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_arready))) {
                vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__is_write_txn = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_psel = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_araddr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pstrb = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pprot 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arprot;
            }
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready))) {
                vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_addr_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awaddr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_prot_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awprot;
            }
            if (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wvalid) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_wready))) {
                vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_data_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_strb_reg 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wstrb;
            }
        }
    } else {
        vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 0U;
        vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured = 0U;
        vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_addr_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_prot_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_data_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_strb_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__apb_rdata_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__apb_slverr_reg = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__is_write_txn = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_psel = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pstrb = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pprot = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bvalid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bresp = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rvalid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rdata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rresp = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wdata = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wstrb = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awaddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_araddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured 
        = vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured 
        = vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state 
        = vlSelfRef.__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp = 0U;
    __Vtableidx5 = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pstrb;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask 
        = Vsoc_top__ConstPool__TABLE_h1e1d6789_0[__Vtableidx5];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata = 0xdeadbeefU;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid = 0U;
    if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rresp;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rvalid;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_data_reg;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg;
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp = 0U;
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rdata_r;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid 
                    = (2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state));
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rdata_reg;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg;
            }
        }
    } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp = 3U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata = 0xdeaddeadU;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid = 1U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid = 0U;
    if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bresp;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bvalid;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r;
            }
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp = 2U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg;
        }
    } else if ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp = 3U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid = 1U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_wready 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured)) 
           & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured)) 
           & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 1U;
    if ((0x00000040U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        } else if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        } else if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        }
    } else if ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    }
                } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                }
            } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                }
            } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            }
        } else if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                }
            } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            }
        } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            }
        } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        }
    } else if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                }
            } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            }
        } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            }
        } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        }
    } else if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            }
        } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        }
    } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        }
    } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
    } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel 
        = (((0x20000000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr) 
            & (0x20000fffU >= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))
            ? 0U : (((0x20001000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr) 
                     & (0x20001fffU >= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))
                     ? 1U : (((0x20002000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr) 
                              & (0x20002fffU >= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))
                              ? 2U : (((0x20003000U 
                                        <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr) 
                                       & (0x20003fffU 
                                          >= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))
                                       ? 3U : (((0x20004000U 
                                                 <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr) 
                                                & (0x20004fffU 
                                                   >= vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))
                                                ? 4U
                                                : 7U)))));
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rvalid 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid;
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rvalid = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_bvalid 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_ready 
        = ((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid)) 
            & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_bready)) 
           | (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready = 0U;
    if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wstrb 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_wready;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_wready;
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready 
                = ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))
                    ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_wready)
                    : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_wready));
        }
    } else if ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready = 0U;
    if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state)) 
          & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid)) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_decerr)))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awprot = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awaddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_awready;
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready 
                = ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel))
                    ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_awready)
                    : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_awready));
        }
    } else if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state)) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid)) 
                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_decerr))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready = 1U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_arready 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready) 
           & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured)) 
              & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid))));
    __Vtableidx2 = (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel) 
                     << 1U) | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_psel));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart 
        = Vsoc_top__ConstPool__TABLE_h27ce561f_0[__Vtableidx2];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_timer 
        = Vsoc_top__ConstPool__TABLE_hc27dba7d_0[__Vtableidx2];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_gpio 
        = Vsoc_top__ConstPool__TABLE_hc596960b_0[__Vtableidx2];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_spi 
        = Vsoc_top__ConstPool__TABLE_h88828eae_0[__Vtableidx2];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_debug 
        = Vsoc_top__ConstPool__TABLE_h9b50a213_0[__Vtableidx2];
    if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata;
    } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word 
            = ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1)
                ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata 
                   >> 0x10U) : (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata));
    } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word 
            = ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1)
                ? ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1)
                    ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata 
                       >> 0x18U) : (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata 
                                                   >> 0x10U)))
                : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1)
                    ? (0x000000ffU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata 
                                      >> 8U)) : (0x000000ffU 
                                                 & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata)));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_ready) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wready 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active)
            ? ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready))
            : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awready 
        = (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active)) 
            & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid))
            ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready)
            : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active) 
               & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready = 0U;
    if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state)) 
          & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid)) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_decerr)))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arvalid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_araddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arprot 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready 
                    = (1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_arready));
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready 
                    = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg)));
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready 
                = (1U & ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel))
                          ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_arready)
                          : (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg))));
        }
    } else {
        if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
            if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
                if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arprot 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_prot_reg;
                }
            }
        }
        if ((1U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
            if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state)) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid)) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_decerr))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready = 1U;
            }
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT____VdfgRegularize_hf7b9a0fb_0_0 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_gpio));
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_timer) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__apb_write 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__prdata_timer 
            = ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                ? ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                    ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                     ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter)))
                        : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                     ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_reg)))
                    : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                     ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_irq_aggregator__DOT__timer_irq)))
                        : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                     ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__raw_int)))))
                : ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                    ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? 0U : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                 ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                          ? 0U : (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_enable) 
                                                   << 7U) 
                                                  | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_mode) 
                                                      << 6U) 
                                                     | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_int_en) 
                                                         << 5U) 
                                                        | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale) 
                                                            << 2U) 
                                                           | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size) 
                                                               << 1U) 
                                                              | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_one_shot)))))))))
                    : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                     ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter_value))
                        : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                     ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_reg)))));
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__apb_write = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__prdata_timer = 0U;
    }
    soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_1 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_spi));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_0 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_debug));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer)
            ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata
            : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_arready 
        = (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active)) 
            & (3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)))
            ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready)
            : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active) 
               & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__apb_write 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT____VdfgRegularize_hf7b9a0fb_0_0) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pslverr 
        = ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
            ? ((1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel) 
                      >> 1U)) || (1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel)))
            : ((1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel) 
                      >> 1U)) && ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))) 
                                  && ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid)) 
                                      & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT____VdfgRegularize_hf7b9a0fb_0_0)))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_write 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__apb_write) 
           & (0U == (0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_write 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__apb_write) 
           & (0x18U == (0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_write 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__apb_write) 
           & (8U == (0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_write 
        = ((IData)(soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_1) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_read 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite)) 
           & (IData)(soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_1));
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_0) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pstrb;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr 
            = (0x0000007fU & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                              >> 2U));
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_wdata;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_wstrb;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr 
            = (0x0000007fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_addr));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write 
        = (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_0) 
            & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite)) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_valid) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_write)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_0 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_write) 
           & (0x18U == (0x0000003fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_pop = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_spi = 0U;
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_read) {
        if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                      >> 5U)))) {
            if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                        if ((1U & (~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr 
                                      >> 1U)))) {
                            if ((1U & (~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))) {
                                if ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count))) {
                                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_pop = 1U;
                                }
                            }
                        }
                    }
                }
            }
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_spi 
            = ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                ? ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                    ? ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? 0U : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                 ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                     ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                              ? 0U : 
                                             (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst) 
                                               << 1U) 
                                              | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_enable))))
                                 : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                     ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                              ? 0U : 
                                             ((((0U 
                                                 == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state)) 
                                                << 0x0000001fU) 
                                               | ((0U 
                                                   == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count)) 
                                                  << 0x0000001eU)) 
                                              | (((8U 
                                                   == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)) 
                                                  << 0x0000001dU) 
                                                 | (((0U 
                                                      != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state)) 
                                                     << 0x0000001cU) 
                                                    | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count) 
                                                        << 4U) 
                                                       | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)))))))))
                    : ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip)))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ie))))
                        : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_rxmark)))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_txmark))))))
                : ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                    ? ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : ((0U 
                                                  == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count))
                                                  ? 0x80000000U
                                                  : 
                                                 (0x7fffffffU 
                                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo
                                                  [
                                                  (7U 
                                                   & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr))]))))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : ((8U 
                                                  == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)) 
                                                 << 0x0000001fU))))
                        : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen) 
                                                  << 0x00000010U) 
                                                 | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_endian))))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csmode)))))
                    : ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csdef)))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csid))))
                        : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpha))))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sckdiv)))))));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_write 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) 
           & (0x3cU == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_read 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) 
           & ((0x39U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadonaddr)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug = 0U;
    if ((0x00000040U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug = 0U;
    } else if ((0x00000020U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
        if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
            if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))
                            ? 0U : ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))
                                     ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0));
                } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug = 0U;
                } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = (0x20000000U | (0x1fffffffU 
                                          & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug));
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = ((0xff8fffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug) 
                           | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbbusyerror) 
                               << 0x00000016U) | ((
                                                   (0U 
                                                    != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)) 
                                                   << 0x00000015U) 
                                                  | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadonaddr) 
                                                     << 0x00000014U))));
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = (0x00000400U | ((0xfff0001fU 
                                           & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug) 
                                          | (((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size) 
                                                << 0x0000000cU) 
                                               | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbautoincrement) 
                                                  << 0x0000000bU)) 
                                              | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadondata) 
                                                  << 0x0000000aU) 
                                                 | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sberror) 
                                                    << 7U))) 
                                             << 5U)));
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = (7U | vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug);
                }
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug = 0U;
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug = 0U;
        }
    } else if ((0x00000010U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
        if ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug = 0U;
        } else if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
            if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = ((0xffffefffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug) 
                           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy) 
                              << 0x0000000cU));
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = ((0xfffff8ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug) 
                           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__cmderr) 
                              << 8U));
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                        = (1U | (0xfffffff0U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug));
                }
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug = 0U;
            }
        } else if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                = ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))
                    ? 0U : 0x00081000U);
        } else if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                = ((0xfffff1ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug) 
                   | (((4U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)) 
                              << 2U)) | ((2U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)) 
                                                << 1U)) 
                                         | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted))) 
                      << 9U));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                = (0x00000080U | ((0xfffffe3fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug) 
                                  | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted) 
                                     << 8U)));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                = ((0xfffcffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug) 
                   | (((2U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)) 
                              << 1U)) | (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)))) 
                      << 0x00000010U));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                = (2U | (0xfffffff0U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug));
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                = ((0x3fffffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug) 
                   | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__haltreq) 
                       << 0x0000001fU) | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq) 
                                          << 0x0000001eU)));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
                = ((0xfffffffeU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug) 
                   | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive));
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug 
            = ((8U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))
                ? 0U : ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))
                         ? ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))
                             ? 0U : ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr))
                                      ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0))
                         : 0U));
    }
}

void Vsoc_top___024root___nba_sequent__TOP__6(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___nba_sequent__TOP__6\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.soc_top__DOT__rst_ff2 = ((IData)(vlSelfRef.rst_n) 
                                       && (IData)(vlSelfRef.soc_top__DOT__rst_ff1));
    vlSelfRef.soc_top__DOT__rst_ff1 = vlSelfRef.rst_n;
}

void Vsoc_top___024root___nba_comb__TOP__0(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___nba_comb__TOP__0\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
        = ((0x00000040U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
            ? ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                ? 0U : ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                         ? 0U : ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                  ? 0U : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                           ? 0U : (
                                                   (2U 
                                                    & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                                    ? 0U
                                                    : 
                                                   ((1U 
                                                     & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                                     ? 0U
                                                     : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_sel))))))
            : ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                ? ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                    ? ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_en))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_out_xor)))
                        : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie))))
                    : ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie)))
                        : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie)))))
                : ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                    ? ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie)))
                        : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_ds))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_pue))))
                    : ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                        ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en)))
                        : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en))
                            : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                         ? 0U : (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en 
                                                 & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2))))))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_prdata 
        = ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
            ? ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
                ? 0U : ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug))
            : ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
                ? ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
                    ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_spi
                    : vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio)
                : ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
                    ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__prdata_timer
                    : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart)
                        ? ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                            ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                             ? 0U : 
                                            (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__irq_en) 
                                              << 0x00000012U) 
                                             | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_en) 
                                                 << 0x00000011U) 
                                                | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_en) 
                                                    << 0x00000010U) 
                                                   | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_div))))))
                                : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                             ? 0U : 
                                            ((((((0U 
                                                  != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state)) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_err_sticky) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_overrun) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__full))) 
                                              << 3U) 
                                             | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty) 
                                                 << 2U) 
                                                | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__full) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__empty)))))))
                            : ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                    ? 0U : ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                             ? 0U : 
                                            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem
                                            [(7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr))]))
                                : 0U)) : 0U))));
}

void Vsoc_top___024root___nba_comb__TOP__1(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___nba_comb__TOP__1\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_write 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           & ((~ (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state))) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word_q;
    if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__prefetched_high_word)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word = 0U;
    }
    if ((1U & (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch) 
                | (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state))) 
               | (~ (IData)(vlSelfRef.soc_top__DOT__rst_ff2))))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_read 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           & ((~ (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state))) 
              & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst) 
                 | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch) 
                    | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata)))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           & (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer) 
               & ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state)) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____VdfgRegularize_had7d1046_0_1))) 
              | ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state)) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst))));
}

void Vsoc_top___024root___eval_nba(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_nba\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((8ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vsoc_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vsoc_top___024root___nba_sequent__TOP__1(vlSelf);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    if ((5ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vsoc_top___024root___nba_sequent__TOP__2(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
    }
    if ((0x0000000000000010ULL & vlSelfRef.__VnbaTriggered
         [0U])) {
        Vsoc_top___024root___nba_sequent__TOP__3(vlSelf);
    }
    if ((8ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vsoc_top___024root___nba_sequent__TOP__4(vlSelf);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vsoc_top___024root___nba_sequent__TOP__5(vlSelf);
        vlSelfRef.__Vm_traceActivity[5U] = 1U;
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vsoc_top___024root___nba_sequent__TOP__6(vlSelf);
    }
    if ((5ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vsoc_top___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vsoc_top___024root___nba_comb__TOP__1(vlSelf);
        vlSelfRef.__Vm_traceActivity[6U] = 1U;
    }
}

void Vsoc_top___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vsoc_top___024root___eval_phase__act(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_phase__act\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vsoc_top___024root___eval_triggers__act(vlSelf);
    Vsoc_top___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vsoc_top___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vsoc_top___024root___eval_phase__nba(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_phase__nba\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vsoc_top___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vsoc_top___024root___eval_nba(vlSelf);
        Vsoc_top___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vsoc_top___024root___eval(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vsoc_top___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("../rtl/../rtl/soc_top.sv", 14, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vsoc_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("../rtl/../rtl/soc_top.sv", 14, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vsoc_top___024root___eval_phase__act(vlSelf));
    } while (Vsoc_top___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vsoc_top___024root___eval_debug_assertions(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_debug_assertions\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");
    }
    if (VL_UNLIKELY(((vlSelfRef.uart_rx & 0xfeU)))) {
        Verilated::overWidthError("uart_rx");
    }
    if (VL_UNLIKELY(((vlSelfRef.spi_miso & 0xfeU)))) {
        Verilated::overWidthError("spi_miso");
    }
    if (VL_UNLIKELY(((vlSelfRef.flash_miso & 0xfeU)))) {
        Verilated::overWidthError("flash_miso");
    }
    if (VL_UNLIKELY(((vlSelfRef.jtag_tck & 0xfeU)))) {
        Verilated::overWidthError("jtag_tck");
    }
    if (VL_UNLIKELY(((vlSelfRef.jtag_tms & 0xfeU)))) {
        Verilated::overWidthError("jtag_tms");
    }
    if (VL_UNLIKELY(((vlSelfRef.jtag_tdi & 0xfeU)))) {
        Verilated::overWidthError("jtag_tdi");
    }
}
#endif  // VL_DEBUG
