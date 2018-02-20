/*
 * Position.h
 *
 *  Created on: 19 пїЅпїЅпїЅпїЅ. 2018 пїЅ.
 *      Author: Sales
 */

#ifndef MC_POSITION_H_
#define MC_POSITION_H_

/*
 *  С-врапперы для синглтонов позиций X и Y
 *
 *
 * */

int64_t GetPositionX();
int64_t GetPositionY();
void SetPositionX(int64_t x);
void SetPositionY(int64_t y);

//
void shiftPositionX();

#endif /* MC_POSITION_H_ */
