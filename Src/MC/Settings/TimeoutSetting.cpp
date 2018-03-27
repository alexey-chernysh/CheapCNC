/*
 * TimeoutSetting.cpp
 *
 *  Created on: 23 ���. 2018 �.
 *      Author: Sales
 */

#include <stdint.h>
#include <MC/Settings/TimeoutSetting.hpp>
#include "MC/MotionController.hpp"

TimeoutSetting::TimeoutSetting(float factorySetting /* ��������� ��������� � �������� */, uint32_t offset)
:SettingInt32((uint32_t)(factorySetting*motionController->GetTimerFrequency()), offset){
}

