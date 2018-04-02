/*
 * TimerFrequency.cpp
 *
 *  Created on: 27 мар. 2018 г.
 *      Author: Sales
 */

#include "stm32f1xx_hal.h"
#include "MC/General.h"
#include <MC/TimerFrequency.hpp>

float GetMCUFrequency(){
	return (float)HAL_RCC_GetPCLK2Freq();
}

float GetTimerFrequency(){
	return GetMCUFrequency()/(PWM_PRESCALER+1)/(PWM_PERIOD+1);;
}

