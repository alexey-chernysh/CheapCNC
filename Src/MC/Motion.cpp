/*
 * Motion.cpp
 *
 *  Created on: 26 ���. 2018 �.
 *      Author: Sales
 */

#include "MC/General.h"
#include "MC/Motion.hpp"
#include "MC/Action.hpp"
#include "MC/Position.hpp"
#include "MC/MotionController.hpp"

Motion::~Motion() {
	// TODO Auto-generated destructor stub
}

Motion::Motion( double _relEndPosX,
			    double _relEndPosY,
			    MOTION_VELOCITY velocity,
			    double startVel,
			    double endVel) {

	MotionController* mc = MotionController::GetInstance();
	this->relEndPosX = mc->Get64bitForDoubleMM(_relEndPosX);
	this->relEndPosY = mc->Get64bitForDoubleMM(_relEndPosY);

	this->relCurrentPosX = 0;
	this->relCurrentPosY = 0;

	this->stepSizeConstantVelocity = getStepSize(velocity);
	this->stepSizeBeforeAcceleration = getStep4Velocity(startVel);
	this->stepSizeAfterDeceleration = getStep4Velocity(endVel);
	this->stepSizeIncrement = getStepIncrement();

	this->phase = HEAD;

	this->startAbsPosX = 0;
	this->startAbsPosY = 0;
	this->stepSizeCurrent = 0;
	this->currentDistanceToTarget = 0;
	this->wayLength = 0;
}

void Motion::calcWayLength(){
	this->wayLengthCurrent = 0LL;
	this->wayLengthAcceleration = getWayLength4StepChange(this->stepSizeBeforeAcceleration, this->stepSizeConstantVelocity);
	this->wayLengthDeceleration = getWayLength4StepChange(this->stepSizeConstantVelocity, this->stepSizeAfterDeceleration);

	int64_t wayLengthConstantVelocity = this->wayLength - this->wayLengthAcceleration - this->wayLengthDeceleration;
	if(wayLengthConstantVelocity < 0){
		// motion too short, processing without constant velocity ramp
		this->wayLengthAcceleration += wayLengthConstantVelocity /2;
		this->wayLengthDeceleration += wayLengthConstantVelocity /2;
	}

}

void Motion::setupMotion(){
	bool executionIsForward = MotionController::GetInstance()->IsForward();
	this->currentDistanceToTarget = this->wayLength;

	if(executionIsForward)
		this->stepSizeCurrent =  this->stepSizeBeforeAcceleration;
	else
		this->stepSizeCurrent = this->stepSizeAfterDeceleration;

	if(executionIsForward){
		this->startAbsPosX = PositionX::GetInstance()->Get();
		this->startAbsPosY = PositionY::GetInstance()->Get();
	}
}

static int64_t iabs(int64_t x){
	if(x >= 0) return x;
	else return -x;
}

bool Motion::iterateForward(){ // return true if another step needed

	this->wayLengthCurrent += this->stepSizeCurrent;
	this->onFastTimerTick();

	PositionX::GetInstance()->Set(this->startAbsPosX + this->relCurrentPosX);
	PositionY::GetInstance()->Set(this->startAbsPosY + this->relCurrentPosY);
	setCurrentStepSize(this->stepSizeCurrent);

	switch (this->phase){
		case HEAD:
			if(this->stepSizeCurrent < this->stepSizeConstantVelocity)
				this->stepSizeCurrent += this->stepSizeIncrement;
			else {
				this->stepSizeCurrent = this->stepSizeConstantVelocity;
				this->phase = BODY;
			}
			break;
		case BODY:
			this->stepSizeCurrent = this->stepSizeConstantVelocity;
			break;
		case TAIL:
			if(this->stepSizeCurrent > this->stepSizeAfterDeceleration)
				this->stepSizeCurrent -= this->stepSizeIncrement;
			else this->stepSizeCurrent = this->stepSizeAfterDeceleration;
			break;
	}

	this->currentDistanceToTarget = this->wayLength - this->wayLengthCurrent;
	if(this->currentDistanceToTarget < this->wayLengthDeceleration)
		this->phase = TAIL;

	return (iabs(this->currentDistanceToTarget) > this->stepSizeCurrent);
}

bool Motion::iterateBackward(){ // return true if another step needed

	this->wayLengthCurrent -= this->stepSizeCurrent;
	this->onFastTimerTick();

	PositionX::GetInstance()->Set(this->startAbsPosX + this->relCurrentPosX);
	PositionY::GetInstance()->Set(this->startAbsPosY + this->relCurrentPosY);
	setCurrentStepSize(this->stepSizeCurrent);

	switch (this->phase){
		case HEAD:
			if(this->stepSizeCurrent > this->stepSizeBeforeAcceleration)
				this->stepSizeCurrent -= this->stepSizeIncrement;
			else this->stepSizeCurrent = this->stepSizeBeforeAcceleration;
			break;
		case BODY:
			this->stepSizeCurrent = this->stepSizeConstantVelocity;
			break;
		case TAIL:
			if(this->stepSizeCurrent < this->stepSizeConstantVelocity)
				this->stepSizeCurrent += this->stepSizeIncrement;
			else {
				this->stepSizeCurrent = this->stepSizeConstantVelocity;
				this->phase = BODY;
			}
			break;
	}

	this->currentDistanceToTarget = this->wayLengthCurrent;
	if(this->currentDistanceToTarget < this->wayLengthAcceleration)
		this->phase = HEAD;

	return (iabs(this->currentDistanceToTarget) > this->stepSizeCurrent);
}

