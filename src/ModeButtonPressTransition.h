/*
 * ModeButtonPressTransition.h
 *
 *  Created on: May 6, 2014
 *      Author: nmc2484
 */

#ifndef MODEBUTTONPRESSTRANSITION_H_
#define MODEBUTTONPRESSTRANSITION_H_

#include "Transition.h"
#include "Enums.h"

class ModeButtonPressTransition {
public:
	ModeButtonPressTransition();
	virtual ~ModeButtonPressTransition();

	bool checkAccept(StateNode node, EVENT ev);

	void accept(EVENT ev);

	//void guard();




};

#endif /* MODEBUTTONPRESSTRANSITION_H_ */
