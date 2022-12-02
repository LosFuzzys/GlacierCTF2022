// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VStackmachine.h for the primary calling header

#include "verilated.h"

#include "VStackmachine__Syms.h"
#include "VStackmachine___024root.h"

VL_INLINE_OPT void VStackmachine___024root___sequent__TOP__0(VStackmachine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VStackmachine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VStackmachine___024root___sequent__TOP__0\n"); );
    // Init
    CData/*6:0*/ __Vdly__Stackmachine__DOT__sp;
    IData/*31:0*/ __Vdly__out;
    CData/*0:0*/ __Vdly__err;
    CData/*6:0*/ __Vdlyvdim0__Stackmachine__DOT__stack__v0;
    IData/*31:0*/ __Vdlyvval__Stackmachine__DOT__stack__v0;
    CData/*0:0*/ __Vdlyvset__Stackmachine__DOT__stack__v0;
    CData/*6:0*/ __Vdlyvdim0__Stackmachine__DOT__stack__v1;
    IData/*31:0*/ __Vdlyvval__Stackmachine__DOT__stack__v1;
    CData/*0:0*/ __Vdlyvset__Stackmachine__DOT__stack__v1;
    CData/*6:0*/ __Vdlyvdim0__Stackmachine__DOT__stack__v2;
    IData/*31:0*/ __Vdlyvval__Stackmachine__DOT__stack__v2;
    CData/*0:0*/ __Vdlyvset__Stackmachine__DOT__stack__v2;
    CData/*6:0*/ __Vdlyvdim0__Stackmachine__DOT__stack__v3;
    IData/*31:0*/ __Vdlyvval__Stackmachine__DOT__stack__v3;
    CData/*0:0*/ __Vdlyvset__Stackmachine__DOT__stack__v3;
    CData/*6:0*/ __Vdlyvdim0__Stackmachine__DOT__stack__v4;
    IData/*31:0*/ __Vdlyvval__Stackmachine__DOT__stack__v4;
    CData/*6:0*/ __Vdlyvdim0__Stackmachine__DOT__stack__v5;
    IData/*31:0*/ __Vdlyvval__Stackmachine__DOT__stack__v5;
    CData/*0:0*/ __Vdlyvset__Stackmachine__DOT__stack__v5;
    CData/*6:0*/ __Vdlyvdim0__Stackmachine__DOT__stack__v6;
    IData/*31:0*/ __Vdlyvval__Stackmachine__DOT__stack__v6;
    CData/*0:0*/ __Vdlyvset__Stackmachine__DOT__stack__v6;
    // Body
    __Vdly__err = vlSelf->err;
    __Vdly__out = vlSelf->out;
    __Vdly__Stackmachine__DOT__sp = vlSelf->Stackmachine__DOT__sp;
    __Vdlyvset__Stackmachine__DOT__stack__v0 = 0U;
    __Vdlyvset__Stackmachine__DOT__stack__v1 = 0U;
    __Vdlyvset__Stackmachine__DOT__stack__v2 = 0U;
    __Vdlyvset__Stackmachine__DOT__stack__v3 = 0U;
    __Vdlyvset__Stackmachine__DOT__stack__v5 = 0U;
    __Vdlyvset__Stackmachine__DOT__stack__v6 = 0U;
    if (vlSelf->rst) {
        vlSelf->Stackmachine__DOT__unnamedblk1__DOT__i = 0U;
        __Vdly__Stackmachine__DOT__sp = 0U;
        __Vdly__out = 0U;
        __Vdly__err = 0U;
        while (VL_GTS_III(32, 0x80U, vlSelf->Stackmachine__DOT__unnamedblk1__DOT__i)) {
            vlSelf->Stackmachine__DOT__stack[(0x7fU 
                                              & vlSelf->Stackmachine__DOT__unnamedblk1__DOT__i)] = 0U;
            vlSelf->Stackmachine__DOT__unnamedblk1__DOT__i 
                = ((IData)(1U) + vlSelf->Stackmachine__DOT__unnamedblk1__DOT__i);
        }
    } else if (((~ (IData)(vlSelf->err)) & (0U == vlSelf->out))) {
        vlSelf->Stackmachine__DOT____Vstrobe0 = 1U;
        if ((8U & (IData)(vlSelf->in))) {
            if ((4U & (IData)(vlSelf->in))) {
                if ((2U & (IData)(vlSelf->in))) {
                    VL_WRITEF("DONE %10#%1#\n",32,vlSelf->Stackmachine__DOT__stack
                              [vlSelf->Stackmachine__DOT__sp],
                              1,(1U & (IData)(vlSelf->in)));
                    if ((0U >= (IData)(vlSelf->Stackmachine__DOT__sp))) {
                        __Vdly__err = 1U;
                        __Vdly__out = 0xfU;
                    }
                    if ((0U == vlSelf->Stackmachine__DOT__stack
                         [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                    - (IData)(1U)))])) {
                        __Vdly__err = 1U;
                        __Vdly__out = 0xeU;
                    }
                    __Vdly__out = vlSelf->Stackmachine__DOT__stack
                        [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                   - (IData)(1U)))];
                } else {
                    VL_WRITEF("NOP %10#%1#\n",32,vlSelf->Stackmachine__DOT__stack
                              [vlSelf->Stackmachine__DOT__sp],
                              1,(1U & (IData)(vlSelf->in)));
                }
            } else if ((2U & (IData)(vlSelf->in))) {
                VL_WRITEF("MUL %10#%1#\n",32,vlSelf->Stackmachine__DOT__stack
                          [vlSelf->Stackmachine__DOT__sp],
                          1,(1U & (IData)(vlSelf->in)));
                if ((1U >= (IData)(vlSelf->Stackmachine__DOT__sp))) {
                    __Vdly__err = 1U;
                    __Vdly__out = 0xfU;
                }
                __Vdlyvval__Stackmachine__DOT__stack__v0 
                    = (vlSelf->Stackmachine__DOT__stack
                       [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                  - (IData)(2U)))] 
                       * vlSelf->Stackmachine__DOT__stack
                       [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                  - (IData)(1U)))]);
                __Vdlyvset__Stackmachine__DOT__stack__v0 = 1U;
                __Vdlyvdim0__Stackmachine__DOT__stack__v0 
                    = (0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                - (IData)(2U)));
                __Vdly__Stackmachine__DOT__sp = (0x7fU 
                                                 & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                                    - (IData)(1U)));
            } else {
                VL_WRITEF("ADD %10#%1#\n",32,vlSelf->Stackmachine__DOT__stack
                          [vlSelf->Stackmachine__DOT__sp],
                          1,(1U & (IData)(vlSelf->in)));
                if ((1U >= (IData)(vlSelf->Stackmachine__DOT__sp))) {
                    __Vdly__err = 1U;
                    __Vdly__out = 0xfU;
                }
                __Vdlyvval__Stackmachine__DOT__stack__v1 
                    = ((1U & (IData)(vlSelf->in)) ? 
                       (vlSelf->Stackmachine__DOT__stack
                        [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                   - (IData)(2U)))] 
                        + vlSelf->Stackmachine__DOT__stack
                        [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                   - (IData)(1U)))])
                        : (vlSelf->Stackmachine__DOT__stack
                           [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                      - (IData)(2U)))] 
                           - vlSelf->Stackmachine__DOT__stack
                           [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                      - (IData)(1U)))]));
                __Vdlyvset__Stackmachine__DOT__stack__v1 = 1U;
                __Vdlyvdim0__Stackmachine__DOT__stack__v1 
                    = (0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                - (IData)(2U)));
                __Vdly__Stackmachine__DOT__sp = (0x7fU 
                                                 & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                                    - (IData)(1U)));
            }
        } else if ((4U & (IData)(vlSelf->in))) {
            if ((2U & (IData)(vlSelf->in))) {
                VL_WRITEF("DUP %10#%1#\n",32,vlSelf->Stackmachine__DOT__stack
                          [vlSelf->Stackmachine__DOT__sp],
                          1,(1U & (IData)(vlSelf->in)));
                if ((0U >= (IData)(vlSelf->Stackmachine__DOT__sp))) {
                    __Vdly__err = 1U;
                    __Vdly__out = 0xfU;
                }
                if ((0x7fU <= (IData)(vlSelf->Stackmachine__DOT__sp))) {
                    __Vdly__err = 1U;
                    __Vdly__out = 0xfU;
                }
                __Vdlyvval__Stackmachine__DOT__stack__v2 
                    = vlSelf->Stackmachine__DOT__stack
                    [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                               - (IData)(1U)))];
                __Vdlyvset__Stackmachine__DOT__stack__v2 = 1U;
                __Vdlyvdim0__Stackmachine__DOT__stack__v2 
                    = vlSelf->Stackmachine__DOT__sp;
                __Vdly__Stackmachine__DOT__sp = (0x7fU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlSelf->Stackmachine__DOT__sp)));
            } else {
                VL_WRITEF("SWAP %10#%1#\n",32,vlSelf->Stackmachine__DOT__stack
                          [vlSelf->Stackmachine__DOT__sp],
                          1,(1U & (IData)(vlSelf->in)));
                if ((1U >= (IData)(vlSelf->Stackmachine__DOT__sp))) {
                    __Vdly__err = 1U;
                    __Vdly__out = 0xfU;
                }
                __Vdlyvval__Stackmachine__DOT__stack__v3 
                    = vlSelf->Stackmachine__DOT__stack
                    [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                               - (IData)(2U)))];
                __Vdlyvset__Stackmachine__DOT__stack__v3 = 1U;
                __Vdlyvdim0__Stackmachine__DOT__stack__v3 
                    = (0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                - (IData)(1U)));
                __Vdlyvval__Stackmachine__DOT__stack__v4 
                    = vlSelf->Stackmachine__DOT__stack
                    [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                               - (IData)(1U)))];
                __Vdlyvdim0__Stackmachine__DOT__stack__v4 
                    = (0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                - (IData)(2U)));
            }
        } else if ((2U & (IData)(vlSelf->in))) {
            VL_WRITEF("INC %10#%1#\n",32,vlSelf->Stackmachine__DOT__stack
                      [vlSelf->Stackmachine__DOT__sp],
                      1,(1U & (IData)(vlSelf->in)));
            if ((0U >= (IData)(vlSelf->Stackmachine__DOT__sp))) {
                __Vdly__err = 1U;
                __Vdly__out = 0xfU;
            }
            __Vdlyvval__Stackmachine__DOT__stack__v5 
                = ((1U & (IData)(vlSelf->in)) ? ((IData)(1U) 
                                                 + 
                                                 vlSelf->Stackmachine__DOT__stack
                                                 [(0x7fU 
                                                   & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                                      - (IData)(1U)))])
                    : (vlSelf->Stackmachine__DOT__stack
                       [(0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                                  - (IData)(1U)))] 
                       - (IData)(1U)));
            __Vdlyvset__Stackmachine__DOT__stack__v5 = 1U;
            __Vdlyvdim0__Stackmachine__DOT__stack__v5 
                = (0x7fU & ((IData)(vlSelf->Stackmachine__DOT__sp) 
                            - (IData)(1U)));
        } else {
            VL_WRITEF("SET %10#%1#\n",32,vlSelf->Stackmachine__DOT__stack
                      [vlSelf->Stackmachine__DOT__sp],
                      1,(1U & (IData)(vlSelf->in)));
            if ((0x7fU <= (IData)(vlSelf->Stackmachine__DOT__sp))) {
                __Vdly__err = 1U;
                __Vdly__out = 0xfU;
            }
            __Vdlyvval__Stackmachine__DOT__stack__v6 
                = (1U & (IData)(vlSelf->in));
            __Vdlyvset__Stackmachine__DOT__stack__v6 = 1U;
            __Vdlyvdim0__Stackmachine__DOT__stack__v6 
                = vlSelf->Stackmachine__DOT__sp;
            __Vdly__Stackmachine__DOT__sp = (0x7fU 
                                             & ((IData)(1U) 
                                                + (IData)(vlSelf->Stackmachine__DOT__sp)));
        }
    }
    vlSelf->out = __Vdly__out;
    vlSelf->err = __Vdly__err;
    vlSelf->Stackmachine__DOT__sp = __Vdly__Stackmachine__DOT__sp;
    if (__Vdlyvset__Stackmachine__DOT__stack__v0) {
        vlSelf->Stackmachine__DOT__stack[__Vdlyvdim0__Stackmachine__DOT__stack__v0] 
            = __Vdlyvval__Stackmachine__DOT__stack__v0;
    }
    if (__Vdlyvset__Stackmachine__DOT__stack__v1) {
        vlSelf->Stackmachine__DOT__stack[__Vdlyvdim0__Stackmachine__DOT__stack__v1] 
            = __Vdlyvval__Stackmachine__DOT__stack__v1;
    }
    if (__Vdlyvset__Stackmachine__DOT__stack__v2) {
        vlSelf->Stackmachine__DOT__stack[__Vdlyvdim0__Stackmachine__DOT__stack__v2] 
            = __Vdlyvval__Stackmachine__DOT__stack__v2;
    }
    if (__Vdlyvset__Stackmachine__DOT__stack__v3) {
        vlSelf->Stackmachine__DOT__stack[__Vdlyvdim0__Stackmachine__DOT__stack__v3] 
            = __Vdlyvval__Stackmachine__DOT__stack__v3;
        vlSelf->Stackmachine__DOT__stack[__Vdlyvdim0__Stackmachine__DOT__stack__v4] 
            = __Vdlyvval__Stackmachine__DOT__stack__v4;
    }
    if (__Vdlyvset__Stackmachine__DOT__stack__v5) {
        vlSelf->Stackmachine__DOT__stack[__Vdlyvdim0__Stackmachine__DOT__stack__v5] 
            = __Vdlyvval__Stackmachine__DOT__stack__v5;
    }
    if (__Vdlyvset__Stackmachine__DOT__stack__v6) {
        vlSelf->Stackmachine__DOT__stack[__Vdlyvdim0__Stackmachine__DOT__stack__v6] 
            = __Vdlyvval__Stackmachine__DOT__stack__v6;
    }
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
