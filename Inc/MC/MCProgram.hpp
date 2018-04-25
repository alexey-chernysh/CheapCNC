/*
 * MCProgram.hpp
 *
 *  Created on: 24 апр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_MCPROGRAM_HPP_
#define MC_MCPROGRAM_HPP_

#include "MC/General.h"
#include "MC/CommandList.hpp"
#include "MC/Action.hpp"
#include "MC/Motions/MotionStraight.hpp"
#include "MC/Motions/MotionArc.hpp"

#define COMMAND_CASH_SIZE 16

typedef union {
	Action action;
	MotionStraight motionStraight;
	MotionArc motionArc;
} ActionItem;

class MCProgram {
private:
	CommandList* program;
	ActionItem action[COMMAND_CASH_SIZE];
	bool doNotDisturb;
	uint16_t firstActionNum;
	uint16_t lastActionNum;
	uint16_t currentActionNum;
public:
	MCProgram(CommandList* p);
	void UpdateCash();
};

#endif /* MC_MCPROGRAM_HPP_ */
