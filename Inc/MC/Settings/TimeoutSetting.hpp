/*
 * TimeoutSetting.hpp
 *
 *  Created on: 23 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_TIMEOUTSETTING_HPP_
#define MC_TIMEOUTSETTING_HPP_

#include "MC/Settings/Setting.hpp"

class TimeoutSetting: public SettingInt32 {
public:
	TimeoutSetting(float firstRunSetting /* ��������� ��������� � �������� */, uint32_t offset);
};

#endif /* MC_TIMEOUTSETTING_HPP_ */
