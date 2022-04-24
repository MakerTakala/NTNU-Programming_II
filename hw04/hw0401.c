#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "file_processing.h"

#define WHITE {0xFF, 0xFF, 0xFF}

int main( int argc, char *argv[] ) {
    srandom( time(NULL) );

    if( argc != 2 ) {
        printf( "Wrong Option!!\n" );
        exit(0);
    }
    char image_name[4096] = {0};
    strncpy( image_name, argv[1], 4096 );
    FILE *image = open_file( image_name, "r" );
    BmpHeader header;
    fread( &header, sizeof( header ), 1, image );
    if( strncmp( header.bm, "BM", 2 ) || header.bpp != 24 ) {
        printf("Wrong file format!\n");
        exit(0);
    }
    if( strlen( image_name ) >= 4 && strncmp( strrchr( image_name, '.' ), ".bmp", 4 ) ) {
        printf("File name should suffix with \".bmp\"!\n");
        exit(0);
    }

    uint8_t image_data[header.height][header.width][3];
    fread( &image_data, sizeof( image_data ), 1, image );
    for( int i = 0; i < header.height; i++ ) {
        for( int j = 0; j < header.width; j++ ) {
            uint8_t gray = (uint8_t)( (double)image_data[i][j][0] * 0.114 + (double)image_data[i][j][1] * 0.587 + (double)image_data[i][j][2] * 0.299 );
            gray = ( gray < 128 ? 0 : 0XFF );
            for( int k = 0; k < 3; k++ )
                image_data[i][j][k] = gray;
        }
    }
    
    header.height *= 2;
    header.width *= 2;
    header.size = 54 + ( header.height * header.width * 24 / 8 );
    header.bitmap_size = header.height * header.width * 24 / 8;

    char layer1_name[4096] = {0}, layer2_name[4096] = {0}, overlap_name[4096] = {0};
    strncat( strncpy( layer1_name, image_name, strlen( image_name ) - 4 ), "_layer1.bmp", 4096 );
    strncat( strncpy( layer2_name, image_name, strlen( image_name ) - 4 ), "_layer2.bmp", 4096 );
    strncat( strncpy( overlap_name, image_name, strlen( image_name ) - 4 ), "_overlap.bmp", 4096 );
    FILE *layer1 = open_file( layer1_name, "w" ), *layer2 = open_file( layer2_name, "w" ), *overlap = open_file( overlap_name, "w" );
    fwrite( &header, sizeof( header ), 1, layer1 );
    fwrite( &header, sizeof( header ), 1, layer2 );
    fwrite( &header, sizeof( header ), 1, overlap );

    for( int i = 0; i < header.height / 2; i++ ) {
        uint8_t layer1_data[2][header.width][3], layer2_data[2][header.width][3], overlap_data[2][header.width][3];
        memset( layer1_data, 0, header.width * 2 * 3 );
        memset( layer2_data, 0, header.width * 2 * 3 );
        memset( overlap_data, 0, header.width * 2 * 3 );
        for( int j = 0; j < header.width / 2; j++ ) {
            if( image_data[i][j][0] == 0XFF ) {
                if( random() & 1 ) {
                    for( int k = 0; k < 3; k++ )
                        layer1_data[0][j * 2 + 0][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer1_data[1][j * 2 + 1][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer2_data[0][j * 2 + 0][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer2_data[1][j * 2 + 1][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        overlap_data[0][j * 2 + 0][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        overlap_data[1][j * 2 + 1][k] = 0XFF;
                }
                else {
                    for( int k = 0; k < 3; k++ )
                        layer1_data[0][j * 2 + 1][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer1_data[1][j * 2 + 0][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer2_data[0][j * 2 + 1][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer2_data[1][j * 2 + 0][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        overlap_data[0][j * 2 + 1][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        overlap_data[1][j * 2 + 0][k] = 0XFF;
                }
            }
            else {
                if( random() & 1 ) {
                    for( int k = 0; k < 3; k++ )
                        layer1_data[0][j * 2 + 1][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer1_data[1][j * 2 + 0][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer2_data[0][j * 2 + 0][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer2_data[1][j * 2 + 1][k] = 0XFF;
                }
                else {
                    for( int k = 0; k < 3; k++ )
                        layer1_data[0][j * 2 + 0][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer1_data[1][j * 2 + 1][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer2_data[0][j * 2 + 1][k] = 0XFF;
                    for( int k = 0; k < 3; k++ )
                        layer2_data[1][j * 2 + 0][k] = 0XFF;
                }
            }
            srandom( random() );
        }
        fwrite( &layer1_data, sizeof(layer1_data), 1, layer1 );
        fwrite( &layer2_data, sizeof(layer2_data), 1, layer2 );
        fwrite( &overlap_data, sizeof(overlap_data), 1, overlap );
    }

    fclose( image );
    fclose( layer1 );
    fclose( layer2 );
    fclose( overlap );
}