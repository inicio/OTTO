#include "OTTOreborn.h"

char array[] =
		// This is a test graphic
		"T0 L1 F0 B0\n "
		"T0 L1 F0 B1\n "

		//
		"T5 L15 F12 B0\n "
		"T5 L4 F12 B1\n "

		"T9 L1 F0 B1\n "
		"T10 L1 F12 B1\n "
		"T11 L1 F0 B1\n "
		"T12 L1 F12 B1\n "
		"T13 L1 F0 B1\n "
		"T14 L1 F12 B1\n "
		"T15 L1 F0 B1\n "

		"T16 L4 F12 B1\n "

		//
		"T20 L15 F12 B1\n "
		"T20 L4 F12 B0\n "

		"T24 L1 F0 B0\n "
		"T25 L1 F12 B0\n "
		"T26 L1 F0 B0\n "
		"T27 L1 F12 B0\n "
		"T28 L1 F0 B0\n "
		"T29 L1 F12 B0\n "
		"T30 L1 F0 B0\n "

		"T31 L4 F12 B0\n "

		//
		"T35 L15 F12 B0\n "
		"T35 L4 F12 B1\n "

		"T39 L1 F0 B1\n "
		"T40 L1 F12 B1\n "
		"T41 L1 F0 B1\n "
		"T42 L1 F12 B1\n "
		"T43 L1 F0 B1\n "
		"T44 L1 F12 B1\n "
		"T45 L1 F0 B1\n "

		"T46 L4 F12 B1\n ";

int main(void){

	init();

	Serial.begin(9600);
	inout.addServos();
	inout.controls();

	Composition comp;
	comp.readSheetMusic(array);
	comp.sortNotes();

	Composition* comp_pointer;
	comp_pointer = &comp;

	Timeline timeline;
	timeline.loadComposition(comp_pointer); // Can't just send the address of the comp. Needs to be a pointer to the address
	timeline.start(); // the button will activate this. init some variables.

	// DEBUG only

	int *values = comp.getNoteValues(0); // naturally, this var must be a pointer. C++ can't fill an array based on = operator

	Serial.println("Cycle");
	for(int j = 0; j < 30; j++){
		for(int i = 0; i < 4; i++){ // just to check, not being used yet
			Serial.print(comp.getNoteValues(j)[i]);
			Serial.print(" ");
		}
		Serial.println();
	}


	bool started = false;

	pinMode(11,OUTPUT);
	digitalWrite(11,HIGH);

	for(;;){

		timeline.run();

		if (inout.button() && started) {
			timeline.start();
			started = false;
		} else if (!inout.button()) {
			timeline.stop();
			timeline.restart();
			timeline.setSpeed(analogRead(0)*2); // set speed only when not running
			started = true;
		}

	}

}
