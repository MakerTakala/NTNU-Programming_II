#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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