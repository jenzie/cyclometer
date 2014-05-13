/*
 * SetUnitsState.h
 *
 *  Created on: May 12, 2014
 *      Author: nmc2484
 */

#ifndef SETUNITSSTATE_H_
#define SETUNITSSTATE_H_

#include "StateNode.h"
#include "SetUnitsState.h"
#include "ModeButtonPressTransition.h"
#include "SetButtonPressTransition.h"
#include "Transition.h"
#include "Enums.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <vector>

class SetUnitsState: public StateNode{
private:
	int myID;
	std::vector<Transition*> transVector;

public:
	int getID();
	void (*createCallback)(int);
	void (*createCallback2)(int);
	SetUnitsState();
	virtual ~SetUnitsState();
	void enter();
	void entry();
	void exit();
	void doThis();
	void is_in();
	void accept(EVENT e);
	void addTransition(Transition* t);
	void setUnits(int iD, void(*callbackfunc)(int),void (*callbackfunc2)(int));
};

#endif /* SETUNITSSTATE_H_ */
