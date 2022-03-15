#include <stdlib.h>
#include "myvector.h"

sVector *myvector_init() {
    sVector *pvector = malloc( sizeof(sVector) );
    pvector->type = 0;
    pvector->data.c.x = 0;
    pvector->data.c.y = 0;
    return pvector;
}

int myvector_set( sVector *pVector , uint8_t type, double a, double b ) {
    if( pVector == NULL || ( type != 1  && type != 2 ) ) {
        return -1;
    }
    pVector->type = type;
    pVector->data.c.x = a;
    pVector->data.c.x = b;
    return 0;
}

int myvector_print( const sVector *pVector , uint8_t type ) {
    if( pVector == NULL   ) {
        return -1;
    }
}

int myvector_add( sVector *pA, const sVector *pB, const sVector *pC ) {
    if( pA == NULL || pB == NULL || pC == NULL ) {
        return -1;
    }
    sVector *tmp_pB = pB, *tmp_pc = pC;
    pA->type = tmp_pB->type;


}

int myvector_inner_product( double *pA, const sVector *pB, const sVector *pC ) {

}

int myvector_area( double *pArea , const sVector *pB, const sVector *pC ) {

}

int myvector_cvp( double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB ) {

}

void CtoP( sVector *pvector ) {
    if( pvector->type == 1 ) {
        pvector->type = 2;
        double x = pvector->data.c.x, y = pvector->data.c.y;
        pvector->data.p.distance = atan( y / x ) / 180;
    }
    return; 
}

void PtoC( sVector *pvector ) {

}