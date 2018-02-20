/*
 * MotionController.cpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#include "MC/MotionController.hpp"
#include "MC/Motion.hpp"
#include "MC/Position.hpp"
#include "Math/sine_n_cosine.h"

MotionController::MotionController() {
	this->positionX = PositionX();
	this->positionY = PositionY();

	this->cncTask = Sequence();
	this->taskSize = cncTask.getSize();

	this->Reset();

	initMath();
//	setupSteppersGPIO();
//	MC_onFreeRunForward();
}

MotionController::~MotionController() {
	// TODO Auto-generated destructor stub
}

void MotionController::Reset(){
	this->isRunning = false;
	this->isForward = true;

	this->currentMotionNum = 0;
	this->currentMotion = (Motion*)cncTask.getAction(this->currentMotionNum);
}

void MotionController::iterateActionNum(){
	if(this->isForward)
		this->currentMotionNum++;
	else
		this->currentMotionNum--;
}

void MotionController::onTimerTick(){
	if(this->currentMotion != 0){
		bool anotherStepNeeded = true;
		if(this->isRunning) {
			if(this->isForward){
				anotherStepNeeded = currentMotion->iterateForward();
			} else {
				anotherStepNeeded = currentMotion->iterateBackward();
			}
		}

		if(anotherStepNeeded) return;
		else{
			iterateActionNum();
			if((this->currentMotionNum >= 0)&&(this->currentMotionNum < this->taskSize)){
				this->currentMotion = (Motion*)cncTask.getAction(this->currentMotionNum);
				this->currentMotion->setupMotion();
			} else this->Reset();
		}
	}
}

