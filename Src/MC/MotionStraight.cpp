/*
 * MotionStraight.cpp
 *
 *  Created on: 26 џэт. 2018 у.
 *      Author: Sales
 */

#include "MC/MotionStraight.hpp"
#include "MC/Motion.hpp"

MotionStraight::~MotionStraight() {
	// TODO Auto-generated destructor stub
}

MotionStraight::MotionStraight( double _relEndPosX,
								double _relEndPosY,
								MOTION_VELOCITY velocity,
								double startVel,
								double endVel):Motion(_relEndPosX, _relEndPosY, velocity, startVel, endVel){
	double x = this->relEndPosX;
	double y = this->relEndPosY;
	this->wayLength = (int64_t)sqrt(x*x + y*y);
	assert(this->wayLength);

	this->Kx = getLongFromDouble(x/this->wayLength);
	this->Ky = getLongFromDouble(y/this->wayLength);

	this->calcWayLength();
}

void MotionStraight::onFastTimerTickt(){
//	int64_t dx = _wayLengthCurrent * this->Kx;
//	this->relCurrentPosX = dx>>SCALING_SHIFT;
	this->relCurrentPosX = mulshift(this->wayLengthCurrent, this->Kx, SCALING_SHIFT);
//	int64_t dy = _wayLengthCurrent * this->Ky;
//	this->relCurrentPosY = dy>>SCALING_SHIFT;
	this->relCurrentPosY = mulshift(this->wayLengthCurrent, this->Ky, SCALING_SHIFT);
}

