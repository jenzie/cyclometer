/*
 * Transition.h
 *
 *  Created on: May 6, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "Enums.h"
#include "CyclometerIterator.h"

class Transition {

public:

	virtual bool checkAccept(int stateIndex, EVENT ev) = 0;

	virtual void accept(int stateIndex, EVENT ev) = 0;

	virtual void setUnits(CyclometerIterator myIterator) = 0;
};

#endif /* TRANSITION_H_ */
