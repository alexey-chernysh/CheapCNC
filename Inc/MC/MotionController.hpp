/*
 * MotionController.hpp
 *
 *  Created on: 28 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONCONTROLLER_HPP_
#define MC_MOTIONCONTROLLER_HPP_

#include <MC/Sequence.hpp>
#include "Math/int_math.h"
#include "MC/VelocitySettings.hpp"
#include "MC/Position.hpp"
#include "MC/Motion.hpp"

class MotionController {
private:
	VelocitySettings velocitySettings;

	PositionX positionX;
	PositionX positionY;

	bool isRunning;
	bool isForward;

	Sequence cncTask;
	uint32_t taskSize;
	uint32_t currentMotionNum;
	Motion *currentMotion;
public:
	MotionController();
	virtual ~MotionController();
	void Reset();
	void onTimerTick();
private:
	void iterateActionNum();
};

#endif /* MC_MOTIONCONTROLLER_HPP_ */
