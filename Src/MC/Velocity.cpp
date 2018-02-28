/*
 * Velocity.cpp
 *
 *  Created on: 27 ����. 2018 �.
 *      Author: Sales
 */

#include "MC/Velocity.hpp"
#include "MC/MotionController.hpp"

Velocity::Velocity(float initialValue){
	this->Set(initialValue);
}

Velocity::~Velocity() {
	// TODO Auto-generated destructor stub
}

void Velocity::Set(float newValue){
	this->stepSize = GetStep4Velocity(newValue);
}

float Velocity::Get(){
	return GetVelocity4Step(this->stepSize);
}

uint32_t Velocity::GetStepSize(){
	return this->stepSize;
}

float Velocity::GetVelocity4Step(uint32_t stepSize){
	return  stepSize
			*MotionController::GetOneBitLengthMM()
			*MotionController::GetTimerFrequency();
}

uint32_t Velocity::GetStep4Velocity(float velocity){
	float mmInTick = velocity/MotionController::GetTimerFrequency();
	return (uint32_t)(mmInTick/MotionController::GetOneBitLengthMM());
}

WorkingVelocity::WorkingVelocity(float initialValue):Velocity(initialValue){
	SetLimit();
}

void WorkingVelocity::Set(float newValue){
	this->Velocity::Set(newValue);
	SetLimit();
}

void WorkingVelocity::SetLimit(){
	// set auto limit at 80% from WorkingVelocity
	this->autoLimit = (204L*this->stepSize)>>8;
}

uint32_t WorkingVelocity::GetAutoLimit(){
	return this->autoLimit;
}
