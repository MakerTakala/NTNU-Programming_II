#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "file_processing.h"

FILE *open_file( char name[], char permission[] ) {
    FILE *file = calloc( sizeof(FILE*), 1 );
    if( ( file = fopen( name, permission ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    return file;
}