/*
 * MotionController.h
 *
 *  Created on: 22 ����. 2018 �.
 *      Author: Sales
 */

#ifndef MC_MOTIONCONTROLLER_H_
#define MC_MOTIONCONTROLLER_H_

void MC_Init();
void MC_OnTimer();
void MC_onControlKey(char controlKey);
char* prepareUSBMessage(uint32_t requestNum);

#endif /* MC_MOTIONCONTROLLER_H_ */
