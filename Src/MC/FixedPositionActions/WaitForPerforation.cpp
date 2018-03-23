/*
 * WaitForPerforation.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include <MC/FixedPositionActions/WaitForPerforation.hpp>
#include "MC/Settings/Settings.hpp"

WaitForPerforation::WaitForPerforation()
:WaitForTimeout(&(settings.perforationTime)) {
	// TODO Auto-generated constructor stub

}

