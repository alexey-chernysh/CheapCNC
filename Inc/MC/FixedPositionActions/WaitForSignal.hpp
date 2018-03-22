/*
 * WaitForEvent.hpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_
#define MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_

#include <stdint.h>
#include "MC/FixedPositionActions/WaitForTimeout.hpp"
#include "MC/GPIO/Pin.hpp"

class WaitForSignal: public WaitForTimeout, public Pin {
public:
	WaitForSignal(GPIO_TypeDef* p, uint32_t pN, /* нога сигнала */
				  uint32_t timeout /* в миллисекундах */);
};

#endif /* MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_ */
