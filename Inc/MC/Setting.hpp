/*
 * Setting.hpp
 *
 *  Created on: 12 мар. 2018 г.
 *      Author: Sales
 */

#ifndef SETTING_HPP_
#define SETTING_HPP_

#include <stdint.h>
#include "FlashDataBlock.hpp"

class Setting {
protected:
	uint32_t offset;
public:
	Setting(uint32_t _offset);
};

class SettingFloat : public Setting {
public:
	SettingFloat(float defaultValue, uint32_t _offset);
	float Get();
	void Set(float newValue);
};

#endif /* SETTING_HPP_ */
