/*
 * SetCircumference.h
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#pragma once

#ifndef SETCIRCUMFERENCE_H_
#define SETCIRCUMFERENCE_H_



#include "ModeButtonPressTransition.h"

#include "Transition.h"
#include "Enums.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>

class SetCircumference : public StateNode{
private:
	int myID;
	std::vector<Transition*> transVector;

public:
	int getID();
	void(*createCallback)(int);
	void(*createCallback2)(int);
	bool(*createCallback3)(void);
	SetCircumference();
	~SetCircumference();
	void enter();
	void entry();
	void exit();
	void doThis();
	void is_in();
	void accept(EVENT e);
	virtual void* runProcessCircumference(void);
	void addTransition(Transition* t);
	virtual void display();
	virtual void setUnits(int iD, void(*callbackfunc)(int), void(*callbackfunc2)(int),bool (*callbackfunc3)(void));
};


#endif /* SETCIRCUMFERENCE_H_ */
