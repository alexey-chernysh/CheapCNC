/*
 * MCProgram.cpp
 *
 *  Created on: 24 апр. 2018 г.
 *      Author: Sales
 */

#include <MC/ActionsCache.hpp>
#include "MC/CommandList.hpp"
#include "MC/MotionController.hpp"

ActionsCache::ActionsCache(CommandList* p):program(p){
	CommandListItem* nextListItem = 0;
	uint16_t i = 0;
	firstActionNum = 0;
	lastActionNum = 0;
	currentActionNum = 0;
	doNotDisturb = false;
	uint32_t programSize = program->GetSize();
	while( (i<ACTION_CACHE_SIZE) && (i<programSize) ){
		nextListItem = program->Get(i);
		lastActionNum = currentActionNum;
		cache[currentActionNum] = ActionItem(nextListItem);
		currentActionNum++;
		i++;
	}
	currentActionNum = 0;
}

int16_t ActionsCache::GetForwardLength(){
	if(lastActionNum > currentActionNum) return lastActionNum - currentActionNum;
	else return lastActionNum - currentActionNum + ACTION_CACHE_SIZE;
};

int16_t ActionsCache::GetBackwardLength(){
	if(firstActionNum < currentActionNum) return currentActionNum - firstActionNum;
	else return currentActionNum - firstActionNum + ACTION_CACHE_SIZE;
};

int16_t IncNum(int16_t num){
	int16_t tmp = num + 1;
	if(tmp >= ACTION_CACHE_SIZE) return tmp - ACTION_CACHE_SIZE;
	else return tmp;
}

int16_t DecNum(int16_t num){
	int16_t tmp = num - 1;
	if(tmp < 0) return tmp + ACTION_CACHE_SIZE;
	else return tmp;
}

bool Collision(uint16_t first, uint16_t last){
	uint16_t diff = last - first;
	if(diff > 0) return false;
	else
		if(diff < 0 )return false;
		else return true;
}

void ActionsCache::Update(){
	if(!doNotDisturb){
		doNotDisturb = true;
		if(motionController->executionState.DirectionIsForward()){
			int16_t len = GetForwardLength();
			if(len < ACTION_CACHE_CENTER){
				uint32_t lastActionCommandNum = cache[lastActionNum].parentCommand->GetNum();
				uint32_t newActionCommandNum = lastActionCommandNum + 1;
				if(newActionCommandNum < program->GetSize()){
					CommandListItem* nextItem = program->Get(newActionCommandNum);
					int16_t tmp = IncNum(lastActionNum);
					cache[tmp] = ActionItem(nextItem);
					lastActionNum = tmp;
					if(Collision(firstActionNum, lastActionNum))
						firstActionNum = IncNum(firstActionNum);
				}
			}
		} else {
			int16_t len = GetBackwardLength();
			if(len < ACTION_CACHE_CENTER){
				uint32_t firstActionCommandNum = cache[firstActionNum].parentCommand->GetNum();
				uint32_t newActionCommandNum = firstActionCommandNum - 1;
				if(newActionCommandNum >= 0){
					CommandListItem* prevItem = program->Get(newActionCommandNum);
					int16_t tmp = DecNum(firstActionNum);
					cache[tmp] = ActionItem(prevItem);
					firstActionNum = tmp;
					if(Collision(firstActionNum, lastActionNum))
						lastActionNum = DecNum(lastActionNum);
				}
			}
		}
		doNotDisturb = false;
	};
};
