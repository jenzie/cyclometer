/*
 * ClaculationState.cpp
 *
 *  Created on: May 15, 2014
 *      Author: nmc2484
 */

#include "CalculationState.h"
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
pthread_t csio;
pthread_t cs2io;
#define IO_PORT_SIZE 1
bool display;
#define CTRLCB_ADDRESS 0x289
#define CTRLCA_ADDRESS 0x288
#define CTRLCC_ADDRESS 0x28a
#define CYCLE_MASK 0b00010000
float cycleCount =0;
float prevCycleCount =0;
float speed =0;
int avSpeed;
bool calculate = false;
bool manual = true;
bool khm = true;
int circumference;
uintptr_t ctrlCBHandle;
uintptr_t ctrlCAHandle;
uintptr_t ctrlCCHandle;
uint8_t cycles;

CalculationState::CalculationState() {
	// TODO Auto-generated constructor stub

}

CalculationState::~CalculationState() {
	// TODO Auto-generated destructor stub
}

void* calculationStateHelper(void* args){
	return static_cast<CalculationState*>(args)->runCProcess();
}

void* CalculationStateSpeedHelper(void* args){
	return static_cast<CalculationState*>(args)->runProcessSpeed();
}

void CalculationState::setUnits(int iD, void(*callbackfunc)(int),void (*callbackfunc2)(int),int (*callbackfunc3)(void),bool (*callbackfunc4)(void)){
	this->createCallback = callbackfunc;
	this->createCallback2 = callbackfunc2;
	this->createCallback3 = callbackfunc3;
	this->createCallback4 = callbackfunc4;
	this->myID =iD;
	pthread_create(&csio, NULL, &calculationStateHelper, this);
	pthread_create(&cs2io, NULL, &CalculationStateSpeedHelper, this);

}

void CalculationState::entry(){
	createCallback(myID);
	circumference = createCallback3();
	khm =createCallback4();
	display = true;
	calculate = true;
	printf("entered the calc state circumference is %d \n",circumference );
	printf("entered the calc state khm is %d \n",khm );
}
void CalculationState::exit(){
	display = false;
	createCallback2(myID);

}
void CalculationState::doThis(){}
void CalculationState::is_in(){}
void CalculationState::accept(EVENT e){

	if (transVector[0]->checkAccept(myID, e)){
		printf("mode button hit check accept true \n");
		exit();
		transVector[0]->accept(myID, e);
	}
	else{
		printf("failed!");
	}

}

void CalculationState::addTransition(Transition* e){
	transVector.push_back(e);
}

int CalculationState::getID(){
	return myID;
}


void* CalculationState::runCProcess(void){
	if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1)
			{

			perror("Failed to get I/O access permission");
			//return 1;
			}
		ctrlCBHandle = mmap_device_io(IO_PORT_SIZE, CTRLCB_ADDRESS);
		ctrlCAHandle = mmap_device_io(IO_PORT_SIZE, CTRLCA_ADDRESS);
		ctrlCCHandle = mmap_device_io(IO_PORT_SIZE, CTRLCC_ADDRESS);
	while (true){
		cycles = in8(ctrlCAHandle);
		if(display){
			//usleep(500);
			if(cycles & CYCLE_MASK){
				//printf("cycling \n");
				sleep(1);
				cycleCount++;
				//printf("cyleCount is %d \n",cycleCount);
			}else{
				//printf("no cycling \n");
				sleep(.5);
			}
		}else{
			//printf("no display \n");
			sleep(.5);
		}
	}
	return NULL;
}


void* CalculationState::runProcessSpeed(void){
	while(true){
			if(calculate){
				int curr = cycleCount - prevCycleCount;
				if (curr!=0){
					if(khm){
						printf("calc khm \n");
						speed = (float)circumference / 100000;
						speed = speed * (float)curr * 3600;

					}else{
						printf("calc mph \n");
						speed = (circumference/100000) *( curr*3600);
						speed = speed * .621371192;
					}
				}
				prevCycleCount=cycleCount;
				printf("the speed is %f \n", speed);
				sleep(2);
			}else{
				sleep(.5);
			}
		}
	return NULL;
}

void* CalculationState::runProcessTime(void){return NULL;}
void* CalculationState::runProcessDistance(void){return NULL;}






