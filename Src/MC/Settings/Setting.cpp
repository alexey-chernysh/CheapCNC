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
	if(!settings.DataIntegrityIsOK()) settings.SetInt32(firstRunSetting, offset);
}

uint32_t SettingInt32::Get(){
	return settings.GetInt32(offset);
}

void SettingInt32::Set(uint32_t newValue){
	settings.SetInt32(newValue, offset);
}

FloatSetting::FloatSetting(float firstRunSetting, uint32_t _offset):Setting(_offset){
	if(!settings.DataIntegrityIsOK()) settings.SetFloat(firstRunSetting, offset);
};

float FloatSetting::Get(){
	return settings.GetFloat(offset);
};

void FloatSetting::Set(float newValue){
	settings.SetFloat(newValue, offset);
};
