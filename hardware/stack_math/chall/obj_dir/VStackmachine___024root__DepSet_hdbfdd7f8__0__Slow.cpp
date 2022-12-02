// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VStackmachine.h for the primary calling header

#include "verilated.h"

#include "VStackmachine___024root.h"

VL_ATTR_COLD void VStackmachine___024root___eval_initial(VStackmachine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VStackmachine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VStackmachine___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

VL_ATTR_COLD void VStackmachine___024root___eval_settle(VStackmachine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VStackmachine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VStackmachine___024root___eval_settle\n"); );
}

VL_ATTR_COLD void VStackmachine___024root___final(VStackmachine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VStackmachine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VStackmachine___024root___final\n"); );
}

VL_ATTR_COLD void VStackmachine___024root___ctor_var_reset(VStackmachine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VStackmachine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VStackmachine___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->in = VL_RAND_RESET_I(4);
    vlSelf->out = VL_RAND_RESET_I(32);
    vlSelf->err = VL_RAND_RESET_I(1);
    for (int __Vi0=0; __Vi0<128; ++__Vi0) {
        vlSelf->Stackmachine__DOT__stack[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->Stackmachine__DOT__sp = VL_RAND_RESET_I(7);
    vlSelf->Stackmachine__DOT__unnamedblk1__DOT__i = VL_RAND_RESET_I(32);
}
