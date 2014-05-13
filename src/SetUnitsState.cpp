/*
 * SetUnitsState.cpp
 *
 *  Created on: May 12, 2014
 *      Author: nmc2484
 */

#include "SetUnitsState.h"


SetUnitsState::SetUnitsState(){

	// TODO Auto-generated constructor stub

}

SetUnitsState::~SetUnitsState() {
	// TODO Auto-generated destructor stub
}

void SetUnitsState::setUnits(int iD, void(*callbackfunc)(int),void (*callbackfunc2)(int)){
	this->createCallback = callbackfunc;
	this->createCallback2 = callbackfunc2;
	this->myID =iD;

}

void SetUnitsState::entry(){
	createCallback(myID);
	printf("entered the setUnits state");
}
void SetUnitsState::exit(){
	createCallback2(myID);
}
void SetUnitsState::doThis(){}
void SetUnitsState::is_in(){}
void SetUnitsState::accept(EVENT e){
	printf("accept hit state \n");
	if (e == MODEBUTTONPRESS){
		printf("mode button hit \n");
		if(transVector[0]->checkAccept(myID,e)){
			printf("mode button hit check accept true \n");
			transVector[0]->accept(myID,e);
		}
	}

}

void SetUnitsState::addTransition(Transition* e){
	transVector.push_back(e);
}

int SetUnitsState::getID(){
	return myID;
}
