/*
 * CyclometerContext.h
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#ifndef CYCLOMETERCONTEXT_H_
#define CYCLOMETERCONTEXT_H_

#include "ModeButtonPressTransition.h"

#include "SetUnitsState.h"
#include "SetCircumference.h"
#include "CyclometerIterator.h"
#include "CalculationState.h"
#include "StateNode.h"
#include "Enums.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>



class CyclometerContext {
private:
	CyclometerIterator theIterator;
    pthread_t io;
    SetUnitsState setUnitsKMKH;
	SetCircumference setUnitsDistance;
	CalculationState calculateState;
    ModeButtonPressTransition modeButton;



public:
	void* runProcess(void);
	CyclometerContext(CyclometerIterator myIterator);
	virtual ~CyclometerContext();
	virtual void accept(EVENT e);



};

#endif /* CYCLOMETERCONTEXT_H_ */
