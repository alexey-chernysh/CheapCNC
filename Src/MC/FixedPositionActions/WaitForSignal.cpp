/*
 * WaitForEvent.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include <MC/FixedPositionActions/WaitForSignal.hpp>

WaitForSignal::WaitForSignal(GPIO_TypeDef* p, uint32_t pN, uint32_t timeout /* в миллисекундах */):
WaitForTimeout(timeout),
Pin(p, pN) {
	// TODO Auto-generated constructor stub

}

