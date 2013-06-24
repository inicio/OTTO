/*
 * Note.cpp
 *
 *  Created on: 2012-06-30
 *      Author: scott
 */

#include "Note.h"

Note::Note(){
	build_index = 0;
}

Note::Note(int timestamp, int length, int force, int bar) {
	params.timestamp = timestamp;
	params.length = length;
	params.force = force;
	params.bar = bar;
}

Note::~Note() {

}

int Note::getValue(int val){ // Yuck, two very similar functions.
	switch(val){
		case 0: return params.timestamp;
			break;
		case 1:	 return params.length;
			break;
		case 2: return params.force;
			break;
		case 3: return params.bar;
			break;
	}

	return 0;
}

void Note::build(int val){
	switch(build_index++){
		case 0: params.timestamp = val;
			break;
		case 1:	params.length = val;
			break;
		case 2: params.force = val;
			break;
		case 3: params.bar = val;
			break;
	}
}

