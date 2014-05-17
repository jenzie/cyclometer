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

	while (true){
	Mcurrent = in8(ctrlAHandle);
	//Bcurrent = in8(ctrlBHandle);
	//printf("bhandle %d", Bcurrent);
	/*
	if(Mcurrent & MODE_BUTTON_MASK){
		printf("mode button from cylclo \n");
		myContext1->accept(MODEBUTTONPRESS);
		sleep(1);

	}
	*/
	if(Mcurrent & MODE_BUTTON_MASK){
		sleep(1);
		if(Mcurrent & MODE_BUTTON_MASK){
			myContext1->accept(MODEBUTTONPRESS);
		}
		else{
			printf("mode button from cylclo \n");
			myContext1->accept(MODEBUTTONPRESS);
			//sleep(1);

		}

	}
	if(Mcurrent & SET_BUTTON_MASK){
		printf("set button from cylclo \n");
		myContext1->accept(SETBUTTONPRESS);
		sleep(1);
	}

	//printf("slept \n");
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_create(&cio, NULL, &runProcess, NULL);
	printf("starting123 \n");
	theItor = CyclometerIterator();
	myContext1 = new CyclometerContext(theItor);


	int x = 0;
    while(true){
        x++;
        x--;
    }




}


