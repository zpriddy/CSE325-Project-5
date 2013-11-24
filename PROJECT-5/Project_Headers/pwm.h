//*******************************************************************************************************
// pwm.h
//
// DESCRIPTION:
//
// AUTHORS:
//  Abdulla Al Braiki (ayalbrai@asu.edu)
//  Zachary Priddy (zpriddy@asu.edu)
//
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
//
// Date: Oct 24, 2013
//
//********************************************************************************************************
//********************************************************************************************************
#ifndef PWM_H_
#define PWM_H_
/*
int PWM_CLK_SRC_AB = 0x00;
int PWM_CLK_SRC_SASB = 0x01;
*/
//--------------------------------------------------------------------------------------------------------------
// FUNCTION: pwm_channel_enable
//
// DESCRIPTION
// Enable PWM channel n for work
//--------------------------------------------------------------------------------------------------------------
void pwm_channel_enable(int n_channel);

//--------------------------------------------------------------------------------------------------------------
// FUNCTION: pwm_channel_disable
//
// DESCRIPTION
// Disable PWM channel n
//--------------------------------------------------------------------------------------------------------------
void pwm_channel_disable(int n_channel);

//--------------------------------------------------------------------------------------------------------------
// FUNCTION: pwm_channel_disable_all
//
// DESCRIPTION
// Disable PWM channel n
//--------------------------------------------------------------------------------------------------------------
void pwm_channel_disable_all();

//--------------------------------------------------------------------------------------------------------------
// FUNCTION: pwm_channel_init
//
// DESCRIPTION
// Function to initialize channel n
// set clock A or B prescale value (PCKA or PCKB), clock SA or SB scale value (SCALEA or SCALEB), signal polarity
// value for PWMPERn register and configure the channel for left-aligned mode
//--------------------------------------------------------------------------------------------------------------
void pwm_channel_init(int n_channel, int pwm_clock_src, int pwm_clock_prescale,
                                                int pwm_scale, int pwm_polarity, int pwm_period);

//--------------------------------------------------------------------------------------------------------------
// FUNCTION: pwm_channel_set_duty
//
// DESCRIPTION
// Set the duty cycle of channel n
//--------------------------------------------------------------------------------------------------------------
void pwm_channel_set_duty(int n_channel, int pwm_duty);

//--------------------------------------------------------------------------------------------------------------
// FUNCTION: pwm_channel_set_frequency
//
// DESCRIPTION
// Set the frequency cycle of channel n
//--------------------------------------------------------------------------------------------------------------
void pwm_channel_set_frequency(int n_channel, int pwm_clock_src, int pwm_psck, int pwm_scale);

//--------------------------------------------------------------------------------------------------------------
// FUNCTION: pwm_channel_start
//
// DESCRIPTION
// Start the signal output of the channel
//--------------------------------------------------------------------------------------------------------------
void pwm_channel_start(int n_channel, int pwm_duty);

void pwm_set_prescale(int p_channel, int pwm_psck);
void pwm_set_scale(int p_channel, int pwm_scale);
void pwm_channel_start_output(int p_channel);
void pwm_channel_set_period(int p_channel, int value);

#endif /* PWM_H_ */