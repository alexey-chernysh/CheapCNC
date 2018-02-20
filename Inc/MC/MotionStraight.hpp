/*
 * MotionStraight.h
 *
 *  Created on: 26 џэт. 2018 у.
 *      Author: Sales
 */

#ifndef MC_MOTIONSTRAIGHT_HPP_
#define MC_MOTIONSTRAIGHT_HPP_

#include "MC/Motion.hpp"
#include "MC/Velocity.hpp"

class MotionStraight : public Motion {
private:
	// straight motion params
	int64_t Kx;
	int64_t Ky;

public:
	MotionStraight( double _relEndPosX,
					double _relEndPosY,
					MOTION_VELOCITY velocity,
					double startVel,
					double endVel);
	virtual ~MotionStraight();
protected:
	virtual void onFastTimerTick();
};

#endif /* MC_MOTIONSTRAIGHT_HPP_ */
