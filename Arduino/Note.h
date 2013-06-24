/*
 * Note.h
 *
 *  Created on: 2012-06-30
 *      Author: scott
 */

#ifndef NOTE_H_
#define NOTE_H_

class Note {
public:
	Note();
	Note(int timestamp, int length, int force, int bar);
	virtual ~Note();

	int getLength() { return params.length; }
	int getTimestamp() { return params.timestamp;}
	int getForce() { return params.force;}
	int getBar() {return params.bar;}

    void build(int);
    int getValue(int);

    #define NOTEPROPS 4

private:


	struct Params {
		int length;
		int timestamp;
		int force;
		int bar;
	};

	struct Params params;

	int build_index;


};

#endif /* NOTE_H_ */
