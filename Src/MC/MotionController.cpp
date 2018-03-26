/*
 * MotionController.cpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "MC/General.h"
#include <Math/sine_n_cosine.hpp>
#include <MC/ExecutionDirection.hpp>
#include <MC/GPIO/OutputSignal.hpp>
#include <MC/Motions/Acceleration.hpp>
#include <MC/Motions/Motion.hpp>
#include <MC/Motions/Velocity.hpp>
#include "MC/MotionController.hpp"
#include "MC/Settings/Settings.hpp"

MotionController motionController;

MotionController::MotionController():
freeRunVelocity(),
workingVelocity(&freeRunVelocity),
startVelocity(&(settings.startVelocity), &freeRunVelocity),
adjustmentVelocity(&(settings.adjustmentVelocity), &freeRunVelocity),
acceleration(){
	initMath();

	this->executionState.SetForwardDirection();

	timerFrequency = ((float)HAL_RCC_GetPCLK2Freq())/(PWM_PRESCALER+1)/(PWM_PERIOD+1);
	float scale = (float)(1LL<<POSITION_FIRST_SIGNIFICANT_BIT);
	oneBitLengthMM = (N_OF_TOOTH * TOOTH_STEP)/STEP_PER_ROTATION/(MAX_MICROSTEP + 1.0)/scale;

	// setting current step size for idle motion
    startStopStepSize = GetStepSize(START);
	currentStepSize = startStopStepSize;

	sequence = new Sequence();
	sequenceSize = sequence->GetSize();
	currentMotionNum = 0;
	currentAction = (Motion*)sequence->GetAction(currentMotionNum);
	currentAction->Init();

	// debug only
	this->SetResuming();

}

void MotionController::Reset(){
	this->executionState.Reset();

	currentMotionNum = 0;
	currentAction = (Motion*)sequence->GetAction(currentMotionNum);
}

float MotionController::GetTimerFrequency(){ return timerFrequency; }

float MotionController::GetOneBitLengthMM(){ return oneBitLengthMM; }

void MotionController::IterateActionNum(){
	if(this->executionState.DirectionIsForward())
		currentMotionNum++;
	else
		currentMotionNum--;
}

void MotionController::OnTimer(){
	if(currentAction != 0){
		bool anotherStepNeeded = true;
		if(this->executionState.IsRunning()) {
			if(this->executionState.DirectionIsForward()){
				anotherStepNeeded = currentAction->IterateForward();
			} else {
				anotherStepNeeded = currentAction->IterateBackward();
			}
		}

		if(anotherStepNeeded) return;
		else{
			IterateActionNum();
			if((currentMotionNum >= 0)&&(currentMotionNum < sequenceSize)){
				currentAction = (Motion*)sequence->GetAction(currentMotionNum);
				currentAction->Init();
			} else Reset();
		}
	}
}

void MotionController::SetResuming(){
    resumingStepSize = startStopStepSize;
    this->executionState.SetResuming();
    this->executionState.SetNonPausing();
    this->executionState.SetRunning();
}

uint32_t MotionController::GetResumingStepSize(uint32_t _currentStepSize){
    if(this->executionState.IsResuming()){
    	uint32_t result = resumingStepSize;
        resumingStepSize += this->acceleration.GetStepIncrement();
        if(result < _currentStepSize) return result;
        else {
        	this->executionState.SetNonResuming();
            return _currentStepSize;
        }
    } else return _currentStepSize;
}

void MotionController::SetPausing(){
    pausingStepSize = GetCurrentStepSize();
    this->executionState.SetNonResuming();
    this->executionState.SetPausing();
}

uint32_t MotionController::GetPausingStepSize(uint32_t currentSS){
    if(this->executionState.IsPausing()){
        uint32_t result = pausingStepSize;
        pausingStepSize -= this->acceleration.GetStepIncrement();
        if(result > startStopStepSize) return result;
        else {
            this->executionState.SetPaused();
            this->executionState.SetNonPausing();
            return startStopStepSize;
        }
    } else return currentSS;
}

void MotionController::SetCurrentStepSize(uint32_t newStepSIze){
	currentStepSize = newStepSIze;
	if(currentStepSize >= workingVelocity.GetAutoLimitStepSize()) THC_AutoOn();
	else THC_AutoOff();
}

float MotionController::GetCurrentVelocity() { // millimeters in minute
	return (float)(60.0  * GetDoubleMMFor64bit(currentStepSize) * timerFrequency);
}

void MotionController::OnControlKey(char controlKey){
	switch(controlKey){
	case 'R': // Start/Resume
		if(this->executionState.IsPaused()){
			this->executionState.SetForwardDirection();
			SetResuming();
		};
		break;
	case 'P': // Stop/Pause
		if(this->executionState.IsRunning())
			SetPausing();
		break;
	case 'B': // Rewind
		if(this->executionState.IsPaused()){
			this->executionState.SetBackwardDirection();
			SetResuming();
		};
		break;
	case 'W': // Up
		break;
	case 'S': // Down
		break;
	case 'A': // Left
		break;
	case 'D': // Right
		break;
	default:
		break;
	};
}

uint32_t MotionController::GetCurrentStepSize(){ return currentStepSize; };

int64_t MotionController::Get64bitForDoubleMM(double mm){ return (int64_t)(mm/oneBitLengthMM); };

double MotionController::GetDoubleMMFor64bit(int64_t iValue){	return oneBitLengthMM*iValue; };

uint32_t MotionController::GetStepSize(MOTION_VELOCITY t) {
	switch (t){
		case FREE_RUN: return freeRunVelocity.GetStepSize();
		case WORKING: return workingVelocity.GetStepSize();
		case START: return startVelocity.GetStepSize();
		case ADJUSTMENT: return adjustmentVelocity.GetStepSize();
		default: return 0;
	}
}

float MotionController::GetVelocity(MOTION_VELOCITY t){
	switch (t){
		case FREE_RUN: return freeRunVelocity.Get();
		case WORKING: return workingVelocity.Get();
		case START: return startVelocity.Get();
		case ADJUSTMENT: return adjustmentVelocity.Get();
		default: return 0;
	}
}

extern "C"{
void MC_OnTimer(){
	motionController.OnTimer();
}

void MC_onControlKey(char controlKey){
	motionController.OnControlKey(controlKey);
}

}
