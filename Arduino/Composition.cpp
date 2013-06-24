/*
 * Composition.cpp
 *
 *  Created on: 2012-06-30
 *      Author: scott
 */

#include "Composition.h"

Composition::Composition() {
	note_index = 0; // init
	comp_length = 0; // init

}

Composition::~Composition() {

}

void Composition::readSheetMusic(char *array){
	sheet = array;
	createNotes();
}

void Composition::createNotes(){

	int notebuilder[NOTEPROPS] = {0,0,0,0};
	int builder_index = 0;

	char c;
	int i = 0;

	int dummy[4] = {0,0,0,0};
	buildnote(&dummy[0]);

	while ((c = sheet[i++]) != '\0') {
		switch(c){
			case 'T':
			case 'L':
			case 'F':
			case 'B':
				notebuilder[builder_index++] = getNoteBuildValue(&sheet[i]);
				break;
			case '\n':
				builder_index = 0;
				buildnote(&notebuilder[0]);
				break;
		}

	}

	// AT this point, the text file has been read.
	comp_length = note_index;
	note_index = 0; // worth reseting?

}

void Composition::sortNotes(){
	// We colud sort the index # of the notes (as they relate to the notes array) into this array
	//	Or pointers to the notes could be sorted... this is easily adjusted if wrong. Let's do *'s
	// To sort through these, we will be accessing the Note params (timestamp and bar).

	// Thinkng ahead, when the notes are accessed by the painter function, will we want to use the note type?

	for(int i = 0; i < COMP_LENGTH; i++){ // clear everything
		for(int j = 0; j < BARS; j++){
			sorted_notes[i][j] = &notes[0]; // first note is dummy note!
		}
	}

	for(int i = 0; i < comp_length; i++){
		Note* note;
		note = &notes[i];

		sorted_notes[note->getTimestamp()][note->getBar()] = note; // the address to the pointer array, right?
		// the above address will disapear...
	}

}

void Composition::buildnote(int *array){
	Note note;

	for(int i = 0; i < NOTEPROPS; i++){
		note.build (*(array+i));
	}

	notes[note_index++] = note;
}

int* Composition::getNoteValues(int index){
	int *array = new int;

	for(int i = 0; i < NOTEPROPS; i++){
		array[i] = notes[index].getValue(i);
	}

	return array;
}

int Composition::getNoteBuildValue(char *array){
	int value = 0, i = 0;
	char c;

	while ((c = array[i++]) != ' ' && c != '\n') { // seperated by a space
		value = 10 * value + (c - '0'); // c - '0' is crucial. shit.
	}

	return value;
}

