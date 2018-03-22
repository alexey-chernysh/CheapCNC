/*
 * MotionController.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONCONTROLLER_HPP_
#define MC_MOTIONCONTROLLER_HPP_

#include <MC/Motions/Acceleration.hpp>
#include <MC/Motions/Motion.hpp>
#include <MC/Motions/MotionDirection.hpp>
#include <MC/Motions/Velocity.hpp>
#include <stdint.h>
#include "MC/Sequence.hpp"

class MotionController : public MotionDirection, public Acceleration {
private:
public:
	MotionController();

	void Reset();

	void OnTimer();
	void OnControlKey(char controlKey);

	static bool IsRunning();
	static bool IsPaused();

	void SetResuming();
	uint32_t GetResumingStepSize(uint32_t currentSS);
	void SetPausing();
	uint32_t GetPausingStepSize(uint32_t currentSS);

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

private:
	void IterateActionNum();
};

extern MotionController motionController;

#endif /* MC_MOTIONCONTROLLER_HPP_ */
