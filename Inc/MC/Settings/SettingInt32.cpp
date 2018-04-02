/*
 * SettingInt32.cpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#include <MC/Settings/Settings.hpp>
#include <MC/Settings/SettingInt32.hpp>

SettingInt32::SettingInt32(uint32_t firstRunSetting, Settings *_parent, uint32_t _offset):Setting(_parent, _offset){
	if(!this->parent->DataIntegrityIsOK())
		this->parent->SetInt32(firstRunSetting, this->GetOffset());
}

uint32_t SettingInt32::Get(){
	return this->parent->GetInt32(this->GetOffset());
}

void SettingInt32::Set(uint32_t newValue){
	this->parent->SetInt32(newValue, this->GetOffset());
}

