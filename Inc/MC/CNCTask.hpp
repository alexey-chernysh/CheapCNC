/*
 * CNCTask.hpp
 *
 *  Created on: 28 џэт. 2018 у.
 *      Author: Sales
 */

#ifndef MC_CNCTASK_HPP_
#define MC_CNCTASK_HPP_

#include "Math/int_math.h"
#include "MC/Action.hpp"
#include "MC/MotionController.hpp"

#define ACTION_BUFFER_SIZE 16

class CNCTask {
private:
	uint32_t size;
	Action *actions[ACTION_BUFFER_SIZE];
	MotionController *parent;
public:
	CNCTask(MotionController *mc);
	virtual ~CNCTask();
	uint32_t getSize();
	Action *getAction(uint32_t ActionNum);
	void fillDebugTask();
	void resetTask();
private:
	void fillLines();
	void fillArcs();
	void fillComplex();
};

#endif /* MC_CNCTASK_HPP_ */
