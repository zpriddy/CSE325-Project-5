//**********************************************************************************************************************************
// FILE: adc.h
//
// DECRIPTION
// Functions for using the ADC module.
// Controls the A/D Converter (ADC) module.
// 
// The scan sequence is determined by defining eight sample slots in ADLST1/ADLST2. If a sequential scan is
// being performed, the scan order is SAMPLE0, SAMPLE1, ..., SAMPLE7. If a parallel scan is being performed,
// ADCA scans in order SAMPLE0, SAMPLE1, SAMPLE2, SAMPLE3 and ADCB scans in order SAMPLE4, SAMPLE5, SAMPLE6,
// SAMPLE7. Sample slots may be disabled by programming ADSDIS (Scan Disable) register.
// 
// The ADC can be configured to perform a single scan and then halt, to perform a scan when triggered, or to
// perform the scan repeatedly until manually stopped.
// 
// Optional interrupts can be generated at the end of scan sequence. Interrupts may signal that a scan has
// ended, that a sample was out of a programmed range (determined by the high and low limit registers), or at
// several different zero crossing conditions.
// 
// The input mode for a sample is determined by the CHNCFG (Channel Configuration) field of CTRL1. The ADC
// modules supports two sample input modes:
// 
// 1. Single-Ended (CHNCFG = 0). In this mode, the input mux selects one of the analog inputs and directs it to
//    the + terminal of the ADC core. The - terminal is connected to VREFL. The ADC measures the voltage of the
//    selected analog input and compares it against (V(REFH) - V(VREFL)).
//    
// 2. Differential Mode (CHNCFG = 1). We will not be using this mode.
// 
// Single-Ended Samples (see Section 30.5.2.1 of the IMRM)
// The digital result is proportional to the ratio of the analog input voltage to the reference voltage using
// the formula,
// 
// 
//                                             V(IN) - V(REFL)
//     Single-Ended Digital Result = round ( ------------------ x 2^12-1 ) x 8
//                                            V(REFH) - V(REFL)
//                                         
// where,
//  
//      V(IN) = Voltage at the input pin
//      V(REFH) and V(REFL) = Voltage at the external reference pins on the controller; pins 71 and 71, respec-
//      tively. On the TWR board, V(REFH) is connected VDDA which is connected to MCU_3V3; V(REFL) is connected
//      to VSSA which is connected to ground.
//  
// Using this formula we have,
// 
// V(IN) = V(REFH); Singled-Ended Digital Result = (2^12 - 1)(2^3) = 2^15 - 8 = 32768 - 8 = 32760.
// V(IN) = V(REFL); Singled-Ended Digital Result = 0.
// 
// Single-Ended Digital Result is a linear function of V(IN) compared to V(REFL).
// 
// See Figure 30-23 in the IMRM.
// The raw output from the ADC is sent to an adder for offset correction. The adder subtracts ADOFSn from the
// sample and stores the result in ADRSLTn.
// 
// Sequential Sampling (see Section 30.5.4 in the IMRM).
// All scan modes use the eight sample slots in ADLST1 and ADLST2. These slots define which single-ended input/
// differential input pair is/are measured at each step in a scan. The SDIS register can disable unneeded slots.
// A single-ended measurement is made is a sample slot refers to an analog input which is not configured as a
// member of a differential pair by CHNCFG in CTRL1.
// 
// Scan modes are sequential or parallel as defined by by the SMODE bit in CTRL1. Scanning is initiated when the
// START0 bit is written as 1. A scan ends when the first disable sample slot is encountered in SDIS. Completion
// of a scan triggers the EOSI0 interrupt if enabled by the EOSIE0 bit. Scanning stops when the STOP0 bit is
// set.
// 
// Scan Sequencing (see Section 30.5.5. in the IMRM).
// Scan modes may be Once, Triggered, or Loop. During a Once scan, a single sequential scan is executed (see
// Section 30.5.4 for a discussion of how the samples are ordered by programming the ADLST1 and ADLST2 regs).
// A Once scan differs from a Triggered scan in that a Once scan must be rearmed after each scan. Rearming
// can occur at any time, even during the scan, by writing to CTRL1.
// 
// Triggered scan modes are identical to Once, except rearming is not performed.
// 
// A Loop scan automatically restarts a scan as soon as the previous scan completes. In Loop Sequential mode
// up to eight samples are captured in the Loop scan.
// 
// Scan Configuration and Control (see Section 30.5.6 in the IMRM).
// The operation of the ADC is controlled by CTRL1 and CTRL2. See Table 30-21 on p. 30-31 of the IMRM.
// 
// Interrupt Sources (see Section 30.5.7 in the IMRM).
// An ADCA conversion complete interrupt (/ADC_CC0_INT) is generated at the end of a scan in ADCA when EOSI0
// goes to 0 and if EOSIE0 is also 0.
// 
// An ADCB conversion complete interrupt (/ADC_CC1_INT) is generated at the end of a scan in ADCB when EOSI1
// goes to 0 and if EOSIE1 is also 0.
// 
// Power Management Details (see Section 30.5.8.2 in the IMRM).
// The ADC voltage reference and converters are powered down (PDn = 1 in the POWER register) at reset. A delay
// of PUDELAY (Power Up Delay) ADC clock cycles (that's ADC clock cycles, not controller clock cycles) when PD0
// or PD1 are cleared to power-up ADCA or ADCB, respectively.
// 
// Any attempt to use a converter when powered down will generate invalid results.
// 
// When starting the ADC in normal power mode, first set PUDELAY to the large power-up value. Next, clear the 
// PD0 and/or PD1 bits to power-up the ADCA and/or ADCB converters. Poll the status bits (PSTSn in POWER) until
// all required converts (ADCA and/or ADCB) are powered up. Following this polling, it is safe to begin scan
// operations.
// 
// ADC Stop Mode of Operation (see Section 30.5.8.3 in the IMRM).
// Any conversion sequence in progress can be stopped by setting STOP0 (for ADCA) or STOP1 (for ADCB). Any
// writes to START0 or START1 are ignored until STOP0 or STOP1 are cleared.
// 
// Clock Operation (see Section 30.5.9.2 in the IMRM).
// The conversion clock rate is f_bus / (2 * (DIV+1)). The DIV field in CTRL2 must be programmed so the con-
// version clock frequency is in [0.1, 5.0] MHz. For example, if f_bus is 40 MHz and DIV is 0, then the con-
// version clock frequency would be 20 MHz, which is too fast. To achieve a conversion clock frequency of no
// more than 5.0 MHz when f_bus is 40 MHz, DIV would have to be,
// 
//       f_bus
//     ---------- <= 5.0 MHz
//     2(DIV + 1) 
//     
// Solving for DIV,
// 
//              f_bus
//     DIV >= ---------- - 1
//            2 * 5 MHz
//         
//             40 MHz
//     DIV >= --------- - 1
//            2 * 5 MHz
//         
//     DIV >= 3
//     
// If f_bus is 40 MHz a system clock cycle would be 12.5 ns. A conversion clock cycle (at 5 MHz) would be
// 200 ns, which is 8 times the length of a system clock cycle.
//
// AUTHORS
// Kevin R. Burger (burgerk@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe, AZ 85287-8809
// Web: http://www.devlang.com
//**********************************************************************************************************************************
#ifndef ADC_H
#define ADC_H

#include "support_common.h"

//==================================================================================================================================
// Public Type Definitions
//==================================================================================================================================

// An enumerated type to use when specifying an ADC channel.
typedef enum {
    adc_chan_0 = 0,
    adc_chan_1 = 1,
    adc_chan_2 = 2,
    adc_chan_3 = 3,
    adc_chan_4 = 4,
    adc_chan_5 = 5,
    adc_chan_6 = 6,
    adc_chan_7 = 7
} adc_chan;

// An enumerated type to use when specifying an ADC sample slot.
typedef enum {
	adc_slot_0 = 0,
	adc_slot_1 = 1,
	adc_slot_2 = 2,
	adc_slot_3 = 3,
	adc_slot_4 = 4,
	adc_slot_5 = 5,
	adc_slot_6 = 6,
	adc_slot_7 = 7
} adc_slot;
	
//==================================================================================================================================
// Public Function Declarations
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adca_chan_init()
//
// DESCRIPTION
// Initializes channel p_chan so it will be sampled in sample slot p_slot during a scan. To obtain the sample result call adc_get_
// result() with the sample slot as the input argument.
//
// Due to the way the channels are sampled and the way this code is written, for the first call to this function, p_slot should be
// adc_slot_0. In subsequent calls, p_slot should be adc_slot_1, then adc_slot_2, then adc_slot_3, and so on. For example, to con-
// figure channels 1 and 2 to be sampled in these sample slots,
//
// ADC Channel  Sample Slot
// -----------  -----------
//      1            0   
//      2            1
//      1            2
//      1            3
//      2            4
// 
// Call this function five times,
//
// adc_chan_init(adc_chan_1, adc_slot_0);  -- Channel 1 sampled in sample slot 0; sample slots 1, 2, 3, ... are disabled
// adc_chan_init(adc_chan_2, adc_slot_1);  -- Channel 2 sampled in sample slot 1; sample slots 2, 3, ... are disabled
// adc_chan_init(adc_chan_1, adc_slot_2);  -- Channel 1 sampled in sample slot 2; sample slots 3, ... are disabled
// adc_chan_init(adc_chan_1, adc_slot_3);  -- Channel 1 sampled in sample slot 3; sample slots 4, ... are disabled
// adc_chan_init(adc_chan_2, adc_slot_4);  -- Channel 2 sampled in sample slot 4; sample slots 5, ... are disabled
//----------------------------------------------------------------------------------------------------------------------------------
void adc_chan_init(adc_chan p_chan, adc_slot p_slot);

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adc_get_result()
//
// DESCRIPTION
// Returns the sampled value for sample slot p_slot.
// 
// NOTE
// The value in ADRSLTn is shifted left three positions, i.e., it is essentially multiplied by 8. We divide the value by 8 before
// returning it. Therefore, the return value will be in [0, 4095].
//----------------------------------------------------------------------------------------------------------------------------------
int adc_get_result(adc_slot p_slot);

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adc_init()
//
// DESCRIPTION:
// Initializes the ADC module to configure all channels for single-ended mode. The p_clock_div parameter is a 5-bit integer in the
// range [0, 31] and is used to form the ADC clock by dividing the internal peripheral bus clock by 2(p_clock_div+1). IMRM Section
// 30.5.9.2 states that the clock divider shall be chosen so the ADC conversion clock frequency is between 100 KHz and 5 MHz. If the
// system clock frequency is 80 MHz, then p_clock_div must be in [3, 31]
//
// p_clock_div  ADC CLock Frequency
// -----------  -------------------
//       3            5.00 MHz
//       4            4.00 MHz
//       5            3.33 MHz
//     ...             ...
//      30           645.2 KHz
//      31           625.0 KHz
//
// The ADC is configured for loop sequential mode with with interrupt requests disabled. Sampling of individual channels is enabled
// by calling adc_chan_init() with the channel number and the sample slot in which that sample will be sampled.
//----------------------------------------------------------------------------------------------------------------------------------
void adc_init(int p_clock_div);

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adc_start_scanning()
//
// DESCRIPTION
// Configures the ADC module to start scanning the channels listed in the ADLST1 and ADLST2 registers. Will continue scanning in
// loop sequential mode until adc_stop_scanning() is called. To obtain the sampled value for a sample slot, call adc_get_result()
// and pass the sample slot as the input argument.
//----------------------------------------------------------------------------------------------------------------------------------
void adc_start_scanning();

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: adca_stop_scanning()
//
// DESCRIPTION
// Stops scanning. Scanning can be restarted by calling adc_start_scanning().
//----------------------------------------------------------------------------------------------------------------------------------
void adc_stop_scanning();

#endif
