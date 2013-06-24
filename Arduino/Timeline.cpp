/*
 * Timeline.cpp
 *
 *  Created on: 2012-07-07
 *      Author: scott
 */

#include "Timeline.h"

Timeline::Timeline() {
	// Prepare the performers

	for(int i = 0; i < BARS; i++){ // foreach bar a writer to be initalized
		Writer writer;
		writer.setID(i); // this was the problem. we were sending writers to a pointer array. we needed to send writers toe a wrtiter array
		writers[i] = writer;
	}

	active = false;

}

Timeline::~Timeline() {

}

void Timeline::loadComposition(Composition *comp){
	this->comp = comp;
}

void Timeline::run(){

	// this is always looping. A timer will need to be used for incrementing the position
	if(active){
		global_timer+=1; // why does this have to be here?
		play();
	} else {
		for(int bar = 0; bar < 2; bar++){ // to keep everything zippy we dedicate a loop to spraying
			Writer* writer;
			writer = &writers[bar];

			writer->setParams(5, 0, 0);
		}
	}

	for(int bar = 0; bar < 2; bar++){ // to keep everything zippy we dedicate a loop to spraying
		Writer* writer;
		writer = &writers[bar];

		if(writer->getEndPos() > time){
			writer->spray(); // What about when one note 'overwrites' another...
		} else {
			writer->stop();
		}
	}
}

void Timeline::play(){
	if(global_timer%speed == 0) {
		time += 1;

		if(time > COMP_LENGTH - 1) {
		    stop();
		}

		for(int bar = 0; bar < BARS; bar++){
			Note* n;
			n = comp->getSortedNote(time,bar);

			if(n->getLength() > 0 && n->getLength() < 100){

				Writer* writer;
				writer = &writers[bar];

				int length = n->getLength();
				int timestamp = n->getTimestamp(); // should be same as time, yeah?
				int force = n->getForce();

//				Serial.print(timestamp); // some of the notes have memory garbage attached to them.
//				Serial.print(" ");
//				Serial.print(length);
//				Serial.print(" ");
//				Serial.print(force);
//				Serial.println();

			    writer->setParams(length, timestamp, force); // set the params, then set this back into the writer array
			//  writers[bar] = writer;
			}
		}

	}

	// this is our problem. with it looping through both writers our servo tries to please them both.
	// so....


}

