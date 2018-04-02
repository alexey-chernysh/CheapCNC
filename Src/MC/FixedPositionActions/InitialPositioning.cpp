/*
 * InitialPositioning.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include "main.h"
#include "MC/GPIO/InputSignal.hpp"
#include <MC/FixedPositionActions/InitialPositioning.hpp>
#include "MC/Settings/Settings.hpp"
#include "MC/MotionController.hpp"

InitialPositioning::InitialPositioning():
WaitForSignal(PositioningComplete_Input_GPIO_Port, PositioningComplete_Input_Pin, &(motionController->settings.initialPositioningTimeoutSetting)),
OutputSignal(InitialPositioning_Output_GPIO_Port, InitialPositioning_Output_Pin){
}

bool InitialPositioning::IterateForward(){
	this->On();
	if(this->WaitForSignal::IterateForward())return true;
	else {
		this->Off();
		return false;
	}
}
