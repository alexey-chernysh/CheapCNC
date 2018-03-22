/*
 * MotionDirection.hpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: alexey
 */

#ifndef MC_MOTIONS_MOTIONDIRECTION_HPP_
#define MC_MOTIONS_MOTIONDIRECTION_HPP_

class MotionDirection {
private:
	bool forward;
public:
	MotionDirection();
	bool DirectionIsForward();
	void SetForwardDirection();
	bool DirectionIsBackward();
	void SetBackwardDirection();
};

#endif /* MC_MOTIONS_MOTIONDIRECTION_HPP_ */
