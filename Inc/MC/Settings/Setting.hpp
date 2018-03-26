/*
 * Setting.hpp
 *
 *  Created on: 12 мар. 2018 г.
 *      Author: Sales
 */

#ifndef SETTING_HPP_
#define SETTING_HPP_

#include <MC/Settings/FlashDataBlock.hpp>
#include <stdint.h>

class Setting {
protected:
	uint32_t offset;
public:
	Setting(uint32_t _offset);
};

class SettingInt32 : public Setting {
public:
	SettingInt32(uint32_t firstRunSetting, uint32_t _offset);
	uint32_t Get();
	void Set(uint32_t newValue);
};

class FloatSetting : public Setting {
public:
	FloatSetting(float firstRunSetting, uint32_t _offset);
	float Get();
	void Set(float newValue);
};

#endif /* SETTING_HPP_ */
