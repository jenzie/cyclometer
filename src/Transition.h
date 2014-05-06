/*
 * Transition.h
 *
 *  Created on: May 6, 2014
 *      Author: nmc2484
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

class Transition {
public:
	Transition();
	virtual ~Transition();

	virtual ~ModeButtonPressTransition();

	bool checkAccept();

	void accept();
};

#endif /* TRANSITION_H_ */
