/*
 * MotionState.hpp
 *
 *  Created on: 26 мар. 2018 г.
 *      Author: alexey
 */

#ifndef MC_STATE_EXECUTIONSTATE_HPP_
#define MC_STATE_EXECUTIONSTATE_HPP_

#include <MC/State/ExecutionDirection.hpp>

class ExecutionState : public ExecutionDirection {
private:
	bool running;
	bool resuming;
	bool pausing;
	bool repositioning;
	bool demoMode;
	bool adjustmentMode;
public:
	ExecutionState();
	void Reset();

	void SetRunningFlag();
	void ResetRunningFlag();
	bool RunningFlagIsOn();

	void SetResumingFlag();
	void ResetResumingFlag();
	bool ResumingFlagIsOn();

	void SetPausingFlag();
	void ResetPausingFlag();
	bool PausingFlagIsOn();

	void SetDemoModeFlag();
	void ResetDemoModeFlag();
	bool DemoModeFlagIsOn();

	void SetRepositioningModeFlag();
	void ResetRepositioningModeFlag();
	bool RepositioningFlagIsOn();

	void SetAdjastmentModeFlag();
	void ResetAdjastmentModeFlag();
	bool AdjustmentFlagIsOn();
};

#endif /* MC_STATE_EXECUTIONSTATE_HPP_ */
