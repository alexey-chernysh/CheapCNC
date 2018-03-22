/*
 * Pin.cpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#include <MC/GPIO/Pin.hpp>

Pin::Pin(GPIO_TypeDef* p, uint32_t pN)
: port(p)
, pinNum(pN) {
	// TODO Auto-generated constructor stub

}

