/*
 * WorkingVelocity.cpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#include <MC/Velocity/WorkingVelocity.hpp>
#include <MC/Velocity/RelativeVelocity.hpp>
#include "MC/MotionController.hpp"

WorkingVelocity::WorkingVelocity(FreeRunVelocity* frv):
RelativeVelocity(&(motionController->settings.workingVelocitySetting), frv),
_autoLimitStepSize(0),
_autoLimitRatio(&(motionController->settings.autoLimitRatioSetting)) {
	SetAutoLimitStepSize();
}

void WorkingVelocity::SetAutoLimitStepSize(){
	this->_autoLimitStepSize = this->GetStepSize()*this->_autoLimitRatio->Get();
}

void WorkingVelocity::SetLimit(float newLimitRatio){
	this->_autoLimitRatio->Set(newLimitRatio);
	this->SetAutoLimitStepSize();
}

float WorkingVelocity::GetLimit(){
	return 	this->_autoLimitRatio->Get();
}

uint32_t WorkingVelocity::GetAutoLimitStepSize(){
	return this->_autoLimitStepSize;
}
