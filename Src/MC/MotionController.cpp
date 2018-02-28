/*
 * MotionController.cpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#include <Math/sine_n_cosine.hpp>
#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "MC/General.h"
#include "MC/Motion.hpp"
#include "MC/MotionController.hpp"
#include "MC/Velocity.hpp"
#include "MC/Signal.hpp"
#include "MC/MotionDirection.hpp"

static float timerFrequency;
static float oneBitLengthMM;

static bool running;
static MotionDirection motionDirection;
static bool resuming;
static bool pausing;

static uint32_t currentStepSize;
static uint32_t startStopStepSize;
static uint32_t resumingStepSize;
static uint32_t pausingStepSize;

static Velocity startVelocity;
static Velocity freeRunVelocity;
static WorkingVelocity workingVelocity;
static Velocity adjustmentVelocity;

static float acceleration;
static uint32_t stepIncrement;

static Sequence* sequence;
static uint32_t sequenceSize;
static uint32_t currentMotionNum;
static Motion* currentMotion;

MotionController motionController;

MotionController::MotionController() {
	initMath();

	running = false;
	motionDirection.SetForward();
	resuming = false;
	pausing = false;

	timerFrequency = ((float)HAL_RCC_GetPCLK2Freq())/(PWM_PRESCALER+1)/(PWM_PERIOD+1);
	float scale = (float)(1LL<<POSITION_FIRST_SIGNIFICANT_BIT);
	oneBitLengthMM = (N_OF_TOOTH * TOOTH_STEP)/STEP_PER_ROTATION/(MAX_MICROSTEP + 1.0)/scale;

	startVelocity.SetVelocity(100.0/60.0);
	freeRunVelocity.SetVelocity(5000.0/60.0);
	workingVelocity.SetVelocity(1000.0/60.0);
	adjustmentVelocity.SetVelocity(10.0/60.0);

	// setting acceleration & step increment/decrement
	acceleration = 50.0; // mm/sec/sec
	stepIncrement = GetStepIncrement4Acceleration();

	// setting current step size for idle motion
    startStopStepSize = GetStepSize(START);
	currentStepSize = startStopStepSize;

	sequence = new Sequence();
	sequenceSize = sequence->GetSize();
	currentMotionNum = 0;
	currentMotion = (Motion*)sequence->GetAction(currentMotionNum);
	currentMotion->SetupMotion();

	// debug only
	running = true;

}

void MotionController::Reset(){
	running = false;
	motionDirection.SetForward();
	resuming = false;
	pausing = false;

	currentMotionNum = 0;
	currentMotion = (Motion*)sequence->GetAction(currentMotionNum);
}

MotionDirection* MotionController::GetMotionDirection(){
	return &motionDirection;
}

bool MotionController::IsRunning(){ return running; }

bool MotionController::IsPaused(){ return !running; }

float MotionController::GetTimerFrequency(){ return timerFrequency; }

float MotionController::GetOneBitLengthMM(){ return oneBitLengthMM; }

float MotionController::GetMinVelocity(){ return 60.0*timerFrequency*oneBitLengthMM; }

float MotionController::GetMaxVelocity(){ return 60.0*timerFrequency*(N_OF_TOOTH*TOOTH_STEP)/STEP_PER_ROTATION/2; }

void MotionController::IterateActionNum(){
	if(motionDirection.IsForward())
		currentMotionNum++;
	else
		currentMotionNum--;
}

void MotionController::OnTimer(){
	if(currentMotion != 0){
		bool anotherStepNeeded = true;
		if(running) {
			if(motionDirection.IsForward()){
				anotherStepNeeded = currentMotion->IterateForward();
			} else {
				anotherStepNeeded = currentMotion->IterateBackward();
			}
		}

		if(anotherStepNeeded) return;
		else{
			IterateActionNum();
			if((currentMotionNum >= 0)&&(currentMotionNum < sequenceSize)){
				currentMotion = (Motion*)sequence->GetAction(currentMotionNum);
				currentMotion->SetupMotion();
			} else Reset();
		}
	}
}

void MotionController::SetResuming(){
    resumingStepSize = startStopStepSize;
    resuming = true;
    pausing = false;
    running = true;
}

uint32_t MotionController::GetResumingStepSize(uint32_t currentSS){
    if(resuming){
    	uint32_t result = resumingStepSize;
        resumingStepSize += stepIncrement;
        if(result < currentSS) return result;
        else {
            resuming = false;
            return currentSS;
        }
    } else return currentSS;
}

void MotionController::SetPausing(){
    pausingStepSize = GetCurrentStepSize();
    resuming = false;
    pausing = true;
}

uint32_t MotionController::GetPausingStepSize(uint32_t currentSS){
    if(pausing){
        uint32_t result = pausingStepSize;
        pausingStepSize -= stepIncrement;
        if(result > startStopStepSize) return result;
        else {
            running = false;
            pausing = false;
            return startStopStepSize;
        }
    } else return currentSS;
}

uint32_t MotionController::GetStepIncrement4Acceleration(){
	double intervalInSec = 1.0/timerFrequency;
	double velocityIncrement = acceleration * intervalInSec * intervalInSec;
	int32_t result = Get64bitForDoubleMM(velocityIncrement);
	if(result<1) result  = 1LL;
	return result;
}

void MotionController::SetCurrentStepSize(uint32_t newStepSIze){
	currentStepSize = newStepSIze;
	if(currentStepSize >= workingVelocity.GetAutoLimit()) THC_AutoOn();
	else THC_AutoOff();
}

float MotionController::GetCurrentVelocity() { // millimeters in minute
	return (float)(60.0  * GetDoubleMMFor64bit(currentStepSize) * timerFrequency);
}

void MotionController::OnControlKey(char controlKey){
	switch(controlKey){
	case 'R': // Start/Resume
		if(IsPaused()){
			motionDirection.SetForward();
			SetResuming();
		};
		break;
	case 'P': // Stop/Pause
		if(IsRunning())
			SetPausing();
		break;
	case 'B': // Rewind
		if(IsPaused()){
			motionDirection.SetBackward();
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

int64_t MotionController::GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2) {
	int64_t sqr1 = stepSize1*((int64_t)stepSize1);
	int64_t sqr2 = stepSize2*((int64_t)stepSize2);
	int64_t result = ((sqr2-sqr1)/stepIncrement)/2;
	if(result >= 0) return result;
	else return -result;
}

uint32_t MotionController::GetCurrentStepSize(){ return currentStepSize; };

uint32_t MotionController::GetStepIncrement(){ return stepIncrement; }

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
		case FREE_RUN: return freeRunVelocity.GetVelocity();
		case WORKING: return workingVelocity.GetVelocity();
		case START: return startVelocity.GetVelocity();
		case ADJUSTMENT: return adjustmentVelocity.GetVelocity();
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
