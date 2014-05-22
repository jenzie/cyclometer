/*
 * SetButtonPressTransition.h
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#ifndef SETBUTTONPRESSTRANSITION_H_
#define SETBUTTONPRESSTRANSITION_H_

#include "Transition.h"
#include "Enums.h"
#include "StateNode.h"
#include "CyclometerIterator.h"

class SetButtonPressTransition: public Transition {
public:
	SetButtonPressTransition();
	virtual ~SetButtonPressTransition();

	bool checkAccept(int stateIndex, EVENT ev);

	void accept(int stateIndex, EVENT ev);

	void setUnits(CyclometerIterator myIterator);


};

#endif /* SETBUTTONPRESSTRANSITION_H_ */
