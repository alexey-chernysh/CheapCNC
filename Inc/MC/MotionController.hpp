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
#include "MC/Velocity.hpp"
#include "MC/MotionDirection.hpp"

class MotionController {
private:
public:
	MotionController();

	static void Reset();

	static void OnTimer();
	static void OnControlKey(char controlKey);

	static MotionDirection* GetMotionDirection();
	static bool IsRunning();
	static bool IsPaused();

	static void SetResuming();
	static uint32_t GetResumingStepSize(uint32_t currentSS);
	static void SetPausing();
	static uint32_t GetPausingStepSize(uint32_t currentSS);

	static float GetTimerFrequency();
	static float GetOneBitLengthMM();

	static float GetMinVelocity();
	static float GetMaxVelocity();

	static void SetCurrentStepSize(uint32_t newStepSIze);
	static uint32_t GetCurrentStepSize();
	static float GetCurrentVelocity();

	static int64_t Get64bitForDoubleMM(double mm);
	static double GetDoubleMMFor64bit(int64_t iValue);

	static uint32_t GetStepSize(MOTION_VELOCITY t);
	static float GetVelocity(MOTION_VELOCITY t);
	static uint32_t GetStepIncrement();
	static int64_t GetWayLength4StepChange(int32_t stepSize1, int32_t stepSize2);

private:
	static void IterateActionNum();
	static uint32_t GetStepIncrement4Acceleration();
};

extern MotionController motionController;

#endif /* MC_MOTIONCONTROLLER_HPP_ */
