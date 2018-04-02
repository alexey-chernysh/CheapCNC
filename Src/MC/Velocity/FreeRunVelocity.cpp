/*
 * FreeRunVelocity.cpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#include <MC/Velocity/FreeRunVelocity.hpp>
#include "MC/MotionController.hpp"

FreeRunVelocity::FreeRunVelocity():
Velocity(0.0),
_value(&(motionController->settings.freeRunVelocitySetting)){
	float currentVelocitySetting = this->_value->Get();
	this->SetStepSize(currentVelocitySetting);
}

FreeRunVelocity::~FreeRunVelocity() {
}

void FreeRunVelocity::Set(float newVelocity) {
	this->_value->Set(newVelocity);
	this->SetStepSize(this->Get());
};

float FreeRunVelocity::Get() {
	return this->_value->Get();
};

