/*
 * Acceleration.cpp
 *
 *  Created on: 28 февр. 2018 г.
 *      Author: Sales
 */

#include <MC/Acceleration.hpp>
#include "MC/MotionController.hpp"

Acceleration::Acceleration(float initialValue) {
	Set(initialValue);
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

int64_t Acceleration::GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2) {
	int64_t sqr1 = stepSize1*((int64_t)stepSize1);
	int64_t sqr2 = stepSize2*((int64_t)stepSize2);
	int64_t result = ((sqr2-sqr1)/this->stepIncrement)/2;
	if(result >= 0) return result;
	else return -result;
}

