/*
 * MotionArc.cpp
 *
 *  Created on: 26 ���. 2018 �.
 *      Author: Sales
 */

#include <stdint.h>
#include <math.h>
#include <Math/sine_n_cosine.hpp>
#include "MC/Enums.h"
#include "MC/MotionArc.hpp"
#include "MC/MotionController.hpp"

MotionArc::~MotionArc() {
}

static const double twoPi = 2.0 * M_PI;

MotionArc::MotionArc(  double _relEndPosX,
				   	   double _relEndPosY,
					   double _relCenterPosX,
					   double _relCenterPosY,
					   ARC_DIRECTION dir,
					   MOTION_VELOCITY velocity,
					   double startVel,
					   double endVel):Motion(_relEndPosX, _relEndPosY, velocity, startVel, endVel){
    this->relCenterPosX = MotionController::Get64bitForDoubleMM(_relCenterPosX);
    this->relCenterPosY = MotionController::Get64bitForDoubleMM(_relCenterPosY);
    this->arcDirection = dir;

	double      angle;
	double startAngle;
	double   endAngle;

	double x = (double)this->relCenterPosX;
	double y = (double)this->relCenterPosY;
	this->radiusLong = (int64_t)sqrt(x*x + y*y);

	int64_t tmp64 = (1LL<<SCALING_SHIFT);
	this->oneDividedByRadiusScaled = (tmp64*tmp64)/ this->radiusLong;

	startAngle = atan2(-(double)this->relCenterPosY,-(double)this->relCenterPosX);
	endAngle = atan2((double)(this->relEndPosY - this->relCenterPosY), (double)(this->relEndPosX - this->relCenterPosX));
	switch (this->arcDirection) {
		case CW:
			while(startAngle <= -M_PI)
				startAngle += twoPi;
			while(endAngle >= startAngle )
				endAngle -= twoPi;
			while((startAngle - endAngle) > twoPi )
				endAngle += twoPi;
			break;
		case CCW:
			while(startAngle >= M_PI)
				startAngle -= twoPi;
			while(endAngle <= startAngle )
				endAngle += twoPi;
			while((endAngle - startAngle) > twoPi )
				endAngle -= twoPi;
			break;
	}
	angle = endAngle - startAngle;

	this->angleScaled = getLongFromDouble(angle);
//	volatile double check1 = getDoubleFromLong(this->angleScaled);
	this->startAngleScaled = getLongFromDouble(startAngle);
//	volatile double check2 = getDoubleFromLong(this->startAngleScaled);
	this->currentAngleScaled = this->startAngleScaled;

	double tmp = angle;
	if(tmp<0) tmp = -angle;
	this->wayLength = (int64_t)(this->radiusLong * tmp);

	this->CalcWayLength();

	volatile int64_t angleCheck = (this->wayLength * this->oneDividedByRadiusScaled) >> SCALING_SHIFT;
//	volatile int64_t angleCheck = mulshift(this->wayLength, this->oneDividedByRadiusScaled, SCALING_SHIFT);
	volatile double check = getDoubleFromLong(angleCheck);
	check = check/angle;
	volatile int64_t tmpX = (this->radiusLong * cosInt9(this->currentAngleScaled)) >> SCALING_SHIFT;
//	volatile int64_t tmpX = mulshift(this->radiusLong, cosInt9(this->currentAngleScaled), SCALING_SHIFT);
	volatile int64_t tmpY = (this->radiusLong * sinInt9(this->currentAngleScaled)) >> SCALING_SHIFT;
//	volatile int64_t tmpY = mulshift(this->radiusLong, sinInt9(this->currentAngleScaled), SCALING_SHIFT);
	tmpX = this->relCenterPosX + tmpX;
	tmpY= this->relCenterPosY + tmpY;

}

void MotionArc::OnIteration() {
	volatile int64_t angleChange = (this->wayLengthCurrent * this->oneDividedByRadiusScaled) >> SCALING_SHIFT;
//	volatile int64_t angleChange = mulshift(this->wayLengthCurrent, this->oneDividedByRadiusScaled, SCALING_SHIFT);
	if(this->arcDirection == CW) angleChange = - angleChange;
	this->currentAngleScaled = this->startAngleScaled + angleChange;
	int64_t tmpX = (this->radiusLong * cosInt9(this->currentAngleScaled)) >> SCALING_SHIFT;
//	int64_t tmpX = mulshift(this->radiusLong, cosInt9(this->currentAngleScaled), SCALING_SHIFT);
	int64_t tmpY = (this->radiusLong * sinInt9(this->currentAngleScaled)) >> SCALING_SHIFT;
//	int64_t tmpY = mulshift(this->radiusLong, sinInt9(this->currentAngleScaled), SCALING_SHIFT);
	this->relCurrentPosX = this->relCenterPosX + tmpX;
	this->relCurrentPosY = this->relCenterPosY + tmpY;
}
