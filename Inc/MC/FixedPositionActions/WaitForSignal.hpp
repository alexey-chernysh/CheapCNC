/*
 * WaitForEvent.hpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_
#define MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_

#include <MC/FixedPositionActions/WaitForTimeout.hpp>

class WaitForSignal: public WaitForTimeout {
public:
	WaitForSignal(uint32_t timeout /* в миллисекундах */);
};

#endif /* MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_ */
