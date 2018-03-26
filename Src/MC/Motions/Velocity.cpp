/*
 * Velocity.cpp
 *
 *  Created on: 27 ����. 2018 �.
 *      Author: Sales
 */

#include <MC/Motions/Velocity.hpp>
#include "MC/MotionController.hpp"
#include "MC/Settings/Settings.hpp"

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
	return  stepSize*60.0
			*motionController.GetOneBitLengthMM()
			*motionController.GetTimerFrequency;
}

uint32_t Velocity::GetStep4Velocity(float velocity){
	float mmInTick = velocity/60.0/motionController.GetTimerFrequency();
	return (uint32_t)(mmInTick/motionController.GetOneBitLengthMM());
}

FreeRunVelocity::FreeRunVelocity():
Velocity(0.0),
_value(&(settings.freeRunVelocity)){
	this->SetStepSize(this->_value->Get());
}

FreeRunVelocity::~FreeRunVelocity() {
}

void FreeRunVelocity::Set(float newVelocity) {
	this->_value->Set(newVelocity);
	this->SetStepSize(this->Get());
};

float FreeRunVelocity::Get() {
	return this->_value->Get();
};

RelativeVelocity::RelativeVelocity(FloatSetting* currentSetting, FreeRunVelocity* frv):
Velocity(0.0),
_freeRunVelocity(frv),
_ratio(currentSetting){
	this->Set(this->_freeRunVelocity->Get()*this->_ratio->Get());
}

void RelativeVelocity::Set(float newVelocity){
	float tmpRatio = newVelocity/this->_freeRunVelocity->Get();
	if(tmpRatio < 0.0) tmpRatio = 0.0;
	if(tmpRatio > 1.0) tmpRatio = 1.0;
	this->_ratio->Set(tmpRatio);
	this->SetStepSize(this->Get());
}

float RelativeVelocity::Get(){
	return (this->_freeRunVelocity->Get() * this->_ratio->Get());
}

WorkingVelocity::WorkingVelocity(FreeRunVelocity* frv):
RelativeVelocity(&(settings.workingVelocity), frv),
_autoLimitStepSize(0),
_autoLimitRatio(&(settings.autoLimitRatio)) {
	SetAutoLimitStepSize();
}

void WorkingVelocity::SetAutoLimitStepSize(){
	this->_autoLimitStepSize = this->GetStepSize()*this->_autoLimitRatio->Get();
}

void WorkingVelocity::SetLimit(float newLimitRatio){
	this->_autoLimitRatio->Set(newLimitRatio);
}

float WorkingVelocity::GetLimit(){
	return 	this->_autoLimitRatio->Get();
}

uint32_t WorkingVelocity::GetAutoLimitStepSize(){}
