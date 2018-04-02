/*
 * Acceleration.hpp
 *
 *  Created on: 28 ����. 2018 �.
 *      Author: Sales
 */

#ifndef MC_VELOCITY_ACCELERATION_HPP_
#define MC_VELOCITY_ACCELERATION_HPP_

#include <stdint.h>
#include "MC/Settings/FloatSetting.hpp"

class Acceleration {
private:
	FloatSetting* _value;
	uint32_t _stepIncrement;
public:
	Acceleration();
	void Set(float newValue);
	float Get();
	uint32_t GetStepIncrement();
	int64_t GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2);
private:
	void SetIncrement();
};

#endif /* MC_VELOCITY_ACCELERATION_HPP_ */
