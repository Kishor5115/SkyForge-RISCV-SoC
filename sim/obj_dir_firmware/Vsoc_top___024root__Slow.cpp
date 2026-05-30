// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_top.h for the primary calling header

#include "Vsoc_top__pch.h"

void Vsoc_top___024root___ctor_var_reset(Vsoc_top___024root* vlSelf);

Vsoc_top___024root::Vsoc_top___024root(Vsoc_top__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vsoc_top___024root___ctor_var_reset(this);
}

void Vsoc_top___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vsoc_top___024root::~Vsoc_top___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
