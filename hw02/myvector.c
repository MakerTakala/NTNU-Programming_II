#include <stdlib.h>
#include <math.h>
#include <stdio.h>
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
    if( type  == 2 && a < 0 ) {
        return -1;
    }
    pVector->type = type;
    pVector->data.c.x = a;
    pVector->data.c.x = b;
    fix_polar_angle(pVector);
    return 0;
}

int myvector_print( const sVector *pVector , uint8_t type ) {
    if( pVector == NULL || ( type != 1 && type != 2 ) ) {
        return -1;
    }
    sVector tmp;
    if( type == 1 ) {
        tmp = PtoC( pVector );
        printf( "(%lf,%lf)", tmp.data.c.x, tmp.data.c.y );
    }
    if( type == 2 ) {
        tmp = CtoP( pVector );
        printf( "(%lf,%lf-pi)", tmp.data.p.distance, tmp.data.p.angleUser );
    }
    return 0;
}

int myvector_add( sVector *pA, const sVector *pB, const sVector *pC ) {
    if( pA == NULL || pB == NULL || pC == NULL ) {
        return -1;
    }
    sVector tmp_pB = PtoC(pB), tmp_pC = PtoC(pC);
    pA->type = 1;
    pA->data.c.x = tmp_pB.data.c.x + tmp_pC.data.c.x;
    pA->data.c.y = tmp_pB.data.c.y + tmp_pC.data.c.y;
    if( pB->type == 2 ) {
        *pA = CtoP(pA);
    }
    return 0;
}

int myvector_inner_product( double *pA, const sVector *pB, const sVector *pC ) {
    if( pA == NULL || pB == NULL || pC == NULL ) {
        return -1;
    }
    sVector tmp_pB = PtoC(pB), tmp_pC = PtoC(pC);
    *pA = tmp_pB.data.c.x * tmp_pC.data.c.x + tmp_pB.data.c.y * tmp_pC.data.c.y;
    return 0;
}

int myvector_area( double *pArea , const sVector *pB, const sVector *pC ) {
    if( pArea == NULL || pB == NULL || pC == NULL ) {
        return -1;
    }
    sVector tmp_pB = PtoC(pB), tmp_pC = PtoC(pC);
    long double x1 = tmp_pB.data.c.x, x2 = tmp_pC.data.c.x;
    long double y1 = tmp_pC.data.c.y, y2 = tmp_pC.data.c.y;
    *pArea = 0.5 * (x1 * y2 - x2 * y1);
    return 0;
}

int myvector_cvp( double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB ) {

}

sVector CtoP( sVector *pvector ) {
    sVector tmp = *pvector;
    if( tmp->type == 1 ) {
        tmp->type = 2;
        double x = tmp->data.c.x, y = tmp->data.c.y;
        tmp->data.p.distance = sqrt( x * x + y * y );
        tmp->data.p.angle = atan( y / x );
    }
    return tmp;
}

sVector PtoC( sVector *pvector ) {
    sVector tmp = *pvector;
    if( tmp->type == 2 ) {
        tmp->type = 1;
        double distance = tmp->data.c.distance, angle = tmp->data.c.angle;
        tmp->data.p.x = distance * cos( angle );
        tmp->data.p.y = distance * sin( angle );
    }
    return tmp; 
}

void fix_polar_angle( sVector* pvector ) {
    if( pvector->type == 2 ) {
        if( pvector->data.p.angle > 180 ) {
            while( pvector->data.p.angle > 180 ) {
                pvector->data.p.angle -= 180;
            }
        }
        if( pvector->data.p.angle < 0 ) {
            while( pvector->data.p.angle < 0 ) {
                pvector->data.p.angle += 180;
            }
        }
    }
    return;
}