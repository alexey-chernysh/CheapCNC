/*
 * InitialPositioning.hpp
 *
 *  Created on: 22 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_INITIALPOSITIONING_HPP_
#define MC_FIXEDPOSITIONACTIONS_INITIALPOSITIONING_HPP_

#include "MC/GPIO/OutputSignal.hpp"
#include <MC/FixedPositionActions/WaitForSignal.hpp>

class InitialPositioning: public WaitForSignal, private OutputSignal {
public:
	InitialPositioning();
	virtual bool IterateForward();
};

#endif /* MC_FIXEDPOSITIONACTIONS_INITIALPOSITIONING_HPP_ */
