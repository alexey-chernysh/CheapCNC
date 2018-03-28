/*
 * MotionController.cpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#include <stdint.h>
#include <MC/ExecutionDirection.hpp>
#include <MC/Motions/Acceleration.hpp>
#include <MC/Motions/Motion.hpp>
#include <MC/Motions/Velocity.hpp>
#include <MC/Settings/Settings.hpp>
#include "MC/MotionController.hpp"

MotionController* motionController = 0;

MotionController::MotionController()
:TimerFrequency()
,Settings()
,positionX()
,positionY()
,velocityProfile()
,executionState()
,startStopStepSize(velocityProfile.startVelocity.GetStepSize())
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
			if((currentActionNum >= 0)&&(currentActionNum < sequenceSize)){
				currentAction = (Motion*)sequence->GetAction(currentActionNum);
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
        resumingStepSize += this->velocityProfile.acceleration.GetStepIncrement();
        if(result < _currentStepSize) return result;
        else {
        	this->executionState.SetNonResuming();
            return _currentStepSize;
        }
    } else return _currentStepSize;
}

void MotionController::SetPausing(){
    pausingStepSize = velocityProfile.GetCurrentStepSize();
    executionState.SetNonResuming();
    executionState.SetPausing();
}

uint32_t MotionController::GetPausingStepSize(uint32_t currentSS){
    if(this->executionState.IsPausing()){
        uint32_t result = pausingStepSize;
        pausingStepSize -= this->velocityProfile.acceleration.GetStepIncrement();
        if(result > startStopStepSize) return result;
        else {
            this->executionState.SetPaused();
            this->executionState.SetNonPausing();
            return startStopStepSize;
        }
    } else return currentSS;
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

}
