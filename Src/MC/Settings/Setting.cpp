/*
 * Setting.cpp
 *
 *  Created on: 12 мар. 2018 г.
 *      Author: Sales
 */

#include "MC/Settings/Setting.hpp"
#include "MC/Settings/Settings.hpp"

Setting::Setting(uint32_t _offset) {
	this->offset = _offset;
}

SettingInt32::SettingInt32(uint32_t firstRunSetting, uint32_t _offset):Setting(_offset){
	if(!settingsBlock.DataIntegrityIsOK()) settingsBlock.SetInt32(firstRunSetting, offset);
}

uint32_t SettingInt32::Get(){
	return settingsBlock.GetInt32(offset);
}

void SettingInt32::Set(uint32_t newValue){
	settingsBlock.SetInt32(newValue, offset);
}

SettingFloat::SettingFloat(float firstRunSetting, uint32_t _offset):Setting(_offset){
	if(!settingsBlock.DataIntegrityIsOK()) settingsBlock.SetFloat(firstRunSetting, offset);
};

float SettingFloat::Get(){
	return settingsBlock.GetFloat(offset);
};

void SettingFloat::Set(float newValue){
	settingsBlock.SetFloat(newValue, offset);
};
