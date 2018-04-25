/*
 * MCProgram.cpp
 *
 *  Created on: 24 апр. 2018 г.
 *      Author: Sales
 */

#include <MC/MCProgram.hpp>
#include "MC/CommandList.hpp"

MCProgram::MCProgram(CommandList* p):program(p){
	CommandListItem* nextListItem = 0;
	uint16_t i = 0;
	firstActionNum = 0;
	lastActionNum = 0;
	currentActionNum = 0;
	doNotDisturb = false;
	while( (nextListItem = program->GetCurrent())&&(i<COMMAND_CASH_SIZE) ){
		lastActionNum = currentActionNum;
		action[currentActionNum] = Action(nextListItem->command);
		currentActionNum++;
		program->IterateForward();
		i++;
	}
	currentActionNum = 0;
}

