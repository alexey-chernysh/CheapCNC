/*
 * CommandList.hpp
 *
 *  Created on: 25 апр. 2018 г.
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
	CommandList():first(0),last(0),current(0){};
	void AddCommand(Command* newCommand){
		CommandListItem* newCommandListItem = new CommandListItem(newCommand);
		if(last){
			last->next = newCommandListItem;
			newCommandListItem->prev = last;
			last = newCommandListItem;
		} else {
			first = newCommandListItem;
			last = first;
			current = first;
		};
	};
	Command* GetNextCommand(){
		if(current){
			current = current->next;
			if(current) return current->command;
			else return 0;
		} else {
			return 0;
		};
	}
	Command* GetPrevCommand(){
		if(current){
			current = current->prev;
			if(current) return current->command;
			else return 0;
		} else {
			return 0;
		};
	}
};

#endif /* MC_COMMANDLIST_HPP_ */
