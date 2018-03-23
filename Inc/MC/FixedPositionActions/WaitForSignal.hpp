/*
 * WaitForEvent.hpp
 *
 *  Created on: 22 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_
#define MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_

#include <MC/Settings/Setting.hpp>
#include <stdint.h>
#include "MC/FixedPositionActions/WaitForTimeout.hpp"
#include "MC/GPIO/InputSignal.hpp"

class WaitForSignal: public WaitForTimeout, private InputSignal {
public:
	WaitForSignal(GPIO_TypeDef* p, uint32_t pN, /* ���� ������� */
				  SettingInt32* timeout /* � ������������� */);
	virtual bool IterateForward();
};

#endif /* MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_ */
