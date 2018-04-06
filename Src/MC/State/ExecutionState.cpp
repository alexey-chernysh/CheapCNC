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

void ExecutionState::SetRunningFlag(){ this->running = true;}
void ExecutionState::ResetRunningFlag(){ this->running = false;}
bool ExecutionState::RunningFlagIsOn(){ return this->running; }

void ExecutionState::SetResumingFlag(){ this->resuming = true; }
void ExecutionState::ResetResumingFlag(){ this->resuming = false; }
bool ExecutionState::ResumingFlagIsOn(){ return this->resuming; }

void ExecutionState::SetPausingFlag(){ this->pausing = true; }
void ExecutionState::ResetPausingFlag(){ this->pausing = false; }
bool ExecutionState::PausingFlagIsOn(){ return this->pausing; }

void ExecutionState::SetDemoModeFlag(){ this->demoMode = true; }
void ExecutionState::ResetDemoModeFlag(){ this->demoMode = false; }
bool ExecutionState::DemoModeFlagIsOn(){ return this->demoMode; }

void ExecutionState::SetRepositioningModeFlag(){ this->repositioning = true; }
void ExecutionState::ResetRepositioningModeFlag(){ this->repositioning = false; }
bool ExecutionState::RepositioningFlagIsOn(){ return this->repositioning; }

void ExecutionState::SetAdjastmentModeFlag(){ this->adjustmentMode = true; }
void ExecutionState::ResetAdjastmentModeFlag(){ this->adjustmentMode = false; }
bool ExecutionState::AdjustmentFlagIsOn(){ return this->adjustmentMode; }
