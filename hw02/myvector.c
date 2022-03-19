#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <float.h>
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
    pVector->data.c.y = b;
    fix_polar_angle(pVector);
    return 0;
}

int myvector_print( const sVector *pVector , uint8_t type ) {
    if( pVector == NULL || ( type != 1 && type != 2 ) ) {
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
    sVector tmp_pB = PtoC( (sVector*)pB ), tmp_pC = PtoC( (sVector*)pC );
    *pA = tmp_pB.data.c.x * tmp_pC.data.c.x + tmp_pB.data.c.y * tmp_pC.data.c.y;
    return 0;
}

int myvector_area( double *pArea , const sVector *pB, const sVector *pC ) {
    if( pArea == NULL || pB == NULL || pC == NULL ) {
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
    sVector tmp_pA = PtoC( (sVector*)pA ), tmp_pB = PtoC( (sVector*)pB );
    int64_t x_edge = (int64_t)( fmax( abs( *pTx / pA->data.c.x ), abs( *pTx / pB->data.c.x ) ) ) + 1;
    int64_t y_edge = (int64_t)( fmax( abs( *pTy / pA->data.c.y ), abs( *pTy / pB->data.c.y ) ) ) + 1;
    printf("x_edge:%lu y_edge:%lu\n", x_edge, y_edge);
    double cloest_distance = DBL_MAX;
    for( int64_t m = (-1) * x_edge; m <= x_edge; m++ ){
        for( int64_t n = (-1) * y_edge; n <= y_edge; n++ ) {
            double cur_x = tmp_pA.data.c.x * m + tmp_pB.data.c.x * n;
            double cur_y = tmp_pA.data.c.y * m + tmp_pB.data.c.y * n;
            printf("m:%ld n:%ld cur_x:%lf cur_y:%lf\n", m, n, cur_x, cur_y);
            double cur_distance = get_distance( *pTx, *pTy, cur_x, cur_y );
            printf("%lf\n", cur_distance);
            if( cur_distance < cloest_distance ) {
                cloest_distance = cur_distance;
                *pX = cur_x;
                *pY = cur_y;
            }
        }
    }
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