/*
 * MotionController.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONCONTROLLER_HPP_
#define MC_MOTIONCONTROLLER_HPP_

#include <stdint.h>
#include "MC/Motion.hpp"
#include "MC/Sequence.hpp"

class MotionController { // MC singleton
private:
	MotionController();
	virtual ~MotionController();
    MotionController(const MotionController&) = delete;
    MotionController& operator=(const MotionController&) = delete;
public:
	static MotionController* GetInstance();
private:
	bool running;
	bool forward;
	bool resuming;
	bool pausing;

	Sequence* sequence;
	uint32_t sequenceSize;
	uint32_t currentMotionNum;
	Motion* currentMotion;

public:
	void Reset();
	void OnTimer();

	void OnControlKey(char controlKey);
	bool IsRunning();
	bool IsPaused();

	bool IsForward();
	void SetForward();
	bool IsBackward();
	void SetBackward();

	void SetResuming();
	int32_t GetResumingStepSize(int32_t currentStepSize);
	void SetPausing();
	int32_t GetPausingStepSize(int32_t currentStepSize);

	float GetTimerFrequency();
	float GetOneBitLengthMM();

	float GetMinVelocity();
	float GetMaxVelocity();

	void SetCurrentStepSize(int32_t newStepSIze);
	int32_t GetCurrentStepSize();
	float GetCurrentVelocity();

private:
	void IterateActionNum();
	double  GetVelocity4Step(int32_t stepSize);
	int32_t GetStepIncrement4Acceleration();
};

int64_t Get64bitForDoubleMM(double mm);
double GetDoubleMMFor64bit(int64_t iValue);

int32_t GetStepSize(MOTION_VELOCITY t);
int32_t GetStepIncrement();
int32_t GetStep4Velocity(double velocity);
int64_t GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2);

float GetStartVelocity();
float GetFreeRunVelocity();
float GetWorkingVelocity();

#endif /* MC_MOTIONCONTROLLER_HPP_ */
