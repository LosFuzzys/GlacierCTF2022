// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VStackmachine.h for the primary calling header

#include "verilated.h"

#include "VStackmachine__Syms.h"
#include "VStackmachine___024root.h"

void VStackmachine___024root___ctor_var_reset(VStackmachine___024root* vlSelf);

VStackmachine___024root::VStackmachine___024root(VStackmachine__Syms* symsp, const char* name)
    : VerilatedModule{name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    VStackmachine___024root___ctor_var_reset(this);
}

void VStackmachine___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

VStackmachine___024root::~VStackmachine___024root() {
}
