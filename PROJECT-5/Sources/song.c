//*******************************************************************************************************
// song.c
//
// Date: 2013-11-14 10:50:57
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


#include "song.h"
#include "note.h"
#include "uc_pot.h"



song_t generate_song()
{
	int OFFSET = 0x03;
	int TLEN = 0;
	int COUNT = 0;
	song_t GENERATED_SONG;

		
	
	for( int i = 5+3 ; i < 7+3 ; i++)
	{
		GENERATED_SONG.tlength = (GENERATED_SONG.tlength << 8);
		GENERATED_SONG.tlength = DATA[i]+1;
	}
	COUNT = 0;
	for(int i=7+3 ; i < GENERATED_SONG.tlength+7+3 ; i++)
	{
		GENERATED_SONG.title[COUNT] = DATA[i];
		COUNT++;
	}
	
	//TEMPO
	{
		GENERATED_SONG.tempo = DATA[63];
		GENERATED_SONG.tempo = (GENERATED_SONG.tempo << 8);
		GENERATED_SONG.tempo |= DATA[64];
	}
	
	//NUMBER OF NOTES
	{
		GENERATED_SONG.num_notes = DATA[65];
		GENERATED_SONG.num_notes = (GENERATED_SONG.num_notes << 8);
		GENERATED_SONG.num_notes |= DATA[66];
	}
	
	COUNT = 0;
	for(int i=67; i < 67+(GENERATED_SONG.num_notes * 2) ; i++)
	{
		GENERATED_SONG.notes[COUNT] = generate_note(DATA[i], DATA[i+1]);
		i++;
		COUNT++;
	}
	
	

	return GENERATED_SONG;
}

//USED TO GET P0 - P6 
int get_pot()
{
	int POT_RETURN;
	//Get the current pot pos
	int CURRENT_POT_POS = uc_pot_get_setting();

	if(CURRENT_POT_POS <= 584)
	{
		POT_RETURN = 0;
	}
	else if(CURRENT_POT_POS <= 1169)
	{
		POT_RETURN = 1;
	}
	else if(CURRENT_POT_POS <= 1754)
	{
		POT_RETURN = 2;
	}
	else if(CURRENT_POT_POS <= 2339)
	{
		POT_RETURN = 3;
	}
	else if(CURRENT_POT_POS <= 2924)
	{
		POT_RETURN = 4;
	}
	else if(CURRENT_POT_POS <= 3509)
	{
		POT_RETURN = 5;
	}
	else if(CURRENT_POT_POS <= 4095)
	{
		POT_RETURN = 6;
	}

	return POT_RETURN;

}

//Used to get the tempo
int get_tempo(song_t p_song)
{
	int RETURN_TEMPO;

	switch(get_pot())
	{
		case 0:
			RETURN_TEMPO = (int)(p_song.tempo * 1.75);
			break;
		case 1:
			RETURN_TEMPO = (int)(p_song.tempo * 1.50);
			break;
		case 2:
			RETURN_TEMPO = (int)(p_song.tempo * 1.25);
			break;
		case 3:
			RETURN_TEMPO = p_song.tempo;
			break;
		case 4:
			RETURN_TEMPO = (int)(p_song.tempo * 0.75);
			break;
		case 5:
			RETURN_TEMPO = (int)(p_song.tempo * 0.50);
			break;
		case 6:
			RETURN_TEMPO = (int)(p_song.tempo * 0.25);
			break;	
	} //switch 

	return RETURN_TEMPO;

}