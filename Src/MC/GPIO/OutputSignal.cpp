/*
 * Signal.cpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: Sales
 */

#include <MC/GPIO/OutputSignal.hpp>
#include "main.h"

OutputSignal::OutputSignal(GPIO_TypeDef* p, uint32_t pN, bool initialState)
:Pin(p, pN) {
	if(initialState)HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_RESET);
}

void OutputSignal::On(){
	HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_SET);
}

void OutputSignal::Off(){
	HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_RESET);
}

static SignalSet signalSet;

SignalSet::SignalSet(){
	THC_auto_output = new OutputSignal(THC_Auto_Output_GPIO_Port, THC_Auto_Output_Pin);
}

void THC_AutoOn(){
	signalSet.THC_auto_output->On();
}

void THC_AutoOff(){
	signalSet.THC_auto_output->Off();
}

