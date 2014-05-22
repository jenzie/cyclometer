/*
 * CyclometerIterator.h
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#ifndef CYCLOMETERITERATOR_H_
#define CYCLOMETERITERATOR_H_

#define STATE_SETUNITS 0

#include <vector>
#include <queue>
#include "StateNode.h"
#include "Enums.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class CyclometerIterator {
private:
	
	int prevState;



public:
	CyclometerIterator();
	virtual ~CyclometerIterator();

	virtual void addState(StateNode* node);
	virtual void updateCurrentState(int stateID);
	virtual void accept(EVENT a);
	virtual void enterState(int stateID);
};

#endif /* CYCLOMETERITERATOR_H_ */
