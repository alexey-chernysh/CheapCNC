/*
 * MotionDirection.cpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: alexey
 */

#include <MC/State/ExecutionDirection.hpp>

ExecutionDirection::ExecutionDirection() {
	forward = true;
}

bool ExecutionDirection::DirectionIsForward(){ return forward; }

bool ExecutionDirection::DirectionIsBackward(){ return !forward; }

void ExecutionDirection::SetForwardDirection(){ forward = true; }

void ExecutionDirection::SetBackwardDirection(){ forward = false; }

