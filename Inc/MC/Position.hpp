/*
 * Position.hpp
 *
 *  Created on: 19 ����. 2018 �.
 *      Author: Sales
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <stdint.h>

class Position {
private:
	int64_t absPosition;
public:
	Position();
	virtual ~Position();
	int64_t Get();
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
