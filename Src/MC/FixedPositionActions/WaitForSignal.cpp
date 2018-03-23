/*
 * WaitForEvent.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include <MC/FixedPositionActions/WaitForSignal.hpp>

WaitForSignal::WaitForSignal(GPIO_TypeDef* p, uint32_t pN, SettingInt32* timeout /* в миллисекундах */):
WaitForTimeout(timeout),
InputSignal(p, pN) {
}

bool WaitForSignal::IterateForward(){
	if(this->WaitForTimeout::IterateForward()){
		return this->GetSignal();
	} else return false;
}

