// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vsoc_top__Syms.h"


void Vsoc_top___024root__trace_chg_0_sub_0(Vsoc_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vsoc_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root__trace_chg_0\n"); );
    // Body
    Vsoc_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsoc_top___024root*>(voidSelf);
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vsoc_top___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vsoc_top___024root__trace_chg_0_sub_0(Vsoc_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root__trace_chg_0_sub_0\n"); );
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[0U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__unnamedblk1__DOT__i),32);
        bufp->chgIData(oldp+1,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__unnamedblk1__DOT__i),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgBit(oldp+2,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__bypass_reg));
        bufp->chgIData(oldp+3,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__idcode_shift),32);
        bufp->chgIData(oldp+4,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_shift),32);
        bufp->chgCData(oldp+5,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_stat),2);
        bufp->chgBit(oldp+6,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_busy));
        bufp->chgIData(oldp+7,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_data),32);
        bufp->chgCData(oldp+8,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_resp_op),2);
        bufp->chgBit(oldp+9,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync1));
        bufp->chgBit(oldp+10,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_sync2));
        bufp->chgBit(oldp+11,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tog_last));
        bufp->chgBit(oldp+12,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_tck_pulse));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[2U]))) {
        bufp->chgBit(oldp+13,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_awvalid));
        bufp->chgIData(oldp+14,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_addr),32);
        bufp->chgBit(oldp+15,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_wvalid));
        bufp->chgIData(oldp+16,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wdata),32);
        bufp->chgCData(oldp+17,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_wstrb),4);
        bufp->chgBit(oldp+18,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_bready));
        bufp->chgBit(oldp+19,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_arvalid));
        bufp->chgCData(oldp+20,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_instr)
                                  ? 4U : 0U)),3);
        bufp->chgBit(oldp+21,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rready));
        bufp->chgBit(oldp+22,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid));
        bufp->chgIData(oldp+23,((0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0)),32);
        bufp->chgBit(oldp+24,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wvalid));
        bufp->chgIData(oldp+25,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wdata_aligned),32);
        bufp->chgCData(oldp+26,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_wstrb),4);
        bufp->chgBit(oldp+27,((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))));
        bufp->chgBit(oldp+28,((3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))));
        bufp->chgBit(oldp+29,((4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state))));
        bufp->chgIData(oldp+30,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__cpu_eoi),32);
        bufp->chgBit(oldp+31,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awvalid));
        bufp->chgBit(oldp+32,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_awready));
        bufp->chgIData(oldp+33,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awaddr),32);
        bufp->chgCData(oldp+34,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awprot),3);
        bufp->chgBit(oldp+35,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wvalid));
        bufp->chgBit(oldp+36,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s0_axi_wready));
        bufp->chgIData(oldp+37,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wdata),32);
        bufp->chgCData(oldp+38,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_wstrb),4);
        bufp->chgBit(oldp+39,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__bvalid_reg));
        bufp->chgBit(oldp+40,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_bready));
        bufp->chgBit(oldp+41,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arvalid));
        bufp->chgBit(oldp+42,((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg)))));
        bufp->chgIData(oldp+43,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_araddr),32);
        bufp->chgCData(oldp+44,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_arprot),3);
        bufp->chgBit(oldp+45,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rvalid_reg));
        bufp->chgBit(oldp+46,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_rready));
        bufp->chgIData(oldp+47,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__rdata_reg),32);
        bufp->chgBit(oldp+48,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awvalid));
        bufp->chgBit(oldp+49,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_awready));
        bufp->chgIData(oldp+50,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awaddr),32);
        bufp->chgCData(oldp+51,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awprot),3);
        bufp->chgBit(oldp+52,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wvalid));
        bufp->chgBit(oldp+53,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_wready));
        bufp->chgIData(oldp+54,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wdata),32);
        bufp->chgCData(oldp+55,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_wstrb),4);
        bufp->chgBit(oldp+56,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__bvalid_r));
        bufp->chgBit(oldp+57,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_bready));
        bufp->chgBit(oldp+58,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arvalid));
        bufp->chgBit(oldp+59,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s1_axi_arready));
        bufp->chgIData(oldp+60,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_araddr),32);
        bufp->chgCData(oldp+61,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_arprot),3);
        bufp->chgBit(oldp+62,((2U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state))));
        bufp->chgBit(oldp+63,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_rready));
        bufp->chgIData(oldp+64,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rdata_r),32);
        bufp->chgBit(oldp+65,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awvalid));
        bufp->chgBit(oldp+66,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_awready));
        bufp->chgIData(oldp+67,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awaddr),32);
        bufp->chgCData(oldp+68,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awprot),3);
        bufp->chgBit(oldp+69,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wvalid));
        bufp->chgBit(oldp+70,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__s2_axi_wready));
        bufp->chgIData(oldp+71,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wdata),32);
        bufp->chgCData(oldp+72,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_wstrb),4);
        bufp->chgBit(oldp+73,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bvalid_r));
        bufp->chgBit(oldp+74,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_bready));
        bufp->chgBit(oldp+75,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arvalid));
        bufp->chgBit(oldp+76,((1U & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg)))));
        bufp->chgIData(oldp+77,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr),32);
        bufp->chgCData(oldp+78,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_arprot),3);
        bufp->chgBit(oldp+79,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_valid_reg));
        bufp->chgBit(oldp+80,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_rready));
        bufp->chgIData(oldp+81,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__r_data_reg),32);
        bufp->chgBit(oldp+82,(((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty)) 
                               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__irq_en))));
        bufp->chgBit(oldp+83,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_irq_aggregator__DOT__timer_irq));
        bufp->chgBit(oldp+84,((0U != ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ie) 
                                      & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip)))));
        bufp->chgBit(oldp+85,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_req));
        bufp->chgBit(oldp+86,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_resume_req));
        bufp->chgBit(oldp+87,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted));
        bufp->chgBit(oldp+88,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_1) 
                               & ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                   >> 0x00000010U) 
                                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_3)))));
        bufp->chgBit(oldp+89,(((~ (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                   >> 0x00000010U)) 
                               & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_1) 
                                  & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_3)))));
        bufp->chgCData(oldp+90,((0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)),5);
        bufp->chgIData(oldp+91,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__data0),32);
        bufp->chgIData(oldp+92,(((0U != (0x0000001fU 
                                         & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command))
                                  ? vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs
                                 [(0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)]
                                  : 0U)),32);
        bufp->chgIData(oldp+93,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_pc),32);
        bufp->chgBit(oldp+94,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__dbg_halted) 
                               & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_written))));
        bufp->chgIData(oldp+95,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_shadow),32);
        bufp->chgBit(oldp+96,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_valid));
        bufp->chgBit(oldp+97,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_write));
        bufp->chgBit(oldp+98,(((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy)) 
                               & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)))));
        bufp->chgCData(oldp+99,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_addr),8);
        bufp->chgIData(oldp+100,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_wdata),32);
        bufp->chgCData(oldp+101,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_wstrb),4);
        bufp->chgBit(oldp+102,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_enable) 
                                & (0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state)))));
        bufp->chgIData(oldp+103,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_jedec_id),24);
        bufp->chgBit(oldp+104,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_xip_en));
        bufp->chgBit(oldp+105,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active));
        bufp->chgBit(oldp+106,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active));
        bufp->chgBit(oldp+107,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold));
        bufp->chgBit(oldp+108,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold));
        bufp->chgBit(oldp+109,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awvalid));
        bufp->chgIData(oldp+110,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_awaddr),32);
        bufp->chgBit(oldp+111,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wvalid));
        bufp->chgIData(oldp+112,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wdata),32);
        bufp->chgCData(oldp+113,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_wstrb),4);
        bufp->chgBit(oldp+114,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_bready));
        bufp->chgBit(oldp+115,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arvalid));
        bufp->chgIData(oldp+116,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_araddr),32);
        bufp->chgCData(oldp+117,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_arprot),3);
        bufp->chgBit(oldp+118,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__m_axi_rready));
        bufp->chgCData(oldp+119,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_slave_sel),2);
        bufp->chgCData(oldp+120,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_slave_sel),2);
        bufp->chgBit(oldp+121,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__aw_decerr));
        bufp->chgBit(oldp+122,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__ar_decerr));
        bufp->chgCData(oldp+123,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_state),2);
        bufp->chgCData(oldp+124,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_slave_reg),2);
        bufp->chgIData(oldp+125,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_addr_reg),32);
        bufp->chgCData(oldp+126,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__w_prot_reg),3);
        bufp->chgCData(oldp+127,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_state),2);
        bufp->chgCData(oldp+128,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_slave_reg),2);
        bufp->chgIData(oldp+129,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_addr_reg),32);
        bufp->chgCData(oldp+130,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__u_xbar__DOT__r_prot_reg),3);
        bufp->chgCData(oldp+131,((0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_araddr)),8);
        bufp->chgCData(oldp+132,((0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s0_awaddr)),8);
        bufp->chgBit(oldp+133,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__aw_done));
        bufp->chgBit(oldp+134,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_bootrom__DOT__w_done));
        bufp->chgBit(oldp+135,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__trace_valid));
        bufp->chgQData(oldp+136,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__trace_data),36);
        bufp->chgBit(oldp+138,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_valid));
        bufp->chgBit(oldp+139,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__mem_instr));
        bufp->chgBit(oldp+140,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__pcpi_valid));
        bufp->chgIData(oldp+141,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__pcpi_insn),32);
        bufp->chgIData(oldp+142,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1),32);
        bufp->chgIData(oldp+143,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2),32);
        bufp->chgBit(oldp+144,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_awvalid));
        bufp->chgBit(oldp+145,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_arvalid));
        bufp->chgBit(oldp+146,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__ack_wvalid));
        bufp->chgBit(oldp+147,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__axi_adapter__DOT__xfer_done));
        bufp->chgIData(oldp+148,((((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch) 
                                   | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst))
                                   ? (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_pc)
                                   : (0xfffffffcU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1))),32);
        bufp->chgIData(oldp+149,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wdata),32);
        bufp->chgCData(oldp+150,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_wstrb),4);
        bufp->chgQData(oldp+151,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_cycle),64);
        bufp->chgQData(oldp+153,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__count_instr),64);
        bufp->chgIData(oldp+155,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_pc),32);
        bufp->chgIData(oldp+156,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_next_pc),32);
        bufp->chgIData(oldp+157,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_out),32);
        bufp->chgCData(oldp+158,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_sh),5);
        bufp->chgIData(oldp+159,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_insn_opcode),32);
        bufp->chgIData(oldp+160,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_opcode),32);
        bufp->chgIData(oldp+161,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_addr),32);
        bufp->chgIData(oldp+162,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_pc),32);
        bufp->chgBit(oldp+163,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_delay));
        bufp->chgBit(oldp+164,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_active));
        bufp->chgIData(oldp+165,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_mask),32);
        bufp->chgIData(oldp+166,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending),32);
        bufp->chgIData(oldp+167,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__timer),32);
        bufp->chgBit(oldp+168,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_halt_allowed));
        bufp->chgBit(oldp+169,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__ebreak_halt_trigger));
        bufp->chgCData(oldp+170,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_state),2);
        bufp->chgCData(oldp+171,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_wordsize),2);
        bufp->chgIData(oldp+172,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_q),32);
        bufp->chgBit(oldp+173,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch));
        bufp->chgBit(oldp+174,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rinst));
        bufp->chgBit(oldp+175,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_rdata));
        bufp->chgBit(oldp+176,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_wdata));
        bufp->chgBit(oldp+177,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_secondword));
        bufp->chgBit(oldp+178,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_firstword_reg));
        bufp->chgBit(oldp+179,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__last_mem_valid));
        bufp->chgBit(oldp+180,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__prefetched_high_word));
        bufp->chgBit(oldp+181,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_do_prefetch) 
                                | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT____VdfgRegularize_had7d1046_0_1))));
        bufp->chgBit(oldp+182,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lui));
        bufp->chgBit(oldp+183,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_auipc));
        bufp->chgBit(oldp+184,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jal));
        bufp->chgBit(oldp+185,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_jalr));
        bufp->chgBit(oldp+186,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_beq));
        bufp->chgBit(oldp+187,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bne));
        bufp->chgBit(oldp+188,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_blt));
        bufp->chgBit(oldp+189,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bge));
        bufp->chgBit(oldp+190,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bltu));
        bufp->chgBit(oldp+191,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_bgeu));
        bufp->chgBit(oldp+192,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lb));
        bufp->chgBit(oldp+193,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lh));
        bufp->chgBit(oldp+194,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lw));
        bufp->chgBit(oldp+195,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lbu));
        bufp->chgBit(oldp+196,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_lhu));
        bufp->chgBit(oldp+197,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sb));
        bufp->chgBit(oldp+198,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sh));
        bufp->chgBit(oldp+199,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sw));
        bufp->chgBit(oldp+200,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_addi));
        bufp->chgBit(oldp+201,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slti));
        bufp->chgBit(oldp+202,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltiu));
        bufp->chgBit(oldp+203,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xori));
        bufp->chgBit(oldp+204,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ori));
        bufp->chgBit(oldp+205,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_andi));
        bufp->chgBit(oldp+206,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slli));
        bufp->chgBit(oldp+207,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srli));
        bufp->chgBit(oldp+208,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srai));
        bufp->chgBit(oldp+209,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_add));
        bufp->chgBit(oldp+210,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sub));
        bufp->chgBit(oldp+211,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sll));
        bufp->chgBit(oldp+212,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_slt));
        bufp->chgBit(oldp+213,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sltu));
        bufp->chgBit(oldp+214,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_xor));
        bufp->chgBit(oldp+215,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srl));
        bufp->chgBit(oldp+216,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sra));
        bufp->chgBit(oldp+217,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_or));
        bufp->chgBit(oldp+218,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_and));
        bufp->chgBit(oldp+219,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycle));
        bufp->chgBit(oldp+220,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdcycleh));
        bufp->chgBit(oldp+221,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstr));
        bufp->chgBit(oldp+222,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_rdinstrh));
        bufp->chgBit(oldp+223,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_ecall_ebreak));
        bufp->chgBit(oldp+224,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_fence));
        bufp->chgBit(oldp+225,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_getq));
        bufp->chgBit(oldp+226,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_setq));
        bufp->chgBit(oldp+227,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_retirq));
        bufp->chgBit(oldp+228,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_maskirq));
        bufp->chgBit(oldp+229,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_waitirq));
        bufp->chgBit(oldp+230,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_timer));
        bufp->chgCData(oldp+231,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rd),6);
        bufp->chgCData(oldp+232,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs1),6);
        bufp->chgCData(oldp+233,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_rs2),5);
        bufp->chgIData(oldp+234,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm),32);
        bufp->chgIData(oldp+235,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoded_imm_j),32);
        bufp->chgBit(oldp+236,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger));
        bufp->chgBit(oldp+237,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_trigger_q));
        bufp->chgBit(oldp+238,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger));
        bufp->chgBit(oldp+239,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q));
        bufp->chgBit(oldp+240,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__compressed_instr));
        bufp->chgBit(oldp+241,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal));
        bufp->chgBit(oldp+242,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu));
        bufp->chgBit(oldp+243,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_slli_srli_srai));
        bufp->chgBit(oldp+244,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi));
        bufp->chgBit(oldp+245,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sb_sh_sw));
        bufp->chgBit(oldp+246,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sll_srl_sra));
        bufp->chgBit(oldp+247,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lui_auipc_jal_jalr_addi_add_sub));
        bufp->chgBit(oldp+248,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_slti_blt_slt));
        bufp->chgBit(oldp+249,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_sltiu_bltu_sltu));
        bufp->chgBit(oldp+250,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu));
        bufp->chgBit(oldp+251,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_lbu_lhu_lw));
        bufp->chgBit(oldp+252,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_imm));
        bufp->chgBit(oldp+253,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_alu_reg_reg));
        bufp->chgBit(oldp+254,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_compare));
        bufp->chgBit(oldp+255,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh));
        bufp->chgQData(oldp+256,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__new_ascii_instr),64);
        bufp->chgQData(oldp+258,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_instr),64);
        bufp->chgIData(oldp+260,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_imm),32);
        bufp->chgCData(oldp+261,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs1),5);
        bufp->chgCData(oldp+262,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rs2),5);
        bufp->chgCData(oldp+263,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_insn_rd),5);
        bufp->chgIData(oldp+264,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val),32);
        bufp->chgIData(oldp+265,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val),32);
        bufp->chgBit(oldp+266,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs1val_valid));
        bufp->chgBit(oldp+267,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_rs2val_valid));
        bufp->chgQData(oldp+268,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_ascii_instr),64);
        bufp->chgIData(oldp+270,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_imm),32);
        bufp->chgIData(oldp+271,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_opcode),32);
        bufp->chgCData(oldp+272,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs1),5);
        bufp->chgCData(oldp+273,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rs2),5);
        bufp->chgCData(oldp+274,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__q_insn_rd),5);
        bufp->chgBit(oldp+275,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_next));
        bufp->chgBit(oldp+276,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__launch_next_insn));
        bufp->chgBit(oldp+277,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_valid_insn));
        bufp->chgQData(oldp+278,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_ascii_instr),64);
        bufp->chgIData(oldp+280,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_imm),32);
        bufp->chgIData(oldp+281,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_opcode),32);
        bufp->chgCData(oldp+282,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs1),5);
        bufp->chgCData(oldp+283,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rs2),5);
        bufp->chgCData(oldp+284,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cached_insn_rd),5);
        bufp->chgCData(oldp+285,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpu_state),8);
        bufp->chgCData(oldp+286,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_state),2);
        bufp->chgIData(oldp+287,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__irq_pending_ack),32);
        bufp->chgWData(oldp+288,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__dbg_ascii_state),128);
        bufp->chgBit(oldp+292,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rinst));
        bufp->chgBit(oldp+293,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_rdata));
        bufp->chgBit(oldp+294,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__set_mem_do_wdata));
        bufp->chgBit(oldp+295,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_store));
        bufp->chgBit(oldp+296,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_stalu));
        bufp->chgBit(oldp+297,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_branch));
        bufp->chgBit(oldp+298,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_compr));
        bufp->chgBit(oldp+299,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_trace));
        bufp->chgBit(oldp+300,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lu));
        bufp->chgBit(oldp+301,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lh));
        bufp->chgBit(oldp+302,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_is_lb));
        bufp->chgCData(oldp+303,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__latched_rd),6);
        bufp->chgIData(oldp+304,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__current_pc),32);
        bufp->chgBit(oldp+305,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__pcpi_timeout));
        bufp->chgIData(oldp+306,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__next_irq_pending),32);
        bufp->chgBit(oldp+307,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__do_waitirq));
        bufp->chgIData(oldp+308,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out),32);
        bufp->chgIData(oldp+309,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_q),32);
        bufp->chgBit(oldp+310,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0));
        bufp->chgBit(oldp+311,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_out_0_q));
        bufp->chgBit(oldp+312,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_wait));
        bufp->chgBit(oldp+313,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_wait_2));
        bufp->chgIData(oldp+314,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sub)
                                   ? (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                      - vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2)
                                   : (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                      + vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2))),32);
        bufp->chgIData(oldp+315,((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                  << (0x0000001fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2))),32);
        bufp->chgIData(oldp+316,((IData)((0x00000001ffffffffULL 
                                          & VL_SHIFTRS_QQI(33,33,5, 
                                                           (((QData)((IData)(
                                                                             (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_sra) 
                                                                               | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__instr_srai)) 
                                                                              & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1 
                                                                                >> 0x0000001fU)))) 
                                                             << 0x00000020U) 
                                                            | (QData)((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op1))), 
                                                           (0x0000001fU 
                                                            & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__reg_op2))))),32);
        bufp->chgBit(oldp+317,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_eq));
        bufp->chgBit(oldp+318,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_ltu));
        bufp->chgBit(oldp+319,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__alu_lts));
        bufp->chgBit(oldp+320,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word_q));
        bufp->chgBit(oldp+321,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_write));
        bufp->chgIData(oldp+322,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_wrdata),32);
        bufp->chgIData(oldp+323,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs1),32);
        bufp->chgIData(oldp+324,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__cpuregs_rs2),32);
        bufp->chgBit(oldp+325,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dmactive));
        bufp->chgBit(oldp+326,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__haltreq));
        bufp->chgBit(oldp+327,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resumereq));
        bufp->chgIData(oldp+328,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command),32);
        bufp->chgIData(oldp+329,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dcsr_shadow),32);
        bufp->chgBit(oldp+330,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dbg_halted_q));
        bufp->chgBit(oldp+331,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__abstract_busy));
        bufp->chgCData(oldp+332,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__cmderr),3);
        bufp->chgBit(oldp+333,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__dpc_written));
        bufp->chgBit(oldp+334,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadonaddr));
        bufp->chgBit(oldp+335,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbautoincrement));
        bufp->chgBit(oldp+336,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbreadondata));
        bufp->chgBit(oldp+337,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbbusyerror));
        bufp->chgCData(oldp+338,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sberror),3);
        bufp->chgCData(oldp+339,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaccess_size),3);
        bufp->chgIData(oldp+340,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbaddress0),32);
        bufp->chgIData(oldp+341,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sbdata0),32);
        bufp->chgBit(oldp+342,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__resume_pending_q));
        bufp->chgBit(oldp+343,((1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                      >> 0x00000010U))));
        bufp->chgBit(oldp+344,((1U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                      >> 0x00000011U))));
        bufp->chgSData(oldp+345,((0x0000ffffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command)),16);
        bufp->chgCData(oldp+346,((7U & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                        >> 0x00000014U))),3);
        bufp->chgBit(oldp+347,((1U == (0x0000000fU 
                                       & (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command 
                                          >> 0x0000000cU)))));
        bufp->chgBit(oldp+348,((0x0301U == (0x0000ffffU 
                                            & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command))));
        bufp->chgBit(oldp+349,((0x07b1U == (0x0000ffffU 
                                            & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command))));
        bufp->chgBit(oldp+350,((0x07b0U == (0x0000ffffU 
                                            & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__command))));
        bufp->chgCData(oldp+351,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state),3);
        bufp->chgBit(oldp+352,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__aw_done));
        bufp->chgBit(oldp+353,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__w_done));
        bufp->chgCData(oldp+354,((0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_araddr)),8);
        bufp->chgCData(oldp+355,((0x000000ffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s2_awaddr)),8);
        bufp->chgBit(oldp+356,(((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_rvalid_reg)) 
                                & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending)) 
                                   & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_xip_en)))));
        bufp->chgIData(oldp+357,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_rdata_reg),32);
        bufp->chgBit(oldp+358,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_rvalid_reg));
        bufp->chgBit(oldp+359,((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_aw_done)) 
                                      & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_bvalid_r))))));
        bufp->chgBit(oldp+360,((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_w_done)) 
                                      & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_bvalid_r))))));
        bufp->chgBit(oldp+361,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_bvalid_r));
        bufp->chgBit(oldp+362,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_enable));
        bufp->chgCData(oldp+363,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr_width),2);
        bufp->chgCData(oldp+364,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd),8);
        bufp->chgBit(oldp+365,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_cmd_start));
        bufp->chgIData(oldp+366,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_addr),32);
        bufp->chgCData(oldp+367,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_txdata),8);
        bufp->chgSData(oldp+368,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_clkdiv),16);
        bufp->chgCData(oldp+369,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__reg_dummy_cycles),4);
        bufp->chgCData(oldp+370,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state),4);
        bufp->chgSData(oldp+371,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_cnt),16);
        bufp->chgBit(oldp+372,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_phase));
        bufp->chgCData(oldp+373,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__bit_cnt),5);
        bufp->chgCData(oldp+374,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_out),8);
        bufp->chgCData(oldp+375,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__shift_in),8);
        bufp->chgCData(oldp+376,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__byte_cnt),3);
        bufp->chgIData(oldp+377,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_buf),32);
        bufp->chgBit(oldp+378,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_valid));
        bufp->chgCData(oldp+379,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__rx_data_reg),8);
        bufp->chgBit(oldp+380,((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__state))));
        bufp->chgBit(oldp+381,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__timeout_err));
        bufp->chgIData(oldp+382,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__timeout_cnt),20);
        bufp->chgBit(oldp+383,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__sclk_reg));
        bufp->chgBit(oldp+384,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__cs_n_reg));
        bufp->chgBit(oldp+385,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__mosi_reg));
        bufp->chgBit(oldp+386,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_done_r));
        bufp->chgBit(oldp+387,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__w_done_r));
        bufp->chgCData(oldp+388,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__aw_addr_captured),6);
        bufp->chgBit(oldp+389,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_aw_done));
        bufp->chgBit(oldp+390,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_w_done));
        bufp->chgBit(oldp+391,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_pending));
        bufp->chgIData(oldp+392,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__xip_read_addr),32);
        bufp->chgBit(oldp+393,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_flash__DOT__clk_tick));
        bufp->chgBit(oldp+394,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff1));
        bufp->chgBit(oldp+395,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff2));
        bufp->chgBit(oldp+396,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff3));
        bufp->chgBit(oldp+397,(((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff3)) 
                                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__sync_ff2))));
        bufp->chgBit(oldp+398,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_toggle_sys));
        bufp->chgIData(oldp+399,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_data_sys),32);
        bufp->chgCData(oldp+400,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__resp_op_sys),2);
        bufp->chgSData(oldp+401,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sckdiv),16);
        bufp->chgBit(oldp+402,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpol));
        bufp->chgBit(oldp+403,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_cpha));
        bufp->chgCData(oldp+404,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csid),2);
        bufp->chgCData(oldp+405,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csdef),4);
        bufp->chgCData(oldp+406,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_csmode),2);
        bufp->chgBit(oldp+407,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_endian));
        bufp->chgCData(oldp+408,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_framelen),5);
        bufp->chgCData(oldp+409,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_txmark),3);
        bufp->chgCData(oldp+410,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_rxmark),3);
        bufp->chgCData(oldp+411,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ie),4);
        bufp->chgCData(oldp+412,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip),4);
        bufp->chgBit(oldp+413,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_enable));
        bufp->chgBit(oldp+414,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_sw_rst));
        bufp->chgIData(oldp+415,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[0]),32);
        bufp->chgIData(oldp+416,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[1]),32);
        bufp->chgIData(oldp+417,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[2]),32);
        bufp->chgIData(oldp+418,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[3]),32);
        bufp->chgIData(oldp+419,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[4]),32);
        bufp->chgIData(oldp+420,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[5]),32);
        bufp->chgIData(oldp+421,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[6]),32);
        bufp->chgIData(oldp+422,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_fifo[7]),32);
        bufp->chgCData(oldp+423,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_wptr),4);
        bufp->chgCData(oldp+424,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_rptr),4);
        bufp->chgCData(oldp+425,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count),4);
        bufp->chgBit(oldp+426,((8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count))));
        bufp->chgBit(oldp+427,((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count))));
        bufp->chgIData(oldp+428,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[0]),32);
        bufp->chgIData(oldp+429,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[1]),32);
        bufp->chgIData(oldp+430,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[2]),32);
        bufp->chgIData(oldp+431,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[3]),32);
        bufp->chgIData(oldp+432,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[4]),32);
        bufp->chgIData(oldp+433,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[5]),32);
        bufp->chgIData(oldp+434,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[6]),32);
        bufp->chgIData(oldp+435,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_fifo[7]),32);
        bufp->chgCData(oldp+436,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_wptr),4);
        bufp->chgCData(oldp+437,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_rptr),4);
        bufp->chgCData(oldp+438,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count),4);
        bufp->chgBit(oldp+439,((8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count))));
        bufp->chgBit(oldp+440,((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count))));
        bufp->chgCData(oldp+441,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state),3);
        bufp->chgSData(oldp+442,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_cnt),16);
        bufp->chgBit(oldp+443,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase));
        bufp->chgCData(oldp+444,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__bit_cnt),5);
        bufp->chgIData(oldp+445,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_out),32);
        bufp->chgIData(oldp+446,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__shift_in),32);
        bufp->chgBit(oldp+447,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__sclk_reg));
        bufp->chgBit(oldp+448,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__mosi_reg));
        bufp->chgBit(oldp+449,((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state))));
        bufp->chgCData(oldp+450,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_setup_cnt),4);
        bufp->chgCData(oldp+451,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt),4);
        bufp->chgBit(oldp+452,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count) 
                                <= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_txmark))));
        bufp->chgBit(oldp+453,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_count) 
                                >= (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_rxmark))));
        bufp->chgBit(oldp+454,(((4U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state)) 
                                & ((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__cs_hold_cnt)) 
                                   & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__clk_phase)))));
        bufp->chgBit(oldp+455,(((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__spi_state)) 
                                & ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)) 
                                   & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_enable)))));
        bufp->chgBit(oldp+456,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_push));
        bufp->chgCData(oldp+457,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__out_bit_idx),5);
        bufp->chgSData(oldp+458,((0x00003fffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_awaddr)),14);
        bufp->chgSData(oldp+459,((0x00003fffU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__s1_araddr)),14);
        bufp->chgBit(oldp+460,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_csb0));
        bufp->chgBit(oldp+461,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_web0));
        bufp->chgCData(oldp+462,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_wmask0),4);
        bufp->chgSData(oldp+463,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_addr0),12);
        bufp->chgIData(oldp+464,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_din0),32);
        bufp->chgIData(oldp+465,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__sram_dout0),32);
        bufp->chgBit(oldp+466,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_captured));
        bufp->chgBit(oldp+467,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_captured));
        bufp->chgBit(oldp+468,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__wr_pending));
        bufp->chgSData(oldp+469,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__aw_addr_r),12);
        bufp->chgIData(oldp+470,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_data_r),32);
        bufp->chgCData(oldp+471,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__w_strb_r),4);
        bufp->chgCData(oldp+472,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_state),2);
        bufp->chgBit(oldp+473,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_sram__DOT__rd_access));
        bufp->chgBit(oldp+474,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_one_shot));
        bufp->chgBit(oldp+475,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size));
        bufp->chgCData(oldp+476,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale),2);
        bufp->chgBit(oldp+477,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_int_en));
        bufp->chgBit(oldp+478,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_mode));
        bufp->chgBit(oldp+479,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_enable));
        bufp->chgIData(oldp+480,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_reg),32);
        bufp->chgIData(oldp+481,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_reg),32);
        bufp->chgIData(oldp+482,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter),32);
        bufp->chgBit(oldp+483,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__raw_int));
        bufp->chgBit(oldp+484,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__timer_stopped));
        bufp->chgCData(oldp+485,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_counter),8);
        bufp->chgBit(oldp+486,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__prescale_tick));
        bufp->chgCData(oldp+487,(((0U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale))
                                   ? 0U : ((1U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale))
                                            ? 0x0fU
                                            : ((2U 
                                                == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_prescale))
                                                ? 0xffU
                                                : 0U)))),8);
        bufp->chgIData(oldp+488,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_timer_size)
                                   ? 0xffffffffU : 0x0000ffffU)),32);
        bufp->chgIData(oldp+489,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter_value),32);
        bufp->chgBit(oldp+490,((0U == vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__counter_value)));
        bufp->chgSData(oldp+491,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_div),16);
        bufp->chgBit(oldp+492,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_en));
        bufp->chgBit(oldp+493,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_en));
        bufp->chgBit(oldp+494,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__irq_en));
        bufp->chgBit(oldp+495,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_overrun));
        bufp->chgBit(oldp+496,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_err_sticky));
        bufp->chgBit(oldp+497,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__wr_ctrl_pulse));
        bufp->chgSData(oldp+498,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_counter),16);
        bufp->chgBit(oldp+499,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick));
        bufp->chgBit(oldp+500,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_tick_16x));
        bufp->chgCData(oldp+501,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_sub_cnt),4);
        bufp->chgBit(oldp+502,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_en));
        bufp->chgCData(oldp+503,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_fifo_wr_data),8);
        bufp->chgBit(oldp+504,(((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__empty)) 
                                & ((~ ((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state)) 
                                       | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start))) 
                                   & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_en)))));
        bufp->chgCData(oldp+505,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem
                                 [(7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr))]),8);
        bufp->chgBit(oldp+506,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__empty));
        bufp->chgBit(oldp+507,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__full));
        bufp->chgBit(oldp+508,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_en));
        bufp->chgCData(oldp+509,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_data_in),8);
        bufp->chgCData(oldp+510,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem
                                 [(7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr))]),8);
        bufp->chgBit(oldp+511,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty));
        bufp->chgBit(oldp+512,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__full));
        bufp->chgBit(oldp+513,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_start));
        bufp->chgCData(oldp+514,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_data_out),8);
        bufp->chgBit(oldp+515,((0U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state))));
        bufp->chgBit(oldp+516,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_valid));
        bufp->chgBit(oldp+517,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__frame_error));
        bufp->chgCData(oldp+518,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__state),2);
        bufp->chgCData(oldp+519,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__shift_reg),8);
        bufp->chgCData(oldp+520,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__bit_cnt),3);
        bufp->chgCData(oldp+521,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__sample_cnt),4);
        bufp->chgBit(oldp+522,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_0));
        bufp->chgBit(oldp+523,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx__DOT__rx_sync_1));
        bufp->chgCData(oldp+524,((0x0000000fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr) 
                                                 - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr)))),4);
        bufp->chgCData(oldp+525,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[0]),8);
        bufp->chgCData(oldp+526,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[1]),8);
        bufp->chgCData(oldp+527,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[2]),8);
        bufp->chgCData(oldp+528,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[3]),8);
        bufp->chgCData(oldp+529,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[4]),8);
        bufp->chgCData(oldp+530,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[5]),8);
        bufp->chgCData(oldp+531,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[6]),8);
        bufp->chgCData(oldp+532,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem[7]),8);
        bufp->chgCData(oldp+533,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr),4);
        bufp->chgCData(oldp+534,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr),4);
        bufp->chgCData(oldp+535,((7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__wr_ptr))),3);
        bufp->chgCData(oldp+536,((7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr))),3);
        bufp->chgCData(oldp+537,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__state),2);
        bufp->chgCData(oldp+538,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__shift_reg),8);
        bufp->chgCData(oldp+539,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx__DOT__bit_cnt),3);
        bufp->chgCData(oldp+540,((0x0000000fU & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr) 
                                                 - (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr)))),4);
        bufp->chgCData(oldp+541,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[0]),8);
        bufp->chgCData(oldp+542,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[1]),8);
        bufp->chgCData(oldp+543,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[2]),8);
        bufp->chgCData(oldp+544,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[3]),8);
        bufp->chgCData(oldp+545,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[4]),8);
        bufp->chgCData(oldp+546,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[5]),8);
        bufp->chgCData(oldp+547,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[6]),8);
        bufp->chgCData(oldp+548,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__mem[7]),8);
        bufp->chgCData(oldp+549,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr),4);
        bufp->chgCData(oldp+550,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr),4);
        bufp->chgCData(oldp+551,((7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__wr_ptr))),3);
        bufp->chgCData(oldp+552,((7U & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_tx_fifo__DOT__rd_ptr))),3);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[2U] 
                      | vlSelfRef.__Vm_traceActivity
                      [5U])))) {
        bufp->chgBit(oldp+553,(((1U & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active)) 
                                       & (~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid))))
                                 ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready)
                                 : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active) 
                                    & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)) 
                                       & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready))))));
        bufp->chgBit(oldp+554,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_active)
                                 ? ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)) 
                                    & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready))
                                 : ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awvalid)) 
                                    & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready)))));
        bufp->chgBit(oldp+555,(((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)) 
                                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid))));
        bufp->chgBit(oldp+556,((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active)) 
                                 & (3U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)))
                                 ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready)
                                 : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active) 
                                    & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)) 
                                       & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready))))));
        bufp->chgBit(oldp+557,(((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)) 
                                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid))));
        bufp->chgCData(oldp+558,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)
                                   ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp))),2);
        bufp->chgCData(oldp+559,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)
                                   ? 0U : (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp))),2);
        bufp->chgCData(oldp+560,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__w_sel_hold)
                                   ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp)
                                   : 0U)),2);
        bufp->chgBit(oldp+561,((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active)) 
                                 & (3U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_state)))
                                 ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready)
                                 : ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_active) 
                                    & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold) 
                                       & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready))))));
        bufp->chgCData(oldp+562,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__r_sel_hold)
                                   ? (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp)
                                   : 0U)),2);
        bufp->chgIData(oldp+563,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart)
                                   ? ((8U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                       ? ((4U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                           ? ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                               ? 0U
                                               : ((1U 
                                                   & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                                   ? 0U
                                                   : 
                                                  (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__irq_en) 
                                                    << 0x00000012U) 
                                                   | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__rx_en) 
                                                       << 0x00000011U) 
                                                      | (((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__tx_en) 
                                                          << 0x00000010U) 
                                                         | (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__baud_div))))))
                                           : ((2U & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                               ? 0U
                                               : ((1U 
                                                   & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                                   ? 0U
                                                   : 
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
                                               ? 0U
                                               : ((1U 
                                                   & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)
                                                   ? 0U
                                                   : 
                                                  vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__mem
                                                  [
                                                  (7U 
                                                   & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__rd_ptr))]))
                                           : 0U)) : 0U)),32);
        bufp->chgBit(oldp+564,((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite)) 
                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT____VdfgRegularize_h3902cce4_0_0)) 
                                | ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_write)) 
                                   & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__jdbg_valid)))));
        bufp->chgBit(oldp+565,(((8U != (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)) 
                                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_0))));
        bufp->chgBit(oldp+566,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT____VdfgRegularize_h11c1cc39_0_0) 
                                & (8U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__tx_count)))));
        bufp->chgBit(oldp+567,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart) 
                                & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite)) 
                                   & ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable) 
                                      & ((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty)) 
                                         & (4U == (0x0000000fU 
                                                   & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr))))))));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[3U]))) {
        bufp->chgBit(oldp+568,((0U != ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie 
                                        & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip) 
                                       | ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie 
                                           & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip) 
                                          | ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie 
                                              & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip) 
                                             | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie 
                                                & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip)))))));
        bufp->chgIData(oldp+569,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_pue),32);
        bufp->chgIData(oldp+570,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_ds),32);
        bufp->chgIData(oldp+571,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_en),32);
        bufp->chgIData(oldp+572,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_iof_sel),32);
        bufp->chgIData(oldp+573,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en),32);
        bufp->chgIData(oldp+574,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_en),32);
        bufp->chgIData(oldp+575,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_output_val),32);
        bufp->chgIData(oldp+576,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie),32);
        bufp->chgIData(oldp+577,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip),32);
        bufp->chgIData(oldp+578,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie),32);
        bufp->chgIData(oldp+579,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip),32);
        bufp->chgIData(oldp+580,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie),32);
        bufp->chgIData(oldp+581,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip),32);
        bufp->chgIData(oldp+582,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie),32);
        bufp->chgIData(oldp+583,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip),32);
        bufp->chgIData(oldp+584,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_out_xor),32);
        bufp->chgIData(oldp+585,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage1),32);
        bufp->chgIData(oldp+586,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2),32);
        bufp->chgIData(oldp+587,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_prev),32);
        bufp->chgIData(oldp+588,(((~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_prev) 
                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2)),32);
        bufp->chgIData(oldp+589,(((~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2) 
                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_prev)),32);
        bufp->chgIData(oldp+590,((~ vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2)),32);
        bufp->chgIData(oldp+591,((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_input_en 
                                  & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__sync_stage2)),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[4U]))) {
        bufp->chgCData(oldp+592,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__tap_state),4);
        bufp->chgCData(oldp+593,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_shift),5);
        bufp->chgCData(oldp+594,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__ir_reg),5);
        bufp->chgQData(oldp+595,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift),41);
        bufp->chgQData(oldp+597,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_shift_rev),41);
        bufp->chgBit(oldp+599,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dtmcs_dmireset_pulse));
        bufp->chgBit(oldp+600,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__update_dmi_d));
        bufp->chgBit(oldp+601,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_write_tck));
        bufp->chgCData(oldp+602,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_addr_tck),7);
        bufp->chgIData(oldp+603,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_jtag_dtm__DOT__dmi_wdata_tck),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[5U]))) {
        bufp->chgIData(oldp+604,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m0_axi_rdata),32);
        bufp->chgBit(oldp+605,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_awready));
        bufp->chgBit(oldp+606,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_wready));
        bufp->chgBit(oldp+607,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_bvalid));
        bufp->chgBit(oldp+608,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rvalid));
        bufp->chgIData(oldp+609,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__m1_axi_rdata),32);
        bufp->chgBit(oldp+610,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awvalid));
        bufp->chgBit(oldp+611,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_awready));
        bufp->chgIData(oldp+612,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awaddr),32);
        bufp->chgCData(oldp+613,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_awprot),3);
        bufp->chgBit(oldp+614,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wvalid));
        bufp->chgBit(oldp+615,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_wready));
        bufp->chgIData(oldp+616,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wdata),32);
        bufp->chgCData(oldp+617,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_wstrb),4);
        bufp->chgBit(oldp+618,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bvalid));
        bufp->chgBit(oldp+619,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bready));
        bufp->chgCData(oldp+620,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_bresp),2);
        bufp->chgBit(oldp+621,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arvalid));
        bufp->chgBit(oldp+622,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__axi_arready));
        bufp->chgIData(oldp+623,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_araddr),32);
        bufp->chgCData(oldp+624,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_arprot),3);
        bufp->chgBit(oldp+625,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rvalid));
        bufp->chgBit(oldp+626,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rready));
        bufp->chgIData(oldp+627,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rdata),32);
        bufp->chgCData(oldp+628,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__s3_rresp),2);
        bufp->chgBit(oldp+629,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_psel));
        bufp->chgBit(oldp+630,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_penable));
        bufp->chgBit(oldp+631,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwrite));
        bufp->chgIData(oldp+632,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr),32);
        bufp->chgIData(oldp+633,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pwdata),32);
        bufp->chgCData(oldp+634,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pstrb),4);
        bufp->chgCData(oldp+635,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pprot),3);
        bufp->chgBit(oldp+636,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_pslverr));
        bufp->chgBit(oldp+637,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_uart));
        bufp->chgBit(oldp+638,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_timer));
        bufp->chgIData(oldp+639,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__prdata_timer),32);
        bufp->chgBit(oldp+640,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_gpio));
        bufp->chgBit(oldp+641,(((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid)) 
                                & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT____VdfgRegularize_hf7b9a0fb_0_0))));
        bufp->chgBit(oldp+642,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_spi));
        bufp->chgIData(oldp+643,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_spi),32);
        bufp->chgBit(oldp+644,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__psel_debug));
        bufp->chgIData(oldp+645,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_debug),32);
        bufp->chgCData(oldp+646,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_apb_xbar__DOT__slave_sel),3);
        bufp->chgCData(oldp+647,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__state),3);
        bufp->chgBit(oldp+648,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_captured));
        bufp->chgBit(oldp+649,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_captured));
        bufp->chgIData(oldp+650,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_addr_reg),32);
        bufp->chgCData(oldp+651,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__aw_prot_reg),3);
        bufp->chgIData(oldp+652,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_data_reg),32);
        bufp->chgCData(oldp+653,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__w_strb_reg),4);
        bufp->chgIData(oldp+654,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__apb_rdata_reg),32);
        bufp->chgBit(oldp+655,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__apb_slverr_reg));
        bufp->chgBit(oldp+656,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi2apb__DOT__is_write_txn));
        bufp->chgBit(oldp+657,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_awready));
        bufp->chgBit(oldp+658,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_wready));
        bufp->chgBit(oldp+659,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bvalid));
        bufp->chgCData(oldp+660,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_bresp),2);
        bufp->chgBit(oldp+661,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_arready));
        bufp->chgBit(oldp+662,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rvalid));
        bufp->chgCData(oldp+663,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rresp),2);
        bufp->chgIData(oldp+664,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_axi_xbar__DOT__x_rdata),32);
        bufp->chgBit(oldp+665,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_ready));
        bufp->chgIData(oldp+666,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_word),32);
        bufp->chgBit(oldp+667,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_xfer));
        bufp->chgIData(oldp+668,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle),32);
        bufp->chgBit(oldp+669,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write));
        bufp->chgCData(oldp+670,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr),7);
        bufp->chgIData(oldp+671,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wdata),32);
        bufp->chgCData(oldp+672,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_wstrb),4);
        bufp->chgBit(oldp+673,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_write) 
                                & (0x17U == (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__bus_addr)))));
        bufp->chgBit(oldp+674,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_read));
        bufp->chgBit(oldp+675,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_debug__DOT__sba_start_write));
        bufp->chgBit(oldp+676,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__apb_write));
        bufp->chgIData(oldp+677,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__strb_mask),32);
        bufp->chgBit(oldp+678,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__addr_valid));
        bufp->chgBit(oldp+679,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_write));
        bufp->chgBit(oldp+680,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__apb_read));
        bufp->chgCData(oldp+681,((0x0000003fU & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)),6);
        bufp->chgBit(oldp+682,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__rx_pop));
        bufp->chgBit(oldp+683,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__load_write));
        bufp->chgBit(oldp+684,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__bgload_write));
        bufp->chgBit(oldp+685,(((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__apb_write) 
                                & (0x0cU == (0x0000001fU 
                                             & vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_paddr)))));
        bufp->chgBit(oldp+686,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__ctrl_write));
        bufp->chgBit(oldp+687,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_timer__DOT__apb_write));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[6U]))) {
        bufp->chgBit(oldp+688,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_read));
        bufp->chgBit(oldp+689,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_la_write));
        bufp->chgBit(oldp+690,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__clear_prefetched_high_word));
        bufp->chgBit(oldp+691,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_cpu__DOT__picorv32_core__DOT__mem_done_raw));
    }
    bufp->chgBit(oldp+692,(vlSelfRef.clk));
    bufp->chgBit(oldp+693,(vlSelfRef.rst_n));
    bufp->chgBit(oldp+694,(vlSelfRef.uart_tx));
    bufp->chgBit(oldp+695,(vlSelfRef.uart_rx));
    bufp->chgIData(oldp+696,(vlSelfRef.gpio_in),32);
    bufp->chgIData(oldp+697,(vlSelfRef.gpio_out),32);
    bufp->chgIData(oldp+698,(vlSelfRef.gpio_oe),32);
    bufp->chgBit(oldp+699,(vlSelfRef.spi_sclk));
    bufp->chgBit(oldp+700,(vlSelfRef.spi_mosi));
    bufp->chgBit(oldp+701,(vlSelfRef.spi_miso));
    bufp->chgCData(oldp+702,(vlSelfRef.spi_cs_n),4);
    bufp->chgBit(oldp+703,(vlSelfRef.flash_sclk));
    bufp->chgBit(oldp+704,(vlSelfRef.flash_cs_n));
    bufp->chgBit(oldp+705,(vlSelfRef.flash_mosi));
    bufp->chgBit(oldp+706,(vlSelfRef.flash_miso));
    bufp->chgBit(oldp+707,(vlSelfRef.jtag_tck));
    bufp->chgBit(oldp+708,(vlSelfRef.jtag_tms));
    bufp->chgBit(oldp+709,(vlSelfRef.jtag_tdi));
    bufp->chgBit(oldp+710,(vlSelfRef.jtag_tdo));
    bufp->chgBit(oldp+711,(vlSelfRef.trap));
    bufp->chgBit(oldp+712,(vlSelfRef.soc_top__DOT__rst_ff2));
    bufp->chgBit(oldp+713,(vlSelfRef.soc_top__DOT__rst_ff1));
    bufp->chgIData(oldp+714,(((((0U != ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ie) 
                                        & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_spi__DOT__reg_ip))) 
                                << 6U) | ((0U != ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ie 
                                                   & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_rise_ip) 
                                                  | ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ie 
                                                      & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_fall_ip) 
                                                     | ((vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ie 
                                                         & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_high_ip) 
                                                        | (vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ie 
                                                           & vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_gpio__DOT__reg_low_ip))))) 
                                          << 5U)) | 
                              ((((~ (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__u_rx_fifo__DOT__empty)) 
                                 & (IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_uart__DOT__irq_en)) 
                                << 4U) | ((IData)(vlSelfRef.soc_top__DOT__u_soc_core__DOT__u_irq_aggregator__DOT__timer_irq) 
                                          << 3U)))),32);
    bufp->chgIData(oldp+715,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__apb_prdata),32);
    bufp->chgIData(oldp+716,(vlSelfRef.soc_top__DOT__u_soc_core__DOT__prdata_gpio),32);
}

void Vsoc_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_top___024root__trace_cleanup\n"); );
    // Body
    Vsoc_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsoc_top___024root*>(voidSelf);
    Vsoc_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[4U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[5U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[6U] = 0U;
}
