/*
 * Writer.h
 *
 *  Created on: 2012-07-07
 *      Author: scott
 */

#ifndef WRITER_H_
#define WRITER_H_

#include "Arduino.h"
#include "IO.h"

class Writer {
public:
//	Writer(int); // we need  id to assign unique pin
	Writer();
	virtual ~Writer();

	struct Params {
		int length;
		int timestamp;
		int force;
	};

	struct Params params;

	void setID(int init_id){id = init_id;}

	void spray();
	void stop();

	void setParams(int length, int timestamp, int force) {
		params.length = length;
		params.timestamp = timestamp;
		params.force = force;
	}

	int getEndPos() {return params.timestamp + params.length;}
	int getForce() {return params.force;}

	int id;
private:
	#define SERVO_OFF 0
	#define SERVO_MAX 2000
	#define SERVO_MIN 700

	boolean state;


};

#endif /* WRITER_H_ */
