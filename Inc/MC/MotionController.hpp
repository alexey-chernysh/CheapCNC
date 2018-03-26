/*
 * MotionController.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONCONTROLLER_HPP_
#define MC_MOTIONCONTROLLER_HPP_

#include <MC/ExecutionDirection.hpp>
#include <stdint.h>
#include <MC/Motions/Acceleration.hpp>
#include <MC/Motions/Motion.hpp>
#include <MC/Motions/Velocity.hpp>
#include "MC/Sequence.hpp"
#include "MC/ExecutionState.hpp"

class MotionController {
public:
	float timerFrequency;
	float oneBitLengthMM;

	uint32_t currentStepSize;
	uint32_t startStopStepSize;
	uint32_t resumingStepSize;
	uint32_t pausingStepSize;

	ExecutionState executionState;

	Acceleration acceleration;
	FreeRunVelocity freeRunVelocity;
	WorkingVelocity workingVelocity;
	RelativeVelocity startVelocity;
	RelativeVelocity adjustmentVelocity;

	Sequence* sequence;
	uint32_t sequenceSize;
	uint32_t currentMotionNum;
	Action* currentAction;

public:
	MotionController();

	void Reset();

	void OnTimer();
	void OnControlKey(char controlKey);

	void SetResuming();
	uint32_t GetResumingStepSize(uint32_t currentSS);
	void SetPausing();
	uint32_t GetPausingStepSize(uint32_t currentSS);

	float GetTimerFrequency();
	float GetOneBitLengthMM();

	void SetCurrentStepSize(uint32_t newStepSIze);
	uint32_t GetCurrentStepSize();
	float GetCurrentVelocity();

	int64_t Get64bitForDoubleMM(double mm);
	double GetDoubleMMFor64bit(int64_t iValue);

	uint32_t GetStepSize(MOTION_VELOCITY t);
	float GetVelocity(MOTION_VELOCITY t);

private:
	void IterateActionNum();
};

extern MotionController motionController;

#endif /* MC_MOTIONCONTROLLER_HPP_ */
