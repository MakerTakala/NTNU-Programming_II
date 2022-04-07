#include <stdio.h>
#include <setjmp.h>
#include <math.h>

jmp_buf jmpbuffer;

double func_b( int num ) {
    if( num < 0 ) {
        longjmp( jmpbuffer, 2 );
    }
    return sqrt( (double)num );
}

int func_a( int a, int b ) {
    a = func_b( a );
    if( b == 0 ) {
        longjmp( jmpbuffer, 1 );
    }
    return a / b;
}

int main() {
    
    int a = 0, b = 0;
    printf( "a: " );
    scanf( "%d", &a );
    printf( "b: " );
    scanf( "%d", &b );

    int jmpval = setjmp( jmpbuffer );
    
    if( jmpval == 1 ) {
        printf( "func_a error\n" );
    }
    else if ( jmpval == 2 ){
        printf( "func_b error\n" );
    }
    else {
        int ans = func_a( a, b );
        printf("sqrt(a) / b = %d\n", ans);
    }
    return 0;
}