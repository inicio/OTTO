/*
 * Composition.h
 *
 *  Created on: 2012-06-30
 *      Author: scott
 */

#ifndef COMPOSITION_H_
#define COMPOSITION_H_
#include "Note.h"
#include "Arduino.h"
#include "stdio.h"
#include "string.h"

class Composition {
public:
	Composition(); // string s (s1) is also suppose to work?
	virtual ~Composition();

	#define BARS 2
	#define COMP_LENGTH 100

	void readSheetMusic(char *);
	void sortNotes();

	int* getNoteValues(int);

	Note* getSortedNote(int time, int bar) { return sorted_notes[time][bar];}

private:
	void createNotes();


	Note notes[50]; // MUST be initialized! TODO: Make it Auto-matic
	Note *sorted_notes[COMP_LENGTH][BARS]; // uhh [time][bar,bar] returns the note as Note

	char *sheet;
	int note_index;
	int comp_length;

	int getNoteBuildValue(char *);
	void buildnote(int *);
};

#endif /* COMPOSITION_H_ */

// will the compositon generate its own notes? probably. it could read from a
// 	text file and create notes according
// 	to some pre set qualities
