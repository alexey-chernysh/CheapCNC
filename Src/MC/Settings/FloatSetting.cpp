/*
 * FloatSetting.cpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#include "MC/Settings/FloatSetting.hpp"
#include "MC/Settings/Settings.hpp"

FloatSetting::FloatSetting(float firstRunSetting, Settings *_parent, uint32_t _offset):Setting(_parent, _offset){
	if(!this->parent->DataIntegrityIsOK())
		this->parent->SetFloat(firstRunSetting, this->GetOffset());
};

float FloatSetting::Get(){
	return this->parent->GetFloat(this->GetOffset());
};

void FloatSetting::Set(float newValue){
	this->parent->SetFloat(newValue, this->GetOffset());
};
