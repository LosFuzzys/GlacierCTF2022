// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "StackMachine.h"
#include "StackMachine__Syms.h"

//============================================================
// Constructors

StackMachine::StackMachine(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new StackMachine__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , in{vlSymsp->TOP.in}
    , err{vlSymsp->TOP.err}
    , out{vlSymsp->TOP.out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

StackMachine::StackMachine(const char* _vcname__)
    : StackMachine(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

StackMachine::~StackMachine() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void StackMachine___024root___eval_initial(StackMachine___024root* vlSelf);
void StackMachine___024root___eval_settle(StackMachine___024root* vlSelf);
void StackMachine___024root___eval(StackMachine___024root* vlSelf);
#ifdef VL_DEBUG
void StackMachine___024root___eval_debug_assertions(StackMachine___024root* vlSelf);
#endif  // VL_DEBUG
void StackMachine___024root___final(StackMachine___024root* vlSelf);

static void _eval_initial_loop(StackMachine__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    StackMachine___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        StackMachine___024root___eval_settle(&(vlSymsp->TOP));
        StackMachine___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void StackMachine::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate StackMachine::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    StackMachine___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        StackMachine___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

const char* StackMachine::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void StackMachine::final() {
    StackMachine___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* StackMachine::hierName() const { return vlSymsp->name(); }
const char* StackMachine::modelName() const { return "StackMachine"; }
unsigned StackMachine::threads() const { return 1; }
