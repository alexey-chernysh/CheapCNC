/*
 * VelocitySettings.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_VELOCITYSETTINGS_HPP_
#define MC_VELOCITYSETTINGS_HPP_

#include <stdint.h>
#include "MC/Enums.h"

class VelocitySettings {
private:
	float oneBitLength;
	float timerFrequency;

	float startVelocity;
	float freeRunVelocity;
	float workingVelocity;
	float adjustmentVelocity;
	double acceleration;
	int32_t stepIncrement;
	int32_t currentStepSize;

private:
	VelocitySettings();
	virtual ~VelocitySettings();
    VelocitySettings(const VelocitySettings&) = delete;
    VelocitySettings& operator=(const VelocitySettings&) = delete;
public:
	static VelocitySettings* GetInstance();
public:
	int32_t GetStepSize(MOTION_VELOCITY t);
	void SetCurrentStepSize(int32_t newStepSIze);
	int32_t GetCurrentStepSize();
	int32_t GetStepIncrement();
	float GetStartVelocity();
	float GetFreeRunVelocity();
	float GetWorkingVelocity();
	float GetCurrentVelocity();
	int64_t GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2);
	int32_t GetStep4Velocity(double velocity);

private:
	double  GetVelocity4Step(int32_t stepSize);
	int32_t GetStepIncrement4Acceleration();
};

#endif /* MC_VELOCITYSETTINGS_HPP_ */
