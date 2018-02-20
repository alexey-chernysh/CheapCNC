/*
 * general.c
 *
 *  Created on: 20 февр. 2018 г.
 *      Author: Sales
 */

#include "MC/general.h"

static float GetTimerFrequency(){
    // calc timer interrupt frequency
	return ((float)HAL_RCC_GetPCLK2Freq())/(PWM_PRESCALER+1)/(PWM_PERIOD+1);
}

static float GetOneBitLengthMM(){
	float scale = (float)(1LL<<POSITION_FIRST_SIGNIFICANT_BIT);
	return (N_OF_TOOTH * TOOTH_STEP)/STEP_PER_ROTATION/(MAX_MICROSTEP + 1.0)/scale;
}

static float GetMinVelocityMM(){  // mm in minute
	// calc min velocity
	return 60.0*GetOneBitLengthMM()*GetTimerFrequency();
}

static float GetMaxVelocity(){  // mm in minute
	// calc max velocity
	float maxPositionIncrement = (N_OF_TOOTH*TOOTH_STEP)/STEP_PER_ROTATION/2;
	return 60.0*maxPositionIncrement*GetTimerFrequency();
}
