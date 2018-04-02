/*
 * FreeRunVelocity.hpp
 *
 *  Created on: 2 апр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_VELOCITY_FREERUNVELOCITY_HPP_
#define MC_VELOCITY_FREERUNVELOCITY_HPP_

#include <MC/Velocity/Velocity.hpp>
#include "MC/Settings/FloatSetting.hpp"

class FreeRunVelocity : public Velocity {
private:
	FloatSetting* _value; // in mm in minute
public:
	FreeRunVelocity();
	virtual ~FreeRunVelocity();
	virtual void Set(float newVelocity);
	virtual float Get();
};

#endif /* MC_VELOCITY_FREERUNVELOCITY_HPP_ */
