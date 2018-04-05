/*
 * MotionDirection.hpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: alexey
 */

#ifndef MC_STATE_EXECUTIONDIRECTION_HPP_
#define MC_STATE_EXECUTIONDIRECTION_HPP_

class ExecutionDirection {
private:
	bool forward;
public:
	ExecutionDirection();
	bool DirectionIsForward();
	void SetForwardDirection();
	bool DirectionIsBackward();
	void SetBackwardDirection();
};

#endif /* MC_STATE_EXECUTIONDIRECTION_HPP_ */
