/*
 * CNCTask.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_SEQUENCE_HPP_
#define MC_SEQUENCE_HPP_

#include <stdint.h>

class Action;

#define ACTION_BUFFER_SIZE 16

class MotionController;

class Sequence {
private:
	uint32_t size;
	Action *actions[ACTION_BUFFER_SIZE];
public:
	Sequence();
	virtual ~Sequence();
	uint32_t GetSize();
	Action *GetAction(uint32_t ActionNum);
	void FillDebugTask();
	void ResetTask();
private:
	void FillLines();
	void FillArcs();
	void FillComplex();
};

#endif /* MC_SEQUENCE_HPP_ */
