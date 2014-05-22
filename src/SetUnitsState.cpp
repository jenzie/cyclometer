/*
 * SetUnitsState.cpp
 *
 *  Created on: May 12, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#include "SetUnitsState.h"
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
pthread_t io;
#define IO_PORT_SIZE 1
#define CTRLSB_ADDRESS 0x289
#define CTRLSA_ADDRESS 0x28a
#define ONE_MASK 0b11111001
#define TWO_MASK 0b10100100
#define SHOW_MASK       0b01111110
#define SHOW_MASK_TWO   0b11111110


uintptr_t ctrlSBHandle;
uintptr_t ctrlSAHandle;
uint8_t mask;



SetUnitsState::SetUnitsState(){

	// TODO Auto-generated constructor stub

}

SetUnitsState::~SetUnitsState() {
	// TODO Auto-generated destructor stub
}

void SetUnitsState::setUnits(int iD, void(*callbackfunc)(int),void (*callbackfunc2)(bool)){
	this->createCallback = callbackfunc;
	this->createCallback2 = callbackfunc2;
	this->myID =iD;
	//pthread_create(&io, NULL, &setUnitsHelper, this);

}

void SetUnitsState::entry(){
	display = true;
	doThis();
	createCallback(myID);
	printf("entered the setUnits state \n");
}
void SetUnitsState::exit(){
	display = false;
	createCallback2(khm);
}

void SetUnitsState::doThis(){
	if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1)
		{

		perror("Failed to get I/O access permission");
		//return 1;
		}
	ctrlSBHandle = mmap_device_io(IO_PORT_SIZE, CTRLSB_ADDRESS);
	ctrlSAHandle = mmap_device_io(IO_PORT_SIZE, CTRLSA_ADDRESS);
	if(!khm){
		khm = true;
		//mask = in8(ctrlSAHandle);
		//mask = mask | SHOW_REST_MASK;
		//mask = mask & SHOW_MASK;
		//in8(ctrlSAHandle);
		out8(ctrlSAHandle, SHOW_MASK);
		out8(ctrlSBHandle, ONE_MASK);

	}
	else {
		khm = false;
		//mask = in8(ctrlSAHandle);
		//mask = mask | SHOW_REST_MASK;
		//mask = mask & SHOW_MASK;
		out8(ctrlSAHandle, SHOW_MASK_TWO);
		out8(ctrlSBHandle, TWO_MASK);}
}


void SetUnitsState::is_in(){

}
void SetUnitsState::accept(EVENT e){

	if (transVector[0]->checkAccept(myID, e)){
		printf("mode button hit check accept true \n");
		exit();
		transVector[0]->accept(myID, e);
	}
	else{
		printf("failed!");
	}

}

void SetUnitsState::addTransition(Transition* e){
	transVector.push_back(e);
}

int SetUnitsState::getID(){
	return myID;
}


