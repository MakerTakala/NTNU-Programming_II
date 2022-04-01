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
    FILE *input_image = NULL;
    FILE *output_image = NULL;

    sBmpHeader header;

    char input_file_name[MAX_STRING_SIZE] = {0};
    char output_file_name[MAX_STRING_SIZE] = {0};

    printf( "Please enter the input image name: " );
    string_input_template( input_file_name );
    if( ( input_image = fopen( input_file_name, "r" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    fread( &header, sizeof( header ), 1, input_image );
    if( header.bm[0] != 'B' || header.bm[1] !='M' ) {
        printf("Wrong file format!\n");
        exit(0);
    }

    printf( "Please enter the output image name: " );
    string_input_template( output_file_name );
    if( ( output_image = fopen( output_file_name, "w" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }

    header.bpp = 16;
    fwrite( &header, sizeof( header ), 1, output_image );

    while( !feof( input_image ) ) {
        uint8_t original[3] = {0};
        uint8_t modified[2] = {0};
        
        fread( original, 1, 3, input_image );
        modified[0] += original[0] & 0b11111000;
        modified[0] += ( original[1] & 0b11100000 ) >> 5;
        modified[1] += ( original[1] & 0b00011100 ) << 3;
        modified[1] += ( original[2] & 0b11111000 ) >> 3;

        fwrite( modified, 2, 1, output_image );
    }


    fclose( input_image );
    fclose( output_image );

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