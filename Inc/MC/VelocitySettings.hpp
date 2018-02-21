/*
 * VelocitySettings.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_VELOCITYSETTINGS_HPP_
#define MC_VELOCITYSETTINGS_HPP_

#include "Math/int_math.h"

#define N_OF_TOOTH 15
#define TOOTH_STEP 3.14
#define STEP_PER_ROTATION 200.0

typedef enum {
	FREE_RUN = 0,
	WORKING,
	START,
	ADJUSTMENT,
} MOTION_VELOCITY;

class VelocitySettings {
private:
	static float oneBitLength;
	static float timerFrequency;

	static float startVelocity;
	static float freeRunVelocity;
	static float workingVelocity;
	static float adjustmentVelocity;
	static double acceleration;
	static int32_t stepIncrement;
	static int32_t currentStepSize;

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
	inline int32_t GetStepIncrement(){ return stepIncrement; }
	int32_t GetStep4Velocity(double velocity);
	inline float GetStartVelocity(){ return startVelocity; }
	inline float GetFreeRunVelocity() { return freeRunVelocity; }
	inline float GetWorkingVelocity() { return workingVelocity; }
	float GetCurrentVelocity();
	int64_t GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2);

private:
	double  GetVelocity4Step(int32_t stepSize);
	int32_t GetStepIncrement4Acceleration();
};

#endif /* MC_VELOCITYSETTINGS_HPP_ */
