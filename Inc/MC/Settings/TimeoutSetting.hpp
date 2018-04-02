/*
 * TimeoutSetting.hpp
 *
 *  Created on: 23 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_TIMEOUTSETTING_HPP_
#define MC_TIMEOUTSETTING_HPP_

#include "MC/Settings/SettingInt32.hpp"

class Settings;

class TimeoutSetting: public SettingInt32 {
public:
	TimeoutSetting(float firstRunSetting /* заводская установка в секундах */, Settings *_parent, uint32_t offset);
};

#endif /* MC_TIMEOUTSETTING_HPP_ */
