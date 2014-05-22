/*
 * DisplayTime.h
 *
 *  Created on: May 18, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#ifndef DISPLAYTIME_H_
#define DISPLAYTIME_H_
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <exception>

class DisplayTime {
public:
	DisplayTime();
	virtual ~DisplayTime();
	virtual void* runProcessDisplayTime(void);
	virtual void updateTime(int minutes, int seconds);
	virtual void startThread();
	virtual void stopThread();
};

#endif /* DISPLAYTIME_H_ */
