/*
 * Velocity.hpp
 *
 *  Created on: 27 ����. 2018 �.
 *      Author: Sales
 */

#ifndef MC_VELOCITY_HPP_
#define MC_VELOCITY_HPP_

#include <stdint.h>

#define WORKING_VELOCITY 16.666

class Velocity {
protected:
	uint32_t stepSize;
public:
	Velocity(float initialValue = 0.0);
	virtual ~Velocity();
	virtual void SetVelocity(float newValue);
	float GetVelocity();
	uint32_t GetStepSize();

public:
	// static methods
	static float  GetVelocity4Step(uint32_t stepSize);
	static uint32_t GetStep4Velocity(float velocity);
};

class WorkingVelocity: public Velocity {
private:
	uint32_t autoLimit;
	void SetLimit();
public:
	WorkingVelocity(float initialValue = WORKING_VELOCITY);
	virtual void SetVelocity(float newValue);
	uint32_t GetAutoLimit();
};

#endif /* MC_VELOCITY_HPP_ */
