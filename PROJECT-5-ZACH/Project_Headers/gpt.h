//**********************************************************************************************************************************
// FILE: gpt.h
//
// DECRIPTION
// GPT module related functions.
//
// AUTHORS
// Kevin R. Burger (burgerk@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe, AZ 85287-8809
// Web: http://www.devlang.com
//**********************************************************************************************************************************
#ifndef GPT_H
#define GPT_H

//==================================================================================================================================
// Global Type Definitions
//==================================================================================================================================

typedef enum {
    gpt_pin_0 = 0,  // The pin connected to GPT channel 0
    gpt_pin_1 = 1,  // The pin connected to GPT channel 1
    gpt_pin_2 = 2,  // The pin connected to GPT channel 2
    gpt_pin_3 = 3   // The pin connected to GPT channel 3
} gpt_pin;

typedef enum {
    gpt_incap_edge_disabled = 0,  // Not performing input capture on a pin
    gpt_incap_edge_rising   = 1,  // Capture a rising edge on a pin
    gpt_incap_edge_falling  = 2,  // Capture a falling edge on a pin
    gpt_incap_edge_both     = 3   // Capture both falling and rising edges on a pin
} gpt_incap_edge;
//==================================================================================================================================
// Public Function Declarations
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: __declspec(register_abi) void gpt_clr_flag(gpt_pin p_pin)
//
// DESCRIPTION
// Clears the interrupt request flag for pin p_pin.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(register_abi) void gpt_clr_flag(gpt_pin p_pin);

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: __declspec(register_abi) void gpt_disable()
//
// DESCRIPTION
// Disables the GPT module.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(register_abi) void gpt_disable();

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: __declspec(register_abi) void gpt_enable()
//
// DESCRIPTION
// Enables the GPT module.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(register_abi) void gpt_enable();

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: __declspec(register_abi) void gpt_incap_config(gpt_pin p_pin, gpt_incap_edge p_incap_edge)
//
// DESCRIPTION
// Configures pin p_pin of GPT for the input capture mode, triggering an interrupt on the edge or edges specified by p_incap_edge.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(register_abi) void gpt_incap_config(gpt_pin p_pin, gpt_incap_edge p_incap_edge);
__declspec(register_abi) void gpt_init();

#endif
