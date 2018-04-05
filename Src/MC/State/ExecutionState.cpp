/*
 * MotionState.cpp
 *
 *  Created on: 26 мар. 2018 г.
 *      Author: alexey
 */

#include <MC/State/ExecutionDirection.hpp>
#include <MC/State/ExecutionState.hpp>

ExecutionState::ExecutionState():
running(false),
resuming(false),
pausing(false),
repositioning(false),
demoMode(false),
adjustmentMode(false){
}

void ExecutionState::Reset(){
	running = false;
	resuming = false;
	pausing = false;
	repositioning = false;
	demoMode = false;
	adjustmentMode = false;
	this->SetForwardDirection();
}

void ExecutionState::SetRunning(){ this->running = true;}

void ExecutionState::SetPaused(){ this->running = false;}

bool ExecutionState::IsRunning(){ return this->running; }

bool ExecutionState::IsPaused(){ return !this->running; }

void ExecutionState::SetResuming(){ this->resuming = true; }

void ExecutionState::SetNonResuming(){ this->resuming = false; }

bool ExecutionState::IsResuming(){ return this->resuming; }

void ExecutionState::SetPausing(){ this->pausing = true; }

void ExecutionState::SetNonPausing(){ this->pausing = false; }

bool ExecutionState::IsPausing(){ return this->pausing; }
