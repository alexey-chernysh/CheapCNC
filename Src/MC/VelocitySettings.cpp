/*
 * VelocitySettings.cpp
 *
 *  Created on: 28 џэт. 2018 у.
 *      Author: Sales
 */

#include "MC/VelocitySettings.hpp"
#include "MC/Position.hpp"
#include "Math/int_math.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

static VelocitySettings velocitySettings();

VelocitySettings::VelocitySettings(){
	// calc timer interrupt frequency
	this->timerInterruptFrequency = ((double)HAL_RCC_GetPCLK2Freq())/(PWM_PRESCALER+1)/(PWM_PERIOD+1);
	// calc one bit length
	double scale = (double)(1LL<<SMOOTHING_SCALE);
	double oneBitAngleInMM = (N_OF_TOOTH * TOOTH_STEP)/STEP_PER_ROTATION/(MAX_PHASE + 1.0);
	this->oneBitLength = oneBitAngleInMM/scale;
	// calc min velocity
	this->minVelocity = this->timerInterruptFrequency*60.0*getOneBitLength();
	// calc max velocity
	double maxPositionIncrement = (N_OF_TOOTH*TOOTH_STEP)/STEP_PER_ROTATION/4;
	double maxVelocityInSec = this->timerInterruptFrequency*maxPositionIncrement;
	this->maxVelocity = 60.0*maxVelocityInSec; // mm in minute
	// setting velocities
	this->startVelocity =   100.0/60.0;
	this->freeRunVelocity = 5000.0/60.0;
	this->workingVelocity = 1000.0/60.0;
	this->adjustmentVelocity = 10.0/60.0;
	// setting acceleration & step increment/decrement
	this->acceleration = 50.0; // mm/sec/sec
	this->stepIncrement = this->getStepIncrement4Acceleration();
	// setting current step size for idle motion
	this->currentStepSize = 0;
}

VelocitySettings::~VelocitySettings(){

}

double VelocitySettings::getOneBitLength(){  // one bit length in mm
	return this->oneBitLength;
}

float VelocitySettings::getMinVelocity(){
	return this->minVelocity;
}

float VelocitySettings::getMaxVelocity(){
	return this->maxVelocity;
}

double VelocitySettings::getTimerFrequencyUsed(){
	return this->timerInterruptFrequency;
}

int64_t VelocitySettings::get64bitForDoubleMM(double mm){
	return (int64_t)(mm/this->oneBitLength);
}

double VelocitySettings::getDoubleMMFor64bit(int64_t iValue){
	return this->oneBitLength*iValue;
}

int32_t VelocitySettings::getStep4Velocity(double velocity){
	double mmInTick = velocity/getTimerFrequencyUsed();
	return (int32_t)(mmInTick/this->oneBitLength);
}

double VelocitySettings::getVelocity4Step(int32_t stepSize){
	return 60.0*stepSize*oneBitLength*getTimerFrequencyUsed();
}

int32_t VelocitySettings::getStepSize(MOTION_VELOCITY t) {
	switch (t){
		case FREE_RUN: return getStep4Velocity(freeRunVelocity);
		case WORKING: return getStep4Velocity(workingVelocity);
		case START: return getStep4Velocity(startVelocity);
		case ADJUSTMENT: return getStep4Velocity(adjustmentVelocity);
		default: return 0;
	}
}

int32_t VelocitySettings::getStepIncrement4Acceleration(){
	double intervalInSec = 1.0/this->timerInterruptFrequency;
	double velocityIncrement = this->acceleration * intervalInSec * intervalInSec;
	int32_t result = this->get64bitForDoubleMM(velocityIncrement);
	if(result<1) result  = 1LL;
	return result;
}

void VelocitySettings::setCurrentStepSize(int32_t newStepSIze){
	currentStepSize = newStepSIze;
}

float VelocitySettings::getCurrentVelocity() { // mm in min
	return (float)(60.0  * this->getDoubleMMFor64bit(this->currentStepSize) * this->timerInterruptFrequency);
}

int64_t VelocitySettings::getWayLength4StepChange(int32_t stepSize1, int32_t stepSize2) {
	bool isAccelereting = (stepSize2 >= stepSize1);
	int64_t result = 0;
	int32_t stepSize = stepSize1;
	// TODO change this stupid
	if(isAccelereting){
		while (stepSize < stepSize2){
			result += stepSize;
			stepSize += this->stepIncrement;
		}
	} else {
		while (stepSize > stepSize2){
			result += stepSize;
			stepSize -= this->stepIncrement;
		}
	}
	return result;
}

