#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

bool is_hexdigit( char input ) {
    return ( '0' <= input && input <= '9' ) || ( 'a' <= input && input <= 'f' ) || ( 'A' <= input && input <= 'F' );
}

void input_test( char input[] ) {
    if( !is_hexdigit( input[0] ) || !is_hexdigit( input[1] ) ) {
        printf( "\nInvaild Input.\n" );
        exit(0);
    }
    if( input[0] == '0' && input[1] == '0' ) {
        printf("\n");
        exit(0);
    }
    return;
}

uint8_t reverse ( uint8_t num ) {
    uint8_t reverse_num = 0;
    for( int i = 0 ; i < 8; i++ ) {
        reverse_num  = (reverse_num << 1) + ( num & 1 );
        num >>= 1;
    }
    return reverse_num;
}

int main() {
    char string_hex_number[3] = {0};
    printf( "Please enter the hex string: " );
    while( fgets( string_hex_number, 3, stdin ) ) {
        input_test( string_hex_number );
        uint8_t reverse_number = reverse( strtol( string_hex_number, NULL, 16 ) );
        if( reverse_number < 32 || 126 < reverse_number ){
            printf( "Your reverse input is unprintable.\n" );
            exit(0);
        }
        printf("%c", reverse_number );
    }
    return 0;
}