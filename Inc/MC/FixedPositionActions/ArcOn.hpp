/*
 * ArcOn.hpp
 *
 *  Created on: 22 ���. 2018 �.
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
