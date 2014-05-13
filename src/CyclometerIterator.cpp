/*
 * CyclometerIterator.cpp
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 */

#include "CyclometerIterator.h"

CyclometerIterator::CyclometerIterator() {
	// TODO Auto-generated constructor stub

}

CyclometerIterator::~CyclometerIterator() {
	// TODO Auto-generated destructor stub
}



void CyclometerIterator::addState(StateNode* node){
	printf(" adding %d \n", node->getID());
	this->states.push_back(node);
	printf(" stop ");

}

void CyclometerIterator::updateCurrentState(int stateID){
	printf("update state on itor \n");
	this->currentState = stateID;
	printf("the current state is %d \n ", stateID);
}

void CyclometerIterator::accept(EVENT a){
	printf("state %d \n", (StateNode*)(states.at(currentState))->getID());
	//printf("state %d \n", states.at(currentState)->getID());
	printf("state size %d \n", states.size());
	//printf("accept on itor \n");
	//printf("state %d", states.at(1)->getID());
	//printf("state %d", states[currentState]->getID());
	states.at(currentState)->accept(a);
}
