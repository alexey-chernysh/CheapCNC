/*
 * WaitForTime.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include <MC/FixedPositionActions/WaitForTimeout.hpp>
#include "MC/Settings/Settings.hpp"

WaitForTimeout::WaitForTimeout(SettingInt32*  timeout /* в миллисекундах */):
_timeout(timeout),
_counter(0L){
}

void WaitForTimeout::Reset(){
	this->_counter = 0;
}

bool WaitForTimeout::IterateForward(){
	this->_counter++;
	if(this->_counter < this->_timeout->Get()) return true;
	else {
		this->Reset();
		return true;
	}
}

bool WaitForTimeout::IterateBackward(){
	this->Reset();
	return false;
}

void WaitForTimeout::OnResumeKeyPressed(){
	this->_counter = MAX_COUNTER;
}

void WaitForTimeout::OnStoreNResumeKeyPressed(){
	this->_timeout->Set(this->_counter);
	settingsBlock.CommitChanges();
	this->OnResumeKeyPressed();
}
