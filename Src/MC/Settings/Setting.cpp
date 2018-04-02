/*
 * Setting.cpp
 *
 *  Created on: 12 мар. 2018 г.
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
