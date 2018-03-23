/*
 * InputSignal.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include "stm32f1xx_hal.h"
#include <MC/GPIO/InputSignal.hpp>

InputSignal::InputSignal(GPIO_TypeDef* p, uint32_t pN)
: Pin(p, pN) {
}

bool InputSignal::GetSignal(){
	GPIO_PinState currentState = HAL_GPIO_ReadPin(this->port, this->pinNum);
	if(currentState) return true;
	else return false;
}
