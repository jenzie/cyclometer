/*
 * DisplaySpeed.h
 *
 *  Created on: May 18, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#ifndef DISPLAYSPEED_H_
#define DISPLAYSPEED_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <exception>

class DisplaySpeed {
public:
	DisplaySpeed();
	virtual ~DisplaySpeed();
	virtual void* runProcessDisplay(void);
	virtual void updateSpeed(float speed, float avSpeed);
	virtual void startThread();
	virtual void stopThread();
};

#endif /* DISPLAYSPEED_H_ */
