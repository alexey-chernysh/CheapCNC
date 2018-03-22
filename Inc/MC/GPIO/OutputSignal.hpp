/*
 * Signal.hpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_GPIO_OUTPUTSIGNAL_HPP_
#define MC_GPIO_OUTPUTSIGNAL_HPP_

#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include "MC/GPIO/Pin.hpp"

class OutputSignal: public Pin {
public:
	OutputSignal(GPIO_TypeDef* p, uint32_t pN, bool initialState = false);
	void On();
	void Off();
};

#define AUTO_PIN_NUM 1

class SignalSet {
public:
	OutputSignal* THC_auto_output;
public:
	SignalSet();
};

void THC_AutoOn();
void THC_AutoOff();

#endif /* MC_GPIO_OUTPUTSIGNAL_HPP_ */
