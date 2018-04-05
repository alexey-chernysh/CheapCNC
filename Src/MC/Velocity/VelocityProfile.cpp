/*
 * VelocityProfile.cpp
 *
 *  Created on: 27 мар. 2018 г.
 *      Author: Sales
 */

#include <MC/Velocity/Velocity.hpp>
#include <MC/Velocity/VelocityProfile.hpp>
#include "MC/Settings/Settings.hpp"
#include "MC/MotionController.hpp"
#include "MC/GPIO/OutputSignal.hpp"
#include "MC/Position.hpp"

static VelocityProfile* _instance = 0;

VelocityProfile::VelocityProfile():
freeRunVelocity(),
workingVelocity(&freeRunVelocity),
startVelocity(&(Settings::GetInstance()->startVelocitySetting), &freeRunVelocity),
adjustmentVelocity(&(Settings::GetInstance()->adjustmentVelocitySetting), &freeRunVelocity),
acceleration(),
currentStepSize(startVelocity.GetStepSize()){
}

uint32_t VelocityProfile::GetStepSize(MOTION_VELOCITY t) {
	switch (t){
		case FREE_RUN: return freeRunVelocity.GetStepSize();
		case WORKING: return workingVelocity.GetStepSize();
		default: return 0;
	}
}

float VelocityProfile::GetVelocity(MOTION_VELOCITY t){
	switch (t){
		case FREE_RUN: return freeRunVelocity.Get();
		case WORKING: return workingVelocity.Get();
		default: return 0;
	}
}

uint32_t VelocityProfile::GetCurrentStepSize(){
	return this->currentStepSize;
};

void VelocityProfile::SetCurrentStepSize(uint32_t newStepSIze){
	this->currentStepSize = newStepSIze;
	if(this->currentStepSize >= this->workingVelocity.GetAutoLimitStepSize()) THC_AutoOn();
	else THC_AutoOff();
}

float VelocityProfile::GetCurrentVelocity() { // millimeters in minute
	return (float)(60.0
			     *GetDoubleMMFor64bit(this->currentStepSize)
				 *GetTimerFrequency());
}

VelocityProfile* VelocityProfile::GetInstance(){
	if(_instance == 0) _instance = new VelocityProfile();
	return _instance;;
}

VelocityProfile::~VelocityProfile(){}
