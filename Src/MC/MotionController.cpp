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
#include "MC/VelocitySettings.hpp"

MotionController::MotionController() {
	running = false;
	forward = true;
	resuming = false;
	pausing = false;

	timerFrequency = ((float)HAL_RCC_GetPCLK2Freq())/(PWM_PRESCALER+1)/(PWM_PERIOD+1);
	float scale = (float)(1LL<<POSITION_FIRST_SIGNIFICANT_BIT);
	oneBitLengthMM = (N_OF_TOOTH * TOOTH_STEP)/STEP_PER_ROTATION/(MAX_MICROSTEP + 1.0)/scale;

	sequence = Sequence();
	sequenceSize = sequence.GetSize();
	currentMotionNum = 0;
	currentMotion = (Motion*)sequence.GetAction(currentMotionNum);

	initMath();
}

MotionController::~MotionController() {
	// TODO Auto-generated destructor stub
}

MotionController* MotionController::GetInstance(){
    static MotionController instance;
    return &instance;
}

void MotionController::Reset(){
	running = false;
	forward = true;
	resuming = false;
	pausing = false;

	currentMotionNum = 0;
	currentMotion = (Motion*)sequence.GetAction(currentMotionNum);
}

bool MotionController::IsRunning(){ return running; };

bool MotionController::IsForward(){ return forward; };

float MotionController::GetTimerFrequency(){ return timerFrequency; };

float MotionController::GetOneBitLengthMM(){ return oneBitLengthMM; };

int64_t MotionController::Get64bitForDoubleMM(double mm){ return (int64_t)(mm/oneBitLengthMM); };

double MotionController::GetDoubleMMFor64bit(int64_t iValue){	return oneBitLengthMM*iValue; };

float MotionController::GetMinVelocity(){ return 60.0*timerFrequency*oneBitLengthMM; };

float MotionController::GetMaxVelocity(){ return 60.0*timerFrequency*(N_OF_TOOTH*TOOTH_STEP)/STEP_PER_ROTATION/2; };

void MotionController::IterateActionNum(){
	if(this->forward)
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
				currentMotion = (Motion*)sequence.GetAction(this->currentMotionNum);
				currentMotion->SetupMotion();
			} else this->Reset();
		}
	}
}

void MotionController::SetResuming(){
    resuming = true;
    pausing = false;
    startStopStepSize = VelocitySettings::GetInstance()->GetStepSize(START);
    stepIncrement = VelocitySettings::GetInstance()->GetStepIncrement();
    resumingStepSize = startStopStepSize;
}

int32_t MotionController::GetResumingStepSize(int32_t currentStepSize){
    if(resuming){
    	int32_t result = resumingStepSize;
        resumingStepSize += stepIncrement;
        if(result < currentStepSize) return result;
        else {
            resuming = false;
            return currentStepSize;
        }
    } else return currentStepSize;
}

void MotionController::SetPausing(){
    resuming = false;
    pausing = true;
    startStopStepSize = VelocitySettings::GetInstance()->GetStepSize(START);
    stepIncrement = VelocitySettings::GetInstance()->GetStepIncrement();
    pausingStepSize = VelocitySettings::GetInstance()->GetCurrentStepSize();
}

int32_t MotionController::GetPausingStepSize(int32_t currentStepSize){
    if(pausing){
        int32_t result = pausingStepSize;
        pausingStepSize -= stepIncrement;
        if(result > startStopStepSize) return result;
        else {
            running = false;
            pausing = false;
            return startStopStepSize;
        }
    } else return currentStepSize;
}

extern "C"{
void MC_OnTimer(){
	MotionController::GetInstance()->OnTimer();
}

void MC_Setup(){
	MotionController::GetInstance();
	VelocitySettings::GetInstance();
}

}
