/*
 * VelocityProfile.hpp
 *
 *  Created on: 27 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_VELOCITY_VELOCITYPROFILE_HPP_
#define MC_VELOCITY_VELOCITYPROFILE_HPP_

#include <stdint.h>
#include "MC/Enums.h"
#include <MC/Velocity/Acceleration.hpp>
#include <MC/Velocity/FreeRunVelocity.hpp>
#include <MC/Velocity/WorkingVelocity.hpp>
#include <MC/Velocity/RelativeVelocity.hpp>

class VelocityProfile {
public:
	FreeRunVelocity freeRunVelocity;
	WorkingVelocity workingVelocity;
	RelativeVelocity startVelocity;
	RelativeVelocity adjustmentVelocity;

	Acceleration acceleration;

private:
	uint32_t currentStepSize;

public:
	VelocityProfile();
	uint32_t GetStepSize(MOTION_VELOCITY t);
	float GetVelocity(MOTION_VELOCITY t);
	void SetCurrentStepSize(uint32_t newStepSIze);
	uint32_t GetCurrentStepSize();
	float GetCurrentVelocity();
};

#endif /* MC_VELOCITY_VELOCITYPROFILE_HPP_ */
