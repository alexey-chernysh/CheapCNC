/*
 * TimerFrequency.cpp
 *
 *  Created on: 27 мар. 2018 г.
 *      Author: Sales
 */

#include "stm32f1xx_hal.h"
#include "MC/General.h"
#include <MC/TimerFrequency.hpp>

static float MCUfrequency;
static float timerFrequency;

TimerFrequency::TimerFrequency(){
	MCUfrequency = (float)HAL_RCC_GetPCLK2Freq();
	timerFrequency = MCUfrequency/(PWM_PRESCALER+1)/(PWM_PERIOD+1);
}

float TimerFrequency::GetTimerFrequency(){ return timerFrequency; }

