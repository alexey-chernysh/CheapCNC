/*
 * int128.h
 *
 *  Created on: 27 дек. 2017 г.
 *      Author: Sales
 */

#ifndef MATH_INT128_H_
#define MATH_INT128_H_

void umul64wide (uint64_t a, uint64_t b, uint64_t *hi, uint64_t *lo);
void mul64wide (int64_t a, int64_t b, int64_t *hi, int64_t *lo);
int64_t mulshift (int64_t a, int64_t b, uint8_t shift);

#endif /* MATH_INT128_H_ */
