// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See StackMachine.h for the primary calling header

#include "verilated.h"

#include "StackMachine__Syms.h"
#include "StackMachine___024root.h"

void StackMachine___024root___ctor_var_reset(StackMachine___024root* vlSelf);

StackMachine___024root::StackMachine___024root(StackMachine__Syms* symsp, const char* name)
    : VerilatedModule{name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    StackMachine___024root___ctor_var_reset(this);
}

void StackMachine___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

StackMachine___024root::~StackMachine___024root() {
}
