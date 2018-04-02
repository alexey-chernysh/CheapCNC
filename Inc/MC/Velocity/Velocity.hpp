/*
 * Velocity.hpp
 *
 *  Created on: 27 ����. 2018 �.
 *      Author: Sales
 */

#ifndef MC_VELOCITY_VELOCITY_HPP_
#define MC_VELOCITY_VELOCITY_HPP_

#include <stdint.h>

class Velocity {
protected:
	uint32_t stepSize;
public:
	Velocity(float initialValue);
	virtual float Get();
	virtual void Set(float newVelocity);
	uint32_t GetStepSize();
	virtual ~Velocity();
protected:
	void SetStepSize(float newVelocity);
public:
	// static methods
	static float  GetVelocity4Step(uint32_t stepSize);
	static uint32_t GetStep4Velocity(float velocity);
	static float GetMinVelocity();
	static float GetMaxVelocity();
};

#endif /* MC_VELOCITY_VELOCITY_HPP_ */
