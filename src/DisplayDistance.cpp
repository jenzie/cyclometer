/*
 * DisplayDistance.cpp
 *
 *  Created on: May 18, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#include "DisplayDistance.h"

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

uintptr_t ctrlDDCHandle;
uintptr_t ctrlDDBHandle;
#define IO_PORT_SIZE 1
pthread_t ddsio;

#define CTRLDDB_ADDRESS 0x289
#define CTRLDDA_ADDRESS 0x288
#define CTRLDDC_ADDRESS 0x28a

int dzero = 0b11000000;
int *dzp = &dzero;

int done = 0b11111001;
int *dop = &done;

int dtwo =0b10100100;
int *dtp = &dtwo;

int dthree= 0b10110000;
int *dthp = &dthree;

int dfour =0b10011001;
int *dfp = &dfour;

int dfive =0b10010010;
int *dfip = &dfive;

int dsix =0b10000011;
int *dsp = &dsix;

int dseven =0b11111000;
int *dsep = &dseven;

int deight =0b10000000;
int *dep = &deight;

int dnine =0b10011000;
int *dnp = &dnine;

int ddot  =0b01111111;
int *ddt = &ddot;

int nuller = 0b11111111;
int *nu = &nuller;


int *Dvalues[12]={dzp,dop,dtp,dthp,dfp,dfip,dsp,dsep,dep,dnp,ddt,nu};

int da;
int db;
int dc;
int ddd;

void* calculationStateDisplayDistanceHelper(void* args){
	return static_cast<DisplayDistance*>(args)->runProcessDisplayDistance();
}

DisplayDistance::DisplayDistance() {
	// TODO Auto-generated constructor stub

}

DisplayDistance::~DisplayDistance() {
	// TODO Auto-generated destructor stub
}




void DisplayDistance::startThread(){
	ctrlDDBHandle = mmap_device_io(IO_PORT_SIZE, CTRLDDB_ADDRESS);
	ctrlDDCHandle = mmap_device_io(IO_PORT_SIZE, CTRLDDC_ADDRESS);
	pthread_create(&ddsio, NULL, &calculationStateDisplayDistanceHelper, this);
}

void* DisplayDistance::runProcessDisplayDistance(void){
	struct timespec ddtim;
	ddtim.tv_sec = 0;
	ddtim.tv_nsec = 1000000;
	while(1){

			out8(ctrlDDCHandle, SHOW_RIGHT_MASK);
			out8(ctrlDDBHandle, *Dvalues[da]);

			nanosleep(&ddtim, NULL);

			out8(ctrlDDCHandle, SHOW_MID_MASK);
			out8(ctrlDDBHandle, *Dvalues[db] & 0b01111111);

			nanosleep(&ddtim, NULL);



			out8(ctrlDDCHandle, SHOW_LEFT_MASK);
			out8(ctrlDDBHandle, *Dvalues[dc]);

			nanosleep(&ddtim, NULL);


			out8(ctrlDDCHandle, SHOW_FAR_LEFT_MASK);
			out8(ctrlDDBHandle, *Dvalues[ddd]);
			nanosleep(&ddtim, NULL);
	}
	return NULL;}


void DisplayDistance::updateDistance(float distance){
	da = fmod((distance * 10),10);
	db = fmod((floor(distance)),10);
	dc = fmod((floor(distance/10)),10);
	ddd = fmod((floor(distance/100)),10);
	if(dc < 1 ){
		dc = 11;
	}
	if( ddd < 1){
		ddd = 11;
	}




}

void DisplayDistance::stopThread(){
	pthread_cancel(ddsio);
}

