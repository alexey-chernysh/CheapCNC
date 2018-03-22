/*
 * Pin.hpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_GPIO_PIN_HPP_
#define MC_GPIO_PIN_HPP_

#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>

class Pin {
protected:
	GPIO_TypeDef* port;
	uint32_t pinNum;
public:
	Pin(GPIO_TypeDef* p, uint32_t pN);
};

#endif /* MC_GPIO_PIN_HPP_ */
