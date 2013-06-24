/*
 * Timeline.h
 *
 *  Created on: 2012-07-07
 *      Author: scott
 */

#ifndef TIMELINE_H_
#define TIMELINE_H_
#include "Composition.h"
#include "Writer.h"

class Timeline {
public:
	Timeline();
	virtual ~Timeline();

	void start() {global_timer = 0; active = true; time = 0;}
	void restart() {global_timer = 0; time = 0;}
	void stop() {active = false; }

	void setSpeed(int a){speed = a;}

	bool hasStarted();

	void run(); // this will not actually start anything, it gets looped

	void loadComposition(Composition *);

private:

	int speed;

	Composition* comp;
	Writer writers[BARS];

	int global_timer;
	int time;
	boolean active;

	void play();

};

#endif /* TIMELINE_H_ */
