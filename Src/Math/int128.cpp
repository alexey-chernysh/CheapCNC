/*
 * int128.c
 *
 *  Created on: 27 дек. 2017 г.
 *      Author: Sales
 */

#include "Math/int_math.h"

#ifdef __cplusplus
extern "C" {
#endif

void umul64wide (uint64_t a, uint64_t b, uint64_t *hi, uint64_t *lo)
{
    uint64_t a_lo = (uint64_t)(uint32_t)a;
    uint64_t a_hi = a >> 32;
    uint64_t b_lo = (uint64_t)(uint32_t)b;
    uint64_t b_hi = b >> 32;

    uint64_t p0 = a_lo * b_lo;
    uint64_t p1 = a_lo * b_hi;
    uint64_t p2 = a_hi * b_lo;
    uint64_t p3 = a_hi * b_hi;

    uint32_t cy = (uint32_t)(((p0 >> 32) + (uint32_t)p1 + (uint32_t)p2) >> 32);

    *lo = p0 + (p1 << 32) + (p2 << 32);
    *hi = p3 + (p1 >> 32) + (p2 >> 32) + cy;
}

void mul64wide (int64_t a, int64_t b, int64_t *hi, int64_t *lo)
{
    umul64wide ((uint64_t)a, (uint64_t)b, (uint64_t *)hi, (uint64_t *)lo);
    if (a < 0LL) *hi -= b;
    if (b < 0LL) *hi -= a;
}

/* compute mul_wide (a, b) >> s, for s in [0,63] */
int64_t mulshift (int64_t a, int64_t b, uint8_t s)
{
    int64_t res;
    int64_t hi, lo;
    mul64wide (a, b, &hi, &lo);
    if (s) {
        res = ((uint64_t)hi << (64 - s)) | ((uint64_t)lo >> s);
    } else {
        res = lo;
    }
    return res;
}

#ifdef __cplusplus
}
#endif

