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

bool MotionDirection::IsForward(){ return forward; }

bool MotionDirection::IsBackward(){ return !forward; }

void MotionDirection::SetForward(){ forward = true; }

void MotionDirection::SetBackward(){ forward = false; }

