/*
 * FloatSetting.hpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_SETTINGS_FLOATSETTING_HPP_
#define MC_SETTINGS_FLOATSETTING_HPP_

#include <MC/Settings/Setting.hpp>

class Settings;

class FloatSetting: public Setting {
public:
	FloatSetting(float firstRunSetting, Settings *parent, uint32_t _offset);
	float Get();
	void Set(float newValue);
};


#endif /* MC_SETTINGS_FLOATSETTING_HPP_ */
