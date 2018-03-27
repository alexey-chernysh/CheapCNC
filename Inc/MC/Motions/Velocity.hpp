/*
 * Velocity.hpp
 *
 *  Created on: 27 ����. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONS_VELOCITY_HPP_
#define MC_MOTIONS_VELOCITY_HPP_

#include <stdint.h>
#include "MC/Settings/Setting.hpp"

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


class FreeRunVelocity : public Velocity {
private:
	FloatSetting* _value; // in mm in minute
public:
	FreeRunVelocity();
	virtual ~FreeRunVelocity();
	virtual void Set(float newVelocity);
	virtual float Get();
};

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

#endif /* MC_MOTIONS_VELOCITY_HPP_ */
