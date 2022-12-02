// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSTACKMACHINE__SYMS_H_
#define VERILATED_VSTACKMACHINE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VStackmachine.h"

// INCLUDE MODULE CLASSES
#include "VStackmachine___024root.h"

// SYMS CLASS (contains all model state)
class VStackmachine__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VStackmachine* const __Vm_modelp;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VStackmachine___024root        TOP;

    // CONSTRUCTORS
    VStackmachine__Syms(VerilatedContext* contextp, const char* namep, VStackmachine* modelp);
    ~VStackmachine__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
