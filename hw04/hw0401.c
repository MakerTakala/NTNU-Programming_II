#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "file_processing.h"

int main( int argc, char *argv[] ) {
    if( argc != 2 ) {
        printf( "Wrong Argument!!\n" );
        exit(0);
    }
    FILE *image = open_file( "r", 4096, argv[1] );
    BmpHeader header;
    fread( &header, sizeof( header ), 1, image );
    if( strncmp( header.bm, "BM", 2 ) || header.bpp != 24 ) {
        printf("Wrong file format!\n");
        exit(0);
    }

    uint8_t image_data[header.height][header.width][3];
    fread( &image_data, sizeof( image_data ), 1, image );
    for( int i = 0; i < header.height; i++ ) {
        for( int j = 0; j < header.width; j++ ) {
            uint8_t gray = (uint8_t)( (double)image_data[i][j][0] * 0.114 + (double)image_data[i][j][1] * 0.587 + (double)image_data[i][j][2] * 0.299 );
            gray = ( gray <= 127 ? 0 : 255 );
            for( int k = 0; k < 3; k++ ) {
                image_data[i][j][k] = gray;
            }
        }
    }


    fclose( image );
}