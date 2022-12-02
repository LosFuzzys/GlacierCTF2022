// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_STACKMACHINE__SYMS_H_
#define VERILATED_STACKMACHINE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "StackMachine.h"

// INCLUDE MODULE CLASSES
#include "StackMachine___024root.h"

// SYMS CLASS (contains all model state)
class StackMachine__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    StackMachine* const __Vm_modelp;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    StackMachine___024root         TOP;

    // CONSTRUCTORS
    StackMachine__Syms(VerilatedContext* contextp, const char* namep, StackMachine* modelp);
    ~StackMachine__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
