/*
 * CyclometerIterator.cpp
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#include "CyclometerIterator.h"
std::vector<StateNode*> states;
int currentState;

CyclometerIterator::CyclometerIterator() {

}

CyclometerIterator::~CyclometerIterator() {
	// TODO Auto-generated destructor stub
}



void CyclometerIterator::addState(StateNode* node){
	printf(" adding %d \n", node->getID());
	states.push_back(node);

}

void CyclometerIterator::updateCurrentState(int stateID){
	printf("update state on itor \n");
	currentState = stateID;
	CyclometerIterator::enterState(currentState);
	printf("the current state is %d \n ", currentState);
}

void CyclometerIterator::accept(EVENT a){
	printf("real state %d \n", currentState);
	printf("state %d \n", (StateNode*)(states.at(currentState))->getID());
	//printf("state %d \n", states.at(currentState)->getID());
	printf("state size %d \n", states.size());
	//printf("accept on itor \n");
	//printf("state %d", states.at(1)->getID());
	//printf("state %d", states[currentState]->getID());
	states.at(currentState)->accept(a);
}

void CyclometerIterator::enterState(int stateID){
	states.at(stateID)->entry();
}
