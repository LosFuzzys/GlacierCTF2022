// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VStackmachine.h for the primary calling header

#include "verilated.h"

#include "VStackmachine__Syms.h"
#include "VStackmachine___024root.h"

VL_ATTR_COLD void VStackmachine___024root___settle__TOP__0(VStackmachine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VStackmachine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VStackmachine___024root___settle__TOP__0\n"); );
    // Body
    if (VL_UNLIKELY(vlSelf->Stackmachine__DOT____Vstrobe0)) {
        VL_WRITEF("sp = %3#, stack[sp - 1] = %10#, stack[sp - 2] = %10#\n",
                  7,vlSelf->Stackmachine__DOT__sp,32,
                  vlSelf->Stackmachine__DOT__stack[
                  (0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                            - (IData)(1U)))],32,vlSelf->Stackmachine__DOT__stack
                  [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                             - (IData)(2U)))]);
        vlSelf->Stackmachine__DOT____Vstrobe0 = 0U;
    }
}
