/*
 * WaitForEvent.cpp
 *
 *  Created on: 22 ���. 2018 �.
 *      Author: Sales
 */

#include <MC/FixedPositionActions/WaitForSignal.hpp>

WaitForSignal::WaitForSignal(GPIO_TypeDef* p, uint32_t pN, uint32_t timeout /* � ������������� */):
WaitForTimeout(timeout),
Pin(p, pN) {
	// TODO Auto-generated constructor stub

}

