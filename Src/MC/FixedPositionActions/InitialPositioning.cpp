/*
 * InitialPositioning.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include "main.h"
#include <MC/FixedPositionActions/InitialPositioning.hpp>

InitialPositioning::InitialPositioning():
WaitForSignal(PositioningComplete_Input_GPIO_Port, PositioningComplete_Input_Pin, 10000L){
	// TODO Auto-generated constructor stub

}

