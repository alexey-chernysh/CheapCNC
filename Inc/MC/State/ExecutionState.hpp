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

	void SetRunning();
	void SetPaused();
	bool IsRunning();
	bool IsPaused();

	void SetResuming();
	void SetNonResuming();
	bool IsResuming();

	void SetPausing();
	void SetNonPausing();
	bool IsPausing();
};

#endif /* MC_STATE_EXECUTIONSTATE_HPP_ */
