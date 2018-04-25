/*
 * Command.hpp
 *
 *  Created on: 25 ���. 2018 �.
 *      Author: Sales
 */

#ifndef MC_COMMAND_HPP_
#define MC_COMMAND_HPP_

#include "MC/Enums.h"

class Command {
private:
	COMMAND_TYPE type;
public:
	Command(COMMAND_TYPE t);
	COMMAND_TYPE GetType();
};

#endif /* MC_COMMAND_HPP_ */
