//*******************************************************************************************************
// pwm.c
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

#include "pwm.h"
#include "gpio.h"

void pwm_channel_disable(int p_channel) {
        MCF_PWM_PWME &= ~(0x1 << p_channel);
}

void pwm_channel_enable(int p_channel) {
        MCF_PWM_PWME |= 0x1 << p_channel;
}

void pwm_channel_disable_all() {
        MCF_PWM_PWME &= 0;
}

void pwm_channel_init(int p_channel, int pwm_clock_src, int pwm_clock_prescale, int pwm_scale, int pwm_polarity, int pwm_period)
{
        pwm_channel_set_frequency(p_channel, pwm_clock_src, pwm_clock_prescale, pwm_scale);

        // Enable ports for PWM output
        switch (p_channel)
        {
        case 2:
                gpio_port_init(gpio_port_tc, gpio_pin_1, gpio_funct_tertiary,
                                                gpio_data_dir_x, gpio_pin_state_x);
        case 4:
                gpio_port_init(gpio_port_tc, gpio_pin_2, gpio_funct_tertiary,
                                gpio_data_dir_x, gpio_pin_state_x);
                break;
        case 5:
                gpio_port_init(gpio_port_ta, gpio_pin_2, gpio_funct_tertiary,
                                gpio_data_dir_x, gpio_pin_state_x);
                break;
        case 6:
                gpio_port_init(gpio_port_tc, gpio_pin_3, gpio_funct_tertiary,
                                gpio_data_dir_x, gpio_pin_state_x);
                break;
        }

        //set polarity of PWM signal
        if(pwm_polarity)
                MCF_PWM_PWMPOL |= (uint8) 0x01<<p_channel;
        else
                MCF_PWM_PWMPOL &= (uint8) ~(0x01<<p_channel);

        //set the signal period
        MCF_PWM_PWMPER(p_channel) = (uint8) pwm_period;

        //set signal left-aligned
        MCF_PWM_PWMCAE &= (uint8) ~(0x01<<p_channel);

}
void pwm_channel_set_duty(int p_channel, int pwm_duty){
        MCF_PWM_PWMDTY(p_channel) = (uint8) pwm_duty;
}

void pwm_channel_set_frequency(int p_channel, int pwm_clock_src, int pwm_psck, int pwm_scale){
        if(pwm_clock_src) MCF_PWM_PWMCLK |= (uint8) 1<<p_channel;
        else MCF_PWM_PWMCLK |= ~((uint8)1<<p_channel);
        //clkA
        if ((p_channel == 0)||(p_channel == 1)||(p_channel == 4)||(p_channel == 5)) {
                if(pwm_clock_src) MCF_PWM_PWMSCLA = (uint8) pwm_scale;
                MCF_PWM_PWMPRCLK &= ~((uint8) MCF_PWM_PWMPRCLK_PCKA(0x7));
                MCF_PWM_PWMPRCLK |= (uint8) MCF_PWM_PWMPRCLK_PCKA(pwm_psck);
        }
        //clkB
        else{
                if(pwm_clock_src) MCF_PWM_PWMSCLB = (uint8) pwm_scale;
                MCF_PWM_PWMPRCLK &= ~((uint8) MCF_PWM_PWMPRCLK_PCKB(0x7));
                MCF_PWM_PWMPRCLK |= (uint8) MCF_PWM_PWMPRCLK_PCKB(pwm_psck);
        }
}

void pwm_channel_start(int p_channel, int pwm_duty){
        pwm_channel_disable(p_channel);

        pwm_channel_set_duty(p_channel, pwm_duty);

        //reset and start PWM channel counter
        MCF_PWM_PWMCNT(p_channel) = 0x01;

        pwm_channel_enable(p_channel);
}


void pwm_set_prescale(int p_channel, int pwm_psck)
{
        switch(p_channel)
        {
                case 0:
                case 1:
                case 4:
                case 5:
                        MCF_PWM_PWMPRCLK &= ~((uint8) MCF_PWM_PWMPRCLK_PCKA(0x7));
                        MCF_PWM_PWMPRCLK |= (uint8) MCF_PWM_PWMPRCLK_PCKA(pwm_psck);
                        break;
                case 2:
                case 3:
                case 6:
                case 7:
                        MCF_PWM_PWMPRCLK &= ~((uint8) MCF_PWM_PWMPRCLK_PCKB(0x7));
                        MCF_PWM_PWMPRCLK |= (uint8) MCF_PWM_PWMPRCLK_PCKB(pwm_psck);
                        break;
        }
}

void pwm_set_scale(int p_channel, int pwm_scale)
{
        switch(p_channel)
        {
                case 0:
                case 1:
                case 4:
                case 5:
                        MCF_PWM_PWMSCLA = (uint8) pwm_scale;
                        break;
                case 2:
                case 3:
                case 6:
                case 7:
                        MCF_PWM_PWMSCLB = (uint8) pwm_scale;
                        break;
                }
}

void pwm_channel_set_period(int p_channel, int value)
{

         MCF_PWM_PWMPER(p_channel) = (uint8) value;
}

void pwm_channel_start_output(int p_channel) {
        MCF_PWM_PWME |= 0x1 << p_channel;
}