/*
 * ArcOff.hpp
 *
 *  Created on: 23 мар. 2018 г.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_ARCOFF_HPP_
#define MC_FIXEDPOSITIONACTIONS_ARCOFF_HPP_

#include <MC/Action.hpp>
#include <MC/GPIO/OutputSignal.hpp>

class ArcOff: public Action, private OutputSignal {
public:
	ArcOff();
	virtual bool IterateForward();
};

#endif /* MC_FIXEDPOSITIONACTIONS_ARCOFF_HPP_ */
