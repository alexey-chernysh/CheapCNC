/*
 * MotionStraight.h
 *
 *  Created on: 26 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONS_MOTIONSTRAIGHT_HPP_
#define MC_MOTIONS_MOTIONSTRAIGHT_HPP_

#include <MC/Motions/Motion.hpp>
#include "MC/Enums.h"

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
	virtual void OnIteration();
};

#endif /* MC_MOTIONS_MOTIONSTRAIGHT_HPP_ */
