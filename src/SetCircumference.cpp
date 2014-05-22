/*
 * SetCircumference.cpp
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#include "SetCircumference.h"
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <time.h>
#include <signal.h>
pthread_t scio;
#define IO_PORT_SIZE 1
#define CTRLSCB_ADDRESS 0x289
#define CTRLSCA_ADDRESS 0x28a
#define SHOW_RIGHT_MASK 0b11111110
#define SHOW_MID_MASK   0b11111101
#define SHOW_LEFT_MASK  0b11111011
#define RESET_MASK 0b11111111


uintptr_t ctrlSCBHandle;
uintptr_t ctrlSCAHandle;
uint8_t sCmask;
std::vector<int> circumferences;
int zero = 0b11000000;
int *zp = &zero;

int one = 0b11111001;
int *op = &one;

int two =0b10100100;
int *tp = &two;

int three= 0b10110000;
int *thp = &three;

int four =0b10011001;
int *fp = &four;

int five =0b10010010;
int *fip = &five;

int six =0b10000011;
int *sp = &six;

int seven =0b11111000;
int *sep = &seven;

int eight =0b10000000;
int *ep = &eight;

int nine =0b10011000;
int *np = &nine;

int leftDisplay;
int midSiaplay;
int rightDisplay;
int *circs[10]={zp,op,tp,thp,fp,fip,sp,sep,ep,np};

int leftCircumference=1;
int middleCircumference=8;
int rightCricumference=9;
int theCircumference=190;

int ykhm  =0b01111111;

int nokhm =0b11111111;

int *khmpointer = &ykhm;





volatile bool displayC;
volatile bool exitDisplay = false;

int state = 1;
int *status = &state;

bool khms;




void* circumferenceHelper(void* args){
	return static_cast<SetCircumference*>(args)->runProcessCircumference();
}

SetCircumference::SetCircumference()
{

}


SetCircumference::~SetCircumference()
{
}

void SetCircumference::display(){
	printf("testing \n ");
	if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1)
			{

			perror("Failed to get I/O access permission");
			//return 1;
			}
		ctrlSCBHandle = mmap_device_io(IO_PORT_SIZE, CTRLSCB_ADDRESS);
		ctrlSCAHandle = mmap_device_io(IO_PORT_SIZE, CTRLSCA_ADDRESS);
		out8(ctrlSCAHandle, SHOW_RIGHT_MASK);
		out8(ctrlSCBHandle, *circs[rightCricumference]);


}




void* SetCircumference::runProcessCircumference(void){
		//printf("the number %d",circumferences.at(rightCricumference));
	if ( ThreadCtl(_NTO_TCTL_IO, NULL) == -1)
			{

			perror("Failed to get I/O access permission");
			//return 1;
			}
		ctrlSCBHandle = mmap_device_io(IO_PORT_SIZE, CTRLSCB_ADDRESS);
		ctrlSCAHandle = mmap_device_io(IO_PORT_SIZE, CTRLSCA_ADDRESS);
		struct timespec tim;
		tim.tv_sec = 0;
		tim.tv_nsec = 100;
		while(true){
		while(displayC==true){
			nanosleep(&tim, NULL);
			//usleep(10);
			out8(ctrlSCAHandle, SHOW_RIGHT_MASK & *khmpointer );
			out8(ctrlSCBHandle, *circs[rightCricumference]);
			nanosleep(&tim, NULL);
			//usleep(10);
			out8(ctrlSCAHandle, SHOW_MID_MASK & *khmpointer );
			out8(ctrlSCBHandle, *circs[middleCircumference]);
			nanosleep(&tim, NULL);
			//usleep(10);
			out8(ctrlSCAHandle, SHOW_LEFT_MASK & *khmpointer );
			out8(ctrlSCBHandle, *circs[leftCircumference]);
			}
		}
		return NULL;
}

void SetCircumference::setUnits(int iD, void(*callbackfunc)(int), void(*callbackfunc2)(int),bool (*callbackfunc3)(void)){
	this->createCallback = callbackfunc;
	this->createCallback2 = callbackfunc2;
	this->createCallback3 = callbackfunc3;

	this->myID = iD;


}

void SetCircumference::entry(){
	//int ctrlSSBHandle = circumferences[rightCricumference];
	//printf("the number %u \n", circs[0]);
	printf("entering the set circ \n");
	createCallback(myID);
	khms = createCallback3();
	if(khms){
		khmpointer = &ykhm;
	}else{
		khmpointer = &nokhm;
	}
	//printf("entered the setUnits state");
	//pthread_create(&scio, NULL, &circumferenceHelper, this);
	pthread_create(&scio, NULL, &circumferenceHelper, this);
	doThis();
}

void SetCircumference::exit(){
	pthread_cancel(scio);
	displayC = false;
	printf("the seleceted circ is %d \n",theCircumference-1);
	createCallback2(theCircumference-1);
}
void SetCircumference::doThis(){
	if(leftCircumference==2&&middleCircumference==2){

		leftCircumference=1;
		middleCircumference=9;
		rightCricumference=0;
		theCircumference=190;
	}
	else if(rightCricumference==9){
			rightCricumference=0;
			if(middleCircumference==9){
				middleCircumference=0;
				if(leftCircumference==2){
					leftCircumference=1;
				}else{
					leftCircumference++;
					theCircumference++;
				}
			}else{
				middleCircumference++;
				theCircumference++;
			}
		}else{
			rightCricumference++;
			theCircumference++;
		}


	displayC = true;

}





void SetCircumference::is_in(){}
void SetCircumference::accept(EVENT e){
	if (transVector[0]->checkAccept(myID, e)){
		printf("HIT %d \n ", e);
		exit();
		transVector[0]->accept(myID, e);
	}
	

}

void SetCircumference::addTransition(Transition* e){
	transVector.push_back(e);
}

int SetCircumference::getID(){
	return myID;
}

