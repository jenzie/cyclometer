/*
 * ClaculationState.cpp
 *
 *  Created on: May 15, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#include "CalculationState.h"
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <math.h>

pthread_t csio;
pthread_t cs2io;
pthread_t cs3io;
pthread_t cs4io;
pthread_t cs5io;

#define IO_PORT_SIZE 1
volatile bool display;
#define CTRLCB_ADDRESS 0x289
#define CTRLCA_ADDRESS 0x288
#define CTRLCC_ADDRESS 0x28a
#define CYCLE_MASK 0b00010000
#define SHOW_RIGHT_MASK 0b11111110
#define SHOW_MID_MASK   0b11111101
#define SHOW_LEFT_MASK  0b11111011
#define SHOW_FAR_LEFT_MASK 0b11110111
int cycleCount =0;
int prevCycleCount =0;
float speed =0.0;
float avSpeed =0.0;
volatile bool calculate = false;
bool manual = true;
bool khm = true;
int circumference;
float distanceTraveled = 0.0;
float prevDistance = 0.0;
float prevTime = 0.0;
StateNode *currDisplay;
DisplaySpeed displaySpeeder;
DisplayTime displayTimer;
DisplayDistance displayDistancer;



int elapsedSeconds =0;
int elapsedMinuets=0;



volatile bool displaySpeed = false;
volatile bool displayTime =false;
volatile bool displayDistance =false;
volatile bool changed= false;

volatile int gotCycle =0;
int rCycle=0;

float prevAvSpeed =0.0;

int a;
int b;
int c;
int d;

volatile int stoped = 0;
volatile bool cycling= false;

uintptr_t ctrlCBHandle;
uintptr_t ctrlCAHandle;
uintptr_t ctrlCCHandle;
uint8_t cycles;
uint8_t distanceCycles;



CalculationState::CalculationState() {
	// TODO Auto-generated constructor stub
	ctrlCBHandle = mmap_device_io(IO_PORT_SIZE, CTRLCB_ADDRESS);
	ctrlCCHandle = mmap_device_io(IO_PORT_SIZE, CTRLCC_ADDRESS);

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
void* calculationStateTimeHelper(void* args){
	return static_cast<CalculationState*>(args)->runProcessTime();
}
void* calculationStateLED(void* args){
	return static_cast<CalculationState*>(args)->blinkLED();
}
void* calculationCycleLED(void* args){
	return static_cast<CalculationState*>(args)->cycleLED();
}


void CalculationState::setUnits(int iD, void(*callbackfunc)(int),void (*callbackfunc2)(int),int (*callbackfunc3)(void),bool (*callbackfunc4)(void)){
	this->createCallback = callbackfunc;
	this->createCallback2 = callbackfunc2;
	this->createCallback3 = callbackfunc3;
	this->createCallback4 = callbackfunc4;
	this->myID =iD;
	pthread_create(&csio, NULL, &calculationStateHelper, this);
	pthread_create(&cs2io, NULL, &CalculationStateSpeedHelper, this);
	pthread_create(&cs3io, NULL, &calculationStateTimeHelper, this);
	//pthread_create(&cs4io, NULL, &calculationStateLED, this);
	pthread_create(&cs5io, NULL, &calculationCycleLED, this);


}

void CalculationState::entry(){
	createCallback(myID);
	circumference = createCallback3();
	khm =createCallback4();
	modeSwitch(0);
	display = true;
}
void CalculationState::exit(){
	display = false;
	displayTimer.stopThread();
	displayDistancer.stopThread();
	displaySpeeder.stopThread();
	createCallback2(myID);

}
void CalculationState::doThis(){}
void CalculationState::is_in(){}
void CalculationState::accept(EVENT e){
	if(e == STARTSTOPBUTTONPRESS){
		if(manual == true){
			if(calculate){
				calculate = false;
			}else {
				calculate = true;
			}
		}
	}
	else if(e == MODEBUTTONPRESS){
		modeSwitch(1);
	}

	else if(e == SETBUTTONPRESS){
		if(displayDistance == true ){
			if (transVector[0]->checkAccept(myID, e)){
				exit();
				transVector[0]->accept(myID, e);
			}
		}else{
			if (manual){
				manual = false;
				calculate = true;
			}else{
				manual = true;
			}
		}
	}
	else if (transVector[0]->checkAccept(myID, e)){
		if(e == STARTSTOPANDMODEBUTTONPRESS || SETSTARTSTOPMODEBUTTONPRESS){
			if(e == SETSTARTSTOPMODEBUTTONPRESS){
				displaySpeed = false;
				displayTime =false;
				displayDistance =false;
				resetValues();
			}else{
			resetValues();
			modeSwitch(0);
			}
		}
		//printf("mode button hit check accept true \n");
		exit();
		transVector[0]->accept(myID, e);
	}
	else{
		printf("failed! \n");
	}

}

void* CalculationState::cycleLED(void){
	if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1)
		{

		perror("Failed to get I/O access permission");
		//return 1;
		}
	struct timespec sctsim;
	sctsim.tv_sec = 0;
	sctsim.tv_nsec = 500000000;
	while(1){
		if(cycling){
			//nanosleep(&sctsim, NULL);
			usleep(500000);
		    uint8_t handle1 = in8(ctrlCCHandle);
			//printf("%p\n",handle1);
			out8(ctrlCCHandle, (handle1  & 0b11011111));
			//nanosleep(&sctsim, NULL);
			usleep(500000);
			handle1 = in8(ctrlCCHandle);
			//printf("%p \n",handle2);
			out8(ctrlCCHandle, (handle1 | 0b00100000));
		}else {
			sleep(1);
		}

	}


}

void* CalculationState::blinkLED(void){
	struct timespec cctsim;
	cctsim.tv_sec = 0;
	cctsim.tv_nsec = 500000000;
	while(1){
		if(display== true){
			if(manual== true){
				if(calculate == true){
					nanosleep(&cctsim, NULL);
					uint8_t handle3 = in8(ctrlCCHandle);
					out8(ctrlCCHandle, (handle3 | 0b00010000));
					nanosleep(&cctsim, NULL);
					uint8_t handle4 = in8(ctrlCCHandle);
					out8(ctrlCCHandle, (handle4 | 0b00000000));
				}else{
					uint8_t handle5 = in8(ctrlCCHandle);
					out8(ctrlCCHandle,(handle5 & 0b11101111));
				}
				}else{
					nanosleep(&cctsim, NULL);
					uint8_t handle6 = in8(ctrlCCHandle);
					out8(ctrlCCHandle, (handle6 | 0b00010000));
					nanosleep(&cctsim, NULL);
					uint8_t handle7 = in8(ctrlCCHandle);
					out8(ctrlCCHandle, (handle7 | 0b00000000));
				}
			}else{
				sleep(1);
			}
		}
	return NULL;
	}

void CalculationState::addTransition(Transition* e){
	transVector.push_back(e);
}

int CalculationState::getID(){
	return myID;
}

void CalculationState::modeSwitch(int switcher){
	if(switcher == 1){
		if(displaySpeed){
			displaySpeed = false;
			displaySpeeder.stopThread();
			displayTime = true;
			displayTimer.startThread();

		}
		else if(displayTime){
			displayTime = false;
			displayTimer.stopThread();
			displayDistance = true;
			displayDistancer.startThread();

		}
		else{
			displayDistance = false;
			displayDistancer.stopThread();
			displaySpeed = true;
			displaySpeeder.startThread();

		}
	}else if (switcher == 0){
		if(displaySpeed == false && displayDistance == false && displayTime==false){
			displaySpeeder.startThread();
			displaySpeed = true;
		}else if(displayDistance == true){
			displayDistancer.startThread();
		}else if(displayTime==true){
			displayTimer.startThread();
		}else{
			displaySpeeder.startThread();
		}
	}else{
		return;
	}
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

		struct timespec ctsim;
		ctsim.tv_sec = 0;
		ctsim.tv_nsec = 10;

	while (true){
		cycles = in8(ctrlCAHandle);
		//if(display){
			if(gotCycle==0 && (cycles & CYCLE_MASK)){
					gotCycle++;
					cycleCount++;
					cycling = true;
					if(calculate){
						distanceTraveled =  distanceTraveled + (speed * ((((float)elapsedMinuets*2) + (float)elapsedSeconds)/3600.0));

						avSpeed = (avSpeed * ((float) cycleCount / ((float)cycleCount + 1))) + (speed * ( 1 / ((float)cycleCount+1)));

					}
			}else if( gotCycle == 1 && !(cycles & CYCLE_MASK)){
						gotCycle--;
					}
			else{
				nanosleep(&ctsim, NULL);
				}
		//}
		//else{
		//	nanosleep(&ctsim, NULL);
		//			}
				}

	return NULL;
}




void* CalculationState::runProcessSpeed(void){
	while(true){
				int curr = cycleCount - prevCycleCount;
				if (curr!=0){
					stoped = 0;
					speed = (float)circumference / 100000;
					speed = speed * (float)curr * 3600;
					if(khm){
					}else{
						speed = speed * .621371192;
						avSpeed = avSpeed * .621371192;
					}
					displaySpeeder.updateSpeed(speed,avSpeed);
					displayDistancer.updateDistance(distanceTraveled);
				}else{
					stoped++;
					if(stoped == 2){
						cycling = false;
						displaySpeeder.updateSpeed(0.0,0.0);
					}
				}
				prevCycleCount=cycleCount;
				sleep(1);

		}
	return NULL;
}

void* CalculationState::runProcessTime(void){
	while(true){
		if(calculate == true){
			if(cycling == true){
				sleep(1);
				if (elapsedSeconds==59){
					elapsedSeconds = 0;
					elapsedMinuets++;
				}else{
					elapsedSeconds++;
				}
				displayTimer.updateTime(elapsedMinuets,elapsedSeconds);
				//printf("minuets.seconds %d . %d \n",elapsedMinuets,elapsedSeconds);
			}}else{
			sleep(.5);
		}
	}

	return NULL;}

void CalculationState::resetValues(){
	elapsedSeconds =0;
	elapsedMinuets=0;
	cycleCount =0;
	prevCycleCount =0;
	speed =0;
	avSpeed =0;
	distanceTraveled = 0;
	exit();

}








