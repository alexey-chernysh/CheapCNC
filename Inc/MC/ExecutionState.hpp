/*
 * MotionState.hpp
 *
 *  Created on: 26 мар. 2018 г.
 *      Author: alexey
 */

#ifndef MC_EXECUTIONSTATE_HPP_
#define MC_EXECUTIONSTATE_HPP_

#include <MC/ExecutionDirection.hpp>

class ExecutionState : public ExecutionDirection {
private:
	bool running;
	bool resuming;
	bool pausing;
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

#endif /* MC_EXECUTIONSTATE_HPP_ */
