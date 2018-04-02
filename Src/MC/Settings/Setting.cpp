/*
 * Setting.cpp
 *
 *  Created on: 12 ���. 2018 �.
 *      Author: Sales
 */

#include "MC/Settings/Setting.hpp"
#include "MC/Settings/Settings.hpp"
#include "MC/MotionController.hpp"

Setting::Setting(Settings *_parent, uint32_t _offset) {
	this->parent = _parent;
	this->offset = _offset;
}

uint32_t Setting::GetOffset(){
	return this->offset;
}
