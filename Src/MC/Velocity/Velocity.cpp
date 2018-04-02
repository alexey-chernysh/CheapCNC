/*
 * Velocity.cpp
 *
 *  Created on: 27 ����. 2018 �.
 *      Author: Sales
 */

#include <MC/Velocity/Velocity.hpp>
#include "MC/General.h"
#include "MC/Position.hpp"
#include "MC/MotionController.hpp"
#include "MC/Settings/Settings.hpp"

Velocity::Velocity(float initialValue){
	this->stepSize = GetStep4Velocity(initialValue);
}

Velocity::~Velocity(){
}

void Velocity::Set(float newValue){
	this->SetStepSize(newValue);
}

float Velocity::Get(){
	return GetVelocity4Step(this->stepSize);
}

void Velocity::SetStepSize(float newValue){
	this->stepSize = GetStep4Velocity(newValue);
}

uint32_t Velocity::GetStepSize(){
	return this->stepSize;
}

float Velocity::GetVelocity4Step(uint32_t stepSize){
	return  60.0*stepSize
			*GetOneBitLengthMM()
			*motionController->timerFrequency.GetTimerFrequency();
}

uint32_t Velocity::GetStep4Velocity(float velocity){
	float mmInTick = velocity/60.0/motionController->timerFrequency.GetTimerFrequency();
	return (uint32_t)(mmInTick/GetOneBitLengthMM());
}

float Velocity::GetMinVelocity(){
	return  GetVelocity4Step(1L);
}

float Velocity::GetMaxVelocity(){
	return  60.0
			*motionController->timerFrequency.GetTimerFrequency()
			*(N_OF_TOOTH*TOOTH_STEP)/STEP_PER_ROTATION/2;
}

