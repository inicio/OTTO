/*
 * IO.cpp
 *
 *  Created on: 2012-07-07
 *      Author: scott
 */

#include "IO.h"

IO inout;

IO::IO() {
	// TODO Auto-generated constructor stub
}

IO::~IO() {
	// TODO Auto-generated destructor stub
}

void IO::controls(){
	pinMode(BUTTON,INPUT);

}

bool IO::button(){
	if(digitalRead(BUTTON))
		return true;
	else
		return false;
}

void IO::addServos(){
	int servo_pins[2] = {11,10};

	for(int i = 0; i < 2; i++){
		SoftwareServo servo;
	//	servo.attach(servo_pins[i]);
	//	servo.write(0);
	//	Serial.println("servo attached:"+servo.attached());

	//	servos[i] = servo;
	}

	s1.attach(11);
	s2.attach(10);
//	s.setMinimumPulse(100);
//	s.setMaximumPulse(2000);

	s1.write(OFF);
	s2.write(OFF);
//	SoftwareServo::refresh();
	delay(2000);


}

void IO::addServos(int* array){

	for(int i = *(array); i != '\0'; i = *(array+i)){
		Serial.println(i);
	}

}

void IO::write(int i, int val){ // the problem might be related to the two writers that are calling this class.
	SoftwareServo* servo;
//	servo = &servos[i];
//	servo->write(val);

	switch(i){
		case 0:
			servo = &s1;
			break;
		case 1:
			servo = &s2;
			break;
	}

	servo->write(force[val]);
	servo->refresh();

//	SoftwareServo::refresh();
//	servo->refresh();
//	delay(100);
}

void IO::stop(int i){
	// the servo will not hold the off position...
	SoftwareServo* servo;

}


