/*
 * Velocity.hpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_VELOCITY_HPP_
#define MC_VELOCITY_HPP_

#define WORKING_VELOCITY 16.666

class Velocity {
protected:
	uint32_t stepSize;
public:
	Velocity(float initialValue);
	virtual ~Velocity();
	virtual void SetVelocity(float newValue);
	float GetVelocity();
	uint32_t GetStepSize();
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
