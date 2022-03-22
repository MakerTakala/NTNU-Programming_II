#include <stdio.h>
#include <math.h>
#include "myvector.h"

int main() {
    sVector *v1 = myvector_init();
    sVector *v2 = myvector_init();
    myvector_set( v1, 1, 1, 0 );
    myvector_set( v2, 1, -1, 0 );

    sVector *v3 = myvector_init();
    myvector_add(v3, v1, v2);
    printf("ADD:  X:%lf Y:%lf\n", v3->data.c.x, v2->data.c.y);


    double A = 0;
    myvector_inner_product(&A, v1, v2);
    printf("INNER:%lf\n", A);

    myvector_area(&A, v1, v2);
    printf("AREA:%lf\n", A);

    double X = 0, Y = 0, TX =10, TY = 10;
    myvector_cvp(&X, &Y, &TX, &TY, v1, v2);
    printf("X:%lf Y:%lf\n", X, Y);


    return 0;
}