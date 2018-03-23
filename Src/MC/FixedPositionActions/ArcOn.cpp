/*
 * ArcOn.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include "main.h"
#include <MC/FixedPositionActions/ArcOn.hpp>
#include "MC/Settings/Settings.hpp"
#include "MC/GPIO/OutputSignal.hpp"

ArcOn::ArcOn():
WaitForSignal(ArcTransfer_Input_GPIO_Port, ArcTransfer_Input_Pin, &(settings.ignitionTime)),
OutputSignal(Plasma_OnOff_Output_GPIO_Port, Plasma_OnOff_Output_Pin){
}

bool ArcOn::IterateForward(){
	this->On();
	return this->WaitForSignal::IterateForward();
}
