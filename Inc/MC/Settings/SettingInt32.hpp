/*
 * SettingInt32.hpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_SETTINGS_SETTINGINT32_HPP_
#define MC_SETTINGS_SETTINGINT32_HPP_

#include <MC/Settings/Setting.hpp>

class Settings;

class SettingInt32 : public Setting {
public:
	SettingInt32(uint32_t firstRunSetting, Settings *parent, uint32_t _offset);
	uint32_t Get();
	void Set(uint32_t newValue);
};

#endif /* MC_SETTINGS_SETTINGINT32_HPP_ */
