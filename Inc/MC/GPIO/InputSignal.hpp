/*
 * InputSignal.hpp
 *
 *  Created on: 22 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_GPIO_INPUTSIGNAL_HPP_
#define MC_GPIO_INPUTSIGNAL_HPP_

#include <MC/GPIO/Pin.hpp>

class InputSignal: public Pin {
public:
	InputSignal(GPIO_TypeDef* p, uint32_t pN);
};

#endif /* MC_GPIO_INPUTSIGNAL_HPP_ */
