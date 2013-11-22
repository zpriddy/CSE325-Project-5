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
#include "uc_pot.h"

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
		//	- As a song is being transferred, PB1 & PB2 presses = IGNORED
				// I ALREADY DID IT IN pushb 1 & 2 to not do anything when TRANSFER_STATUS = transfer_in_progress
		TRANSFER_STATUS = transfer_in_progress;
		
		// After receiving each byte of a song packet, LED1 = toggle
		if(flash == 0 )
		{
			uc_led_on(uc_led_1);
			flash = 1;
		}
		else
		{
			uc_led_off(uc_led_1);
			flash = 0 ;
		}
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
			// After receiving final byte of a song packet, LED1 = blinking again at 2Hz
				// I don't know if it should blink for one time or many times
			// FOR ONE TIME:
					/*	uc_led_on(uc_led_1);
						dtim0_busy_delay_ms(250);
						uc_led_off(uc_led_1);
						dtim0_busy_delay_ms(250); */
			// FOR MANY TIMES:
					/*	I DONT KNOW!  */
			
				uc_led_on(uc_led_1); // WHY DO YOU DO THIS WHEN YOU'VE GOT uc_led_all_off() AFTER IT?!
				xfer_end = 1;
				uc_led_all_off();
		}
		count ++;
	}
}

static void pb1_callback()
{
	if(MODE == idle_mode)
	{
		MODE = play_mode;
	}
	if(MODE == play_mode)
	{
		switch(PLAYBACK)
		{
		case playing:
			PLAYBACK = paused;
			break;
		case paused:
			PLAYBACK = playing;
			break;
		}
		
	}
	if(MODE == transfer_mode)
	{
		if(TRANSFER_STATUS == transfer_idle)
		{
			MODE = play_mode;
		}
		else if(TRANSFER_STATUS == transfer_in_progress)
		{	
		}
	}
}

static void pb2_callback()
{
	if(MODE == idle_mode)
	{
		MODE = transfer_mode;
	}
	if(MODE == play_mode)
	{
		PLAYBACK = restart;
		MODE = idle_mode;
	}
	if(MODE == transfer_mode)
	{
		if(TRANSFER_STATUS == transfer_idle)
		{
			MODE = idle_mode;
		}
		else if(TRANSFER_STATUS == transfer_in_progress)
		{	
		}
	}
}

static void hw_init()
{
	int_inhibit_all();
	uc_pushb_init(pb1_callback, pb2_callback);
	uc_pot_init();
	uc_led_init();
	dtim0_init();
	speaker_init();
	uart_channel_init(1, 300, no_parity, eight_bits, stop_bits_1, 7, 7, uart_callback);
	pwm_channel_set_duty(2, 0x5F);
	int_uninhibit_all();
	uart_channel_enable(uart_1);
	MODE = idle_mode;

}

/*
1)Idle Requirements:
        - serial communications module is disabled
        - NO SONG is playing
        - ALL MCB LEDS are off
        - when:
                * PB1: play music mode
                * PB2: transfer song mode
 */
static void idle()
{
	while(MODE == idle_mode)
	{
		uc_led_init();
		uc_led_all_off();
		MODE = transfer_mode;
		// NEED TO DO THE Push Buttons
	}
}

/*
2)Play Music Requirements:
	- [If] no song has been transferred and stored, [then] terminate & return to idle Mode.
	- [Otherwise] LED1 = ON, Stored song= BEGIN PLAYING (at first note, obviously).
	- After a notes ends, LED1 = OFF
	- After a note is played, ADD (default internote pause) of 25ms, during that:
		* speaker = silent
		* all leds = OFF
		*** SEE (Point 5, page 3 for the definition of internote pause and rest)
	- default pause of 25ms after a rest (just like after a note)
	- Tempo of the song is controlled by potentimiometer (pot), Ranges for pot values:
		* pot0 [0, 584]
		* pot1 [585, 1169]
		* pot2 [1170, 1754]
		* pot3 [1755, 2339]
		* pot4 [2340, 2924]
		* pot5 [2925, 3509]
		* pot6 [3510, 4095]
	- When tempo pot is:
		* pot0
			)note duration (=175% of the default duration)
			)internote pause duration (=175% of the default internote duration)

		* pot1
			)note duration (=150% of the default duration)
			)internote pause duration (=150% of the default internote duration)

		* pot2
			)note duration (=125% of the default duration)
			)internote pause duration (=125% of the default internote duration)

		* pot3 = unmodified (GENERAL REQUIREMENTS 5 and 7 for the default tempo, page3)

		* pot4
			)note duration (=75% of the default duration)
			)internote pause duration (=75% of the default internote duration)

		* pot5
			)note duration (=50% of the default duration)
			)internote pause duration (=50% of the default internote duration)

		* pot6
			)note duration (=25% of the default duration)
			)internote pause duration (=25% of the default internote duration)

	- After last note of the played song, LED1=OFF, ONE SECOND pause before replaying the song
	- PB1 = pause playing, pressing again = resume playing at the point it was paused
	- PB2 = terminate PLAY SONG MODE & return to idle mode (even if the song is paused)
	- [BEFORE] exiting PLAY SONG MODE, LED1,3,4 = OFF
 */
static void play()
{
	while(MODE == play_mode)
	{
		//- [If] no song has been transferred and stored, [then] terminate & return to idle Mode.
		if(xfer_end == 0)
		{
			MODE = idle_mode;
			break;
		}
		else
		{
			// - [Otherwise] LED1 = ON
				//uc_led_on(uc_led_1); // UNCOMMENT THIS AFTER POT is WORKING
			
			speaker_init(); // IS IT THE RIGHT PLACE?
			uc_pot_init(); // IS IT THE RIGHT PLACE?
			/******* Stored song= BEGIN PLAYING (at first note, obviously). *******/
			/*
				- After a note ends, LED1 = OFF
        		- After a note is played, ADD (default internote pause) of 25ms, during that:
                	* speaker = silent
                	* all leds = OFF
                	*** SEE (Point 5, page 3 for the definition of internote pause and rest)       																					*/
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
				
				/////////////////// WORK ZONE FOR POT
				int pot_position = uc_pot_get_setting();//get_pot();
				if(pot_position > 0)
					uc_led_on(uc_led_1);
				else if(pot_position < 0)
					uc_led_on(uc_led_3);
				else
					uc_led_on(uc_led_4);
				dtim0_busy_delay_ms(25*CURRENT_SONG.notes[i].duration); //ZACH's version
				if(pot_position > 0)
					uc_led_off(uc_led_1);
				else if(pot_position < 0)
					uc_led_off(uc_led_3);
				else
					uc_led_off(uc_led_4);
				////////////////// END WORK ZONE
				
				//dtim0_busy_delay_ms( CURRENT_SONG.notes[i].duration * get_tempo(CURRENT_SONG)/30);// ABDULLA's version
				pwm_channel_disable(2);
				dtim0_busy_delay_ms(25*2);
			}
						//pwm_channel_enable(2);
						//speaker_play_note(generate_note(pitch_b3,duration_32th));
						//pwm_channel_enable(2);
						
						//xfer_end = 0;
						//count = 0;
			/******* End of playing song *******/
			
			// - After last note of the played song, LED1=OFF
			uc_led_off(uc_led_1);
			
			// - ONE SECOND pause before replaying the song
			dtim0_busy_delay_ms(1000); // 1 sec = 1000 millisecond
			
			// - PB1 = pause playing, pressing again = resume playing at the point it was paused
				/* 
				 if(pb1 == 1)
				 	 pause();
				 else
				 	 resume();
				 */
			
			// - PB2 = terminate PLAY SONG MODE & return to idle mode (even if the song is paused)
				/* 
			 	 if(pb2 == 1)
			 	 {
			 	 	 MODE = idle_mode;
			 	 	 // - [BEFORE] exiting PLAY SONG MODE, LED1,3,4 = OFF
			 	 	 uc_led_off(uc_led_1);
					 uc_led_off(uc_led_3);
					 uc_led_off(uc_led_4);
			 	 	 break();
			 	 }
				 */
		} // END OF ELSE
	}
}

/*
 3)Transfer Song Requirements:
        - Upon entering Transfer Song Mode:
                * system = begin listening on UART1 for a song packet from the host PC.
                * The UART parameters shall be 300 baud, N81.
        - LED1= blinking at 2Hz (i.e., 250ms on, 250ms off .. etc)
        - When song = transferred:
                * Song information SHALL be stored (for future play back in Play Music Mode)
        - After:
                * Receiving each byte of a song packet, LED1 = toggle
                * Receiving final byte of a song packet, LED1 = blinking again at 2Hz
        - As a song is being transferred, PB1 & PB2 presses = IGNORED
        - When song is NOT being transferred, but the system is listening for a song packet:
                * PB2 = terminate TRANSFER SONG MODE & return the system to IDLE MODE
        - When exiting TRANSFER SONG MODE:
                * System = stop listening on UART1
                * LED1,3,4 = OFF
 */
static void transfer()
{
	while(MODE == transfer_mode)
	{
		/*	- Upon entering Transfer Song Mode:
                * system = begin listening on UART1 for a song packet from the host PC.
                * The UART parameters shall be 300 baud, N81.
		 */
		
		//FOR THIS I THINK WE SHOULD DO:
			// uart_channel_init(1, 300, no_parity, eight_bits, stop_bits_1, 7, 7, uart_callback);
			// AND DELETE THAT ONE IN hw_init();
		
		// - LED1= blinking at 2Hz (i.e., 250ms on, 250ms off .. etc)
			uc_led_on(uc_led_1);
			dtim0_busy_delay_ms(250);
			uc_led_off(uc_led_1);
			dtim0_busy_delay_ms(250);
		
		/*
			- When song = transferred:
			         * Song information SHALL be stored (for future play back in Play Music Mode)
		*/
			//uart_callback() already does this
		
		/*
			- After:
                * Receiving each byte of a song packet, LED1 = toggle
                * Receiving final byte of a song packet, LED1 = blinking again at 2Hz
		*/
			// I edited uart_callback to do this
			
		// - As a song is being transferred, PB1 & PB2 presses = IGNORED
			// DO IT in uart_callbacked
		
		/*
	    	- When song is NOT being transferred, but the system is listening for a song packet:
	                * PB2 = terminate TRANSFER SONG MODE & return the system to IDLE MODE
	    */
			/* if(pb2 == 1 & TRANSFERRING_STATUS == 0)
			{
				MODE = idle_mode;
				uc_led_off(uc_led_1);
				uc_led_off(uc_led_3);
				uc_led_off(uc_led_4);
				break;
			}*/
			
		/*
	        - When exiting TRANSFER SONG MODE:
	                * System = stop listening on UART1
	                * LED1,3,4 = OFF
	    */
			//if(pb1 == 1) // Play song mode is on
			//{
			//	MODE = play_mode;
			//	uc_led_off(uc_led_1);
			//	uc_led_off(uc_led_3);
			//	uc_led_off(uc_led_4);
			//}
			MODE = play_mode;
	}
}

/*
General Requirements:
        - 3 modes (Idle Mode, Play Song Mode, or Transfer Song Mode)
        - no more than 256 for each song
        - store one song at a time
        - note = 8unsigned bit ~ pitch(which is note duration)=8unsigned bit
        - Pitches, note durations (including rest durations) must be in enum type.
        - rest=8unsighned int

IMPORTANT:
- System starts with idle mode
 */
static void run()
{
	
	uc_led_all_off();
	pwm_channel_disable(2);
	
	//pwm_channel_set_period(2, 250);
	//pwm_set_prescale(2, 2);
	//pwm_set_scale(2, 81);
	
	
	
	
	/*while(1)
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
				dtim0_busy_delay_ms(25*CURRENT_SONG.notes[i].duration); // MAYBE duration should be duration = duration * get_pot());
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
	
	
	while(1) // I think we can delete while(1) and (break;), if the run() is called repeatedly
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