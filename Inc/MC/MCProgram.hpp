/*
 * MCProgram.hpp
 *
 *  Created on: 24 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MCPROGRAM_HPP_
#define MC_MCPROGRAM_HPP_

class MCProgram {
private:
	CommandFrame* previousFrame;
	CommandFrame* currentFrame;
	CommandFrame* nextFrame;
public:
	MCProgram();
private:
	void Switch2NextFrame();
	void Switch2PreviousFrame();
};

#endif /* MC_MCPROGRAM_HPP_ */
