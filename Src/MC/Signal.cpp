/*
 * Signal.cpp
 *
 *  Created on: 27 ����. 2018 �.
 *      Author: Sales
 */

#include <MC/Signal.hpp>

Signal::Signal(uint32_t pN, bool initialState) {
	pinNum = pN;
	state = initialState;
}

static SignalSet signalSet;

SignalSet::SignalSet(){
	autoSignal = new Signal(AUTO_PIN_NUM);
}

void SetAutoSignalOn(){
	signalSet.autoSignal->On();
}

void SetAutoSignalOff(){
	signalSet.autoSignal->Off();
}

