/*
 * ArcOn.cpp
 *
 *  Created on: 22 ���. 2018 �.
 *      Author: Sales
 */

#include <MC/FixedPositionActions/ArcOn.hpp>

ArcOn::ArcOn()
:WaitForSignal(ArcTransfer_Input_GPIO_Port, ArcTransfer_Input_Pin, 10000L) {
	// TODO Auto-generated constructor stub

}

