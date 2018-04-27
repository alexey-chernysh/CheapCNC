/*
 * CommandList.cpp
 *
 *  Created on: 25 апр. 2018 г.
 *      Author: Sales
 */

#include <MC/CommandList.hpp>

CommandListItem::CommandListItem(Command* c, int32_t n): command(c), prev(0), next(0), num(n){}

uint32_t CommandListItem::GetNum(){ return num; }

CommandList::CommandList():first(0),last(0),current(0),size(0){}

void CommandList::AddCommand(Command* newCommand){
	CommandListItem* newCommandListItem = new CommandListItem(newCommand, size);
	size++;
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

uint32_t CommandList::GetSize(){
	return size;
}

CommandListItem* CommandList::Get(uint32_t n){
	uint32_t currentNum  = current->num;
	while(currentNum < n) IterateForward();
	while(currentNum > n) IterateBackward();
	return current;
}

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
