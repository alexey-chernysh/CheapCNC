/*
 * sine_n_cosine.h
 *
 */

#ifndef SINE_N_COSINE_H_
#define SINE_N_COSINE_H_

#include "Math/int_math.h"

#ifndef SCALING_SHIFT
	#define SCALING_SHIFT 29
#endif

void initMath();

int32_t getScale();
double getDoubleFromLong(int64_t x);
int64_t getLongFromDouble(double x);

int32_t sinInt9(int64_t angle);
int32_t cosInt9(int64_t angle);

#endif /* SINE_N_COSINE_H_ */
