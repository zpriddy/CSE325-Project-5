//*******************************************************************************************************
// uc_led.c
//
// DESCRIPTION:
//
// AUTHORS:
// 	Abdulla Al Braiki (ayalbrai@asu.edu)
//	Zachary Priddy (zpriddy@asu.edu)
//
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
// 
//********************************************************************************************************

#include "common.h"



//Calls uc_led_off() four times to turn all LED's off.
void uc_led_all_off()
{
    uc_led_off(uc_led_1);
    uc_led_off(uc_led_2);
    uc_led_off(uc_led_3);
    uc_led_off(uc_led_4);
}

//Calls uc_led_on() four times to turn all LED's on.
void uc_led_all_on()
{
    uc_led_on(uc_led_1);
    uc_led_on(uc_led_2);
    uc_led_on(uc_led_3);
    uc_led_on(uc_led_4);
}

//Calls gpio_port_init() four times to initialize the pins of port TC that each LED is connected to.
void uc_led_init()
{
    gpio_port_init(gpio_port_tc, uc_led_1, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
    gpio_port_init(gpio_port_tc, uc_led_2, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
    gpio_port_init(gpio_port_tc, uc_led_3, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
    gpio_port_init(gpio_port_tc, uc_led_4, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
}

//Calls gpio_port_set_pin_state() to set the state of the pin in port TC for LED p_led to turn the LED off.
void uc_led_off(gpio_pin_t p_led)
{
	gpio_port_set_pin_state(gpio_port_tc,p_led,gpio_pin_state_low);
    //gpio_port_set_pin_state(p_port, p_pin, p_state);
}

//Calls gpio_port_set_pin_state() to set the state of the pin in port TC for LED p_led to turn the LED on.
void uc_led_on(gpio_pin_t p_led)
{
	gpio_port_set_pin_state(gpio_port_tc,p_led,gpio_pin_state_high);
    //gpio_port_set_pin_state(p_port, p_pin, p_state);
}

//Turn on LED by LED Number ie. 1 2 3 or 4
void uc_led_on_num(gpio_pin_t p_led)
{
	p_led--;
	gpio_port_set_pin_state(gpio_port_tc,p_led,gpio_pin_state_high);
}

//Calls gpio_port_get_pin_state() to determine if LED p_led is on or off. It it is on, turn it off and if it is off, turn it on.
void uc_led_toggle(gpio_pin_t p_led)
{
	if(gpio_port_get_pin_state(gpio_port_tc,p_led)) //Check if the LED is on
	{
		//If its on, then turn it off
		gpio_port_set_pin_state(gpio_port_tc,p_led,gpio_pin_state_low);
	}
	else
	{
		//If its off then turn it on
		gpio_port_set_pin_state(gpio_port_tc,p_led,gpio_pin_state_high);
	}
}

void uc_led_dis_bin(int b_num)
{
	uc_led_all_off();
	if (b_num & 0x01) uc_led_on(uc_led_1);
	if (b_num & 0x02) uc_led_on(uc_led_2);
	if (b_num & 0x04) uc_led_on(uc_led_3);
	if (b_num & 0x08) uc_led_on(uc_led_4);
}
void uc_led_dis_bin_rev(int b_num)
{
	uc_led_all_off();
	if (b_num & 0x01) uc_led_on(uc_led_4);
	if (b_num & 0x02) uc_led_on(uc_led_3);
	if (b_num & 0x04) uc_led_on(uc_led_2);
	if (b_num & 0x08) uc_led_on(uc_led_1);
}
