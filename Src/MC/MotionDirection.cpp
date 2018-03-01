/*
 * MotionDirection.cpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: alexey
 */

#include <MC/MotionDirection.hpp>

MotionDirection::MotionDirection() {
	forward = true;
}

bool MotionDirection::DirectionIsForward(){ return forward; }

bool MotionDirection::DirectionIsBackward(){ return !forward; }

void MotionDirection::SetForwardDirection(){ forward = true; }

void MotionDirection::SetBackwardDirection(){ forward = false; }

