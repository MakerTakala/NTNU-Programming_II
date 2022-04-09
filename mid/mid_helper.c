#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mid_helper.h"

FILE *open_file( char question[], char permission[], uint64_t max_name_size ) {
    printf( "%s", question );
    char file_name[max_name_size];
    stdin_input_string( file_name, max_name_size );
    FILE *file = calloc( sizeof(FILE*), 1 );
    if( ( file = fopen( file_name, permission ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    return file;
}

void stdin_input_string( char *buffer, uint64_t max_name_size ) {
    if( fgets( buffer, max_name_size, stdin ) == NULL ) {
        printf( "Error!\n" );
        exit(0);
    }
    if( buffer[ strlen( buffer ) - 1 ] == '\n' ) {
        buffer[ strlen( buffer ) - 1 ] = 0;
    }
    else {
        uint32_t c = 0;
        while( ( c = fgetc( stdin ) ) != '\n' && c != EOF ){}
    }
}

double ask_angle() {
    printf( "Rotation angle (int, 0-360): " );
    double angle = 0;
    scanf( "%lf", &angle );
    if( angle < 0 || 360 < angle ) {
        printf( "Wrong angle!!\n" );
        exit(0);
    }
    return angle;
}

void count_width_height( uint32_t width, uint32_t height, double angle, uint32_t *new_width, uint32_t *new_height ) {
    long double diagonal_length = sqrtl( width * width + height * height );
    long double original_diagonal_angle = atan( height / width );
    long double fixed_diagonal_angle = original_diagonal_angle + angle;
    *new_width = fabsl( diagonal_length * cos( fixed_diagonal_angle ) );
    *new_height = fabsl( diagonal_length * sin( fixed_diagonal_angle ) ) * 2;
}

uint64_t ask( char question[] ) {
    printf("%s", question);
    uint64_t time = 0;
    char buffer[4096];
    if( fgets( buffer, 4096, stdin ) == NULL ) {
        printf( "Error!\n" );
        exit(0);
    }
    if( buffer[ strlen( buffer ) - 1 ] == '\n' ) {
        buffer[ strlen( buffer ) - 1 ] = 0;
    }
    else {
        uint32_t c = 0;
        while( ( c = fgetc( stdin ) ) != '\n' && c != EOF ){}
    }

    char *end = NULL;
    time = strtoul( buffer, &end, 10 );
    if( *end != 0 ){
        printf("Wrong Input\n");
        exit(0);
    }
    if( time <= 0 ) {
        printf("Wrong Input\n");
        exit(0);
    }
    return time;
}

void print_menu() {
    printf("--- Menu ---\n\
1) Which country has the largest population growth?\n\
2) Which country has the largest population growth rate?\n\
3) Which country has the smallest population growth , including negative growth?\n\
4) Which country has the smallest population growth rate, including negative growth?\n\
5) Which country has the largest population standard deviation?\n\
6) Which country has the smallest population standard deviation?\n\
7) Given a country name (case -insensitive), please use linear least squaresmethod to predict the country's population in 2021.\n\
8) Exit\n");
}