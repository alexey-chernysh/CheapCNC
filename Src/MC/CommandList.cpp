/*
 * CommandList.cpp
 *
 *  Created on: 25 апр. 2018 г.
 *      Author: Sales
 */

#include <MC/CommandList.hpp>

CommandList::CommandList():first(0),last(0),current(0){};

void CommandList::AddCommand(Command* newCommand){
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
}

CommandListItem* CommandList::GetCurrent(){ return current; }

void CommandList::IterateForward(){
	if(current){
		current = current->next;
	};
}

void CommandList::IterateBackward(){
	if(current){
		current = current->prev;
	};
}
