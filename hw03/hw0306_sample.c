#include <stdio.h>
#include <math.h>

double func_b( int num ) {
    return sqrt( (double)num );
}

int func_a( int a, int b ) {
    a = func_b( a );
    return a / b;
}

int main() {
    
    int a = 0, b = 0;
    printf( "a: " );
    scanf( "%d", &a );
    printf( "b: " );
    scanf( "%d", &b );

    int ans = func_a( a, b );
    printf("sqrt(a) / b = %d\n", ans);

    return 0;
}