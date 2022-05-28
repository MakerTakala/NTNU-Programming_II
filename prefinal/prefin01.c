#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "file_processing.h"

void exit_program( char msg[] ) {
    printf( "%s\n", msg );
    exit(0);
}

void read_input( char* input, int64_t data[3] ) {
    int n = strlen(input);
    for( int i = 0, count = 0; i < n; i++ ) {
        if( !isdigit(input[i]) && input[i] != ',' ) 
            exit_program( "Wrong Input" );
        if( input[i] == ',' && ( i == 0 || !isdigit(input[i + 1]) ) ) 
            exit_program( "Wrong Input" );
        if( count > 2 ) 
            exit_program( "Wrong Input" );
    }
    sscanf( input, "%ld,%ld,%ld", &data[2], &data[1], &data[0] );
    for( int i = 0; i < 3; i++ )
        if( data[i] < 0 || 255 < data[i] ) 
            exit_program( "Wrong Input" );
    return;
}

int main() {
    char *file_name = read_string_input( "Please enter the file:" );

    char *read_tl = read_string_input( "Please enter (R,G,B) in the top left pixel:" );
    char *read_tr = read_string_input( "Please enter (R,G,B) in the top right pixel:" );
    char *read_bl = read_string_input( "Please enter (R,G,B) in the bottom left pixel:" );
    char *read_br = read_string_input( "Please enter (R,G,B) in the bottom right pixel:" );

    int64_t tl_data[3] = {0}, tr_data[3] = {0}, bl_data[3] = {0}, br_data[3] = {0};
    read_input( read_tl, tl_data );
    read_input( read_tr, tr_data );
    read_input( read_bl, bl_data );
    read_input( read_br, br_data );
    
    FILE *file = open_file( file_name, "w" );
    
    sBmpHeader *header = BMP_header_init();
    fwrite( header, sizeof(sBmpHeader), 1, file );
    uint8_t color_data[1024][768][3] = {{{0}}};
    for( int i = 0; i < 1024; i++ ) {
        for( int k = 0; k < 3; k++ ) {
            color_data[i][0][k] = (uint8_t)( (double)bl_data[k] + ( (double)(tl_data[k] - bl_data[k]) / (double)1024 ) * (double)i );
            color_data[i][767][k] = (uint8_t)( (double)br_data[k] + ( (double)(tr_data[k] - br_data[k]) / (double)1024 ) * (double)i );
        }
    }

    for( int i = 0; i < 1024; i++ ) {
        for( int j = 1; j < 767; j++ ) {
            for( int k = 0; k < 3; k++ ) {
                color_data[i][j][k] = (uint8_t)( (double)color_data[i][0][k] + ( (double)(color_data[i][767][k] - color_data[i][0][k]) / (double)768 ) * (double)j );
            }
        }
    }
    fwrite( &color_data, sizeof(uint8_t) ,1024 * 768 * 3, file );

    printf("Done\n");
    fclose( file );
    return 0;
}