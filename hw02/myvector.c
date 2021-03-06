#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <float.h>
#include "myvector.h"

sVector *myvector_init() {
    sVector *pvector = malloc( sizeof(sVector) );
    pvector->type = 3;
    pvector->data.c.x = 0;
    pvector->data.c.y = 0;
    return pvector;
}

int myvector_set( sVector *pVector , uint8_t type, double a, double b ) {
    if( pVector == NULL || ( type != 1  && type != 2 ) ) {
        return -1;
    }
    if( pVector->type != 1 && pVector->type != 2 && pVector->type != 3 ) {
        return -1;
    }
    if( type  == 2 && ( a < 0 || b < 0 || 2 * M_PI <= b ) ) {
        return -1;
    }
    pVector->type = type;
    pVector->data.c.x = a;
    pVector->data.c.y = b;
    fix_polar_angle(pVector);
    return 0;
}

int myvector_print( const sVector *pVector , uint8_t type ) {
    if( pVector == NULL || ( type != 1 && type != 2 ) ) {
        return -1;
    }
    if( pVector->type != 1 && pVector->type != 2 ) {
        return -1;
    }
    sVector tmp;
    if( type == 1 ) {
        tmp = PtoC( (sVector*)pVector );
        printf( "(%lf,%lf)\n", tmp.data.c.x, tmp.data.c.y );
    }
    if( type == 2 ) {
        tmp = CtoP( (sVector*)pVector );
        printf( "(%lf,%lf-pi)\n", tmp.data.p.distance, tmp.data.p.angle );
    }
    return 0;
}

int myvector_add( sVector *pA, const sVector *pB, const sVector *pC ) {
    if( pA == NULL || pB == NULL || pC == NULL ) {
        return -1;
    }
    if( pA->type != 1 && pA->type != 2 && pA->type != 3 ) {
        return -1;
    }
    if( pB->type != 1 && pB->type != 2 ) {
        return -1;
    }
    if( pC->type != 1 && pC->type != 2 ) {
        return -1;
    }
    sVector tmp_pB = PtoC( (sVector*)pB ), tmp_pC = PtoC( (sVector*)pC );
    pA->type = 1;
    pA->data.c.x = tmp_pB.data.c.x + tmp_pC.data.c.x;
    pA->data.c.y = tmp_pB.data.c.y + tmp_pC.data.c.y;
    if( pB->type == 2 ) {
        *pA = CtoP(pA);
    }
    fix_polar_angle(pA);
    return 0;
}

int myvector_inner_product( double *pA, const sVector *pB, const sVector *pC ) {
    if( pA == NULL || pB == NULL || pC == NULL ) {
        return -1;
    }
    if( pB->type != 1 && pB->type != 2 ) {
        return -1;
    }
    if( pC->type != 1 && pC->type != 2 ) {
        return -1;
    }
    sVector tmp_pB = PtoC( (sVector*)pB ), tmp_pC = PtoC( (sVector*)pC );
    *pA = tmp_pB.data.c.x * tmp_pC.data.c.x + tmp_pB.data.c.y * tmp_pC.data.c.y;
    return 0;
}

int myvector_area( double *pArea , const sVector *pB, const sVector *pC ) {
    if( pArea == NULL || pB == NULL || pC == NULL ) {
        return -1;
    }
    if( pB->type != 1 && pB->type != 2 ) {
        return -1;
    }
    if( pC->type != 1 && pC->type != 2 ) {
        return -1;
    }
    sVector tmp_pB = PtoC( (sVector*)pB ), tmp_pC = PtoC( (sVector*)pC );
    long double x1 = tmp_pB.data.c.x, x2 = tmp_pC.data.c.x;
    long double y1 = tmp_pB.data.c.y, y2 = tmp_pC.data.c.y;
    *pArea = 0.5 * abs(x1 * y2 - x2 * y1);
    return 0;
}

int myvector_cvp( double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB ) {
    if( pX == NULL || pY == NULL || pTx == NULL || pTy == NULL || pA == NULL || pB == NULL ) {
        return -1;
    }
    if( pA->type != 1 && pA->type != 2 ) {
        return -1;
    }
    if( pB->type != 1 && pB->type != 2 ) {
        return -1;
    }

    sVector tmp_pA = PtoC( (sVector*)pA ), tmp_pB = PtoC( (sVector*)pB );

    double AX = tmp_pA.data.c.x, AY = tmp_pA.data.c.y, BX = tmp_pB.data.c.x, BY = tmp_pB.data.c.y;
    double A = AX * AX + AY * AY, B = AX * BX + AY * BY, C = AX * (*pTx) + AY * (*pTy);
    double D = AX * BX + AY * BY, E = BX * BX + BY * BY, F = BX * (*pTx) + BY * (*pTy);

    double V_delta =  A * E - B * D;
    int64_t M = 0, N = 0;

    double cloest_distance = DBL_MAX, cloest_x = 0, cloest_y = 0;

    if( V_delta != 0 ) {
        M = ( C * E - B * F ) / V_delta;
        N = ( A * F - C * D ) / V_delta;
    }
    else {
        M = ( C - B * (*pTy) ) / A;
        N = *pTy;
    }

    for( int i = -1; i <= 1; i++ ) {
        for( int j = -1; j <= 1; j++ ) {
            double distance = get_distance( *pTx, *pTy, ( M + i ) * AX + ( N + j ) * BX, ( M + i ) * AY + ( N + j ) * BY );
            if( distance < cloest_distance ) {
                cloest_x = ( M + i ) * AX + ( N + j ) * BX;
                cloest_y = ( M + i ) * AY + ( N + j ) * BY;
                cloest_distance = distance;
            }
        }
    }
    
    *pX = cloest_x;
    *pY = cloest_y;
    return 0;
}

sVector CtoP( sVector *pvector ) {
    sVector tmp = *pvector;
    if( tmp.type == 1 ) {
        tmp.type = 2;
        double x = tmp.data.c.x, y = tmp.data.c.y;
        tmp.data.p.distance = sqrt( x * x + y * y );
        tmp.data.p.angle = atan2( y ,x );
        fix_polar_angle(&tmp);
    }
    return tmp;
}

sVector PtoC( sVector *pvector ) {
    sVector tmp = *pvector;
    if( tmp.type == 2 ) {
        tmp.type = 1;
        double distance = tmp.data.p.distance, angle = tmp.data.p.angle;
        tmp.data.c.x = distance * cos( angle );
        tmp.data.c.y = distance * sin( angle );
    }
    return tmp; 
}

void fix_polar_angle( sVector* pvector ) {
    if( pvector->type == 2 ) {
        if( pvector->data.p.angle > 2 * M_PI ) {
            while( pvector->data.p.angle > 2 * M_PI ) {
                pvector->data.p.angle -= 2 * M_PI;
            }
        }
        if( pvector->data.p.angle < 0 ) {
            while( pvector->data.p.angle < 0 ) {
                pvector->data.p.angle += 2 * M_PI;
            }
        }
    }
    return;
}

double get_distance( double x1, double y1, double x2, double y2 ) {
    double del_x = x1 - x2;
    double del_y = y1 - y2;
    return sqrt( del_x * del_x + del_y * del_y );
}