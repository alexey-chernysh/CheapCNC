/*
 * MotionController.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONCONTROLLER_HPP_
#define MC_MOTIONCONTROLLER_HPP_

#include <stdint.h>
#include <MC/Motions/Motion.hpp>
#include "MC/Sequence.hpp"
#include "MC/ExecutionState.hpp"
#include "MC/Position.hpp"
#include <MC/Settings/Settings.hpp>
#include <MC/TimerFrequency.hpp>
#include <MC/Velocity/VelocityProfile.hpp>

class MotionController {
public:
	PositionX positionX;
	PositionY positionY;

	TimerFrequency timerFrequency;
	Settings settings;

	VelocityProfile velocityProfile;
	ExecutionState executionState;

private:
	uint32_t startStopStepSize;
	uint32_t resumingStepSize;
	uint32_t pausingStepSize;
public:
	Sequence* sequence;
	uint32_t sequenceSize;
	uint32_t currentActionNum;
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

private:
	void IterateActionNum();
};

extern MotionController* motionController;

#endif /* MC_MOTIONCONTROLLER_HPP_ */
