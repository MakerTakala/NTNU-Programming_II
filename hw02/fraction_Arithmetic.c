#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "fraction_Arithmetic.h"

void mixed_add( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2) {
    pNumber->upper = r1.upper * r2.lower + r1.lower * r2.upper;
    pNumber->lower = r1.lower * r2.lower;
    fixMixedNumber(pNumber);
    return;
}
// pNumber = r1 + r2

void mixed_sub( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2) {
    pNumber->upper = r1.upper * r2.lower - r1.lower * r2.upper;
    pNumber->lower = r1.lower * r2.lower;
    fixMixedNumber(pNumber);
    return;
}
// pNumber = r1 - r2

void mixed_mul( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2) {
    pNumber->upper = r1.upper * r2.upper;
    pNumber->lower = r1.lower * r2.lower;
    fixMixedNumber(pNumber);
    return;
}
// pNumber = r1 * r2

void mixed_div( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2) {
    if( r2.upper == 0 ) {
        exit(0);
    }
    pNumber->upper = r1.upper * r2.lower;
    pNumber->lower = r1.lower * r2.upper;
    if( pNumber->lower < 0 ) {
        pNumber->upper *= (-1);
        pNumber->lower *= (-1);
    }
    fixMixedNumber(pNumber);
    return;
}
// pNumber = r1 / r2

uint32_t _gcd( uint32_t a, uint32_t b ) {
    if( a % b == 0 ) {
        return b;
    }
    return _gcd( b, a % b );
}

void fixMixedNumber( sMixedNumber *pNumber ) {
    uint32_t gcd = _gcd( abs( pNumber->upper ), abs( pNumber->lower ) );
    pNumber->upper /= gcd;
    pNumber->lower /= gcd;
    return;
}