/*
 * ClaculationState.h
 *
 *  Created on: May 15, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#ifndef CALCULATIONSTATE_H_
#define CALCULATIONSTATE_H_

#include "StateNode.h"
#include "ModeButtonPressTransition.h"
#include "DisplaySpeed.h"
#include "DisplayTime.h"
#include "DisplayDistance.h"
#include "Transition.h"
#include "Enums.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <exception>


class CalculationState : public StateNode{
private:
	int myID;
	std::vector<Transition*> transVector;

public:
	int getID();
	CalculationState();
	virtual ~CalculationState();
	void (*createCallback)(int);
	void (*createCallback2)(int);
	int (*createCallback3)(void);
	bool (*createCallback4)(void);
	void entry();
	void exit();
	void doThis();
	void is_in();
	void accept(EVENT a);
	virtual void setUnits(int iD, void(*callbackfunc)(int),void (*callbackfunc2)(int),int (*callbackfunc3)(void),bool (*callbackfunc4)(void));

	virtual void modeSwitch(int switcher);

	virtual void* runProcessTime(void);
	virtual void* runProcessSpeed(void);
	virtual void* runCProcess(void);
	virtual void* blinkLED(void);
	virtual void* cycleLED(void);
	//virtual void* runProcessDisplaySpeed(void);
	//virtual void* runProcessDisplayTime(void);
	//virtual void* runProcessDisplayDistance(void);

	void addTransition(Transition* e);
	virtual void resetValues();
};

#endif /* CALCULATIONSTATE_H_ */
