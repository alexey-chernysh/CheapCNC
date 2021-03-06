/*
 * Position.cpp
 *
 *  Created on: 19 ����. 2018 �.
 *      Author: Sales
 */

#include <stdint.h>
#include <math.h>
#include "tim.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include <MC/General.h>
#include "MC/Position.hpp"
#include <Math/sine_n_cosine.hpp>

static bool pwm_table_ready = false;
static uint32_t pwm_table[MAX_MICROSTEP+1];
static float oneBitLengthMM;

void buildPwmTable(){
	if(!pwm_table_ready){
		initMath();

		float scale1 = M_PI / 2.0 / MAX_MICROSTEP;
		float scale2 = MAX_PWM_WIDTH * PWM_PERIOD;
		for(uint32_t i=0; i <= MAX_MICROSTEP; i++){
			pwm_table[i] = scale2*sin(scale1*i);
		}
		pwm_table_ready = true;

		float scale = (float)(1LL<<POSITION_FIRST_SIGNIFICANT_BIT);
		oneBitLengthMM = (N_OF_TOOTH * TOOTH_STEP)/STEP_PER_ROTATION/(MAX_MICROSTEP + 1.0)/scale;
	};
}

float GetOneBitLengthMM(){ return oneBitLengthMM; }

int64_t Get64bitForDoubleMM(double mm){ return (int64_t)(mm/oneBitLengthMM); };

double GetDoubleMMFor64bit(int64_t iValue){	return oneBitLengthMM*iValue; };

Position::Position() {
	buildPwmTable();
	this->absPosition = 0LL;
}

Position::~Position() {
}

int64_t Position::Get(){
	return this->absPosition;
}

double Position::GetMM(){
	return GetDoubleMMFor64bit(this->Get());
}

void Position::Set(int64_t newPosition){
	this->absPosition = newPosition;
	this->SetPWM(GetAngle());
}

void Position::Shift(int8_t shift){
	this->absPosition += shift;
	this->SetPWM(GetAngle());
}

uint8_t Position::GetAngle(){
	return (uint8_t)(0x000000FF & (absPosition >> POSITION_FIRST_SIGNIFICANT_BIT));
}

void Position::SetPWM(uint8_t angle){
}
/*
void InitPWM(TIM_HandleTypeDef htim){
  HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_4);

  HAL_TIM_Base_Start(&htim);

  HAL_TIM_Base_Start_IT(&htim);
}
*/
PositionX::PositionX():Position() {
}

PositionX::~PositionX() {
}

void PositionX::SetPWM(uint8_t angle){
	uint32_t phase1, phase2, phase3, phase4;
	uint8_t segment = (angle>>6) & 0b00000011;
	uint8_t phase = angle & MAX_MICROSTEP;
	uint8_t phase_inv = MAX_MICROSTEP-phase;
	uint32_t pwm = pwm_table[phase];
	uint32_t pwm_inv = pwm_table[phase_inv];
	switch(segment){
	case 0:
		phase1 = pwm_inv;
		phase2 = 0;
		phase3 = pwm;
		phase4 = 0;
		break;
	case 1:
		phase1 = 0;
		phase2 = pwm;
		phase3 = pwm_inv;
		phase4 = 0;
		break;
	case 2:
		phase1 = 0;
		phase2 = pwm_inv;
		phase3 = 0;
		phase4 = pwm;
		break;
	case 3:
		phase1 = pwm;
		phase2 = 0;
		phase3 = 0;
		phase4 = pwm_inv;
		break;
	default:
		phase1 = 0;
		phase2 = 0;
		phase3 = 0;
		phase4 = 0;
	}

	X_AXIS_TIMER->CCR1 = phase1;
	X_AXIS_TIMER->CCR2 = phase2;
	X_AXIS_TIMER->CCR3 = phase3;
	X_AXIS_TIMER->CCR4 = phase4;
}

PositionY::PositionY():Position() {
}

PositionY::~PositionY() {
}

void PositionY::SetPWM(uint8_t angle){
	uint32_t phase1, phase2, phase3, phase4;
	uint8_t segment = (angle>>6) & 0b00000011;
	uint8_t phase = angle & MAX_MICROSTEP;
	uint8_t phase_inv = MAX_MICROSTEP-phase;
	uint32_t pwm = pwm_table[phase];
	uint32_t pwm_inv = pwm_table[phase_inv];
	switch(segment){
	case 0:
		phase1 = pwm_inv;
		phase2 = 0;
		phase3 = pwm;
		phase4 = 0;
		break;
	case 1:
		phase1 = 0;
		phase2 = pwm;
		phase3 = pwm_inv;
		phase4 = 0;
		break;
	case 2:
		phase1 = 0;
		phase2 = pwm_inv;
		phase3 = 0;
		phase4 = pwm;
		break;
	case 3:
		phase1 = pwm;
		phase2 = 0;
		phase3 = 0;
		phase4 = pwm_inv;
		break;
	default:
		phase1 = 0;
		phase2 = 0;
		phase3 = 0;
		phase4 = 0;
	}

	Y_AXIS_TIMER->CCR1 = phase1;
	Y_AXIS_TIMER->CCR2 = phase2;
	Y_AXIS_TIMER->CCR3 = phase3;
	Y_AXIS_TIMER->CCR4 = phase4;
}
