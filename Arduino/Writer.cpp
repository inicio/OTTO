/*
 * Writer.cpp
 *
 *  Created on: 2012-07-07
 *      Author: scott
 */

#include "Writer.h"

Writer::Writer() {
	// TODO Auto-generated constructor stub
	params.length = 0;
	params.force = 0;
	params.timestamp = 0;

	state = false;
//	id = init_id;

}

Writer::~Writer() {
	// TODO Auto-generated destructor stub
}

void Writer::spray(){
//	state = true;
	inout.write(this->id,this->params.force);
}

void Writer::stop(){
//	if(state == true){
	inout.write(this->id,0);
//		state = false;
//	} else {
//		inout.stop(id);
//	}
}
