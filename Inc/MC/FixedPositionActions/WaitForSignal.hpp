/*
 * WaitForEvent.hpp
 *
 *  Created on: 22 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_
#define MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_

#include <MC/FixedPositionActions/WaitForTimeout.hpp>

class WaitForSignal: public WaitForTimeout {
public:
	WaitForSignal(uint32_t timeout /* � ������������� */);
};

#endif /* MC_FIXEDPOSITIONACTIONS_WAITFORSIGNAL_HPP_ */
