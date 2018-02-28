/*
 * Acceleration.hpp
 *
 *  Created on: 28 февр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_ACCELERATION_HPP_
#define MC_ACCELERATION_HPP_

#include <stdint.h>

class Acceleration {
private:
	uint32_t stepIncrement;
public:
	Acceleration(float initialValue);
	void Set(float newValue);
	float Get();
	uint32_t GetStepIncrement();
};

#endif /* MC_ACCELERATION_HPP_ */
