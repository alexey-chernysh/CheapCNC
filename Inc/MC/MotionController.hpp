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
	uint32_t GetResumingStepSize(uint32_t currentSS);
	void SetPausing();
	uint32_t GetPausingStepSize(uint32_t currentSS);

	float GetTimerFrequency();
	float GetOneBitLengthMM();

	float GetMinVelocity();
	float GetMaxVelocity();

	void SetCurrentStepSize(uint32_t newStepSIze);
	uint32_t GetCurrentStepSize();
	float GetCurrentVelocity();

private:
	void IterateActionNum();
	uint32_t GetStepIncrement4Acceleration();
};

double  GetVelocity4Step(uint32_t stepSize);
uint32_t GetStep4Velocity(double velocity);

int64_t Get64bitForDoubleMM(double mm);
double GetDoubleMMFor64bit(int64_t iValue);

uint32_t GetStepSize(MOTION_VELOCITY t);
uint32_t GetStepIncrement();
int64_t GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2);

float GetStartVelocity();
float GetFreeRunVelocity();
float GetWorkingVelocity();

#endif /* MC_MOTIONCONTROLLER_HPP_ */
