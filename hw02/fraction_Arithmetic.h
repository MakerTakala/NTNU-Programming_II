#pragma once

#include <stdint.h>

typedef struct _sMixedNumber {
    int64_t upper;
    int64_t lower;
}sMixedNumber;

void mixed_add( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2);
// pNumber = r1 + r2
void mixed_sub( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2);
// pNumber = r1 - r2
void mixed_mul( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2);
// pNumber = r1 * r2
void mixed_div( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2);
// pNumber = r1 / r2

uint32_t _gcd( uint32_t a, uint32_t b );

void fixMixedNumber( sMixedNumber *pNumber );