/*
 * Settings.cpp
 *
 *  Created on: 23 мар. 2018 г.
 *      Author: Sales
 */

#include <MC/Settings/Settings.hpp>
#include "MC/Settings/FlashDataBlock.hpp"

Settings::Settings():
perforationTime(PERFORATION_TIME_FACTORY_SETTING, PERFORATION_TIME_OFFSET),
ignitionTime(IGNITION_TIME_FACTORY_SETTING, IGNITION_TIME_OFFSET),
initialPositioningTimeout(INITIAL_POSITIONING_TIMEOUT_FACTORY_SETTING, INITIAL_POSITIONING_TIMEOUT_OFFSET),
torchUpTime(TORCH_UP_TIMEOUT_FACTORY_SETTING, TORCH_UP_TIMEOUT_OFFSET){
	this->CommitChanges();
}

Settings settings;

