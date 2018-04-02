/*
 * WorkingVelocity.hpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_VELOCITY_WORKINGVELOCITY_HPP_
#define MC_VELOCITY_WORKINGVELOCITY_HPP_

#include <stdint.h>
#include <MC/Velocity/FreeRunVelocity.hpp>
#include <MC/Velocity/RelativeVelocity.hpp>

class WorkingVelocity: public RelativeVelocity {
private:
	uint32_t _autoLimitStepSize;
	FloatSetting* _autoLimitRatio;
public:
	WorkingVelocity(FreeRunVelocity* frv);
	void SetLimit(float newLimitRatio);
	float GetLimit();
	uint32_t GetAutoLimitStepSize();
private:
	void SetAutoLimitStepSize();
};

#endif /* MC_VELOCITY_WORKINGVELOCITY_HPP_ */
