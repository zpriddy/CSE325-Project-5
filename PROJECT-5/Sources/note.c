//*******************************************************************************************************
// note.c
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

note_t generate_note(pitch_t pitch, duration_t duration)
{
	note_t generated_note;
	generated_note.duration = duration;
	generated_note.pitch = pitch;

	return generated_note;
}
