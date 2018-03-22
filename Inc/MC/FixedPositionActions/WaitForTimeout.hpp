/*
 * WaitForTime.hpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_WAITFORTIMEOUT_HPP_
#define MC_FIXEDPOSITIONACTIONS_WAITFORTIMEOUT_HPP_

#include <stdint.h>
#include "MC/Action.hpp"

class WaitForTimeout: public Action {
private:
	uint32_t _timeout;
public:
	WaitForTimeout(uint32_t timeout /* в миллисекундах */);
};

#endif /* MC_FIXEDPOSITIONACTIONS_WAITFORTIMEOUT_HPP_ */
