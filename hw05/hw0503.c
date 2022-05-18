#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>

#include "file_processing.h"

char base64[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

bool encode = false, decode = false, output = false;
char processing_file_name[4097] = {0}, output_file_name[4097] = {0};

uint8_t searching( char base ) {
    if( base == '=' ) {
        return 64;
    }
    for( int i = 0; i < 64; i++ ) {
        if( base == base64[i] ) {
            return i;
        }
    }
    printf( "Wrong decoding file!\n" );
    exit(0);
    return 0;
}

void read_option( int argc, char *argv[] ) {
    int l = 0;
    struct option long_options[] = {
        { "enc",    1, NULL, 'e' }, 
        { "dec",    1, NULL, 'd' },    
        { "output", 1, NULL, 'o' }, 
        { 0, 0, 0, 0 }
    };
    char c = 0;
    while( ( c = getopt_long( argc, argv, "e:d:o:", long_options, NULL ) ) != -1 ) {
        switch ( c ) {
            case 'e':
                encode = true;
                strcpy( processing_file_name, optarg );
                break;
            case 'd':
                decode = true;
                strcpy( processing_file_name, optarg );
                break;
            case 'o':
                output = true;
                strcpy( output_file_name, optarg );
                break;
            case '?':
                printf( "Wrong option!\n" );
                exit(0);
                break;
        }
    }
    return ;
}

int main( int argc, char *argv[] ) {
    read_option( argc, argv );
    FILE *processing_file = open_file( processing_file_name, "r" );
    FILE *output_file = open_file( output_file_name, "w" );
    if( encode && decode ) {
        printf( "Only accept encode or decode option!\n" );
        exit(0);
    }
    if( !encode && !decode ) {
        printf( "Need encode or decode option!\n" );
        exit(0);
    }
    if( !output ) {
        printf( "Need output option!\n" );
        exit(0);
    }

    struct stat st;
    stat( processing_file_name, &st );
    if( encode ) {  
        uint8_t input_data[3] = {0};
        uint8_t output_data[4] = {0};
        for( int i = 0; i < st.st_size / 3; i++ ) {
            memset( input_data, 0, 3 );
            memset( output_data, 0, 4 );
            fread( &input_data, sizeof(uint8_t), 3, processing_file );
            output_data[0] += ( input_data[0] & 0b11111100 ) >> 2;
            output_data[1] += ( input_data[0] & 0b00000011 ) << 4;
            output_data[1] += ( input_data[1] & 0b11110000 ) >> 4;
            output_data[2] += ( input_data[1] & 0b00001111 ) << 2;
            output_data[2] += ( input_data[2] & 0b11000000 ) >> 6;
            output_data[3] += ( input_data[2] & 0b00111111 ) << 0;
            for( int j = 0; j < 4; j++ ) {
                output_data[j] = base64[output_data[j]];
            }
            fwrite( &output_data, sizeof(char), 4, output_file );
        }
        memset( input_data, 0, 3 );
        memset( output_data, 0, 4 );
        if( st.st_size % 3 == 1 ) {
            fread( &input_data, sizeof(uint8_t), 1, processing_file );
            output_data[0] += ( input_data[0] & 0b11111100 ) >> 2;
            output_data[1] += ( input_data[0] & 0b00000011 ) << 4;
            output_data[0] = base64[output_data[0]];
            output_data[1] = base64[output_data[1]];
            output_data[2] = '=';
            output_data[3] = '=';
        }
        if( st.st_size % 3 == 2 ) {
            fread( &input_data, sizeof(uint8_t), 2, processing_file );
            output_data[0] += ( input_data[0] & 0b11111100 ) >> 2;
            output_data[1] += ( input_data[0] & 0b00000011 ) << 4;
            output_data[1] += ( input_data[1] & 0b11110000 ) >> 4;
            output_data[2] += ( input_data[1] & 0b00001111 ) << 2;
            output_data[0] = base64[output_data[0]];
            output_data[1] = base64[output_data[1]];
            output_data[2] = base64[output_data[2]];
            output_data[3] = '=';
        }
        fwrite( &output_data, sizeof(char), 4, output_file );
    }

    if( decode ) {
        uint8_t input_data[4] = {0};
        uint8_t output_data[3] = {0};
        for( int i = 0; i < st.st_size / 4; i++ ) {
            memset( input_data, 0, 4 );
            memset( output_data, 0, 3 );
            fread( &input_data, sizeof(uint8_t), 4, processing_file );
            for( int j = 0; j < 4; j++ ) {
                input_data[j] = searching( input_data[j] );
            }

            if( input_data[3] != 64 ) {
                output_data[0] += (input_data[0] & 0b00111111) << 2;
                output_data[0] += (input_data[1] & 0b00110000) >> 4;
                output_data[1] += (input_data[1] & 0b00001111) << 4;
                output_data[1] += (input_data[2] & 0b00111100) >> 2;
                output_data[2] += (input_data[2] & 0b00000011) << 6;
                output_data[2] += (input_data[3] & 0b00111111) << 0;
                fwrite( &output_data, sizeof(uint8_t), 3, output_file );
            }
            else if( input_data[2] != 64 ) {
                output_data[0] += (input_data[0] & 0b00111111) << 2;
                output_data[0] += (input_data[1] & 0b00110000) >> 4;
                output_data[1] += (input_data[1] & 0b00001111) << 4;
                output_data[1] += (input_data[2] & 0b00111100) >> 2;
                fwrite( &output_data, sizeof(uint8_t), 2, output_file );
            }
            else {
                output_data[0] += (input_data[0] & 0b00111111) << 2;
                output_data[0] += (input_data[1] & 0b00110000) >> 4;
                fwrite( &output_data, sizeof(uint8_t), 1, output_file );
            }
        }
    }

    fclose( processing_file );
    fclose( output_file );
    return 0;
}