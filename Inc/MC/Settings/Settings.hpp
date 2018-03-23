/*
 * Settings.hpp
 *
 *  Created on: 23 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_SETTINGS_HPP_
#define MC_SETTINGS_HPP_

#include <stdint.h>
#include "MC/Settings/TimeoutSetting.hpp"

#define MAX_COUNTER (UINT32_MAX-1)

#define	PERFORATION_TIME_OFFSET 0L
#define PERFORATION_TIME_FACTORY_SETTING 0.0

#define	IGNITION_TIME_OFFSET 4L
#define IGNITION_TIME_FACTORY_SETTING 0.0

#define	INITIAL_POSITIONING_TIMEOUT_OFFSET 8L
#define INITIAL_POSITIONING_TIMEOUT_FACTORY_SETTING 5.0

#define	TORCH_UP_TIMEOUT_OFFSET 12L
#define TORCH_UP_TIMEOUT_FACTORY_SETTING 1.0

class Settings: public FlashDataBlock {
public:
	TimeoutSetting perforationTime;
	TimeoutSetting ignitionTime;
	TimeoutSetting initialPositioningTimeout;
	TimeoutSetting torchUpTime;
public:
	Settings();
};

extern Settings settings;

#endif /* MC_SETTINGS_HPP_ */
