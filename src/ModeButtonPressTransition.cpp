/*
 * ModeButtonPressTransition.cpp
 *
 *  Created on: May 6, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
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
	if(ev == SETSTARTSTOPMODEBUTTONPRESS){
		return true;
	}
	else if (stateIndex == 0 && ev == MODEBUTTONPRESS){
		return true;
	}
	else if (stateIndex == 0 && ev == SETBUTTONPRESS){
		return true;
	}

	else if (stateIndex == 1 && ev == MODEBUTTONPRESS){
		return true;
	}
	else if (stateIndex == 1 && ev == SETBUTTONPRESS){
		return true;
	}
	else if (stateIndex == 2 && ev == MODEBUTTONPRESS){
		return true;
	}
	else if (stateIndex == 2 && ev == SETBUTTONPRESS){
		return true;
	}
	else if (stateIndex == 2 && ev == STARTSTOPANDMODEBUTTONPRESS){
		return true;
	}

	return false;

}

// Accepts the transition, calls the state iterator entry function with the
// state id to go to.
void ModeButtonPressTransition::accept(int stateIndex, EVENT ev){
	if (ev == SETSTARTSTOPMODEBUTTONPRESS ){
		myItor.updateCurrentState(0);
	}
	else if (stateIndex == 0 && ev == MODEBUTTONPRESS){
		//printf("wrong 1 one %d \n",stateIndex);
		//printf("wrong 1 one \n");
		myItor.updateCurrentState(0);
	}
	else if (stateIndex == 0 && ev == SETBUTTONPRESS){
		//printf("wrong 2 one \n");
		myItor.updateCurrentState(1);
	}
	else if (stateIndex == 1 && ev == MODEBUTTONPRESS){
		//printf("correct one \n");
		myItor.updateCurrentState(1);
	}
	else if (stateIndex == 1 && ev == SETBUTTONPRESS){
		//printf("correct one \n");
		myItor.updateCurrentState(2);
	}
	else if (stateIndex == 2 && ev == MODEBUTTONPRESS){
		//printf("correct one \n");
		myItor.updateCurrentState(2);
	}
	else if (stateIndex == 2 && ev == SETBUTTONPRESS){
		//printf("correct one \n");
		myItor.updateCurrentState(1);
	}
	else if (stateIndex == 2 && ev == STARTSTOPANDMODEBUTTONPRESS){
		//printf("correct one \n");
		myItor.updateCurrentState(2);
	}

}

void ModeButtonPressTransition::setUnits(CyclometerIterator myIterator){
	this->myItor = myIterator;
}

