/*
 * Setting.cpp
 *
 *  Created on: 12 мар. 2018 г.
 *      Author: Sales
 */

#include "MC/Settings/Setting.hpp"
#include "MC/Settings/Settings.hpp"
#include "MC/MotionController.hpp"

Setting::Setting(uint32_t _offset) {
	this->offset = _offset;
}

SettingInt32::SettingInt32(uint32_t firstRunSetting, uint32_t _offset):Setting(_offset){
	if(!motionController->DataIntegrityIsOK()) motionController->SetInt32(firstRunSetting, offset);
}

uint32_t SettingInt32::Get(){
	return motionController->GetInt32(offset);
}

void SettingInt32::Set(uint32_t newValue){
	motionController->SetInt32(newValue, offset);
}

FloatSetting::FloatSetting(float firstRunSetting, uint32_t _offset):Setting(_offset){
	if(!motionController->DataIntegrityIsOK()) motionController->SetFloat(firstRunSetting, offset);
};

float FloatSetting::Get(){
	return motionController->GetFloat(offset);
};

void FloatSetting::Set(float newValue){
	motionController->SetFloat(newValue, offset);
};
