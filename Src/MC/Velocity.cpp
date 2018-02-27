/*
 * Velocity.cpp
 *
 *  Created on: 27 ����. 2018 �.
 *      Author: Sales
 */

#include "MC/Velocity.hpp"
#include "MC/MotionController.hpp"

Velocity::Velocity(float initialValue){
	this->SetVelocity(initialValue);
}

Velocity::~Velocity() {
	// TODO Auto-generated destructor stub
}

void Velocity::SetVelocity(float newValue){
	this->stepSize = MotionController::GetStep4Velocity(newValue);
}

float Velocity::GetVelocity(){
	return MotionController::GetVelocity4Step(this->stepSize);
}

uint32_t Velocity::GetStepSize(){
	return this->stepSize;
}

WorkingVelocity::WorkingVelocity(float initialValue):Velocity(initialValue){
	SetLimit();
}

void WorkingVelocity::SetVelocity(float newValue){
	this->Velocity::SetVelocity(newValue);
	SetLimit();
}

void WorkingVelocity::SetLimit(){
	// set auto limit at 80% from WorkingVelocity
	this->autoLimit = (204L*this->stepSize)>>8;
}

uint32_t WorkingVelocity::GetAutoLimit(){
	return this->autoLimit;
}
