#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "fraction_Arithmetic.h"

void mixed_add( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2) {
    pNumber = malloc( sizeof(sMixedNumber) );
    pNumber->upper = r1.upper * r2.lower + r1.lower * r2.upper;
    pNumber->lower = r1.lower * r2.lower;
    return;
}
// pNumber = r1 + r2

void mixed_sub( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2) {
    pNumber = malloc( sizeof(sMixedNumber) );
    pNumber->upper = r1.upper * r2.lower - r1.lower * r2.upper;
    pNumber->lower = r1.lower * r2.lower;
    return;
}
// pNumber = r1 - r2

void mixed_mul( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2) {
    pNumber = malloc( sizeof(sMixedNumber) );
    pNumber->upper = r1.upper * r2.upper;
    pNumber->lower = r1.lower * r2.lower;
    return;
}
// pNumber = r1 * r2

void mixed_div( sMixedNumber *pNumber , const sMixedNumber r1, const sMixedNumber r2) {
    if( r2.upper == 0 ) {
        exit(0);
    }
    pNumber = malloc( sizeof(sMixedNumber) );
    pNumber->upper = r1.upper * r2.lower;
    pNumber->lower = r1.lower * r2.upper;
    if( pNumber->lower < 0 ) {
        pNumber->upper *= (-1);
        pNumber->lower *= (-1);
    }
    return;
}
// pNumber = r1 / r2