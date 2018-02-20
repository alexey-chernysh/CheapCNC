/*
 * general.c
 *
 *  Created on: 20 ����. 2018 �.
 *      Author: Sales
 */

#include "MC/General.h"
#include "stm32f1xx_hal.h"

float GetTimerFrequency(){
    // calc timer interrupt frequency
	return ((float)HAL_RCC_GetPCLK2Freq())/(PWM_PRESCALER+1)/(PWM_PERIOD+1);
}

float GetOneBitLengthMM(){
	float scale = (float)(1LL<<POSITION_FIRST_SIGNIFICANT_BIT);
	return (N_OF_TOOTH * TOOTH_STEP)/STEP_PER_ROTATION/(MAX_MICROSTEP + 1.0)/scale;
}

float GetMinVelocity(){  // mm in minute
	// calc min velocity
	return 60.0*GetOneBitLengthMM()*GetTimerFrequency();
}

float GetMaxVelocity(){  // mm in minute
	// calc max velocity
	float maxPositionIncrement = (N_OF_TOOTH*TOOTH_STEP)/STEP_PER_ROTATION/2;
	return 60.0*maxPositionIncrement*GetTimerFrequency();
}

int64_t get64bitForDoubleMM(double mm){
	return (int64_t)(mm/GetOneBitLengthMM());
}

double getDoubleMMFor64bit(int64_t iValue){
	return GetOneBitLengthMM()*iValue;
}

