/*
 * Signal.hpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_SIGNAL_HPP_
#define MC_SIGNAL_HPP_

class Signal {
private:
	uint32_t pinNum;
	bool state;
public:
	Signal(uint32_t pN, bool initialState = false);
	void On();
	void Off();
	bool IsOn();
	bool IsOff();
};

#define AUTO_PIN_NUM 1

class SignalSet {
public:
	Signal* autoSignal;
public:
	SignalSet();
};

void SetAutoSignalOn();
void SetAutoSignalOff();

#endif /* MC_SIGNAL_HPP_ */
