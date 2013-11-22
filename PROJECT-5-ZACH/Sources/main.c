/*
 * main implementation: use this sample to create your own application
 *
 */


#include "song.h"
#include "pwm.h"
#include "oct_spkr.h"
#include "note.h"
#include "dtim.h"
#include "user.h"

char DATA[1024];
int count = 0;
int xfer_end = 0;
int LENGTH = 0;
song_t CURRENT_SONG;
mode_t MODE;

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

static void pb1_callback()
{
	
	
}

static void pb2_callback()
{
	
}

static void hw_init()
{
	int_inhibit_all();
	
	uc_led_init();
	dtim0_init();
	speaker_init();
	uart_channel_init(1, 300, no_parity, eight_bits, stop_bits_1, 7, 7, uart_callback);
	pwm_channel_set_duty(2, 0x5F);
	int_uninhibit_all();
	uart_channel_enable(uart_1);
	MODE = idle_mode;

}

static void idle()
{
	while(MODE == idle_mode)
	{
		uc_led_init();
		uc_led_all_off();
	}
}

static void play()
{
	while(MODE == play_mode)
	{
		
		
	}
}

static void transfer()
{
	while(MODE == transfer_mode)
	{
		
		
	}
}

static void run()
{
	
	uc_led_all_off();
	pwm_channel_disable(2);
	
	//pwm_channel_set_period(2, 250);
	//pwm_set_prescale(2, 2);
	//pwm_set_scale(2, 81);
	
	
	
	
	while(1)
	{
		if( xfer_end == 1)
		{
			//uc_led_on(uc_led_2);
			CURRENT_SONG = generate_song();
			for(int i = 0 ; i < CURRENT_SONG.num_notes-1 ; i++)
			{
				
				speaker_play_note(CURRENT_SONG.notes[i]);
				if(CURRENT_SONG.notes[i].pitch == pitch_mute)
				{
					
				}
				else 
				{
					pwm_channel_enable(2);
				}
				dtim0_busy_delay_ms(25*CURRENT_SONG.notes[i].duration);
				pwm_channel_disable(2);
				dtim0_busy_delay_ms(25*2);
				
			}
			//pwm_channel_enable(2);
			//speaker_play_note(generate_note(pitch_b3,duration_32th));
			//pwm_channel_enable(2);
			
			xfer_end = 0;
			count = 0;
			
		}
		else
		{

			
			uc_led_on(uc_led_1);
			pwm_channel_disable(2);
		}
	}
	/*
	
	while(1)
	{
		switch(MODE)
		{
		case idle_mode:
			idle();
			break;
		case play_mode:
			play();
			break;
		case transfer_mode:
			transfer();
			break;
		}
	}*/
	
}


__declspec(noreturn) int main()
{
	hw_init();
	run();
}