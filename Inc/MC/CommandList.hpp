/*
 * CommandList.hpp
 *
 *  Created on: 25 апр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_COMMANDLIST_HPP_
#define MC_COMMANDLIST_HPP_

#include "MC/General.h"

class Command;

class CommandListItem {
public:
	Command* command;
	CommandListItem* prev;
	CommandListItem* next;
	const uint32_t num;
public:
	CommandListItem(Command* c, int32_t n);
	uint32_t GetNum();
};

class CommandList {
private:
	CommandListItem* first;
	CommandListItem* last;
	CommandListItem* current;
	uint32_t size;
public:
	CommandList();
	void AddCommand(Command* newCommand);
	CommandListItem* Get(uint32_t n);
	uint32_t GetSize();
private:
	void IterateForward();
	void IterateBackward();
};

#endif /* MC_COMMANDLIST_HPP_ */
