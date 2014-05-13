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
#include "StateNode.h"
#include "CyclometerIterator.h"

class ModeButtonPressTransition: public Transition {
private:
	CyclometerIterator myItor;
public:
	ModeButtonPressTransition();
	virtual ~ModeButtonPressTransition();

	bool checkAccept(int stateIndex, EVENT ev);

	void accept(int stateIndex, EVENT ev);

	void setUnits(CyclometerIterator myIterator);


	//void guard();




};

#endif /* MODEBUTTONPRESSTRANSITION_H_ */
