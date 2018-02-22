/*
 * sine_n_cosine.h
 *
 */

#ifndef SINE_N_COSINE_HPP_
#define SINE_N_COSINE_HPP_

#include <stdint.h>

#define SCALING_SHIFT 29

int32_t getScale();
double getDoubleFromLong(int64_t x);
int64_t getLongFromDouble(double x);

int32_t sinInt9(int64_t angle);
int32_t cosInt9(int64_t angle);

void initMath();

#endif /* SINE_N_COSINE_HPP_ */
