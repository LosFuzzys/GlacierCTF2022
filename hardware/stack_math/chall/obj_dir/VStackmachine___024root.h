// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VStackmachine.h for the primary calling header

#ifndef VERILATED_VSTACKMACHINE___024ROOT_H_
#define VERILATED_VSTACKMACHINE___024ROOT_H_  // guard

#include "verilated.h"

class VStackmachine__Syms;

class VStackmachine___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(in,3,0);
    VL_OUT8(err,0,0);
    CData/*6:0*/ Stackmachine__DOT__sp;
    CData/*0:0*/ __Vclklast__TOP__clk;
    VL_OUT(out,31,0);
    IData/*31:0*/ Stackmachine__DOT__unnamedblk1__DOT__i;
    VlUnpacked<IData/*31:0*/, 128> Stackmachine__DOT__stack;

    // INTERNAL VARIABLES
    VStackmachine__Syms* const vlSymsp;

    // CONSTRUCTORS
    VStackmachine___024root(VStackmachine__Syms* symsp, const char* name);
    ~VStackmachine___024root();
    VL_UNCOPYABLE(VStackmachine___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
