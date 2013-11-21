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

/*
Suggested functionality,
1. Provides an enumerated type to represent the pitches of notes. See mksong.c for an example.
2. Provides an enumerated type to represent the duration of notes and rests. See mksong.c.
3. Provides a structure type to store the information (pitch and duration) for a note or rest. For example,
typedef struct {
 	pitch_t pitch;
 	duration_t duration;
	} note_t;
4. Provides functionality to create a note_t variable given the pitch and duration for the note or rest.
 */

note_t generate_note(pitch_t pitch, duration_t duration)
{
	note_t generated_note;
	generated_note.duration = duration;
	generated_note.pitch = pitch;

	return generated_note;
}
