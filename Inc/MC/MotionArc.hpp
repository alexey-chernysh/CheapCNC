/*
 * MotionArc.hpp
 *
 *  Created on: 26 џэт. 2018 у.
 *      Author: Sales
 */

#ifndef MC_MOTIONARC_HPP_
#define MC_MOTIONARC_HPP_

#include "MC/Motion.hpp"
#include "MC/Velocity.hpp"

typedef enum {
	CW, // clockwise
	CCW // counterclockwise
} ARC_DIRECTION;

class MotionArc: public Motion {
private:
	// arc motion params
	int64_t relCenterPosX;
    int64_t relCenterPosY;
	ARC_DIRECTION arcDirection;

	//arc vars
	int64_t radiusLong;
	int64_t oneDividedByRadiusScaled;

	int32_t angleScaled;
	int32_t startAngleScaled;
	int32_t currentAngleScaled;

public:
	MotionArc(double _relEndPosX,
		   	   double _relEndPosY,
			   double _relCenterPosX,
			   double _relCenterPosY,
			   ARC_DIRECTION dir,
			   MOTION_VELOCITY velocity,
			   double startVel,
			   double endVel);
	virtual ~MotionArc();
protected:
	virtual void onFastTimerTick();
};

#endif /* MC_MOTIONARC_HPP_ */
