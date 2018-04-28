/*
 * Position.hpp
 *
 *  Created on: 19 ����. 2018 �.
 *      Author: Sales
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <stdint.h>

float GetOneBitLengthMM();

int64_t Get64bitForDoubleMM(double mm);

double GetDoubleMMFor64bit(int64_t iValue);

class Position {
private:
	int64_t absPosition;
public:
	Position();
	virtual ~Position();
	int64_t Get();
	double GetMM();
	void Set(int64_t newPosition);
	void Shift(int8_t shift);
private:
	uint8_t GetAngle();
protected:
	virtual void SetPWM(uint8_t angle);
};

class PositionX final : public Position {
public:
	PositionX();
	virtual ~PositionX();
protected:
	virtual void SetPWM(uint8_t angle);
};

class PositionY final : public Position {
public:
	PositionY();
	virtual ~PositionY();
protected:
	virtual void SetPWM(uint8_t angle);
};

#endif /* POSITION_HPP_ */
