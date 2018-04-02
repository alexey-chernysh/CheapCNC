/*
 * RelativeVelocity.cpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#include <MC/Velocity/RelativeVelocity.hpp>
#include "MC/Settings/FloatSetting.hpp"
#include <MC/Velocity/FreeRunVelocity.hpp>

RelativeVelocity::RelativeVelocity(FloatSetting* currentSetting, FreeRunVelocity* frv):
Velocity(0.0),
_freeRunVelocity(frv),
_ratio(currentSetting){
	this->Set(this->_freeRunVelocity->Get()*this->_ratio->Get());
}

RelativeVelocity::~RelativeVelocity(){
}

void RelativeVelocity::Set(float newVelocity){
	float tmpRatio = newVelocity/this->_freeRunVelocity->Get();
	if(tmpRatio < 0.0) tmpRatio = 0.0;
	if(tmpRatio > 1.0) tmpRatio = 1.0;
	this->_ratio->Set(tmpRatio);
	this->SetStepSize(this->Get());
}

float RelativeVelocity::Get(){
	return (this->_freeRunVelocity->Get() * this->_ratio->Get());
}

