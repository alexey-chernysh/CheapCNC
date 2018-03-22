/*
 * Setting.cpp
 *
 *  Created on: 12 мар. 2018 г.
 *      Author: Sales
 */

#include "MC/Setting.hpp"

Setting::Setting(uint32_t _offset) {
	this->offset = _offset;
}

SettingFloat::SettingFloat(float defaultValue, uint32_t _offset):Setting(_offset){
	if(!settingsBlock.DataIntegrityIsOK()) settingsBlock.SetFloat(defaultValue, offset);
};
float SettingFloat::Get(){ return settingsBlock.GetFloat(offset); };
void SettingFloat::Set(float newValue){ settingsBlock.SetFloat(newValue, offset);};
