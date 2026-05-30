// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_top.h for the primary calling header

#include "Vsoc_top__pch.h"

VL_ATTR_COLD void Vsoc_top___024root___eval_static(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_static\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__soc_top__DOT__rst_ff2__0 
        = vlSelfRef.soc_top__DOT__rst_ff2;
    vlSelfRef.__Vtrigprevexpr___TOP__jtag_tck__0 = vlSelfRef.jtag_tck;
}

VL_ATTR_COLD void Vsoc_top___024root___eval_initial__TOP(Vsoc_top___024root* vlSelf);
VL_ATTR_COLD void Vsoc_top___024root____Vm_traceActivitySetAll(Vsoc_top___024root* vlSelf);

VL_ATTR_COLD void Vsoc_top___024root___eval_initial(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_initial\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vsoc_top___024root___eval_initial__TOP(vlSelf);
    Vsoc_top___024root____Vm_traceActivitySetAll(vlSelf);
}

VL_ATTR_COLD void Vsoc_top___024root___eval_initial__TOP(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_initial__TOP\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    IData/*31:0*/ __Vilp1;
    __Vilp1 = 0U;
    while ((__Vilp1 <= 0x0000003fU)) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rom[__Vilp1] = 0x00000013U;
        __Vilp1 = ((IData)(1U) + __Vilp1);
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__unnamedblk1__DOT__i = 0x00000040U;
    VL_READMEM_N(true, 32, 64, 0, "bootrom.hex"s,  &(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rom)
                 , 0, ~0ULL);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__unnamedblk1__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00001000U, vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__unnamedblk1__DOT__i)) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem[(0x00000fffU 
                                                                   & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__unnamedblk1__DOT__i)] = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__unnamedblk1__DOT__i 
            = ((IData)(1U) + vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__unnamedblk1__DOT__i);
    }
    VL_READMEM_N(true, 32, 4096, 0, "firmware_sram.hex"s
                 ,  &(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem)
                 , 0, ~0ULL);
}

VL_ATTR_COLD void Vsoc_top___024root___eval_final(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_final\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vsoc_top___024root___eval_phase__stl(Vsoc_top___024root* vlSelf);

VL_ATTR_COLD void Vsoc_top___024root___eval_settle(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_settle\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vsoc_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("../rtl/../rtl/soc_top.sv", 14, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vsoc_top___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vsoc_top___024root___eval_triggers__stl(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_triggers__stl\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsoc_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vsoc_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vsoc_top___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vsoc_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___trigger_anySet__stl\n"); );
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

extern const VlUnpacked<VlWide<4>/*127:0*/, 256> Vsoc_top__ConstPool__TABLE_h3c1c5ec4_0;
extern const VlUnpacked<IData/*31:0*/, 16> Vsoc_top__ConstPool__TABLE_h1e1d6789_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_h27ce561f_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_hc27dba7d_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_hc596960b_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_h88828eae_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vsoc_top__ConstPool__TABLE_h9b50a213_0;

VL_ATTR_COLD void Vsoc_top___024root___stl_sequent__TOP__0(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___stl_sequent__TOP__0\n"); );
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
    CData/*0:0*/ soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_1;
    soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_1 = 0;
    CData/*7:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*3:0*/ __Vtableidx5;
    __Vtableidx5 = 0;
    // Body
    vlSelfRef.gpio_oe = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en;
    vlSelfRef.spi_sclk = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg;
    vlSelfRef.spi_mosi = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__mosi_reg;
    vlSelfRef.flash_sclk = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg;
    vlSelfRef.flash_cs_n = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__cs_n_reg;
    vlSelfRef.flash_mosi = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_arready 
        = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_arready 
        = (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg)));
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1 
        = ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1))
            ? ((0x23U >= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1))
                ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs
               [vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1]
                : 0U) : 0U);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2 
        = ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2))
            ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs
           [vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2]
            : 0U);
    vlSelfRef.gpio_out = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_out_xor 
                          ^ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_1 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy) 
           & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
              >> 0x00000011U));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_3 
        = (IData)(((0x00001000U == (0x0000f000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)) 
                   & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt) 
           >= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_clkdiv));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tck_pulse 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_last) 
           ^ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync2));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_req 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive) 
           & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__haltreq)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_write 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           & ((~ (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state))) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__ebreak_halt_trigger 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger_q) 
           & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ecall_ebreak)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx 
        = (0x0000001fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_endian)
                           ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt)
                           : (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen) 
                               - (IData)(1U)) - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_dmireset_pulse 
        = ((8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state)) 
           & ((0x10U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg)) 
              & (IData)((0U != (0x00030000U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift)))));
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_web0 
        = (1U & (~ ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured) 
                      & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)) 
                     & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))) 
                    & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending)))));
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
    __Vtableidx5 = vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pstrb;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask 
        = Vsoc_top__ConstPool__TABLE_h1e1d6789_0[__Vtableidx5];
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_pc 
        = (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch) 
            & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store))
            ? (0xfffffffeU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out)
            : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycle) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycleh) 
              | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstr) 
                 | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstrh))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_imm 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_imm;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_opcode 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_opcode;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs1 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs1;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs2 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs2;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rd 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rd;
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 1U;
    if ((0x00000040U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_sel;
        }
    } else if ((0x00000020U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                    } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                    } else {
                        vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_en;
                    }
                } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_out_xor;
                }
            } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip;
                }
            } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie;
            }
        } else if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip;
                }
            } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie;
            }
        } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip;
            }
        } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie;
        }
    } else if ((0x00000010U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
                } else {
                    vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip;
                }
            } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie;
            }
        } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_ds;
            }
        } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_pue;
        }
    } else if ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val;
            }
        } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en;
        }
    } else if ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en;
        }
    } else if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
    } else if ((1U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio = 0U;
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio 
            = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en 
               & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2);
    }
    if ((0x40U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__launch_next_insn 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger) 
               & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_delay) 
                  | ((~ (0U != ((~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_mask) 
                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending))) 
                     | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata = 0U;
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
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__launch_next_insn = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata = 0U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____VdfgRegularize_had7d1046_0_1 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst) 
           | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata) 
              | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_wready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_wready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_wready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_wready 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured)) 
           & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_awready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_awready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_awready 
        = (1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r)) 
                 & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata = 0xdeadbeefU;
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr) 
           == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_eq 
        = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
           == vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_lts 
        = VL_LTS_III(32, vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1, vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_ltu 
        = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
           < vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__full 
        = (((1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr) 
                   >> 3U)) != (1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr) 
                                     >> 3U))) & ((7U 
                                                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr)) 
                                                 == 
                                                 (7U 
                                                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr))));
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured)) 
           & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_irq_aggregator__DOT__timer_irq 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_int_en) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__raw_int));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter_value 
        = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter 
           & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size)
               ? 0xffffffffU : 0x0000ffffU));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_arready 
        = ((~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending) 
               | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)))) 
           & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wvalid 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__w_done)) 
           & (1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count 
        = (0x0000000fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr) 
                          - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count 
        = (0x0000000fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr) 
                          - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr)));
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready 
        = ((~ (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb))) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_bready 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid) 
           & (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb)));
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__aw_done)) 
           & (1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_allowed 
        = ((~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch) 
               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____VdfgRegularize_had7d1046_0_1))) 
           & ((~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid) 
                  | (0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state)))) 
              & (0x40U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state))));
    if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rresp;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rdata;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_data_reg;
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata 
                = ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))
                    ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rdata_r
                    : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rdata_reg);
        }
    } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp = 3U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata = 0xdeaddeadU;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata = 0U;
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata;
    }
    if ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wstrb = 0x0fU;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata;
    } else if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wdata 
            = ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 
                << 0x00000010U) | (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2));
        if ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1)) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wstrb = 0x0cU;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word 
                = (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata 
                   >> 0x10U);
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wstrb = 3U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word 
                = (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata);
        }
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)
            ? (4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))
            : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0 = 0U;
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out = 0U;
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_en 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__full)) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_valid));
    if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_bvalid 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid));
    if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid 
            = ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))
                ? ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))
                    ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rvalid)
                    : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg))
                : ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))
                    ? (2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state))
                    : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg)));
    } else if ((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid = 1U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rvalid 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_instr 
        = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_ascii_instr;
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_next) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_imm 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_imm;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_opcode 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_opcode;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs1 
                = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs1));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs2 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs2;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rd 
                = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rd));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_instr 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_ascii_instr;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_imm 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_opcode 
                = ((3U == (3U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode))
                    ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode
                    : (0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs1 
                = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs2 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rd 
                = (0x0000001fU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rd));
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_instr 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr;
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_arvalid 
        = ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_arvalid)) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready));
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr 
                = (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0);
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid 
                = (3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state));
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot 
                = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_instr)
                    ? 4U : 0U);
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_arvalid;
        }
    } else {
        if ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot = 0U;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr 
                = (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0);
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot 
                = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_instr)
                    ? 4U : 0U);
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr;
        }
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_arvalid) 
               | (3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_ready 
        = ((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid)) 
            & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_bready)) 
           | (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready)));
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
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_5 
        = ((0x00010000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr) 
           & (0x00014000U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr));
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_6 
        = ((0x40000000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr) 
           & (0x41000000U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr));
    soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT____VdfgRegularize_h7658d933_0_7 
        = ((0x20000000U <= vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr) 
           & (0x20010000U > vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_rready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_rready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_rready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rready = 0U;
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
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready;
            }
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_ready) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_bready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_bready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_bready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bready = 0U;
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
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready;
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wdata = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wdata = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wdata = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wstrb = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wstrb = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wstrb = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wstrb = 0U;
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr 
                = (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0);
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wdata;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr;
        }
    } else if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr 
            = (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0);
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wdata;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb;
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer)
            ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata
            : vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q);
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw 
        = ((IData)(vlSelfRef.soc_top__DOT__rst_ff2) 
           & (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer) 
               & ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state)) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____VdfgRegularize_had7d1046_0_1))) 
              | ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state)) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready = 0U;
    if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wstrb 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb;
            }
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wstrb 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb;
            }
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wstrb 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb;
            }
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wdata 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wstrb 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb;
            }
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active)
            ? ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)
                ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wvalid)
                : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_wvalid))
            : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid)
                ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wvalid)
                : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_wvalid)));
    if ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_wready;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_wready;
            }
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready 
                = ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))
                    ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_wready)
                    : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_wready));
        }
        if ((1U & (~ ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
            }
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wvalid 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
            }
        }
    } else if ((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid;
    }
    if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active) {
        if (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wready 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready;
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid 
                = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_awvalid;
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wready = 0U;
        }
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_awvalid) 
               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wready 
            = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid) 
               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__apb_write 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT____VdfgRegularize_hf7b9a0fb_0_0) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite));
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_araddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_araddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_araddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arvalid = 0U;
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
    if ((4U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pslverr 
            = ((1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel) 
                      >> 1U)) || (1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel)));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_prdata 
            = ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
                ? 0U : ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
                         ? 0U : vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug));
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pslverr 
            = ((1U & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel) 
                      >> 1U)) && ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))) 
                                  && ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid)) 
                                      & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT____VdfgRegularize_hf7b9a0fb_0_0))));
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_prdata 
            = ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel))
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
                                : 0U)) : 0U)));
    }
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
            }
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
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arprot 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_prot_reg;
            }
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
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_access 
        = ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state)) 
           & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arvalid) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_arready)));
    if (((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured) 
           & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)) 
          & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_strb_r;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0 
            = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_data_r;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0 
            = (0x00000fffU & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_addr_r));
    } else {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0 = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0 = 0U;
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0 
            = (0x00000fffU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_access)
                               ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_araddr 
                                  >> 2U) : 0U));
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awprot = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awvalid = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awaddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awaddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awaddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awaddr = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready = 0U;
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid = 0U;
    if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state)) 
          & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid)) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_decerr)))) {
        if ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel))) {
            if ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awprot = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awaddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid = 1U;
            } else {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_awready;
            }
            if ((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel)))) {
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awprot = 0U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awvalid = 1U;
                vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awaddr 
                    = vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr;
            }
        } else {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready 
                = ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel))
                    ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_awready)
                    : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_awready));
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
    } else if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state)) 
                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid)) 
                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_decerr))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready = 1U;
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_csb0 
        = ((1U & (~ ((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured) 
                       & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured)) 
                      & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r))) 
                     & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending))))) 
           && (1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_access))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awready 
        = (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active)) 
            & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid))
            ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready)
            : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active) 
               & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_arready 
        = ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready) 
           & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured)) 
              & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid))));
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready = 0U;
    if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state)) 
          & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid)) 
         & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_decerr)))) {
        vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready 
            = (1U & ((2U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel))
                      ? ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel))
                          ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_arready)
                          : (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg)))
                      : ((1U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel))
                          ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_arready)
                          : (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg)))));
    } else if ((1U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state))) {
        if ((((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state)) 
              & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid)) 
             & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_decerr))) {
            vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready = 1U;
        }
    }
    vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_arready 
        = (((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active)) 
            & (3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)))
            ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready)
            : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active) 
               & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold) 
                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready))));
}

VL_ATTR_COLD void Vsoc_top___024root___eval_stl(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_stl\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vsoc_top___024root___stl_sequent__TOP__0(vlSelf);
        Vsoc_top___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD bool Vsoc_top___024root___eval_phase__stl(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___eval_phase__stl\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vsoc_top___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vsoc_top___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vsoc_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vsoc_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vsoc_top___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @(negedge soc_top.rst_ff2)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @(posedge jtag_tck)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @(negedge jtag_tck)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vsoc_top___024root____Vm_traceActivitySetAll(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root____Vm_traceActivitySetAll\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.__Vm_traceActivity[3U] = 1U;
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.__Vm_traceActivity[5U] = 1U;
    vlSelfRef.__Vm_traceActivity[6U] = 1U;
}

VL_ATTR_COLD void Vsoc_top___024root___ctor_var_reset(Vsoc_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root___ctor_var_reset\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->uart_tx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1761512799854230840ull);
    vlSelf->uart_rx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2399467654730215438ull);
    vlSelf->gpio_in = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 629115553822814742ull);
    vlSelf->gpio_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3528322381442655819ull);
    vlSelf->gpio_oe = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9752628960434834032ull);
    vlSelf->spi_sclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11093002469780296933ull);
    vlSelf->spi_mosi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 852284730959930751ull);
    vlSelf->spi_miso = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12140560756394917646ull);
    vlSelf->spi_cs_n = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5466454749172535206ull);
    vlSelf->flash_sclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13130400928625086448ull);
    vlSelf->flash_cs_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4211705990234091973ull);
    vlSelf->flash_mosi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8777728623982306914ull);
    vlSelf->flash_miso = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15258836905819435205ull);
    vlSelf->jtag_tck = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10500983681776930247ull);
    vlSelf->jtag_tms = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16224335879666074583ull);
    vlSelf->jtag_tdi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5289790260552907825ull);
    vlSelf->jtag_tdo = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 293125711922884863ull);
    vlSelf->trap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18214934560881419504ull);
    vlSelf->soc_top__DOT__rst_ff1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8341914603847896198ull);
    vlSelf->soc_top__DOT__rst_ff2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3138640246131085169ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__cpu_eoi = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17094766847249220848ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3018270774318876866ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1650918502843099551ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 1948436000055256153ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17682635633787818429ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15876141158152616478ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9906296624530416992ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11208161978817213594ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2137365642595315836ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6862281234132640302ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 8237683422440539419ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s0_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 837437499096205990ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8580365468535910550ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7602484983570761118ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10466099515817106375ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13862033088692660562ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6831147632465720006ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7111070446237192982ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14448071778633078317ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4862140289912549800ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4778391349118553157ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 2861038703672741085ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s1_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13476337304040413635ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6051980321631440459ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17321381665336257880ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11569552930507498911ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15266570790955269193ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14250481235606288399ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5654870057812197740ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3366906397617544103ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2644449498558603289ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16350694300670511721ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 1852197685251319949ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s2_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14973754339300138639ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12549844770232233799ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7112384096135964737ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9622486063954903972ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12005738260381501910ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4004495325476269372ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1781261501720327815ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9513029350060108893ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17785541061077597794ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2910205796875729807ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8890394169624321243ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12095117622329312808ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 242061229283635155ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13987270500739843340ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15188624410177694021ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1065727634228304471ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__s3_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9179401597027106124ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__apb_psel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5351796800370078172ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__apb_penable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3349893672570200552ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__apb_pwrite = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4403863663804445468ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__apb_paddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4541011158622515180ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__apb_pwdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17756218915006493473ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__apb_pstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17260269440780939676ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__apb_pprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 16717619115380274580ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__apb_prdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11852030936500588386ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__apb_pslverr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13914107640569727428ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__psel_uart = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2029585753117650085ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__psel_timer = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 104670707755798139ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__psel_gpio = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10019411176062385826ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__prdata_gpio = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 636078170951835622ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__psel_spi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 586177228510464521ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__prdata_spi = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5288557551390011102ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__psel_debug = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2937304124461309202ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__prdata_debug = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5651861426274892653ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__dbg_halted = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7685779462696626345ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__jdbg_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9138536706834696688ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__jdbg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6048874065526269426ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__jdbg_addr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11644284650754950974ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__jdbg_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11928848852134480194ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__jdbg_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17784009789332608973ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__trace_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14586632892849791726ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__trace_data = VL_SCOPED_RAND_RESET_Q(36, __VscopeHash, 5191465967150202349ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4653674946354860207ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14756758789053399508ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5655609704584546551ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8569177445123310195ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9910292142413516407ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__pcpi_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2535342682401065052ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__pcpi_insn = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11641853615150755363ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7453489920830587478ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5954108285741161698ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16017180058506344894ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__xfer_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 824526252675975954ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____Vlvbound_hc83e3f8d__0 = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____Vlvbound_h6f5e494c__0 = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 564968630459600348ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11290593027167844166ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1182617904330335072ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9297402877249757963ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 15407323843469498777ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_req = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3007154025292863832ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1424415088616096000ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6244669755412485577ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 3348602361277473067ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15225922953736226440ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5112018640664557320ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10386588659566406623ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13433332923463356958ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3131021192235708435ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 18407541332896559497ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7574833436129643535ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_opcode = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 663092333250723959ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2658948030640016829ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1052020973700946250ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_delay = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3416406912246710752ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2158514019057802093ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_mask = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15007808033564214508ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16532288916100372523ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18236529933200017541ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_allowed = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8538274515123679981ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__ebreak_halt_trigger = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12672204305016569161ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2178243947415832421ull);
    for (int __Vi0 = 0; __Vi0 < 36; ++__Vi0) {
        vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7425804720245930767ull);
    }
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12948762951645447397ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14079676710271283458ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4637651445816651692ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13808607745389581582ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 197604198718611987ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15572560029706240704ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 928599824065521005ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5120052108482256821ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1271026906934195798ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12486973991277801056ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_secondword = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11261249465867062051ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_firstword_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16410529183014513610ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__last_mem_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10447729381093924851ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__prefetched_high_word = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14977191813798452409ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13645224325489127807ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_16bit_buffer = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14586001041964355836ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15112738275931251828ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16257688679630798578ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lui = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16080678678616085261ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_auipc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9078650684813331529ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12710293357016877367ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6557146358318503186ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_beq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1217526011265452709ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bne = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15297370659143918950ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_blt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12124560891413398143ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bge = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18004718643820860253ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bltu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2450037677673720566ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bgeu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13284909401718356774ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8447049562630791585ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10341258372945564929ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 141733880260003991ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lbu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2909782898347943122ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lhu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7901393384003428345ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4366999155061691436ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4305588469728028284ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16382341744756958884ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_addi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3219524051742765266ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slti = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15503452935120988265ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltiu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15257515002448891048ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xori = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10007536898057846526ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ori = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6436906285948976216ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_andi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16307865649742505591ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slli = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4030866376131955487ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srli = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6964491581165625488ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srai = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7414271314080087390ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_add = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1745121595153501291ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sub = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15913724697572410426ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sll = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1981237828651809435ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5165188212880708010ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2728853850417053234ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xor = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16639014964773078536ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srl = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14163322539617782668ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sra = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10405899777029129138ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_or = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 683428522036845476ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_and = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9855306035200631218ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4383691332628237153ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycleh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5669625824345006150ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8630565870893642293ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstrh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16337346192260214125ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ecall_ebreak = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7871378453575963408ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_fence = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16854094838572248880ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_getq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16638559867343683187ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_setq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5659521560416705483ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_retirq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14498839304875801037ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_maskirq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11641137809022810106ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_waitirq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12594909738859961335ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_timer = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8884875028565449531ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rd = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 11098147108468593674ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1 = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 17021696667243489088ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 677870550026441117ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1073457783703500571ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6232190031403073718ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7590763396756803872ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14157097562131646642ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18406128660102736420ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6186995677403279506ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__compressed_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17888147474995268141ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8371019643183843057ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10291374117833299228ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_slli_srli_srai = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16450048172553620084ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9959728263995364198ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sb_sh_sw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17388207514536056914ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sll_srl_sra = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11561744690786225681ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal_jalr_addi_add_sub = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1597270180645260655ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_slti_blt_slt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13999409806264320452ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sltiu_bltu_sltu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15208065389761106769ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3151885938028297488ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lbu_lhu_lw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8790843044214696271ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12018048883706185106ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2489199686253418198ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_compare = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12905178157061066354ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5869070425359230092ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13921940192006772460ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_instr = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16836627765446779960ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9228731353185133335ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 18289873453532961088ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3711324314722902195ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6909212093512655561ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14575569936496569328ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16263855198705046056ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13001100903953848786ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9405404827440977731ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_ascii_instr = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 499169863254759562ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18151826055315480835ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_opcode = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8042425729614854645ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7766030780359933061ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9516859796418877802ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 5804930989423438519ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_next = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14298093529998715415ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__launch_next_insn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5154968977273995757ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_valid_insn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18203039120244874367ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_ascii_instr = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 127208426519372275ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9807076585489884084ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_opcode = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17878965398115376391ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13756934488584917316ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 17996851397518123361ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1389818723001864563ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2592810500974494776ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13871922358140196109ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending_ack = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14662404739478973589ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_state, __VscopeHash, 7497230453354589057ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rinst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8406405993983066631ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1294486645385017437ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_wdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9577014659528975660ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6762089937411179125ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_stalu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 684424492152317690ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9705365118156877519ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4786442921265911702ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_trace = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4568557473656799522ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15850337607158352753ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8333891060933116890ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2320300605823887164ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 12277726979081877238ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5365630416404830095ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__pcpi_timeout_counter = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3041325956309554691ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__pcpi_timeout = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3413040770640373708ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7815021258800211577ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17600933274847156813ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15818013983154097617ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10670612123600021532ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16177445001026674047ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1619234056608185895ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_wait = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18296722347120311355ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_wait_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14912291517354567565ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_eq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11771259482033714710ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_ltu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6930436324938298494ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_lts = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16053756634074257664ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4557342645256935732ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4178065981640268240ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16104977425696378948ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13020844635168707910ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2403105134588887164ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____VdfgRegularize_had7d1046_0_1 = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4402007810920319805ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10573838872066741876ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10235272143501509209ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4494233970822083231ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3184037727399785042ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 26239895775249762ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7773322374269502224ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15308211825234908522ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9126733941112298846ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13617081252158752052ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2734536813906130152ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10331172170639621147ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8886994769931826063ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11984385296893893136ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13560747535403925469ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5183698956807808525ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1606868342354774897ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14518985394727987697ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1241854746600013791ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 144749860229308427ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8398798093694427433ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16337002442460947776ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18114077737117595695ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8035013549536344479ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4586534593772940165ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4635543731959282958ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9125822263355433366ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12377048056756017985ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2804242991595624229ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15790226436133979260ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 6145447909817287955ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18392733450334801015ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14307377804744107139ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12303597051771210033ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 8894944538762673034ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2021364838691076253ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16265191295458054793ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18051328651451043274ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15316910177255602358ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8231692643013092987ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8693643391485698658ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17590979344533518837ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9789878976122896082ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17604313044745015124ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15616615046726215701ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6697441516043488981ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9621201024241803283ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_decerr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10821171083385318218ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_decerr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 653903062871578608ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10885505486739938732ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14609405821078895318ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_addr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4597302592154592110ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_prot_reg = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 195724624500503595ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14224512338090707970ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17434964632352463079ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_addr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10250428725417718571ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_prot_reg = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17288354207565688570ull);
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        vlSelf->soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rom[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16456345767767103383ull);
    }
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14955631401800047028ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rdata_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4604738988536351359ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9525059049829766350ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9748749096258454136ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16314624199405390843ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_csb0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5810189152912253499ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_web0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13892473615427189150ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 4808202662150714285ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0 = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 15580325494904357132ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14006160462080995119ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_dout0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16645840221761500792ull);
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17118217759475387275ull);
    }
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9753824565216272273ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10248081265120428848ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5856713094022057611ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3900962121179883820ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_addr_r = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 114327691220024088ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_data_r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4145248804319941682ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_strb_r = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8854052626251130280ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5349683102002131728ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rdata_r = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7915906173696616689ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_access = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12185336982056716223ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_sram__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11713436494376449482ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_xip_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17109764794704106651ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr_width = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 280936137775737610ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3964674860842328695ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2813248801997032448ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1224928984719153000ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_txdata = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1501543848309036439ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_clkdiv = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7255875899458582498ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_dummy_cycles = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7941504603342880143ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id = VL_SCOPED_RAND_RESET_I(24, __VscopeHash, 8250490556088314601ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17272039976655682050ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12602479474908721933ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17380735312117316870ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 17972452509145806975ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3060468284688491752ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7638551497533405201ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12346623332733240402ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 707606180092888308ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4414687806477154402ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12291982444487680744ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__timeout_err = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11355395352554440078ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__timeout_cnt = VL_SCOPED_RAND_RESET_I(20, __VscopeHash, 15906017838759529459ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6835190459687062403ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__cs_n_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5347227858350973311ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10658499111055295322ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10412684161985627702ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_data_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13351615718118569040ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7805065942178841008ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18304843935747841034ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15429932453364800434ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 3983772367955230871ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_aw_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17781615697759159693ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_w_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6409865796702673792ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_bvalid_r = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6349033065243362360ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_rvalid_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3164528797223942236ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_rdata_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6718954914221839482ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2114969339286791178ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1745348556019750388ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4158386812747046584ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12392304890427698186ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14373104179335309358ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6602259293485808558ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10510769684927568323ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17006088655124096361ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13503016951566224267ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_addr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2283378351364676170ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_prot_reg = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11861721368527940612ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_data_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2901743292963611788ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_strb_reg = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9779095254137035808ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__apb_rdata_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5699964973431366697ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__apb_slverr_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13545976351052931525ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__is_write_txn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8284822624426864319ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__prdata_timer = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3285779753324257909ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11920851425510177853ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_div = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13436159647016167130ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16524481796329978313ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1406639464196554597ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__irq_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9442116309938983133ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_overrun = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14571590366645117250ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_err_sticky = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15202652360248288247ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__wr_ctrl_pulse = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10747775480490398649ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7577611776321771652ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10450347684354670009ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick_16x = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2048905249496540518ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 4804397527470725972ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2997591102898763862ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2939825365791337392ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10751570526920295563ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_data_out = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14137092451554739552ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_data_in = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17478555940397845094ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2404138718019637657ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_error = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17851872049817882829ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9109944685266841002ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12655391813888365276ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11237990622380398768ull);
    }
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 6073290420759149152ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12850011585503050598ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15288378615477204351ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2956371438945349399ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18291060134250550737ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1068575929285568886ull);
    }
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 15457371442283722634ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 14815827692720942291ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10608274678026335715ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__shift_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14653109274592208267ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__bit_cnt = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12722587733749235935ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7111012957352766513ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__shift_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9688812740018234290ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__bit_cnt = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10870376539578021982ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17470029881660887618ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9499563135237686991ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1949490713710776789ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_one_shot = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6843475497463636593ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13798653611330767199ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5125807869604149478ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_int_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13534812069580588737ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_mode = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13363096929628328333ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16224905871396730376ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14169990545989728102ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10231514981717899360ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2182978391116630885ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__raw_int = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13992249120001225769ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7301494722011630802ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12181822649497169672ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_tick = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15378744483025311885ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter_value = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17718455622873865450ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15092389409818169446ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14375830432954013314ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2462504498377677828ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_timer__DOT__apb_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 132366416350178821ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 942577591851807902ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2622200617169608517ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10113592772063588191ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_pue = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10546308035531823794ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_ds = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16134270437037837587ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4121378199896738087ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11759588330593304173ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10117769885636939341ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11408228062351129884ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4236687700319529296ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6036846030340277017ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13612873230553442939ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 181634583118380035ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_out_xor = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12730773777075900499ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_en = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5305518439293634831ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_sel = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15012315811451232582ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8736783742801009290ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8974326361143235827ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_prev = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12874753061001956128ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__apb_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11493566004820262565ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16547492492528784654ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6673122343514095037ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_gpio__DOT____VdfgRegularize_hf7b9a0fb_0_0 = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sckdiv = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1011679935943654046ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14853343984672922643ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpha = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14398219814415660232ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csid = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2381128772893663712ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csdef = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12915988626281458695ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csmode = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4112286295864369914ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_endian = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8730480719339745420ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8745643120277373290ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_txmark = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10605418286154615457ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_rxmark = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11528041001110114919ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ie = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17990571440314222145ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 224435275242880139ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16504408706762391801ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6224987067429421590ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1605580120085140903ull);
    }
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17593900883536585187ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12829091736556683076ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 15032032142293860318ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14770048170275956456ull);
    }
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 11450441233818409833ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 15579480605941747173ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9014824326005447476ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12944812565159822827ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4479114084727255838ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2643212702895503835ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4072591183019898168ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6943065115287725629ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_in = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12750328868173221049ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13637805271166838545ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__mosi_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5674673638688694752ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13752189612143381780ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 726223287530854021ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8101468567639720267ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1687596950176716040ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_pop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1760513582744450935ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_push = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10769095843242910967ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11545962119224344285ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_0 = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9619599945375688571ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 394620160508636586ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9363813547855044710ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1266939719239666044ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2782000953499102509ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__haltreq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14158660394376676623ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10548040301645721761ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15270896591555023616ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13576775402900889963ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_shadow = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12272561111452461226ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15245498606330515540ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dbg_halted_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5400362728186310737ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10707208520410011294ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__cmderr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 14281405540687371534ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_written = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6502943863264165242ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadonaddr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7193970227014088229ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbautoincrement = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13099152467488976196ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadondata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6384690507026440817ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbbusyerror = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13884242894312769115ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sberror = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10716166944796874800ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 3597610556605067901ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18287444526263028838ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13773884645881105586ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resume_pending_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3996812056929969004ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12067010120282298072ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8956131122676005255ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12399382446792675801ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__aw_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5614445746972449211ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__w_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3430044501874414353ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3443430256003636227ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17812623225291164915ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_0 = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_1 = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_3 = 0;
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 11620632513368618913ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_shift = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1637527204784739473ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3332402527522899821ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12291438526444862741ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2719903946553489043ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11087481070115406088ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift = VL_SCOPED_RAND_RESET_Q(41, __VscopeHash, 17481216033395295390ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift_rev = VL_SCOPED_RAND_RESET_Q(41, __VscopeHash, 5180888457810405826ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_stat = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7094170577139593207ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18058659496950648246ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3932818053578157950ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_op = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6599654464952638956ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_dmireset_pulse = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11477072720786128517ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4852391134068754660ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_write_tck = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12082280206671779348ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_addr_tck = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 16480585568532056941ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_wdata_tck = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13635752777406114732ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8775212199360338342ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5512009657263122566ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3890049423671843247ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_toggle_sys = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2951894867392634382ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_data_sys = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 720092143258488739ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_op_sys = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3357561997381972939ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13787045173083108793ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18381519592618526609ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_last = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14619619282594213236ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tck_pulse = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8755511774989809285ull);
    vlSelf->soc_top__DOT__u_soc_core__DOT__u_irq_aggregator__DOT__timer_irq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6225337170000716994ull);
    vlSelf->__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state = 0;
    vlSelf->__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured = 0;
    vlSelf->__Vdly__soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured = 0;
    vlSelf->__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state = 0;
    vlSelf->__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift = 0;
    vlSelf->__Vdly__soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__soc_top__DOT__rst_ff2__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__jtag_tck__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 7; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
