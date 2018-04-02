/*
 * WaitForEvent.hpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_
#define MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_

#include <stdint.h>
#include "MC/GPIO/InputSignal.hpp"
#include "MC/FixedPositionActions/WaitForTimeout.hpp"
#include <MC/Settings/SettingInt32.hpp>

class WaitForSignal: public WaitForTimeout, private InputSignal {
public:
	WaitForSignal(GPIO_TypeDef* p, uint32_t pN, /* нога сигнала */
				  SettingInt32* timeout /* в миллисекундах */);
	virtual bool IterateForward();
};

#endif /* MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_ */
