//**********************************************************************************************************************************
// FILE: adc.c
//
// DESCRIPTION
// See comments in adc.h.
// 
// AUTHORS
// Kevin R. Burger (burgerk@asu.edu)
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
// http://www.devlang.com
//**********************************************************************************************************************************
#include "adc.h"
#include "gpio.h"

//==================================================================================================================================
// Private Preprocessor Macros
//==================================================================================================================================
 
// Macro to access the ADLST1 or ADLST2 register for configuring a channel to be sampled in sample slot sslot.
#define ADC_ADLST(sslot) (*(vuint16*)(0x40190006 + ((sslot) << 1)))

//==================================================================================================================================
// Function Definitions
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adc_chan_init()
//----------------------------------------------------------------------------------------------------------------------------------
void adc_chan_init(adc_chan p_chan, adc_slot p_slot)
{
        // Configure pin p_chan of GPIO port AN for the primary (ADC) function.
    gpio_port_init(gpio_port_an, (gpio_pin_t)p_chan, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
    
    // Configure channel p_chan to be sampled in sample slot p_slot.
    ADC_ADLST(p_slot >> 2) |= (uint16)(p_chan << (p_slot << 2));
    
    // Enable sample slots 0, 1, 2, ..., p_slot and disable sample slots p_slot+1, p_slot+2, ...
    MCF_ADC_ADSDIS = (uint16)(0x00FE << p_slot);

    // Start scanning now in loop sequential mode.
    adc_start_scanning();    
}

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adc_get_result()
//----------------------------------------------------------------------------------------------------------------------------------
int adc_get_result(adc_slot p_slot)
{
    return MCF_ADC_ADRSLT(p_slot) >> 3;
}

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adc_init()
//----------------------------------------------------------------------------------------------------------------------------------
void adc_init(int p_clock_div)
{
    // Power-up ADCA and ADCB by clearing POWER[PD0] and POWER[PD1]. See the note in IMRM Table 30-18 about waiting for PUDELAY ADC
    // clock clock cyles before initiating a scan to allow power levels time to stabilize. At reset, PUDELAY is 13. In theory, we
    // could try speeding up the time it takes for the ADC to power up by decreasing this delay, but for this application, any
    // change would be inconsequential. Therefore, we will leave it alone. We can detect when ADCA and ADCB are powered up by polling
    // POWER[PSTS0] and POWER[PST1] which will change from 1 to 0 when ADCA and ADCB are fully powered up.
    MCF_ADC_POWER = 0x00D4;
    while (MCF_ADC_POWER & 0x0C00) {}

        // Configure ADC for loop sequential mode with EOS interrupts disabled.
        MCF_ADC_CTRL1  = 0x0002;
        
        // Establish the ADC conversion clock frequency.
    MCF_ADC_CTRL2  = (uint16)p_clock_div;
    
    // Clear any pending interrupts. Probably not necessary, but I'm paranoid.
    MCF_ADC_ADSTAT = 0x1800;
        
    // All sample slots are initialized to channel 0. These are changed later when adc_chan_init() is called.
    MCF_ADC_ADLST1 = 0x0000;
    MCF_ADC_ADLST2 = 0x0000;

        // All samples slots are disabled. These are changed later when adc_chan_init() is called.
        MCF_ADC_ADSDIS = 0x00FF;
}

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adca_start_scanning()
//----------------------------------------------------------------------------------------------------------------------------------
void adc_start_scanning()
{
    MCF_ADC_CTRL1 |= 1 << 13;
}

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adca_stop_scanning()
//----------------------------------------------------------------------------------------------------------------------------------
void adc_stop_scanning()
{
    MCF_ADC_CTRL1 |= 1 << 14;
}