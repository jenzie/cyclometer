/*
 * CyclometerContext.cpp
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 */

#include "CyclometerContext.h"


#include <stdint.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <unistd.h>


bool cyclokMH;
int cycloCircumference;
bool cyclomanual;
bool cyclocalculations;


void* cyclometerHelper(void* args){
	return static_cast<CyclometerContext*>(args)->runProcess();
}

void entryAction(int stateIndex){
	printf("entryActionHit \n");

}


void exitAction(int stateIndex){
	printf("exitActionHit \n");

}

void exitActionSetUnits(bool speedUnits){
	printf(" should be true %d \n",speedUnits );
	cyclokMH = speedUnits;

}

void exitActionSetCirc(int circ){
	printf("context recived circ %d \n", circ);
	cycloCircumference = circ;

}

int getCirc(){
	printf("context cric is %d \n", cycloCircumference);
	return cycloCircumference;
}

bool getKHM(){
	printf(" should give true %d \n", cyclokMH );
	return cyclokMH;
}
bool getManual(){
	return cyclomanual;
}
bool getCalculations(){
	return cyclocalculations;
}

void* CyclometerContext::runProcess(void){
	while(true){
		sleep(.5);

	}

}


CyclometerContext::CyclometerContext(CyclometerIterator myIterator) {

	modeButton.setUnits(myIterator);
	setUnitsKMKH.setUnits(0,entryAction, exitActionSetUnits);
	setUnitsDistance.setUnits(1,entryAction, exitActionSetCirc);
	calculateState.setUnits(2,entryAction, exitAction, getCirc, getKHM);
	this->setButton= SetButtonPressTransition();
	this->theIterator = myIterator;
	setUnitsKMKH.addTransition(&modeButton);
	setUnitsDistance.addTransition(&modeButton);
	calculateState.addTransition(&modeButton);
	theIterator.addState(&setUnitsKMKH);
	theIterator.addState(&setUnitsDistance);
	theIterator.addState(&calculateState);
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










