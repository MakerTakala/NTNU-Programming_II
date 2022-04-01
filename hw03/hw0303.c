#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

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
    fwrite( &header, sizeof( header ), 1, output_image );

    uint64_t center_x = 0, center_y = 0;
    char input_buffer[MAX_STRING_SIZE] = {0};
    printf( "Please enter the center: " );
    string_input_template( input_buffer );
    if( input_buffer[0] != '(' || input_buffer[ strlen( input_buffer ) - 1 ] != ')' ) {
        printf("Wrong input format!\n");
        exit(0);
    }
    char *comma = NULL;
    center_x = strtoull( input_buffer + 1, &comma, 10 );
    if( *comma != ',' || !isdigit( *(comma + 1) ) ) {
        printf("Wrong input format!\n");
        exit(0);
    }
    center_y = strtoull( comma + 1, NULL, 10 );

    uint64_t radius = 0;
    printf( "Please enter the radius: " );
    string_input_template( input_buffer );
    char *end = NULL;
    radius = strtoull( input_buffer, &end, 10 );
    if( *end != 0 ) {
        printf("Wrong input format!\n");
        exit(0);
    }
    
    for( int i = 1; i <= header.height; i++ ) {
        for( int j = 1; j <= header.width; j++ ) {
            uint8_t data[3] = {0};
            fread( data, 1, 3, input_image );
            if( sqrt( (double)( ( center_x - j ) * ( center_x - j ) + ( center_y - ( header.height - i ) ) * ( center_y - ( header.height - i ) ) ) ) > (double)radius ) {
                data[0] = UCHAR_MAX;
                data[1] = UCHAR_MAX;
                data[2] = UCHAR_MAX;
            }
            fwrite( data, 3, 1, output_image );
        }
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