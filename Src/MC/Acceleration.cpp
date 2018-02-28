/*
 * Acceleration.cpp
 *
 *  Created on: 28 февр. 2018 г.
 *      Author: Sales
 */

#include <MC/Acceleration.hpp>
#include "MC/MotionController.hpp"

Acceleration::Acceleration(float initialValue) {
	this->Set(initialValue);
}

void Acceleration::Set(float newValue){
	float intervalInSec = 1.0/MotionController::GetTimerFrequency();
	float velocityIncrement = newValue * intervalInSec * intervalInSec;
	int32_t tmp = MotionController::Get64bitForDoubleMM(velocityIncrement);
	if(tmp < 1) tmp  = 1LL;
	this->stepIncrement = tmp;
}

float Acceleration::Get(){
	float tmp = MotionController::Get64bitForDoubleMM(this->stepIncrement);
	float freq = MotionController::GetTimerFrequency();
	return (tmp*freq*freq);
}

uint32_t Acceleration::GetStepIncrement(){
	return this->stepIncrement;
}
