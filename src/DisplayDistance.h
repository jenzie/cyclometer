/*
 * DisplayDistance.h
 *
 *  Created on: May 18, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#ifndef DISPLAYDISTANCE_H_
#define DISPLAYDISTANCE_H_
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <exception>

class DisplayDistance {
public:
	DisplayDistance();
	virtual ~DisplayDistance();
	virtual void* runProcessDisplayDistance(void);
	virtual void updateDistance(float distance);
	virtual void startThread();
	virtual void stopThread();
};

#endif /* DISPLAYDISTANCE_H_ */
