//*******************************************************************************************************
// note.h
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
#ifndef NOTE_H_
#define NOTE_H_

#include "common.h"

typedef enum {
    duration_32th         =   2,
    duration_32th_dot     =   3,
    duration_16th         =   4,
    duration_16th_dot     =   6,
    duration_8th          =   8,
    duration_8th_dot      =  12,
    duration_quarter      =  16,
    duration_quarter_dot  =  24,
    duration_half         =  32,
    duration_half_dot     =  48,
    duration_whole        =  64,
    duration_double_whole = 128
} duration_t;

typedef enum {
    pitch_b3       = 0x00,  /* 246.94 Hz */
    pitch_c4       = 0x01,  /* 261.63 Hz */
    pitch_c4_sharp = 0x02,  /* 277.18 Hz */
    pitch_d4       = 0x03,  /* 293.66 Hz */
    pitch_d4_sharp = 0x04,  /* 311.13 Hz */
    pitch_e4       = 0x05,  /* 329.63 Hz */
    pitch_f4       = 0x06,  /* 349.23 Hz */
    pitch_f4_sharp = 0x07,  /* 369.99 Hz */
    pitch_g4       = 0x08,  /* 392.00 Hz */
    pitch_g4_sharp = 0x09,  /* 415.30 Hz */
    pitch_a4       = 0x0A,  /* 440.00 Hz */
    pitch_a4_sharp = 0x0B,  /* 466.16 Hz */
    pitch_b4       = 0x0C,  /* 493.88 Hz */
    pitch_c5       = 0x0D,  /* 523.25 Hz */
    pitch_c5_sharp = 0x0E,  /* 554.37 Hz */
    pitch_d5       = 0x0F,  /* 587.33 Hz */
    pitch_d5_sharp = 0x10,  /* 622.25 Hz */
    pitch_e5       = 0x11,  /* 659.26 Hz */
    pitch_f5       = 0x12,  /* 698.46 Hz */
    pitch_mute     = 0xFF   /* Mute      */
} pitch_t;

typedef struct {
 	pitch_t pitch;
 	duration_t duration;
} note_t;

note_t generate_note(pitch_t pitch, duration_t duration);

#endif /*NOTE_H_*/