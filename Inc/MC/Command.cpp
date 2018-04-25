/*
 * Command.cpp
 *
 *  Created on: 25 апр. 2018 г.
 *      Author: Sales
 */

#include <MC/Command.hpp>

Command::Command(COMMAND_TYPE t):type(t){};

COMMAND_TYPE Command::GetType(){return type;};
