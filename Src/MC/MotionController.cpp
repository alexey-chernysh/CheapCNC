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

static float timerFrequency;
static float oneBitLengthMM;

static bool running;
static bool forward;
static bool resuming;
static bool pausing;

static uint32_t stepIncrement;
static uint32_t currentStepSize;
static uint32_t startStopStepSize;
static uint32_t resumingStepSize;
static uint32_t pausingStepSize;

static float startVelocity;
static float freeRunVelocity;
static WorkingVelocity workingVelocity;
static float adjustmentVelocity;
static float acceleration;

static Sequence* sequence;
static uint32_t sequenceSize;
static uint32_t currentMotionNum;
static Motion* currentMotion;

MotionController motionController;

MotionController::MotionController() {
	initMath();

	running = false;
	forward = true;
	resuming = false;
	pausing = false;

	timerFrequency = ((float)HAL_RCC_GetPCLK2Freq())/(PWM_PRESCALER+1)/(PWM_PERIOD+1);
	float scale = (float)(1LL<<POSITION_FIRST_SIGNIFICANT_BIT);
	oneBitLengthMM = (N_OF_TOOTH * TOOTH_STEP)/STEP_PER_ROTATION/(MAX_MICROSTEP + 1.0)/scale;

	startVelocity =   100.0/60.0;
	freeRunVelocity = 5000.0/60.0;
	adjustmentVelocity = 10.0/60.0;

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
	forward = true;
	resuming = false;
	pausing = false;

	currentMotionNum = 0;
	currentMotion = (Motion*)sequence->GetAction(currentMotionNum);
}

bool MotionController::IsRunning(){ return running; }

bool MotionController::IsPaused(){ return !running; }

float MotionController::GetTimerFrequency(){ return timerFrequency; }

float MotionController::GetOneBitLengthMM(){ return oneBitLengthMM; }

float MotionController::GetMinVelocity(){ return 60.0*timerFrequency*oneBitLengthMM; }

float MotionController::GetMaxVelocity(){ return 60.0*timerFrequency*(N_OF_TOOTH*TOOTH_STEP)/STEP_PER_ROTATION/2; }

void MotionController::IterateActionNum(){
	if(forward)
		currentMotionNum++;
	else
		currentMotionNum--;
}

void MotionController::OnTimer(){
	if(currentMotion != 0){
		bool anotherStepNeeded = true;
		if(running) {
			if(forward){
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
			SetMotionForward();
			SetResuming();
		};
		break;
	case 'P': // Stop/Pause
		if(IsRunning())
			SetPausing();
		break;
	case 'B': // Rewind
		if(IsPaused()){
			SetMotionBackward();
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

bool MotionController::MotionIsForward(){ return forward; }

bool MotionController::MotionIsBackward(){ return !forward; }

void MotionController::SetMotionForward(){ forward = true; }

void MotionController::SetMotionBackward(){ forward = false; }

int64_t MotionController::GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2) {
	int64_t sqr1 = stepSize1*((int64_t)stepSize1);
	int64_t sqr2 = stepSize2*((int64_t)stepSize2);
	int64_t result = ((sqr2-sqr1)/stepIncrement)/2;
	if(result >= 0) return result;
	else return -result;
}

uint32_t MotionController::GetCurrentStepSize(){ return currentStepSize; };

float MotionController::GetVelocity4Step(uint32_t stepSize){
	return 60.0*stepSize*oneBitLengthMM*timerFrequency;
}

uint32_t MotionController::GetStepIncrement(){ return stepIncrement; }

uint32_t MotionController::GetStep4Velocity(float velocity){
	float mmInTick = velocity/timerFrequency;
	return (uint32_t)(mmInTick/oneBitLengthMM);
}

int64_t MotionController::Get64bitForDoubleMM(double mm){ return (int64_t)(mm/oneBitLengthMM); };

double MotionController::GetDoubleMMFor64bit(int64_t iValue){	return oneBitLengthMM*iValue; };

uint32_t MotionController::GetStepSize(MOTION_VELOCITY t) {
	switch (t){
		case FREE_RUN: return GetStep4Velocity(freeRunVelocity);
		case WORKING: return workingVelocity.GetStepSize();
		case START: return GetStep4Velocity(startVelocity);
		case ADJUSTMENT: return GetStep4Velocity(adjustmentVelocity);
		default: return 0;
	}
}

float MotionController::GetStartVelocity(){ return startVelocity; }
float MotionController::GetFreeRunVelocity() { return freeRunVelocity; }
float MotionController::GetWorkingVelocity() { return workingVelocity.GetVelocity(); }

extern "C"{
void MC_OnTimer(){
	motionController.OnTimer();
}

void MC_onControlKey(char controlKey){
	motionController.OnControlKey(controlKey);
}

}
