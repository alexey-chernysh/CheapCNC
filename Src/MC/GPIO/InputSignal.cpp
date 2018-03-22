/*
 * InputSignal.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include <MC/GPIO/InputSignal.hpp>

InputSignal::InputSignal(GPIO_TypeDef* p, uint32_t pN)
: Pin(p, pN) {
	// TODO Auto-generated constructor stub

}

void InputSignal::OnExternalInterrupt(){
	asm("nop");
}

InputSignal::~InputSignal(){

}
