#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "mid_helper.h"

int main() {
    FILE *in_file = open_file( "Please enter the file name: ", "r", 4096);
    FILE *out_file = NULL;
    if( ( out_file = fopen( "output.bmp", "w" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    double angle = ask_angle();
    
    BmpHeader in_header, out_header;
    fread( &in_header, 54, 1, in_file );
    if( strncmp( in_header.bm, "BM", 2 ) || in_header.bpp != 24 ) {
        printf("Wrong file format!\n");
        exit(0);
    }
    out_header = in_header;
    
    uint64_t width = in_header.width, height = in_header.height;


    return 0;
}