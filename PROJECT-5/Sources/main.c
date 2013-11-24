//*******************************************************************************************************
// main.c
//
// Date: 2013-11-14 10:49:08
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
//*******************************************************************************************************

#include "song.h"
#include "pwm.h"
#include "oct_spkr.h"
#include "note.h"
#include "dtim.h"
#include "user.h"
#include "uc_pushb.h"
#include "pit.h"
#include "uc_pot.h"
#include "adc.h"

char DATA[1024];
int count = 0;
int xfer_end = 0;
int LENGTH = 0;

song_t CURRENT_SONG;
mode_t MODE;
play_t PLAYBACK;
transfer_mode_t TRANSFER_STATUS;


static void uart_callback()
{
	if(MODE == transfer_mode)
	{
		TRANSFER_STATUS = transfer_in_progress;
		
		uc_led_toggle(uc_led_1);
		
		DATA[count]=uart_channel_getchar(uart_1);
		
	   if(count == 1)
		{
			LENGTH = (DATA[count] << 8);

		}
		if(count == 2)
		{
			LENGTH |= (DATA[count]);
		}
		if(count >= LENGTH - 3 && count >= 3)
		{
			TRANSFER_STATUS = transfer_idle;
			CURRENT_SONG = generate_song();
			xfer_end = 1;
		}
		count ++;
	}
	else
	{
		uart_channel_getchar(uart_1);
	}
}

static void pb1_callback()
{
	
	if(MODE == idle_mode)
	{
		if(xfer_end == 1)
			MODE = play_mode;
	}
	else if(MODE == play_mode)
	{
		switch(PLAYBACK)
		{
		case playing:
			PLAYBACK = paused;
			break;
		case paused:
			PLAYBACK = playing;
			break;
		default:
			PLAYBACK = playing;
			break;
		}
		
	}
	else if(MODE == transfer_mode)
	{
		
	}
	
}

static void pb2_callback()
{
	if(MODE == idle_mode)
	{
		MODE = transfer_mode;
	}
	else if(MODE == play_mode)
	{
		PLAYBACK = restart;
		MODE = idle_mode;
	}
	else if(MODE == transfer_mode)
	{
		if(TRANSFER_STATUS == transfer_idle)
		{
			MODE = idle_mode;
		}
	}
	
}

static void pit0_callback()
{
	if(MODE == idle_mode)
	{
	}
	else if(MODE == play_mode)
	{
	}
	if(MODE == transfer_mode && TRANSFER_STATUS != transfer_in_progress)
	{
		uc_led_toggle(uc_led_1);
	}
	
}

static void hw_init()
{
	int_inhibit_all();
	adc_init(5);
	pit0_init(pit0_callback, 9);
	
	uc_pushb_init(pb1_callback, pb2_callback);
	uc_led_init();
	dtim0_init();
	speaker_init();
	uart_channel_init(1, 300, no_parity, eight_bits, stop_bits_1, 7, 7, uart_callback);
	
	pwm_channel_set_duty(2, 50);
	
	uc_pot_init();
	
	int_uninhibit_all();
	
	
	
	pit0_enable();
	pit1_enable();
	
	uart_channel_enable(uart_1);
	MODE = idle_mode;
	TRANSFER_STATUS = transfer_idle;
	
	

}

static void idle()
{
	uc_led_init();
	uc_led_all_off();
	pwm_channel_enable(2);
	
	while(MODE == idle_mode)
	{
		
		
	}
	
	
}

static void play()
{
	
	uc_led_all_off();
	int playback_pos = 0;
	
	if(TRANSFER_STATUS == transfer_idle)
	{
		speaker_init();
		while(MODE == play_mode)
		{
			while(PLAYBACK == playing)
			{
				speaker_play_note(CURRENT_SONG.notes[playback_pos]);
				if(CURRENT_SONG.notes[playback_pos].pitch == pitch_mute)
				{
								
				}
				else 
				{
					uc_led_on(uc_led_1);
					pwm_channel_enable(2);
				}	
				dtim0_busy_delay_ms(CURRENT_SONG.notes[playback_pos].duration * (get_tempo(CURRENT_SONG)/25)); 
				uc_led_all_off();
				pwm_channel_disable(2);
				dtim0_busy_delay_ms(25);
				playback_pos++;
				if(playback_pos >= CURRENT_SONG.num_notes)
				{
					dtim0_busy_delay_ms(1000); 
					uc_led_off(uc_led_1);
					PLAYBACK = restart;
				}
			}
			if(PLAYBACK == restart)
			{
				playback_pos = 0;
				PLAYBACK = playing;
			}
			
		}
	}
}

static void transfer()
{
	count = 0;

	while(MODE == transfer_mode)
	{	
	}
}

static void run()
{
	pwm_channel_disable(2);
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
	}	
}


__declspec(noreturn) int main()
{
	hw_init();
	run();
}