#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool bit_compare( int8_t i, uint64_t* bit ) {
    return ( ( (uint64_t)1 << i) & *bit ) && 1;
}

int main() {
    double input = 0.0;
    printf("Please enter a floating -point number (double precision): ");
    scanf("%lf", &input);
    uint64_t *bit = (uint64_t*)&input;
    uint16_t exponent = 0;
    printf("%lX\n", *bit);

    printf("Sign: %d\n", bit_compare( 63, bit ) );
    printf("Exponent: ");
    for(int i = 62; i >= 52; i--) {
        exponent |= ( bit_compare( i, bit ) << (i - 52) );
        printf("%d", bit_compare( i, bit ) );
    }
    printf("\n");
    printf("Fraction: ");
    for(int i = 51; i >= 0; i--) {
        printf("%d", bit_compare( i, bit ));
    }
    printf("\n");

    printf("%lf = ", input);
    printf("(-1)^%d", bit_compare( 63, bit ) );
    printf(" * ");
    printf("(1");
    for(int i = 51; i >= 0; i--) {
        if( bit_compare( i, bit ) ) {
            printf(" + 2^%d", i - 52);
        }
    }
    printf(")");
    printf(" * 2^(%hu - 1023)\n", exponent);


    return 0;
}