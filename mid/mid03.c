#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "mid_helper.h"

int main() {
    FILE *in_file = open_file( "Please enter the file name: ", "r", 4096);
    FILE *out_file = NULL;
    if( ( out_file = fopen( "output.bmp", "w" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    double angle = ask_angle();
    angle = angle / 180 * M_PI;
    
    BmpHeader header;
    fread( &header, 54, 1, in_file );
    if( strncmp( header.bm, "BM", 2 ) || header.bpp != 24 ) {
        printf("Wrong file format!\n");
        exit(0);
    }
    
    uint32_t original_width = header.width, original_height = header.height;
    uint32_t new_width = 0, new_height = 0;
    count_width_height( original_width, original_height, angle, &new_width, &new_height );
    header.width = new_width;
    header.height = new_height;
    header.size = 54 + ( 24 * header.width + 31 ) / 32 * 4;
    header.bitmap_size = ( 24 * header.width + 31 ) / 32 * 4;
    fwrite( &header, 54, 1, out_file );

    printf("!!!width :%u height: %u\n", new_width, new_height);

    uint8_t ori_pixel[3 * original_width * original_height];
    uint64_t pixel_size = 3 * new_width * new_height + 300;
    uint8_t pixels[pixel_size];
    memset( pixels, 0xFF, pixel_size );
    printf("SEPT\n");
    fread( &ori_pixel, sizeof(ori_pixel), 1, in_file );
    

    int32_t in_center_x = ( original_width - 1 ) / 2, in_center_y = ( original_height - 1 ) / 2;
    int32_t out_center_x = ( new_width - 1 ) / 2, out_center_y = ( new_height - 1 ) / 2;
    printf("%d, %d, %d, %d\n", in_center_x, in_center_y, out_center_x, out_center_y);

    for (int x = 0; x < original_width; x++) {
        for (int y = 0; y < original_height; y++) {
            long double a = x - in_center_x;
            long double b = y - in_center_y;

            int32_t nx = (int)(x * cos(angle) - y * sin(angle) + out_center_x);
            int32_t ny = (int)(x * sin(angle) + y * cos(angle) + out_center_y);

            printf("%d %d\n", nx, ny);

            if(  0 <=  nx && nx < new_width &&  0 <= ny && ny < new_height ) {
                pixels[ 3 * (y * new_height + x ) + 0 ] = ori_pixel[ 3 * ( ny * original_height + nx ) + 0 ];
                pixels[ 3 * (y * new_height + x ) + 1 ] = ori_pixel[ 3 * ( ny * original_height + nx ) + 1 ];
                pixels[ 3 * (y * new_height + x ) + 2 ] = ori_pixel[ 3 * ( ny * original_height + nx ) + 2 ];
            }
        }
    }

    fwrite( &pixels, sizeof(pixels), 1, out_file );

    fclose(in_file);
    fclose(out_file);

    return 0;
}