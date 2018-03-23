/*
 * ArcOn.hpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_ARCON_HPP_
#define MC_FIXEDPOSITIONACTIONS_ARCON_HPP_

#include <MC/FixedPositionActions/WaitForSignal.hpp>
#include "MC/GPIO/OutputSignal.hpp"

class ArcOn: public WaitForSignal, private OutputSignal {
public:
	ArcOn();
	virtual bool IterateForward();
};

#endif /* MC_FIXEDPOSITIONACTIONS_ARCON_HPP_ */
