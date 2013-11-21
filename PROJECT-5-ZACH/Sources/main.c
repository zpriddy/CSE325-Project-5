/*
 * main implementation: use this sample to create your own application
 *
 */


#include "common.h"

char DATA[1024];
int count = 0;
int xfer_end = 0;
int LENGTH = 0;

int flash = 0;
static void uart_callback()
{
	if(flash == 0 )
	{
		uc_led_all_on();
		flash = 1;
	}
	else
	{
		uc_led_all_off();
		flash = 0 ;
	}
	DATA[count]=uart_channel_getchar(uart_1);
	
   if(count == 1)
		{
			LENGTH = (DATA[count] << 8);
			//LENGTH = 10;
		}
		if(count == 2)
		{
			LENGTH |= (DATA[count]);
		}
		if(count >= LENGTH - 3 && count >= 3)
		{
			xfer_end = 1;
			uc_led_all_off();
		}

	
	count ++;
}

static void hw_init()
{
	int_inhibit_all();
	
	uc_led_init();
	uart_channel_init(1, 300, no_parity, eight_bits, stop_bits_1, 7, 7, uart_callback);
	
	int_uninhibit_all();
	uart_channel_enable(uart_1);

}

static void run()
{
	while(1)
	{
		if( xfer_end == 1)
		{
			uc_led_on(uc_led_2);
		}
		else
		{
			uc_led_on(uc_led_1);
		}
	}
	
}


__declspec(noreturn) int main()
{
	hw_init();
	run();
}