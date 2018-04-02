/*
 * TimeoutSetting.cpp
 *
 *  Created on: 23 мар. 2018 г.
 *      Author: Sales
 */

#include <stdint.h>
#include <MC/Settings/TimeoutSetting.hpp>
#include "MC/MotionController.hpp"

TimeoutSetting::TimeoutSetting(float factorySetting /* заводская установка в секундах */, Settings *_parent, uint32_t offset)
:SettingInt32((uint32_t)(factorySetting*GetTimerFrequency()), _parent, offset){
}

