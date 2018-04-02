/*
 * Setting.hpp
 *
 *  Created on: 12 мар. 2018 г.
 *      Author: Sales
 */

#ifndef SETTING_HPP_
#define SETTING_HPP_

#include <stdint.h>

class Settings;

class Setting {
private:
	uint32_t offset;
protected:
	Settings* parent;
public:
	Setting(Settings *_parent, uint32_t _offset);
	uint32_t GetOffset();
};

#endif /* SETTING_HPP_ */
