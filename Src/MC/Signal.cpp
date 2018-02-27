/*
 * Signal.cpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: Sales
 */

#include "main.h"
#include <MC/Signal.hpp>

Signal::Signal(GPIO_TypeDef* p, uint32_t pN, bool initialState) {
	port = p;
	pinNum = pN;
	if(initialState)HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_RESET);
}

void Signal::On(){
	HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_SET);
}

void Signal::Off(){
	HAL_GPIO_WritePin(port, pinNum, GPIO_PIN_RESET);
}

static SignalSet signalSet;

SignalSet::SignalSet(){
	THC_auto_output = new Signal(THC_Auto_Output_GPIO_Port, THC_Auto_Output_Pin);
}

void THC_AutoOn(){
	signalSet.THC_auto_output->On();
}

void THC_AutoOff(){
	signalSet.THC_auto_output->Off();
}

