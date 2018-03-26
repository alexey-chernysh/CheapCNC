/*
 * Acceleration.hpp
 *
 *  Created on: 28 февр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_MOTIONS_ACCELERATION_HPP_
#define MC_MOTIONS_ACCELERATION_HPP_

#include <stdint.h>
#include "MC/Settings/Setting.hpp"

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

#endif /* MC_MOTIONS_ACCELERATION_HPP_ */
