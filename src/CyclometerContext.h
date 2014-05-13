/*
 * CyclometerContext.h
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 */

#ifndef CYCLOMETERCONTEXT_H_
#define CYCLOMETERCONTEXT_H_

#include "ModeButtonPressTransition.h"
#include "SetButtonPressTransition.h"
#include "SetUnitsState.h"
#include "CyclometerIterator.h"
#include "CyclometerIterator.h"
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
	SetButtonPressTransition setButton;
    pthread_t io;
    SetUnitsState setUnitsKMKH;
    SetUnitsState setUnitsDistance;
    ModeButtonPressTransition modeButton;

public:
	void* runProcess(void);
	CyclometerContext(CyclometerIterator myIterator);
	virtual ~CyclometerContext();
	virtual void accept(EVENT e);


};

#endif /* CYCLOMETERCONTEXT_H_ */
