#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/stat.h>

#include "file_processing.h"

void exit_program( char msg[] ) {
    printf( "%s\n", msg );
    exit(0);
}

bool wri = false, ext = false, bit = false;
int64_t N = 1;
void read_option( int argc, char *argv[] ) {
    int l = 0;
    struct option long_options[] = {
        { "write",   0, NULL, 'w' }, 
        { "extract", 0, NULL, 'e' },    
        { "bits=",    1, NULL, 'b' }, 
        { 0, 0, 0, 0 }
    };
    char c = 0;
    while( ( c = getopt_long( argc, argv, "web:", long_options, NULL ) ) != -1 ) {
        switch ( c ) {
            case 'w':
                wri = true;
                break;
            case 'e':
                ext = true;
                break;
            case 'b':
                bit = true;
                for(int i = 0; i < strlen(optarg); i++)
                    if( !isdigit(optarg[i]) )
                        exit_program( "Wrong Option arg!" );
                N = strtoll( optarg, NULL, 10 );
                if( N < 1 || 8 < N ) 
                    exit_program( "Wrong Option arg!" );
                break;
        }
    }
    return ;
}

int main( int argc, char *argv[] ) {
    read_option( argc, argv );
    if( !bit )
        exit_program( "Need bits option!" );
    if( !( wri ^ ext ) ) 
        exit_program( "Only accept either write or extract!" );
    if( argc != 6 ) 
        exit_program( "Wrong Option!" );

    FILE *picture = open_file( argv[argc - 2], "r+" );
    FILE *secret = open_file( argv[argc - 1], "r+" );
    
    sBmpHeader header;
    fread( &header, sizeof( sBmpHeader ), 1, picture );
    if( strncmp( header.bm, "BM", 2 ) )
        exit_program( "Only allow bmp file!" );
    

    if( wri ) {
        struct stat st;
        stat( argv[argc - 1], &st );
        if( st.st_size * 8 > header.width * header.height * N * 3 ) 
            exit_program( "bmp file don't have enough size!" );

        header.reserve = (uint32_t)st.st_size;
        printf( "%u\n", (uint32_t)st.st_size );
        printf( "%u\n", header.reserve );
        fseek( picture, 0, SEEK_SET );
        fwrite( &header, sizeof( sBmpHeader ), 1, picture );
        
        uint8_t times = 0;
        for( int i = 0; i < st.st_size; i++ ) {
            uint8_t secret_data;
            uint8_t picture_data;
            fread( &secret_data, sizeof( uint8_t ), 1, secret );
            for( int j = 7; j >= 0; j-- ) {
                uint8_t b = secret_data & ( (uint8_t)1 << j ) ? 1: 0;
                if( times == 0 ) {
                    fread( &picture_data, sizeof( uint8_t ), 1, picture );
                }
                picture_data = (picture_data & (~((uint8_t)1<<times))) + (b << times);
                times = (times + 1) % N;
            }
            fseek( picture, (-1) * sizeof( uint8_t ), SEEK_CUR );
            fwrite( &picture_data, sizeof( uint8_t ), 1, picture );
        }
    }
    if( ext ) {
        printf( "reverse:%u\n", header.reserve );
        uint8_t times = 0;
        for( int i = 0 ; i < header.reserve; i++ ) {
            uint8_t secret_data = 0;
            uint8_t picture_data = 0;
            for( int j = 7; j >= 0; j-- ) {
                uint8_t b = picture_data & ( (uint8_t)1 << times ) ? 1: 0;
                if( times == 0 ) {
                    fread( &picture_data, sizeof( uint8_t ), 1, picture );
                }
                secret_data = secret_data + (b << j);
                times = (times + 1) % N;
            }
            printf( "%c", secret_data );
            fwrite( &secret_data, sizeof( uint8_t ), 1, secret );
        }
    }
    

    fclose( picture );
    fclose( secret );

    return 0;
}