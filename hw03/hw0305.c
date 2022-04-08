#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 4097

typedef struct {
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__)) sBmpHeader;


void string_input_template( char input[] );

int main() {
    printf( "Please enter the image: " );
    char image_name[MAX_STRING_SIZE] = {0};
    string_input_template( image_name );
    FILE *image;
    if( ( image = fopen( image_name, "r" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    sBmpHeader header;
    fread( &header, sizeof( header ), 1, image );
    if( strncmp( header.bm, "BM", 2 ) || header.bpp != 24 ) {
        printf("Wrong file format!\n");
        exit(0);
    }

    printf( "Please enter the puzzle: " );
    char puzzle_name[MAX_STRING_SIZE] = {0};
    string_input_template( puzzle_name );
    FILE *puzzle;
    if( ( puzzle = fopen( puzzle_name, "r" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    //preprocess

    uint64_t m = 0, n = 0, step = 0;
    char buffer[MAX_STRING_SIZE] = {0};
    fgets( buffer, MAX_STRING_SIZE, puzzle );
    char *end_ptr = NULL;
    m = strtoull( buffer, &end_ptr, 10 );
    if( *end_ptr != ' ' ) {
        printf("Wrong input format!\n");
        exit(0);
    }
    n = strtoull( end_ptr, &end_ptr, 10 );
    if( *end_ptr != '\n' ) {
        printf("Wrong input format!\n");
        exit(0);
    }
    fgets( buffer, MAX_STRING_SIZE, puzzle );
    step = strtoull( buffer, &end_ptr, 10 );
    if( *end_ptr != '\n' ) {
        printf("Wrong input format!\n");
        exit(0);
    }

    for( int i = 0; i < step; i++ ) {
        char new_image_name[MAX_STRING_SIZE];
        sprintf(new_image_name, "%d.bmp", i);
        FILE *new_image;
        if( ( new_image = fopen( new_image_name, "w" ) ) == NULL ) {
            printf( "File could not be opened!\n" );
            exit(0);
        }




    }



    return 0;
}

void string_input_template( char input[] ) {
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
}
