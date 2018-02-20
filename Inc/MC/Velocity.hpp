/*
 * Velocity.h
 *
 *  Created on: 28 џэт. 2018 у.
 *      Author: Sales
 */

#ifndef MC_VELOCITY_HPP_
#define MC_VELOCITY_HPP_

#include "Math/int_math.h"
#include "MC/VelocitySettings.hpp"

class Velocity {
private:
	MOTION_VELOCITY type;
public:
	Velocity(MOTION_VELOCITY t);
	virtual ~Velocity();
	int32_t getStepSize();
};

#endif /* MC_VELOCITY_HPP_ */
