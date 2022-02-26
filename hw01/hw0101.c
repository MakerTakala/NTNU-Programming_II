#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool is_hexdigit( char input ) {
    return ( '0' <= input && input <= '9' ) || ( 'a' <= input && input <= 'f' ) || ( 'A' <= input && input <= 'F' );
}

char reverse ( uint8_t num ) {
    uint8_t reverse_num = 0;
    for( int i = 0 ; i < 8; i++ ) {
        reverse_num  = (reverse_num << 1) + ( num & 1 );
        num >>= 1;
    }
    return (char)reverse_num;
}

int main() {
    char string_hex_number[3] = {0};
    char output[5000000] = {0};
    printf( "Please enter the hex string: " );
    while( fgets( string_hex_number, 3, stdin ) ) {
        if( string_hex_number[0] == '0' && string_hex_number[1] == '0' ) {
            printf( "%s\n", output );
            exit(0);
        }
        if( !is_hexdigit( string_hex_number[0] ) || !is_hexdigit( string_hex_number[1] ) ) {
            printf( "\nInvaild Input.\n" );
            exit(0);
        }
        if( string_hex_number[0] == 0 || string_hex_number[1] == 0 ) {
            printf( "\nInvaild Input.\n" );
            exit(0);
        }
        char reverse_number = reverse( strtol( string_hex_number, NULL, 16 ) );
        if( !isprint( reverse_number ) ){
            printf( "\nInvaild Input.\n" );
            exit(0);
        }
        strncat( output, &reverse_number, 1 );
    }
    return 0;
}