/*
 * VelocitySettings.hpp
 *
 *  Created on: 28 џэт. 2018 у.
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
	static double timerInterruptFrequency;
	static double oneBitLength;
	static float minVelocity;
	static float maxVelocity;
	static float startVelocity;
	static float freeRunVelocity;
	static float workingVelocity;
	static float adjustmentVelocity;
	static double acceleration;
	static int32_t stepIncrement;
	static int32_t currentStepSize;

public:
	VelocitySettings();
	virtual ~VelocitySettings();

// public methods
	double getTimerFrequencyUsed();
	double getOneBitLength();
	int64_t get64bitForDoubleMM(double mm);
	double  getDoubleMMFor64bit(int64_t iValue);
	int32_t getStepSize(MOTION_VELOCITY t);
	void setCurrentStepSize(int32_t newStepSIze);
	inline int32_t getStepIncrement(){ return this->stepIncrement; }
	inline float getStartVelocity(){ return this->startVelocity; }
	inline float getFreeRunVelocity() { return this->freeRunVelocity; }
	inline float getWorkingVelocity() { return this->workingVelocity; }
	float getCurrentVelocity();
	int64_t getWayLength4StepChange(int32_t stepSize1, int32_t stepSize2);

private:
	float getMinVelocity();
	float getMaxVelocity();
	int32_t getStep4Velocity(double velocity);
	double  getVelocity4Step(int32_t stepSize);
	int32_t getStepIncrement4Acceleration();
};

extern VelocitySettings velocitySettings;

#endif /* MC_VELOCITYSETTINGS_HPP_ */
