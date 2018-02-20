/*
 * MotionController.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONCONTROLLER_HPP_
#define MC_MOTIONCONTROLLER_HPP_

#include "Math/int_math.h"
#include <MC/Sequence.hpp>
#include "MC/VelocitySettings.hpp"
#include "MC/Position.hpp"
#include "MC/Motion.hpp"

class MotionController { // MC singleton
private:
	MotionController();
	virtual ~MotionController();
    MotionController(const MotionController&) = delete;
    MotionController& operator=(const MotionController&) = delete;
public:
	static MotionController* GetInstance();
private:
	VelocitySettings velocitySettings;

	static bool running;
	static bool forward;

	static float timerFrequency;
	static float oneBitLengthMM;

	Sequence sequence;
	uint32_t sequenceSize;
	uint32_t currentMotionNum;
	Motion *currentMotion;
public:
	void Reset();
	void onTimer();
	bool IsRunning(){ return running; };
	bool IsForward(){ return forward; };

	float GetTimerFrequency(){ return timerFrequency; };
	float GetOneBitLengthMM(){ return oneBitLengthMM; };
	int64_t Get64bitForDoubleMM(double mm){ return (int64_t)(mm/oneBitLengthMM); };
	double GetDoubleMMFor64bit(int64_t iValue){	return oneBitLengthMM*iValue; };

	float GetMinVelocity(){ return 60.0*timerFrequency*oneBitLengthMM; };
	float GetMaxVelocity(){ return 60.0*timerFrequency*(N_OF_TOOTH*TOOTH_STEP)/STEP_PER_ROTATION/2; };
private:
	void IterateActionNum();
};

#endif /* MC_MOTIONCONTROLLER_HPP_ */
