/*
 * MotionDirection.hpp
 *
 *  Created on: 27 февр. 2018 г.
 *      Author: alexey
 */

#ifndef MC_MOTIONDIRECTION_HPP_
#define MC_MOTIONDIRECTION_HPP_

class MotionDirection {
private:
	bool forward;
public:
	MotionDirection();
	bool IsForward();
	void SetForward();
	bool IsBackward();
	void SetBackward();
};

#endif /* MC_MOTIONDIRECTION_HPP_ */
