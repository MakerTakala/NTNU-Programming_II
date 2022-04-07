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

typedef struct{
    uint32_t rgbBlue;
    uint32_t rgbGreen;
    uint32_t rgbRed;
    uint32_t rgbReserved;
}__attribute__ ((__packed__)) MASK;

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
    if( strncmp( header.bm, "BM", 2 ) || header.bpp != 24 ) {
        printf("Wrong file format!\n");
        exit(0);
    }

    printf( "Please enter the output image name: " );
    string_input_template( output_file_name );
    if( ( output_image = fopen( output_file_name, "w" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }

    header.offset = 70;
    header.bpp = 16;
    header.compression = 3;
    header.size = 70 + ( 16 * header.width + 31 ) / 32 * 4;
    header.bitmap_size = ( 16 * header.width + 31 ) / 32 * 4;
    fwrite( &header, sizeof( header ), 1, output_image );

    MASK mask565 = { 0b1111100000000000U, 0b0000011111100000U, 0b0000000000011111U, 0b0000000000000000U };
    fwrite( &mask565, sizeof( MASK ), 1, output_image );


    while( !feof( input_image ) ) {
        uint8_t original[3] = {0};
        uint16_t modified = 0;
        
        fread( original, 1, 3, input_image );
        /*
        modified[0] += original[0] & 0b11111000;
        modified[0] += ( original[1] & 0b11100000 ) >> 5;
        modified[1] += ( original[1] & 0b00011100 ) << 3;
        modified[1] += ( original[2] & 0b11111000 ) >> 3;
        */
        modified += ( original[2] * 31 / 255 ) << 11;
        modified += ( original[1] * 63 / 255 ) << 5;
        modified += ( original[0] * 31 / 255 );
        fwrite( &modified, 2, 1, output_image );
    }
    printf("Done\n");

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