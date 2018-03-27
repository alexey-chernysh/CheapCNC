/*
 * WaitForPerforation.cpp
 *
 *  Created on: 22 ���. 2018 �.
 *      Author: Sales
 */

#include <MC/FixedPositionActions/WaitForPerforation.hpp>
#include "MC/Settings/Settings.hpp"
#include "MC/MotionController.hpp"

WaitForPerforation::WaitForPerforation()
:WaitForTimeout(&(motionController->perforationTimeSetting)) {
}

