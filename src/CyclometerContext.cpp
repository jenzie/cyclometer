/*
 * CyclometerContext.cpp
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 */

#include "CyclometerContext.h"

#define IO_PORT_SIZE 1
#define CTRLA_ADDRESS 0x288

#define IR_BEAM_MASK
#define OVERCURRENT_MASK
#define BUTTON_MASK
#define RESET_MASK

uintptr_t ctrlCHandle;

uint8_t Ccurrent;
uint8_t CBcurrent;

void* cyclometerHelper(void* args){
	return static_cast<CyclometerContext*>(args)->runProcess();
}

void entryAction(int stateIndex){
	printf("entryActionHit");

}

void exitAction(int stateIndex){

}

void* CyclometerContext::runProcess(void){

}


CyclometerContext::CyclometerContext(CyclometerIterator myIterator) {
	modeButton.setUnits(myIterator);
	setUnitsKMKH.setUnits(0,entryAction, exitAction);
	setUnitsDistance.setUnits(1,entryAction, exitAction);
	this->setButton= SetButtonPressTransition();
	this->theIterator = myIterator;
	setUnitsKMKH.addTransition(&modeButton);
	setUnitsDistance.addTransition(&modeButton);
	theIterator.addState(&setUnitsKMKH);
	theIterator.addState(&setUnitsDistance);
	theIterator.updateCurrentState(0);


   // pthread_create(&io, NULL, &cyclometerHelper, this);


}

CyclometerContext::~CyclometerContext() {
	// TODO Auto-generated destructor stub
}


void CyclometerContext::accept(EVENT e){
	printf("accept in context \n");
	theIterator.accept(e);
}










