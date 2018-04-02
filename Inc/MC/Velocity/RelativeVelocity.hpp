/*
 * RelativeVelocity.hpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_VELOCITY_RELATIVEVELOCITY_HPP_
#define MC_VELOCITY_RELATIVEVELOCITY_HPP_

#include "MC/Velocity/Velocity.hpp"
#include "MC/Settings/FloatSetting.hpp"

class FreeRunVelocity;

class RelativeVelocity: public Velocity {
private:
	FreeRunVelocity* _freeRunVelocity;  // reference to instance of free run veocity
	FloatSetting* _ratio; // ratio to free run velocity
public:
	RelativeVelocity(FloatSetting* currentSetting, FreeRunVelocity* frv);
	virtual ~RelativeVelocity();
	virtual void Set(float newVelocity);
	virtual float Get();
};

#endif /* MC_VELOCITY_RELATIVEVELOCITY_HPP_ */
