/*
 * IO.h
 *
 *  Created on: 2012-07-07
 *      Author: scott
 */

// Class for controlling the ins and outs of our board.


#ifndef IO_H_
#define IO_H_

#include "Arduino.h"
#include "Servo/SoftwareServo.h"

const int force[12] = {130,120,115,110,105,100,95,90,85,80,75,70}; // declaration, not definition

// If it's inside the class definition, then it's a part of class description,
// not an declaration of an external global variable - totally unrelated concepts!
// If it's part of a class,
// then add it without extern to the class definition and then initialize it in the constructor.
//
//

class IO {
public:
	IO();
	virtual ~IO();

	void addServos(int *);
	void addServos();
	void controls(); // can we add to a button array dynamically? probably, but to what avail

	bool button();

	void write(int,int);
	void stop(int);

private:
	SoftwareServo servos[2]; // TODO: create a include populated with constants that apply to all of the prog
	SoftwareServo s1, s2;

	#define OFF 130
	#define BUTTON 9


};

extern IO inout;

#endif /* IO_H_ */
