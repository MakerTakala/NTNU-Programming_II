#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "file_processing.h"
#define MAX_STRING_SIZE 4098

void exit_program( char msg[] ) {
    printf( "%s\n", msg );
    exit(0);
}

FILE *open_file( char* name, char permission[] ) {
    FILE *file = calloc( sizeof(FILE*), 1 );
    if( ( file = fopen( name, permission ) ) == NULL ) {
        printf( "%s could not be opened!\n", name );
        exit(0);
    }
    return file;
}

char* read_string_input( char ask[] ) {
    printf( "%s ", ask );
    char *input = calloc( sizeof(char), MAX_STRING_SIZE );
    if( fgets( input, MAX_STRING_SIZE, stdin ) == NULL ) {
        printf( "Error!\n" );
        exit(0);
    }
    if( input[ strlen( input ) - 1 ] == '\n' ) {
        input[ strlen( input ) - 1 ] = 0;
    }
    else {
        uint32_t c = 0;
        while( ( c = fgetc( stdin ) ) != '\n' && c != EOF ){}
    }
    return input;
}

sBmpHeader* BMP_header_init() {
    sBmpHeader *header = calloc( sizeof(sBmpHeader), 1 );
    header->bm[0] = 'B';
    header->bm[1] = 'M';
    header->size = 54 + 1024 * 768 * 3;
    header->offset = 54;
    header->header_size = 40;
    header->width = 768;
    header->height = 1024;
    header->planes = 1;
    header->bpp = 24;
    header->compression = 0;
    header->bitmap_size = 1024 * 768 * 3;
    header->hres = 25000;
    header->vres = 25000;
    header->used = 0;
    header->important = 0;
    return header;
}