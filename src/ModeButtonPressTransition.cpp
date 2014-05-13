/*
 * ModeButtonPressTransition.cpp
 *
 *  Created on: May 6, 2014
 *      Author: nmc2484
 */

#include "ModeButtonPressTransition.h"

ModeButtonPressTransition::ModeButtonPressTransition() {
	// TODO Auto-generated constructor stub

}

ModeButtonPressTransition::~ModeButtonPressTransition() {
	// TODO Auto-generated destructor stub
}

// Checks the state node and event to see if the transition is possible or no.
bool ModeButtonPressTransition::checkAccept(int stateIndex, EVENT ev){
	if( stateIndex == 0 || ev == 0){
		return true;
	}

	return false;

}

// Accepts the transition, calls the state iterator entry function with the
// state id to go to.
void ModeButtonPressTransition::accept(int stateIndex, EVENT ev){
	if( stateIndex == 0 || ev == 0){
		myItor.updateCurrentState(1);
	}

}

void ModeButtonPressTransition::setUnits(CyclometerIterator myIterator){
	this->myItor = myIterator;
}

