/*
 * Command.cpp
 *
 *  Created on: 25 ���. 2018 �.
 *      Author: Sales
 */

#include <MC/Command.hpp>

Command::Command(COMMAND_TYPE t):type(t){};

COMMAND_TYPE Command::GetType(){return type;};
