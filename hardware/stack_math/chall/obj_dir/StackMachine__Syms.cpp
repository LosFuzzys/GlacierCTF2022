// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "StackMachine__Syms.h"
#include "StackMachine.h"
#include "StackMachine___024root.h"

// FUNCTIONS
StackMachine__Syms::~StackMachine__Syms()
{
}

StackMachine__Syms::StackMachine__Syms(VerilatedContext* contextp, const char* namep, StackMachine* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
}
