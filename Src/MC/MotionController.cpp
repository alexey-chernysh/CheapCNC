/*
 * MotionController.cpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#include <stdint.h>
#include <MC/Motions/Motion.hpp>
#include <MC/Settings/Settings.hpp>
#include <MC/State/ExecutionDirection.hpp>
#include <MC/Velocity/Acceleration.hpp>
#include <MC/Velocity/Velocity.hpp>
#include "MC/MotionController.hpp"

MotionController* motionController = 0;

MotionController::MotionController()
:positionX()
,positionY()
,executionState()
,startStopStepSize(VelocityProfile::GetInstance()->startVelocity.GetStepSize())
,resumingStepSize(startStopStepSize)
,pausingStepSize(startStopStepSize){
	sequence = new Sequence();
	sequenceSize = sequence->GetSize();
	currentActionNum = 0;
	currentAction = (Motion*)sequence->GetAction(currentActionNum);
	currentAction->Init();

	// debug only
	this->SetResuming();

}

void MotionController::Reset(){
	this->executionState.Reset();

	currentActionNum = 0;
	currentAction = (Motion*)sequence->GetAction(currentActionNum);
}

void MotionController::IterateActionNum(){
	if(this->executionState.DirectionIsForward())
		currentActionNum++;
	else
		currentActionNum--;
}

void MotionController::OnTimer(){
	if(currentAction != 0){
		bool anotherStepNeeded = true;
		if(this->executionState.RunningFlagIsOn()) {
			if(this->executionState.DirectionIsForward()){
				anotherStepNeeded = currentAction->IterateForward();
			} else {
				anotherStepNeeded = currentAction->IterateBackward();
			}
		}

		if(anotherStepNeeded) return;
		else{
			IterateActionNum();
			if((currentActionNum >= 0)&&(currentActionNum < sequenceSize)){
				currentAction = (Motion*)sequence->GetAction(currentActionNum);
				currentAction->Init();
			} else Reset();
		}
	}
}

void MotionController::StartResuming(){
	resumingStepSize = startStopStepSize;
	this->executionState.SetResumingFlag();
	this->executionState.ResetPausingFlag();
	this->executionState.SetRunningFlag();
}

void MotionController::SetResuming(){
	if(!this->executionState.RunningFlagIsOn()){
		this->executionState.SetForwardDirection();
		this->StartResuming();
	}
}

void MotionController::SetResumingBackward(){
	if(!this->executionState.RunningFlagIsOn()){
		this->executionState.SetBackwardDirection();
		this->StartResuming();
	}
}

void MotionController::SetPausing(){
	if(this->executionState.RunningFlagIsOn()){
	    pausingStepSize = VelocityProfile::GetInstance()->GetCurrentStepSize();
	    executionState.ResetResumingFlag();
	    executionState.SetPausingFlag();
	}
}

uint32_t MotionController::GetResumingStepSize(uint32_t _currentStepSize){
    if(this->executionState.ResumingFlagIsOn()){
    	uint32_t result = resumingStepSize;
        resumingStepSize += VelocityProfile::GetInstance()->acceleration.GetStepIncrement();
        if(result < _currentStepSize) return result;
        else {
        	this->executionState.ResetResumingFlag();
            return _currentStepSize;
        }
    } else return _currentStepSize;
}

uint32_t MotionController::GetPausingStepSize(uint32_t currentSS){
    if(this->executionState.PausingFlagIsOn()){
        uint32_t result = pausingStepSize;
        pausingStepSize -= VelocityProfile::GetInstance()->acceleration.GetStepIncrement();
        if(result > startStopStepSize) return result;
        else {
            this->executionState.ResetRunningFlag();
            this->executionState.ResetPausingFlag();
            return startStopStepSize;
        }
    } else return currentSS;
}

void MotionController::OnControlKey(char controlKey){
	switch(controlKey){
	case 'R': // Start/Resume
		SetResuming();
		break;
	case 'P': // Stop/Pause
		SetPausing();
		break;
	case 'B': // Rewind
		SetResumingBackward();
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

#define MAX_MESSAGE_SIZE 64

static char messageBuffer[MAX_MESSAGE_SIZE];

uint8_t dtoa(char *buffer, double d) {
	uint8_t result = 0;
	bool minus = (d<0);
	double tmpD;
	if(minus) tmpD = -d;
	else tmpD = d;
	uint32_t tmpUI = d*100;

	buffer[result++] = tmpUI % 10;
	tmpUI /= 10;

	buffer[result++] = tmpUI % 10;
	tmpUI /= 10;

	buffer[result++] = '.';

	do {
		buffer[result++] = tmpUI % 10;
		tmpUI /= 10;
	} while(tmpUI>0);

	if(minus) buffer[result++] = '-';

	uint8_t n = result/2;
	for(uint8_t i=0; i<n; i++){
		uint8_t oppositeNum = result - i -1;
		char swap = buffer[i];
		buffer[i] = buffer[oppositeNum];
		buffer[oppositeNum] = swap;
	}
	return result;
}

extern "C"{

void MC_Init(){
	motionController = new MotionController();
}

void MC_OnTimer(){
	motionController->OnTimer();
}

void MC_onControlKey(char controlKey){
	motionController->OnControlKey(controlKey);
}

char* prepareUSBMessage(uint32_t requestNum){
	double px = motionController->positionX.GetMM();
	double py = motionController->positionY.GetMM();
	int semiPos  = dtoa(&messageBuffer[0], px);
	messageBuffer[semiPos] = ';';
	int nullPos  = dtoa(&messageBuffer[semiPos+1], py);
	messageBuffer[nullPos] = 0;
	return messageBuffer;
}

}
