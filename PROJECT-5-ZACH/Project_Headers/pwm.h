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

#ifndef PWM_H_
#define PWM_H_
#include "common.h"

typedef enum
{
	pwm_pin_0     = 0x1,
	pwm_pin_1     = 0x2,
	pwm_pin_2     = 0x4,
	pwm_pin_3     = 0x8,
	pwm_pin_4     = 0x10,
	pwm_pin_5     = 0x20,
	pwm_pin_6     = 0x40,
	pwm_pin_7     = 0x80,
	
	pwm_pin_red   = 0x10,
	pwm_pin_green = 0x20,
	pwm_pin_blue  = 0x40

}pwm_pin_t;

typedef enum
{
	pwm_pol_high = 1,
	pwm_pol_low  = 0
}pwm_pol_t;

typedef enum
{
	pwm_clk_a = 0,
	pwm_clk_b = 0,
	pwm_clk_sa = 1,
	pwm_clk_sb = 1
}pwm_clk_t;


void pwm_channel_disable(int p_channel);
void pwm_channel_enable(int p_channel);
void pwm_channel_disable_all();
void pwm_channel_init(int p_channel);
void pwm_channel_set_duty(int p_channel, int p_duty);
void pwm_channel_set_frequency();
void pwm_channel_start_output(int p_channel);
void pwm_set_scale(int p_channel, int p_scale);
void pwm_channel_set_period(int p_channel, int value);
void pwm_set_prescale(int p_channel, int p_prescale);

#endif /* PWM_H_ */
