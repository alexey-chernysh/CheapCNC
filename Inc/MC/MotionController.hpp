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

	float timerFrequency;
	float oneBitLengthMM;

	Sequence sequence;
	uint32_t sequenceSize;
	uint32_t currentMotionNum;
	Motion *currentMotion;

	int32_t stepIncrement;
	int32_t startStopStepSize;
	int32_t resumingStepSize;
	int32_t pausingStepSize;
public:
	void Reset();
	void OnTimer();
	bool IsRunning();
	bool IsForward();
	void SetResuming();
	int32_t GetResumingStepSize(int32_t currentStepSize);
	void SetPausing();
	int32_t GetPausingStepSize(int32_t currentStepSize);

	float GetTimerFrequency();
	float GetOneBitLengthMM();
	int64_t Get64bitForDoubleMM(double mm);
	double GetDoubleMMFor64bit(int64_t iValue);

	float GetMinVelocity();
	float GetMaxVelocity();
private:
	void IterateActionNum();
};

#endif /* MC_MOTIONCONTROLLER_HPP_ */
