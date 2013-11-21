//*******************************************************************************************************
// oct_spkr.c
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
//********************************************************************************************************

#include "note.h"
#include "pwm.h"
#include "oct_spkr.h"
#include "dtim.h"


void speaker_init()
{
	pwm_channel_init(2);

}

void speaker_play_note(note_t p_note)
{
	
	
	switch(p_note.pitch)
	{
		case pitch_b3:
			pwm_channel_set_period(2, 250);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 81);
			break;
		case pitch_c4:
			pwm_channel_set_period(2, 245);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 78);
			break;
		case pitch_c4_sharp:
			pwm_channel_set_period(2, 220);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 82);
			break;
		case pitch_d4:
			pwm_channel_set_period(2, 198);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 86);
			break;
		case pitch_d4_sharp:
			pwm_channel_set_period(2, 164);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 98);
			break;
		case pitch_e4:
			pwm_channel_set_period(2, 96);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 158);
			break;
		case pitch_f4:
			pwm_channel_set_period(2, 139);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 103);
			break;
		case pitch_f4_sharp:
			pwm_channel_set_period(2, 124);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 109);
			break;
		case pitch_g4:
			pwm_channel_set_period(2, 109);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 117);
			break;
		case pitch_g4_sharp:
			pwm_channel_set_period(2, 142);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 80);
			break;
		case pitch_a4:
			pwm_channel_set_period(2, 142);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 80);
			break;
		case pitch_a4_sharp:
			pwm_channel_set_period(2, 62);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 173);
			break;
		case pitch_b4:
			pwm_channel_set_period(2, 45);
			pwm_set_prescale(2, 0x00);
			pwm_set_scale(2, 225);
			break;
		case pitch_c5:
			pwm_channel_set_period(2, 39);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 245);
			break;
		case pitch_c5_sharp:
			pwm_channel_set_period(2, 41);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 220);
			break;
		case pitch_d5:
			pwm_channel_set_period(2, 198);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 43);
			break;
		case pitch_d5_sharp:
			pwm_channel_set_period(2, 196);
			pwm_set_prescale(2, 0x02);
			pwm_set_scale(2, 41);
			break;
		case pitch_e5:
			pwm_channel_set_period(2, 41);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 189);
			break;
		case pitch_f5:
			pwm_channel_set_period(2, 45);
			pwm_set_prescale(2, 2);
			pwm_set_scale(2, 159);
			break;
		case pitch_mute:
			pwm_channel_disable(2);
			break;
		
			/*
		if(p_note.pitch != pitch_mute)
			pwm_channel_enable(2);
			*/
		
		//pwm_channel_enable(2);
			
		
		
		//pwm_channel_disable(2);
	}


}


//    pitch_b3       = 0x00,  /* 246.94 Hz */
//    pitch_c4       = 0x01,  /* 261.63 Hz */
//    pitch_c4_sharp = 0x02,  /* 277.18 Hz */
//    pitch_d4       = 0x03,  /* 293.66 Hz */
//    pitch_d4_sharp = 0x04,  /* 311.13 Hz */
//    pitch_e4       = 0x05,  /* 329.63 Hz */
//    pitch_f4       = 0x06,  /* 349.23 Hz */
//    pitch_f4_sharp = 0x07,  /* 369.99 Hz */
//    pitch_g4       = 0x08,  /* 392.00 Hz */
//    pitch_g4_sharp = 0x09,  /* 415.30 Hz */
//    pitch_a4       = 0x0A,  /* 440.00 Hz */
//    pitch_a4_sharp = 0x0B,  /* 466.16 Hz */
//    pitch_b4       = 0x0C,  /* 493.88 Hz */
//    pitch_c5       = 0x0D,  /* 523.25 Hz */
//    pitch_c5_sharp = 0x0E,  /* 554.37 Hz */
//    pitch_d5       = 0x0F,  /* 587.33 Hz */
//    pitch_d5_sharp = 0x10,  /* 622.25 Hz */
//    pitch_e5       = 0x11,  /* 659.26 Hz */
//    pitch_f5       = 0x12,  /* 698.46 Hz */
//    pitch_mute     = 0xFF   /* Mute      */
 


