/*
 * TimerFrequency.hpp
 *
 *  Created on: 27 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_TIMERFREQUENCY_HPP_
#define MC_TIMERFREQUENCY_HPP_

class TimerFrequency {
private:
	float MCUfrequency;
	float timerFrequency;
public:
	TimerFrequency();
	float GetTimerFrequency();
};

#endif /* MC_TIMERFREQUENCY_HPP_ */
