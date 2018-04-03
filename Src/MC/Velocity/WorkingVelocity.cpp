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
RelativeVelocity(&(Settings::GetInstance()->workingVelocitySetting), frv),
_autoLimitStepSize(0),
_autoLimitRatio(&(Settings::GetInstance()->autoLimitRatioSetting)) {
	SetAutoLimitStepSize();
}

void WorkingVelocity::SetAutoLimitStepSize(){
	uint32_t ss = this->GetStepSize();
	float r = this->_autoLimitRatio->Get();
	this->_autoLimitStepSize = ss * r;
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
