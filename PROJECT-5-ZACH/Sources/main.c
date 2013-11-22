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
#include "uc_pushb.h"
#include "pit.h"

char DATA[1024];
int count = 0;
int xfer_end = 0;
int LENGTH = 0;
int playback_pos = 0;
song_t CURRENT_SONG;
mode_t MODE;
play_t PLAYBACK;
transfer_mode_t TRANSFER_STATUS;

int flash = 0;

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
			MODE = idle_mode;
			CURRENT_SONG = generate_song();
			//uc_led_all_off();
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
	
	//else if(MODE == transfer_mode && TRANSFER_STATUS == transfer_no_song)
	//{
	//	uc_led_toggle(uc_led_1);
	//}
	
	//return;
	

	
}
static void pit1_callback()
{

}

static void hw_init()
{
	int_inhibit_all();
	
	pit0_init(pit0_callback, 9);
	//pit1_init(pit1_callback, 9);
	
	uc_pushb_init(pb1_callback, pb2_callback);
	uc_led_init();
	dtim0_init();
	speaker_init();
	uart_channel_init(1, 300, no_parity, eight_bits, stop_bits_1, 7, 7, uart_callback);
	
	pwm_channel_set_duty(2, 0x5F);
	
	int_uninhibit_all();
	
	
	
	pit0_enable();
	pit1_enable();
	
	uart_channel_enable(uart_1);
	MODE = transfer_mode;
	TRANSFER_STATUS = transfer_idle;
	
	

}

static void idle()
{
	uc_led_init();
	uc_led_all_off();
	//uart_channel_disable(uart_1);
	pwm_channel_enable(2);
	
	while(MODE == idle_mode)
	{
		speaker_play_note(generate_note(pitch_c5, duration_half));
		
		
	}
	
	
}

static void play()
{
	
	uc_led_all_off();
	
	if(TRANSFER_STATUS == transfer_idle)
	{
		speaker_init();
		//CURRENT_SONG = generate_song();
		//playback_pos = 0;
		
		while(MODE == play_mode)
		{
			
			
			while(PLAYBACK == playing)
			//for(int i = 0 ; i < CURRENT_SONG.num_notes-1 ; i++)
			{
				speaker_play_note(CURRENT_SONG.notes[playback_pos]);
				if(CURRENT_SONG.notes[playback_pos].pitch == pitch_mute)
				{
								
				}

				else 
				{
					pwm_channel_enable(2);
				}	
				dtim0_busy_delay_ms(25*CURRENT_SONG.notes[playback_pos].duration); 
				pwm_channel_disable(2);
				dtim0_busy_delay_ms(25);
				playback_pos++;
				if(playback_pos >= CURRENT_SONG.num_notes-1)
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
	
	//uc_led_all_off();
	pwm_channel_disable(2);
	
	//pwm_channel_set_period(2, 250);
	//pwm_set_prescale(2, 2);
	//pwm_set_scale(2, 81);
	
	
	
	/*
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
		
	} */
	
	
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