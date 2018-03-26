/*
 * Acceleration.cpp
 *
 *  Created on: 28 февр. 2018 г.
 *      Author: Sales
 */

#include <MC/Motions/Acceleration.hpp>
#include "MC/MotionController.hpp"
#include "MC/Settings/Settings.hpp"

Acceleration::Acceleration(): _value(&(settings.acceleration)) {
	SetIncrement();
}

void Acceleration::SetIncrement(){
	float intervalInSec = 1.0/motionController.GetTimerFrequency();
	float velocityIncrement = _value->Get() * intervalInSec * intervalInSec;
	int32_t tmp = motionController.Get64bitForDoubleMM(velocityIncrement);
	if(tmp < 1) tmp  = 1LL;
	this->_stepIncrement = tmp;
}

void Acceleration::Set(float newValue){
	_value->Set(newValue);
	SetIncrement();
}

float Acceleration::Get(){
	return 	_value->Get();
}

uint32_t Acceleration::GetStepIncrement(){
	return this->_stepIncrement;
}

int64_t Acceleration::GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2) {
	int64_t sqr1 = stepSize1*((int64_t)stepSize1);
	int64_t sqr2 = stepSize2*((int64_t)stepSize2);
	int64_t result = ((sqr2-sqr1)/this->_stepIncrement)/2;
	if(result >= 0) return result;
	else return -result;
}

