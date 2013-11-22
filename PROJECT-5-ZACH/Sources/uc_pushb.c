//*******************************************************************************************************
// uc_pushb.c
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
//********************************************************************************************************


#include "gpio.h"
#include "support_common.h"
#include "uc_pushb.h"
#include "gpt.h"
#include "int.h"


static int_isr g_pb1_callback = 0;
static int_isr g_pb2_callback = 0;

//These will hold the address of the callback location

void uc_pushb_init(int_isr p_pb1_callback, int_isr p_pb2_callback)
{
	g_pb1_callback = p_pb1_callback;
	g_pb2_callback = p_pb2_callback;
	
	//void gpio_port_init(int p_port, int p_pin, int p_funct, int p_data_dir, int p_state)
	gpio_port_init(gpio_port_ta, uc_pb_1, gpio_funct_primary, gpio_data_dir_in, gpio_pin_state_high);
	gpio_port_init(gpio_port_ta, uc_pb_2, gpio_funct_primary, gpio_data_dir_in, gpio_pin_state_high);
	//Call gpt_disable()
	gpt_disable();
	//Call gpt_incap_config() to configure pin 0 for input capture on the falling edge
	gpt_incap_config(gpt_pin_0,gpt_incap_edge_rising);
	//Call gpt_incap_config() to configure pin 1 for input capture on the falling edge
	gpt_incap_config(gpt_pin_1,gpt_incap_edge_rising);
	//Call int_configure(gpt0_int_src, gpt0_int_level, gpt0_int_priority, uc_pushb1_isr) 
	int_config(gpt0_int_src, gpt0_int_level, gpt0_int_priority, uc_pushb1_isr);
	//Call int_configure(gpt1_int_src, gpt1_int_level, gpt1_int_priority, uc_pushb2_isr) 
	int_config(gpt1_int_src, gpt1_int_level, gpt1_int_priority, uc_pushb2_isr);
	//Call gpt_enable() to enable the GPT module
	gpt_enable();

}

void uc_pushb_debounce(gpio_pin_t p_pin)
{
	uint32 state = 0xFFFFFFFF;
	int signal=1;

	while(state != 0)
	{
		if((gpio_port_get_pin_state(gpio_port_ta, p_pin)) == gpio_pin_state_high)
			signal = 0;
		else
			signal = 1;
		
		state = (state << 1);
				state|= signal;
	}

}



__declspec(interrupt) void uc_pushb1_isr() 
{

	
	uc_pushb_debounce(uc_pb_1);
	
	gpt_clr_flag(gpt_pin_0);
	
	if (g_pb1_callback != 0)
	{
		g_pb1_callback();
	}

	return;
	
}

__declspec(interrupt) void uc_pushb2_isr() 
{
	uc_pushb_debounce(uc_pb_2);
	gpt_clr_flag(gpt_pin_1);
	if (g_pb2_callback != 0)
	{
		g_pb2_callback();
	}
}