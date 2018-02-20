/*
 * CNCTask.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_SEQUENCE_HPP_
#define MC_SEQUENCE_HPP_

#include "Math/int_math.h"
#include "MC/Action.hpp"

#define ACTION_BUFFER_SIZE 16

class MotionController;

class Sequence {
private:
	uint32_t size;
	Action *actions[ACTION_BUFFER_SIZE];
	MotionController *parent;
public:
	Sequence(MotionController *mc);
	virtual ~Sequence();
	uint32_t getSize();
	Action *getAction(uint32_t ActionNum);
	void fillDebugTask();
	void resetTask();
private:
	void fillLines();
	void fillArcs();
	void fillComplex();
};

#endif /* MC_SEQUENCE_HPP_ */
