//**********************************************************************************************************************************
// FILE: uc_pot.h
//
// DECRIPTION
// Controls the potentiometer on the TWR board.
// 
// The pot input is connected to pin 69 (AN3) on the MCF52259. This pin belongs to port AN (pin AN3) of the GPIO module, so to
// initialize the pot for input, we must configure port AN pin 3's function to be the primary function (ADC).
//     
// If the ADC is configured for 5 MHz sampling, then an ADC clock cycle would be 200 ns. It takes 8 ADC clock cycles to perform a
// sequential once mode sample, thus it takes 1.6 us to read the state of the pot.
//
// AUTHORS
// Kevin R. Burger (burgerk@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe, AZ 85287-8809
// Web: http://www.devlang.com
//**********************************************************************************************************************************
#ifndef UC_POT_H
#define UC_POT_H

#include "common.h"

//==================================================================================================================================
// Public Function Declarations
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: uc_pot_get_setting()
//
// DESCRIPTION
// Returns the setting of the pot as a value in [0, 4095].
//----------------------------------------------------------------------------------------------------------------------------------
int uc_pot_get_setting();

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: uc_pot_init()
//
// DESCRIPTION
// The setting of the potentiometer is determined by sampling the voltage signal on MCF52259 pin 69 using ADCA. If p_callback is
// non-null, then the ADC will be configured to generate end-of-scan interrupts and the user's callback function p_callback will
// be called. If p_callback is null, then end-of-scan interrupts are disabled and the user should call uc_pot_get_setting() to read
// the state of the pot.
//----------------------------------------------------------------------------------------------------------------------------------
void uc_pot_init();

#endif
