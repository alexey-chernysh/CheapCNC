/*
 * Signal.hpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_SIGNAL_HPP_
#define MC_SIGNAL_HPP_

#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>

class Signal {
private:
	GPIO_TypeDef* port;
	uint32_t pinNum;
public:
	Signal(GPIO_TypeDef* p, uint32_t pN, bool initialState = false);
	void On();
	void Off();
};

#define AUTO_PIN_NUM 1

class SignalSet {
public:
	Signal* THC_auto_output;
public:
	SignalSet();
};

void THC_AutoOn();
void THC_AutoOff();

#endif /* MC_SIGNAL_HPP_ */
