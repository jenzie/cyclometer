/*
 * DisplayTime.cpp
 *
 *  Created on: May 18, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#include "DisplayTime.h"

#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <math.h>

#define SHOW_RIGHT_MASK 0b11111110
#define SHOW_MID_MASK   0b11111101
#define SHOW_LEFT_MASK  0b11111011
#define SHOW_FAR_LEFT_MASK 0b11110111

uintptr_t ctrlTCHandle;
uintptr_t ctrlTBHandle;
#define IO_PORT_SIZE 1
pthread_t tsio;

#define CTRLTB_ADDRESS 0x289
#define CTRLTA_ADDRESS 0x288
#define CTRLTC_ADDRESS 0x28a

int tzero = 0b11000000;
int *tzp = &tzero;

int tone = 0b11111001;
int *top = &tone;

int ttwo =0b10100100;
int *ttp = &ttwo;

int tthree= 0b10110000;
int *tthp = &tthree;

int tfour =0b10011001;
int *tfp = &tfour;

int tfive =0b10010010;
int *tfip = &tfive;

int tsix =0b10000011;
int *tsp = &tsix;

int tseven =0b11111000;
int *tsep = &tseven;

int teight =0b10000000;
int *tep = &teight;

int tnine =0b10011000;
int *tnp = &tnine;

int tdot  =0b01111111;
int *tdt = &tdot;

int tnuller = 0b11111111;
int *tnu = &tnuller;


int *values[12]={tzp,top,ttp,tthp,tfp,tfip,tsp,tsep,tep,tnp,tdt,tnu};

int ta;
int tb;
int tc;
int td;


void* calculationStateDisplayTimeHelper(void* args){
	return static_cast<DisplayTime*>(args)->runProcessDisplayTime();
}

DisplayTime::DisplayTime() {
	// TODO Auto-generated constructor stub

}

DisplayTime::~DisplayTime() {
	// TODO Auto-generated destructor stub
}




void DisplayTime::startThread(){
	ctrlTBHandle = mmap_device_io(IO_PORT_SIZE, CTRLTB_ADDRESS);
	ctrlTCHandle = mmap_device_io(IO_PORT_SIZE, CTRLTC_ADDRESS);
	pthread_create(&tsio, NULL, &calculationStateDisplayTimeHelper, this);
}

void* DisplayTime::runProcessDisplayTime(void){
	struct timespec ttim;
	ttim.tv_sec = 0;
	ttim.tv_nsec = 1000000;
	while(1){

			out8(ctrlTCHandle, SHOW_RIGHT_MASK);
			out8(ctrlTBHandle, *values[ta]);
			nanosleep(&ttim, NULL);

			out8(ctrlTCHandle, SHOW_MID_MASK);
			out8(ctrlTBHandle, *values[tb]);
			//out8(ctrlCCHandle, 0b11111111);
			nanosleep(&ttim, NULL);


			//printf("the first speed %d \n", c);
			out8(ctrlTCHandle, SHOW_LEFT_MASK);
			out8(ctrlTBHandle, *values[tc] & 0b01111111 );
			nanosleep(&ttim, NULL);

			//printf("the second speed %d \n", d);
			out8(ctrlTCHandle, SHOW_FAR_LEFT_MASK);
			out8(ctrlTBHandle, *values[td]);
			nanosleep(&ttim, NULL);
	}
	return NULL;}


void DisplayTime::updateTime(int minutes,int seconds ){
		ta = seconds % 10;
		tb = floor(seconds /10);
		tc = minutes % 10;
		td = floor(minutes /10);


}

void DisplayTime::stopThread(){
	pthread_cancel(tsio);
}

