/*
 * Settings.hpp
 *
 *  Created on: 23 ���. 2018 �.
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

#define	ACCELERATION_OFFSET 16L
#define ACCELERATION_FACTORY_SETTING 100.0

#define	FREE_RUN_VELOCITY_OFFSET 20L
#define	FREE_RUN_VELOCITY_FACTORY_SETTING 5000.0

#define	WORKING_VELOCITY_OFFSET 24L
#define	WORKING_VELOCITY_FACTORY_SETTING 1.0

#define	AUTO_LIMIT_RATIO_OFFSET 28L
#define	AUTO_LIMIT_RATIO_FACTORY_SETTING 0.8

#define	START_VELOCITY_OFFSET 32L
#define	START_VELOCITY_FACTORY_SETTING 0.1

#define	ADJUSTMENT_VELOCITY_OFFSET 36L
#define	ADJUSTMENT_VELOCITY_FACTORY_SETTING 0.05

class Settings: public FlashDataBlock {
public:
	TimeoutSetting perforationTimeSetting;
	TimeoutSetting ignitionTimeSetting;
	TimeoutSetting initialPositioningTimeoutSetting;
	TimeoutSetting torchUpTimeSetting;
	FloatSetting accelerationSetting;
	FloatSetting freeRunVelocitySetting;
	FloatSetting workingVelocitySetting;
	FloatSetting autoLimitRatioSetting;
	FloatSetting startVelocitySetting;
	FloatSetting adjustmentVelocitySetting;
public:
	Settings();
};

#endif /* MC_SETTINGS_HPP_ */
