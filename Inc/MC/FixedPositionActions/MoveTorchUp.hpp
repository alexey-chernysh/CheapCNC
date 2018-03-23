/*
 * MoveTorchUp.hpp
 *
 *  Created on: 23 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_MOVETORCHUP_HPP_
#define MC_FIXEDPOSITIONACTIONS_MOVETORCHUP_HPP_

#include <MC/FixedPositionActions/WaitForTimeout.hpp>
#include "MC/GPIO/OutputSignal.hpp"

class MoveTorchUp: public WaitForTimeout, private OutputSignal {
public:
	MoveTorchUp();
	virtual bool IterateForward();
};

#endif /* MC_FIXEDPOSITIONACTIONS_MOVETORCHUP_HPP_ */
