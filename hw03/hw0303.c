#include <stdio.h>
#include <stdint.h>
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

int main() {
    FILE *input_image = NULL;
    FILE *output_image = NULL;

    sBmpHeader header;

    char input_file_name[MAX_STRING_SIZE] = {0};
    char output_file_name[MAX_STRING_SIZE] = {0};

    printf( "Please enter the input image name: " );
    if( fgets( input_file_name, MAX_STRING_SIZE, stdin ) == NULL ) {
        printf( "Error!\n" );
        exit(0);
    }
    if( input_file_name[ strlen( input_file_name ) - 1 ] == '\n' ) {
        input_file_name[ strlen( input_file_name ) - 1 ] = 0;
    }
    else {
        uint32_t c = 0;
        while( ( c = fgetc( stdin ) ) != '\n' && c != EOF ){}
    }
    if( ( input_image = fopen( input_file_name, "r" ) ) ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    fread( &header, sizeof( header ), 1, input_image );
    if( header.bm[0] != 'B' || header.bm[1] !='M' ) {
        printf("Wrong file format!\n");
        exit(0);
    }

    printf( "Please enter the output image name: " );
    if( fgets( output_file_name, MAX_STRING_SIZE, stdin ) == NULL ) {
        printf( "Error!\n" );
        exit(0);
    }
    if( output_file_name[ strlen( output_file_name ) - 1 ] == '\n' ) {
        output_file_name[ strlen( output_file_name ) - 1 ] = 0;
    }
    else {
        uint32_t c = 0;
        while( ( c = fgetc( stdin ) ) != '\n' && c != EOF ){}
    }
    if( ( output_image = fopen( output_file_name, "r" ) ) ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    fwrite( &header, sizeof( header ), 1, output_image );

    



    return 0;
}

