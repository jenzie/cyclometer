/*
 * StateNode.h
 *
 *  Created on: May 8, 2014
 *      Author: nmc2484
 * 		Author: Jenny Zhen
 */

#ifndef STATENODE_H_
#define STATENODE_H_

#include "Enums.h"

class StateNode {

private:
	int myID;

public:


	virtual void entry() = 0;
	virtual void exit() = 0;
	virtual void doThis() = 0;
	virtual void is_in()= 0;
	virtual void accept(EVENT a)= 0;
	virtual int getID() =0 ;
	//virtual void setUnits(int iD, void(*callbackfunc)(int),void (*callbackfunc2)(int)) =0;
};

#endif /* STATENODE_H_ */
