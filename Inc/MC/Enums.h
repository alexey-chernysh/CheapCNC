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
	WORKING,
	START,
	ADJUSTMENT,
} MOTION_VELOCITY;

typedef enum {
	CW, // clockwise
	CCW // counterclockwise
} ARC_DIRECTION;

#endif /* MC_ENUMS_H_ */
