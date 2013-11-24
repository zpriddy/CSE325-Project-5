//*******************************************************************************************************
// song.h
//
// Date: 2013-11-14 10:51:07
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


#ifndef SONG_H_
#define SONG_H_


#include "note.h"

extern char DATA[1024];

typedef struct {
	 int tlength;
	 note_t notes[256];
	 int num_notes;
	 int tempo;
	 char title[50];
} song_t;

int get_pot();
int get_tempo(song_t p_song);
song_t generate_song();

#endif /*SONG_H_*/