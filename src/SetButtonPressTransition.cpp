/*
 * StateButtonPressTransition.cpp
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 */

#include "SetButtonPressTransition.h"

SetButtonPressTransition::SetButtonPressTransition() {
	// TODO Auto-generated constructor stub

}

SetButtonPressTransition::~SetButtonPressTransition() {
	// TODO Auto-generated destructor stub
}

// Checks the state node and event to see if the transition is possible or no.
bool SetButtonPressTransition::checkAccept(int stateIndex, EVENT ev){

}

// Accepts the transition, calls the state iterator entry function with the
// state id to go to.
void SetButtonPressTransition::accept(int stateIndex, EVENT ev){
	//this->myItor = myIterator;
}


void SetButtonPressTransition::setUnits(CyclometerIterator myIterator){

}
