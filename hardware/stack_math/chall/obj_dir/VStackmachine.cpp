// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VStackmachine.h"
#include "VStackmachine__Syms.h"

//============================================================
// Constructors

VStackmachine::VStackmachine(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VStackmachine__Syms(contextp(), _vcname__, this)}
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

VStackmachine::VStackmachine(const char* _vcname__)
    : VStackmachine(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VStackmachine::~VStackmachine() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void VStackmachine___024root___eval_initial(VStackmachine___024root* vlSelf);
void VStackmachine___024root___eval_settle(VStackmachine___024root* vlSelf);
void VStackmachine___024root___eval(VStackmachine___024root* vlSelf);
#ifdef VL_DEBUG
void VStackmachine___024root___eval_debug_assertions(VStackmachine___024root* vlSelf);
#endif  // VL_DEBUG
void VStackmachine___024root___final(VStackmachine___024root* vlSelf);

static void _eval_initial_loop(VStackmachine__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    VStackmachine___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        VStackmachine___024root___eval_settle(&(vlSymsp->TOP));
        VStackmachine___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void VStackmachine::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VStackmachine::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VStackmachine___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        VStackmachine___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

const char* VStackmachine::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void VStackmachine::final() {
    VStackmachine___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VStackmachine::hierName() const { return vlSymsp->name(); }
const char* VStackmachine::modelName() const { return "VStackmachine"; }
unsigned VStackmachine::threads() const { return 1; }
