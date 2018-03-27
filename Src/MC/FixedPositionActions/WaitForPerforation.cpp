/*
 * WaitForPerforation.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include <MC/FixedPositionActions/WaitForPerforation.hpp>
#include "MC/Settings/Settings.hpp"
#include "MC/MotionController.hpp"

WaitForPerforation::WaitForPerforation()
:WaitForTimeout(&(motionController->perforationTimeSetting)) {
}

