/*
 * MotionArc.hpp
 *
 *  Created on: 26 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONARC_HPP_
#define MC_MOTIONARC_HPP_

#include "MC/Enums.h"
#include "MC/Motion.hpp"

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
	virtual void OnIteration();
};

#endif /* MC_MOTIONARC_HPP_ */
