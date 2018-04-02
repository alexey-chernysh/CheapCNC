/*
 * Settings.cpp
 *
 *  Created on: 23 ���. 2018 �.
 *      Author: Sales
 */

#include <MC/Settings/Settings.hpp>
#include "MC/Settings/FlashDataBlock.hpp"

Settings::Settings():
FlashDataBlock(),
perforationTimeSetting(PERFORATION_TIME_FACTORY_SETTING, this, PERFORATION_TIME_OFFSET),
ignitionTimeSetting(IGNITION_TIME_FACTORY_SETTING, this, IGNITION_TIME_OFFSET),
initialPositioningTimeoutSetting(INITIAL_POSITIONING_TIMEOUT_FACTORY_SETTING, this, INITIAL_POSITIONING_TIMEOUT_OFFSET),
torchUpTimeSetting(TORCH_UP_TIMEOUT_FACTORY_SETTING, this, TORCH_UP_TIMEOUT_OFFSET),
accelerationSetting(ACCELERATION_FACTORY_SETTING, this, ACCELERATION_OFFSET),
freeRunVelocitySetting(FREE_RUN_VELOCITY_FACTORY_SETTING, this, FREE_RUN_VELOCITY_OFFSET),
workingVelocitySetting(WORKING_VELOCITY_FACTORY_SETTING, this, WORKING_VELOCITY_OFFSET),
autoLimitRatioSetting(AUTO_LIMIT_RATIO_FACTORY_SETTING, this, AUTO_LIMIT_RATIO_OFFSET),
startVelocitySetting(START_VELOCITY_FACTORY_SETTING, this, START_VELOCITY_OFFSET),
adjustmentVelocitySetting(ADJUSTMENT_VELOCITY_FACTORY_SETTING, this, ADJUSTMENT_VELOCITY_OFFSET){
	this->CommitChangesToFlash();
}
