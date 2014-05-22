/*
 * DisplaySpeed.cpp
 *
 *  Created on: May 18, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#include "DisplaySpeed.h"


#define SHOW_RIGHT_MASK 0b11111110
#define SHOW_MID_MASK   0b11111101
#define SHOW_LEFT_MASK  0b11111011
#define SHOW_FAR_LEFT_MASK 0b11110111

#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <math.h>

uintptr_t ctrlDCHandle;
uintptr_t ctrlDBHandle;
#define IO_PORT_SIZE 1
pthread_t dsio;

#define CTRLDB_ADDRESS 0x289
#define CTRLDA_ADDRESS 0x288
#define CTRLDC_ADDRESS 0x28a
int czero = 0b11000000;
int *czp = &czero;

int cone = 0b11111001;
int *cop = &cone;

int ctwo =0b10100100;
int *ctp = &ctwo;

int cthree= 0b10110000;
int *cthp = &cthree;

int cfour =0b10011001;
int *cfp = &cfour;

int cfive =0b10010010;
int *cfip = &cfive;

int csix =0b10000011;
int *csp = &csix;

int cseven =0b11111000;
int *csep = &cseven;

int ceight =0b10000000;
int *cep = &ceight;

int cnine =0b10011000;
int *cnp = &cnine;

int cdot  =0b01111111;

int cndot =0b11111111;

int *dotpointer = &cndot;
int *sdotpointer = &cndot;



int *Svalues[10]={czp,cop,ctp,cthp,cfp,cfip,csp,csep,cep,cnp};

int aa;
int bb;
int cc;
int dd;

void* calculationStateDisplayHelper(void* args){
	return static_cast<DisplaySpeed*>(args)->runProcessDisplay();
}

DisplaySpeed::DisplaySpeed() {
	// TODO Auto-generated constructor stub


}

DisplaySpeed::~DisplaySpeed() {

}

void DisplaySpeed::startThread(){
	ctrlDBHandle = mmap_device_io(IO_PORT_SIZE, CTRLDB_ADDRESS);
	ctrlDCHandle = mmap_device_io(IO_PORT_SIZE, CTRLDC_ADDRESS);
	pthread_create(&dsio, NULL, &calculationStateDisplayHelper, this);
}

void* DisplaySpeed::runProcessDisplay(void){
	struct timespec tsim;
	tsim.tv_sec = 0;
	tsim.tv_nsec = 1000000;
	while(1){
			//usleep(11);
			out8(ctrlDCHandle, SHOW_RIGHT_MASK);
			out8(ctrlDBHandle, *Svalues[aa]);

			nanosleep(&tsim, NULL);

			out8(ctrlDCHandle, SHOW_MID_MASK);
			out8(ctrlDBHandle, *Svalues[bb] & *dotpointer);
			//out8(ctrlCCHandle, 0b11111111);
			nanosleep(&tsim, NULL);


			//printf("the first speed %d \n", c);

			out8(ctrlDCHandle, SHOW_LEFT_MASK);
			out8(ctrlDBHandle, *Svalues[cc]);

			nanosleep(&tsim, NULL);

			//printf("the second speed %d \n", d);
			out8(ctrlDCHandle,SHOW_FAR_LEFT_MASK);
			out8(ctrlDBHandle, *Svalues[dd]& *sdotpointer);
			nanosleep(&tsim, NULL);
	}
	return NULL;}


void DisplaySpeed::updateSpeed(float speed, float avSpeed){
	if (avSpeed < 10.0){
		aa = floor(fmod((avSpeed*10),10));
		bb = floor(avSpeed);
		dotpointer = &cdot;
	}else{
		aa =  fmod(avSpeed,10);
		bb = floor(avSpeed /10);
		dotpointer = &cndot;
	}
	if (speed < 10.0){
		cc = floor(fmod((speed*10) , 10));
		dd = floor(speed);
		sdotpointer = &cdot;
	}else{
		cc = fmod(speed,10);
		dd = floor(speed /10);
		sdotpointer = &cndot;
	}

}

void DisplaySpeed::stopThread(){
	pthread_cancel(dsio);
}





