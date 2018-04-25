/*
 * Enums.h
 *
 *  Created on: 22 февр. 2018 г.
 *      Author: Sales
 */

#ifndef MC_ENUMS_H_
#define MC_ENUMS_H_

typedef enum {
	HEAD,
	BODY,
	TAIL
} MOTION_PHASE;

typedef enum {
	FREE_RUN = 0,
	WORKING
} MOTION_VELOCITY;

typedef enum {
	WORKING_STYLE,
	DEMO_STYLE,
	ADJUSTMENT_STYLE
} MOTION_STYLE;

typedef enum {
	FREERUN_TYPE,
	WORKING_TYPE,
	SWITCHING_TYPE
} COMMAND_TYPE;

typedef enum {
	CW, // clockwise
	CCW // counterclockwise
} ARC_DIRECTION;

#endif /* MC_ENUMS_H_ */
