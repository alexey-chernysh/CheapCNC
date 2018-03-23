/*
 * WaitForEvent.cpp
 *
 *  Created on: 22 ���. 2018 �.
 *      Author: Sales
 */

#include <MC/FixedPositionActions/WaitForSignal.hpp>

WaitForSignal::WaitForSignal(GPIO_TypeDef* p, uint32_t pN, SettingInt32* timeout /* � ������������� */):
WaitForTimeout(timeout),
InputSignal(p, pN) {
}

bool WaitForSignal::IterateForward(){
	if(this->WaitForTimeout::IterateForward()){
		return this->GetSignal();
	} else return false;
}

