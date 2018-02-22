/*
 * VelocitySettings.cpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#include <stdint.h>
#include "MC/VelocitySettings.hpp"
#include "MC/MotionController.hpp"

VelocitySettings::VelocitySettings(){
	oneBitLength = MotionController::GetInstance()->GetOneBitLengthMM();
	timerFrequency = MotionController::GetInstance()->GetTimerFrequency();
	// setting velocities
	startVelocity =   100.0/60.0;
	freeRunVelocity = 5000.0/60.0;
	workingVelocity = 1000.0/60.0;
	adjustmentVelocity = 10.0/60.0;
	// setting acceleration & step increment/decrement
	acceleration = 50.0; // mm/sec/sec
	stepIncrement = GetStepIncrement4Acceleration();
	// setting current step size for idle motion
	currentStepSize = 0;
}

VelocitySettings::~VelocitySettings(){

}

VelocitySettings* VelocitySettings::GetInstance(){
    static VelocitySettings instance;
    return &instance;
}

int32_t VelocitySettings::GetStep4Velocity(double velocity){
	double mmInTick = velocity/timerFrequency;
	return (int32_t)(mmInTick/oneBitLength);
}

double VelocitySettings::GetVelocity4Step(int32_t stepSize){
	return 60.0*stepSize*oneBitLength*timerFrequency;
}

int32_t VelocitySettings::GetStepSize(MOTION_VELOCITY t) {
	switch (t){
		case FREE_RUN: return GetStep4Velocity(freeRunVelocity);
		case WORKING: return GetStep4Velocity(workingVelocity);
		case START: return GetStep4Velocity(startVelocity);
		case ADJUSTMENT: return GetStep4Velocity(adjustmentVelocity);
		default: return 0;
	}
}

int32_t VelocitySettings::GetStepIncrement4Acceleration(){
	double intervalInSec = 1.0/timerFrequency;
	double velocityIncrement = acceleration * intervalInSec * intervalInSec;
	int32_t result = MotionController::GetInstance()->Get64bitForDoubleMM(velocityIncrement);
	if(result<1) result  = 1LL;
	return result;
}

void VelocitySettings::SetCurrentStepSize(int32_t newStepSIze){
	currentStepSize = newStepSIze;
}

float VelocitySettings::GetCurrentVelocity() { // millimeters in minute
	return (float)(60.0  * MotionController::GetInstance()->GetDoubleMMFor64bit(currentStepSize) * timerFrequency);
}

int64_t VelocitySettings::GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2) {
	int64_t sqr1 = stepSize1*((int64_t)stepSize1);
	int64_t sqr2 = stepSize2*((int64_t)stepSize2);
	int64_t result = ((sqr2-sqr1)/stepIncrement)/2;
	if(result >= 0) return result;
	else return -result;
}

int32_t VelocitySettings::GetCurrentStepSize(){ return currentStepSize; };
int32_t VelocitySettings::GetStepIncrement(){ return stepIncrement; }
float VelocitySettings::GetStartVelocity(){ return startVelocity; }
float VelocitySettings::GetFreeRunVelocity() { return freeRunVelocity; }
float VelocitySettings::GetWorkingVelocity() { return workingVelocity; }
