#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>

#include "file_processing.h"

int64_t width = 1024, height = 768;
char output_file_name[4098] = "output.bmp";
void read_option( int argc, char *argv[] ) {
    int l = 0;
    struct option long_options[] = {
        { "help", 0, NULL, 'l' }, 
        { 0, 0, 0, 0 }
    };
    char c = 0;
    while( ( c = getopt_long( argc, argv, "w:h:o:l", long_options, NULL ) ) != -1 ) {
        switch ( c ) {
            case 'w':
                for(int i = 0; i < strlen(optarg); i++)
                    if( !isdigit(optarg[i]) )
                        exit_program( "Wrong Option arg!" );
                width = strtoll( optarg, NULL, 10 );
                if( width < 0 || 2000 < width )
                    exit_program( "Wrong Option arg!" );
                break;
            case 'h':
                for(int i = 0; i < strlen(optarg); i++)
                    if( !isdigit(optarg[i]) )
                        exit_program( "Wrong Option arg!" );
                height = strtoll( optarg, NULL, 10 );
                if( height < 0 || 2000 < height )
                    exit_program( "Wrong Option arg!" );
                break;
            case 'o':
                strncpy( output_file_name, optarg, 4096 );
                break;
            case 'l':
                printf( "Usage:\n" );
                printf( "\t./fin01 [options]\n" );
                printf( "\t-w: the width of the output figure. (Default: 1024)\n" );
                printf( "\t-h: the height of the output figure. (Default: 768)\n" );
                printf( "\t-o: the output file name. (Default: output.bmp)\n" );
                printf( "--help: this message\n" );
                exit(0);
                break;
        }
    }
    return ;
}

void read_input( char* input, int64_t data[3] ) {
    int n = strlen(input);
    for( int i = 0; i < n; i++ ) {
        if( !isdigit(input[i]) && input[i] != ',' ) 
            exit_program( "Wrong Input" );
        if( input[i] == ',' && ( i == 0 || !isdigit(input[i + 1]) ) )
            exit_program( "Wrong Input" );
    }
    sscanf( input, "%ld,%ld,%ld", &data[2], &data[1], &data[0] );
    for( int i = 0; i < 3; i++ )
        if( data[i] < 0 || 255 < data[i] ) 
            exit_program( "Wrong Input" );
    return;
}

int main( int argc, char *argv[] ) {
    read_option( argc, argv );
    int64_t tl_data[3] = {0}, tr_data[3] = {0}, bl_data[3] = {0}, br_data[3] = {0};
    char *read_tl = read_string_input( "Please enter (R,G,B) in the top left pixel:" );
    read_input( read_tl, tl_data );
    char *read_tr = read_string_input( "Please enter (R,G,B) in the top right pixel:" );
    read_input( read_tr, tr_data );
    char *read_bl = read_string_input( "Please enter (R,G,B) in the bottom left pixel:" );
    read_input( read_bl, bl_data );
    char *read_br = read_string_input( "Please enter (R,G,B) in the bottom right pixel:" );
    read_input( read_br, br_data );
    
    FILE *file = open_file( output_file_name, "w" );
    
    sBmpHeader *header = BMP_header_init( width, height );

    fwrite( header, sizeof(sBmpHeader), 1, file );
    uint8_t color_data[height][width][3];
    for( int i = 0; i < height; i++ ) {
        for( int k = 0; k < 3; k++ ) {
            color_data[i][0][k] = (uint8_t)( (double)bl_data[k] + ( (double)(tl_data[k] - bl_data[k]) / (double)height ) * (double)i );
            color_data[i][width - 1][k] = (uint8_t)( (double)br_data[k] + ( (double)(tr_data[k] - br_data[k]) / (double)height ) * (double)i );
        }
    }

    for( int i = 0; i < height; i++ ) {
        for( int j = 1; j < width; j++ ) {
            for( int k = 0; k < 3; k++ ) {
                color_data[i][j][k] = (uint8_t)( (double)color_data[i][0][k] + ( (double)(color_data[i][width - 1][k] - color_data[i][0][k]) / (double)width ) * (double)j );
            }
        }
    }
    fwrite( &color_data, sizeof(uint8_t) ,width * height * 3, file );

    printf("Done\n");
    fclose( file );
    return 0;
}