/*
 * Motion.cpp
 *
 *  Created on: 26 ���. 2018 �.
 *      Author: Sales
 */

#include "MC/General.h"
#include <MC/ExecutionDirection.hpp>
#include <MC/MotionController.hpp>
#include <MC/Motions/Motion.hpp>
#include <MC/Velocity/Velocity.hpp>
#include "MC/Action.hpp"
#include "MC/Position.hpp"
#include "MC/Velocity/VelocityProfile.hpp"

Motion::~Motion() {
}

Motion::Motion( double _relEndPosX,
			    double _relEndPosY,
			    MOTION_VELOCITY velocity,
			    double startVel,
			    double endVel):	phase(HEAD),
			    				wayLength(0L),
			    				wayLengthCurrent(0L),
								wayLengthAcceleration(0L),
								wayLengthDeceleration(0L),
								currentDistanceToTarget(0L),
								relEndPosX(Get64bitForDoubleMM(_relEndPosX)),
								relEndPosY(Get64bitForDoubleMM(_relEndPosY)),
								relCurrentPosX(0L),
								relCurrentPosY(0L),
								startAbsPosX(0L),
								startAbsPosY(0L),
								stepSizeCurrent(0L){


	this->stepSizeConstantVelocity = VelocityProfile::GetInstance()->GetStepSize(velocity);
	this->stepSizeBeforeAcceleration = Velocity::GetStep4Velocity(startVel);
	this->stepSizeAfterDeceleration = Velocity::GetStep4Velocity(endVel);
}

void Motion::CalcWayLength(){
	this->wayLengthCurrent = 0LL;
	this->wayLengthAcceleration = VelocityProfile::GetInstance()->acceleration.GetWayLength4StepChange(this->stepSizeBeforeAcceleration, this->stepSizeConstantVelocity);
	this->wayLengthDeceleration = VelocityProfile::GetInstance()->acceleration.GetWayLength4StepChange(this->stepSizeConstantVelocity, this->stepSizeAfterDeceleration);

	int64_t wayLengthConstantVelocity = this->wayLength - this->wayLengthAcceleration - this->wayLengthDeceleration;
	if(wayLengthConstantVelocity < 0){
		// motion too short, processing without constant velocity ramp
		this->wayLengthAcceleration += wayLengthConstantVelocity /2;
		this->wayLengthDeceleration += wayLengthConstantVelocity /2;
	}

}

void Motion::Init(){
	this->currentDistanceToTarget = this->wayLength;

	if(motionController->executionState.DirectionIsForward()){
		this->stepSizeCurrent =  this->stepSizeBeforeAcceleration;
		this->startAbsPosX = motionController->positionX.Get();
		this->startAbsPosY = motionController->positionY.Get();
	} else
		this->stepSizeCurrent = this->stepSizeAfterDeceleration;

}

void Motion::OnIteration(){}

static int64_t iabs(int64_t x){
	if(x >= 0) return x;
	else return -x;
}

bool Motion::IterateForward(){ // return true if another step needed

    stepSizeCurrent = motionController->GetResumingStepSize(stepSizeCurrent);
    stepSizeCurrent = motionController->GetPausingStepSize(stepSizeCurrent);
	this->wayLengthCurrent += this->stepSizeCurrent;
	this->OnIteration();

	motionController->positionX.Set(this->startAbsPosX + this->relCurrentPosX);
	motionController->positionY.Set(this->startAbsPosY + this->relCurrentPosY);
	VelocityProfile::GetInstance()->SetCurrentStepSize(this->stepSizeCurrent);

	switch (this->phase){
		case HEAD:
			if(this->stepSizeCurrent < this->stepSizeConstantVelocity)
				this->stepSizeCurrent += VelocityProfile::GetInstance()->acceleration.GetStepIncrement();
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
				this->stepSizeCurrent -= VelocityProfile::GetInstance()->acceleration.GetStepIncrement();
			else this->stepSizeCurrent = this->stepSizeAfterDeceleration;
			break;
	}

	this->currentDistanceToTarget = this->wayLength - this->wayLengthCurrent;
	if(this->currentDistanceToTarget < this->wayLengthDeceleration)
		this->phase = TAIL;

	return (iabs(this->currentDistanceToTarget) > this->stepSizeCurrent);
}

bool Motion::IterateBackward(){ // return true if another step needed

    stepSizeCurrent = motionController->GetResumingStepSize(stepSizeCurrent);
    stepSizeCurrent = motionController->GetPausingStepSize(stepSizeCurrent);
	this->wayLengthCurrent -= this->stepSizeCurrent;
	this->OnIteration();

	motionController->positionX.Set(this->startAbsPosX + this->relCurrentPosX);
	motionController->positionY.Set(this->startAbsPosY + this->relCurrentPosY);
	VelocityProfile::GetInstance()->SetCurrentStepSize(this->stepSizeCurrent);

	switch (this->phase){
		case HEAD:
			if(this->stepSizeCurrent > this->stepSizeBeforeAcceleration)
				this->stepSizeCurrent -= VelocityProfile::GetInstance()->acceleration.GetStepIncrement();
			else this->stepSizeCurrent = this->stepSizeBeforeAcceleration;
			break;
		case BODY:
			this->stepSizeCurrent = this->stepSizeConstantVelocity;
			break;
		case TAIL:
			if(this->stepSizeCurrent < this->stepSizeConstantVelocity)
				this->stepSizeCurrent += VelocityProfile::GetInstance()->acceleration.GetStepIncrement();
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
