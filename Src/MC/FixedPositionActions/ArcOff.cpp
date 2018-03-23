/*
 * ArcOff.cpp
 *
 *  Created on: 23 мар. 2018 г.
 *      Author: Sales
 */

#include "main.h"
#include <MC/FixedPositionActions/ArcOff.hpp>
#include "MC/GPIO/OutputSignal.hpp"

ArcOff::ArcOff():
OutputSignal(Plasma_OnOff_Output_GPIO_Port, Plasma_OnOff_Output_Pin){
}

bool ArcOff::IterateForward(){
	this->Off();
	return false;
}
