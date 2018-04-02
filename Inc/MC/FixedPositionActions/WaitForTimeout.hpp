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
#include "MC/Settings/SettingInt32.hpp"

class WaitForTimeout: public Action {
private:
	SettingInt32* _timeout;
	uint32_t _counter;
public:
	WaitForTimeout(SettingInt32* timeout /* в миллисекундах */);
	virtual void Init();
	virtual bool IterateForward();
	virtual bool IterateBackward();
	virtual void OnResumeKeyPressed();
	virtual void OnStoreNResumeKeyPressed();
};

#endif /* MC_FIXEDPOSITIONACTIONS_WAITFORTIMEOUT_HPP_ */
