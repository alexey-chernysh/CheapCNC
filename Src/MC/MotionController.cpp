/*
 * MotionController.cpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#include "stm32f1xx_hal.h"
#include "MC/General.h"
#include "MC/MotionController.hpp"
#include "MC/Motion.hpp"
#include "MC/Position.hpp"
#include "Math/sine_n_cosine.h"

MotionController::MotionController() {
	this->running = false;
	this->forward = true;

	this->timerFrequency = ((float)HAL_RCC_GetPCLK2Freq())/(PWM_PRESCALER+1)/(PWM_PERIOD+1);
	float scale = (float)(1LL<<POSITION_FIRST_SIGNIFICANT_BIT);
	this->oneBitLengthMM = (N_OF_TOOTH * TOOTH_STEP)/STEP_PER_ROTATION/(MAX_MICROSTEP + 1.0)/scale;

	this->sequence = Sequence();
	this->sequenceSize = sequence.getSize();
	this->currentMotionNum = 0;
	this->currentMotion = (Motion*)sequence.getAction(this->currentMotionNum);

	initMath();
}

MotionController::~MotionController() {
	// TODO Auto-generated destructor stub
}

MotionController* MotionController::GetInstance(){
    static MotionController instance;
    return &instance;
}

void MotionController::Reset(){
	this->running = false;
	this->forward = true;

	this->currentMotionNum = 0;
	this->currentMotion = (Motion*)sequence.getAction(this->currentMotionNum);
}

void MotionController::IterateActionNum(){
	if(this->forward)
		this->currentMotionNum++;
	else
		this->currentMotionNum--;
}

void MotionController::onTimer(){
	if(this->currentMotion != 0){
		bool anotherStepNeeded = true;
		if(this->running) {
			if(this->forward){
				anotherStepNeeded = currentMotion->iterateForward();
			} else {
				anotherStepNeeded = currentMotion->iterateBackward();
			}
		}

		if(anotherStepNeeded) return;
		else{
			IterateActionNum();
			if((this->currentMotionNum >= 0)&&(this->currentMotionNum < this->sequenceSize)){
				this->currentMotion = (Motion*)sequence.getAction(this->currentMotionNum);
				this->currentMotion->setupMotion();
			} else this->Reset();
		}
	}
}
