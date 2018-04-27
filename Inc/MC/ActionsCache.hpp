/*
 * MCProgram.hpp
 *
 *  Created on: 24 апр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_ACTIONSCACHE_HPP_
#define MC_ACTIONSCACHE_HPP_

#include "MC/General.h"
#include "MC/CommandList.hpp"
#include "MC/Action.hpp"
#include "MC/Motions/MotionStraight.hpp"
#include "MC/Motions/MotionArc.hpp"

#define ACTION_CACHE_SIZE 16
#define ACTION_CACHE_CENTER (ACTION_CACHE_SIZE/2)

class ActionItem{
public:
	CommandListItem* parentCommand;
	ActionItem(){ parentCommand = 0;};
	ActionItem(CommandListItem* c):parentCommand(c){};
};

class ActionsCache {
private:
	CommandList* program;
	ActionItem cache[ACTION_CACHE_SIZE];
	static bool doNotDisturb;
	int16_t firstActionNum;
	int16_t lastActionNum;
	int16_t currentActionNum;
public:
	ActionsCache(CommandList* p);
	void Update();
private:
	int16_t GetForwardLength();
	int16_t GetBackwardLength();
};

#endif /* MC_ACTIONSCACHE_HPP_ */
