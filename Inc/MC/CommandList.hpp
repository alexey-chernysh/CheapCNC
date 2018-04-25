/*
 * CommandList.hpp
 *
 *  Created on: 25 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_COMMANDLIST_HPP_
#define MC_COMMANDLIST_HPP_

class Command;

class CommandListItem {
public:
	CommandListItem* prev;
	CommandListItem* next;
	Command* command;
	CommandListItem(Command* c):prev(0),next(0),command(c){};
};

class CommandList {
private:
	CommandListItem* first;
	CommandListItem* last;
	CommandListItem* current;
public:
	CommandList();
	void AddCommand(Command* newCommand);
	CommandListItem* GetCurrent();
	void IterateForward();
	void IterateBackward();
};

#endif /* MC_COMMANDLIST_HPP_ */
