/*
 * Cyclometer.cc
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */
 
#include <cstdlib>
#include <iostream>
#include "CyclometerIterator.h"
#include "CyclometerContext.h"
#include "Enums.h"
#include <stdint.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <unistd.h>
#include <math.h>

#define IO_PORT_SIZE 1
#define CTRLA_ADDRESS 0x288
#define CTRLB_ADDRESS 0x289
#define DIR_ADDRESS 0x28b
#define MODE_BUTTON_MASK 0b00000001
#define SET_BUTTON_MASK  0b00000010
#define STARTSTOP_BUTTON_MASK 0b00000100
#define SET_STARTSTOP_BUTTON_MASK 0b00000110
#define SET_STARTSTOP_MODE_BUTTON_MASK 0b00000111
#define RESET_MASK 0b00000000
#define REESET_MASK 0b11111111

uint8_t dirControl = 0b11110000;
pthread_t cio;
uintptr_t ctrlCHandle;
uintptr_t ctrlBHandle;
uintptr_t ctrlAHandle;
uintptr_t dirHandle;

uint8_t Ccurrent;
uint8_t CBcurrent;
uint8_t Mcurrent;
uint8_t Bcurrent;
CyclometerIterator theItor;
CyclometerContext* myContext1;


void* runProcess(void*){
	//printf("bhandle \n");
	if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1)
		{

		perror("Failed to get I/O access permission");
		//return 1;
		}
	dirHandle = mmap_device_io(IO_PORT_SIZE, DIR_ADDRESS);
	ctrlBHandle = mmap_device_io(IO_PORT_SIZE, CTRLB_ADDRESS);
	ctrlAHandle = mmap_device_io(IO_PORT_SIZE, CTRLA_ADDRESS);
	out8(dirHandle, dirControl);
	//out8(ctrlBHandle, RESET_MASK);
	//Bcurrent = in8(ctrlBHandle);
    //printf("bhandle %d \n", Bcurrent);
	//out8(ctrlBHandle, RESET_MASK);
	struct timespec msim;
	msim.tv_sec = 0;
	msim.tv_nsec = 500000000;

	while (true){

	Mcurrent = in8(ctrlAHandle);

	Bcurrent = Mcurrent;
	if(Mcurrent & MODE_BUTTON_MASK || Mcurrent & SET_BUTTON_MASK || Mcurrent & STARTSTOP_BUTTON_MASK){
		//printf("got it \n");
		usleep(800);
		Mcurrent = in8(ctrlAHandle);
		if((Mcurrent & MODE_BUTTON_MASK) && (Mcurrent & STARTSTOP_BUTTON_MASK)){
			sleep(1);
			Mcurrent = in8(ctrlAHandle);
			if((Mcurrent & SET_BUTTON_MASK)&&(Mcurrent & MODE_BUTTON_MASK)&&(Mcurrent & STARTSTOP_BUTTON_MASK)){
				sleep(1);
				myContext1->accept(SETSTARTSTOPMODEBUTTONPRESS);
			}else{
				myContext1->accept(STARTSTOPANDMODEBUTTONPRESS);
			}
		}else{
			//printf(" just a button \n");
			if(Bcurrent & MODE_BUTTON_MASK){
				myContext1->accept(MODEBUTTONPRESS);
			printf("got a mode button press \n");
			}else if(Bcurrent & SET_BUTTON_MASK ){
				myContext1->accept(SETBUTTONPRESS);
				//printf("got a set button \n");
			}else if(Bcurrent & STARTSTOP_BUTTON_MASK){
				myContext1->accept(STARTSTOPBUTTONPRESS);
				//printf("got a start stop button \n");
			}
			sleep(1);
		}

	}else{
		usleep(100);
	}



/*

	if(Mcurrent & MODE_BUTTON_MASK){
		Mcurrent = in8(ctrlAHandle);
		//usleep(200);
		if(Mcurrent & SET_BUTTON_MASK && Mcurrent & STARTSTOP_BUTTON_MASK){
			//myContext1->accept(SETSTARTSTOPMODEBUTTONPRESS);
			printf("works 1 \n");
		}
		else if((Mcurrent & MODE_BUTTON_MASK) &&(Mcurrent & STARTSTOP_BUTTON_MASK) ){
			//myContext1->accept(STARTSTOPANDMODEBUTTONPRESS);
			printf("works 2 \n");
		}
		else if(Mcurrent & MODE_BUTTON_MASK){
			sleep(1);
			myContext1->accept(MODEBUTTONPRESS);
		}
		else{
			//printf("mode button from cylclo \n");
			myContext1->accept(MODEBUTTONPRESS);
			//sleep(1);

		}

	}

	else if(Mcurrent & SET_BUTTON_MASK){
		Mcurrent = in8(ctrlAHandle);
		//Mcurrent = in8(ctrlAHandle);
		if(Mcurrent & MODE_BUTTON_MASK && Mcurrent & STARTSTOP_BUTTON_MASK){
			//myContext1->accept(SETSTARTSTOPMODEBUTTONPRESS);
			printf("works 3 \n");
		}else{
		//printf("set button from cylclo \n");
			myContext1->accept(SETBUTTONPRESS);
			sleep(1);
		}
	}

	else if (Mcurrent & STARTSTOP_BUTTON_MASK){
		Mcurrent = in8(ctrlAHandle);
		//Mcurrent = in8(ctrlAHandle);
		if(Mcurrent & MODE_BUTTON_MASK && Mcurrent & SET_BUTTON_MASK ){
			//myContext1->accept(SETSTARTSTOPMODEBUTTONPRESS);
			printf("works 4 \n");
		}
		else if((Mcurrent & STARTSTOP_BUTTON_MASK)&&(Mcurrent & MODE_BUTTON_MASK)){
			//myContext1->accept(STARTSTOPANDMODEBUTTONPRESS);
			printf("works 5 \n");
		}else{
			myContext1->accept(STARTSTOPBUTTONPRESS);
			sleep(1);
		}
	}

*/
	//printf("slept \n");
	}
	sleep (1);
	return NULL;
}


int main(int argc, char *argv[]) {
	pthread_create(&cio, NULL, &runProcess, NULL);
	printf("starting123 \n");
	theItor = CyclometerIterator();
	myContext1 = new CyclometerContext(theItor);
	/*
	sleep(2);
	myContext1->accept(SETBUTTONPRESS);
	sleep(2);
	myContext1->accept(SETBUTTONPRESS);
	sleep(2);
	myContext1->accept(MODEBUTTONPRESS);
	sleep(2);
	myContext1->accept(STARTSTOPBUTTONPRESS);
	sleep(2);
	myContext1->accept(MODEBUTTONPRESS);
	*/
	sleep(200000000);


	int x = 0;
    while(true){
        x++;
        x--;
    }




}


