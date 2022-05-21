#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#include "file_processing.h"

bool seconds = false, count = false;
int DataSizeType = 1, EveryNSecond = 0, CountNTimes = 1;

void read_option( int argc, char *argv[] ) {
    int l = 0;
    struct option long_options[] = {
        { "byte",    0, NULL, 'b' }, 
        { "kilo",    0, &l,    1 },    
        { "mega",    0, &l,    2 }, 
        { "seconds", 1, NULL,  's' }, 
        { "count",   1, NULL,  'c' }, 
        { "help",    0, &l,   3 }, 
        { 0, 0, 0, 0 }
    };
    char c = 0;
    while( ( c = getopt_long( argc, argv, "bs:c:", long_options, NULL ) ) != -1 ) {
        switch ( c ) {
            case 'b':
                DataSizeType = 0;
                break;
            case 's':
                seconds = true;
                for( int i = 0; i < strlen(optarg); i++ ) {
                    if( !isdigit( optarg[i] ) ) {
                        printf( "Wrong option!\n" );
                        exit(0);
                    }
                }
                EveryNSecond = strtol(optarg, NULL, 10);
                if( EveryNSecond == 0 ) {
                    printf( "Wrong option!\n" );
                    exit(0);
                }
                break;
            case 'c':
                count = true;
                for( int i = 0; i < strlen(optarg); i++ ) {
                    if( !isdigit( optarg[i] ) ) {
                        printf( "Wrong option!\n" );
                    }
                }
                CountNTimes = strtol(optarg, NULL, 10);
                break;
            case 0:
                switch ( l ) {
                    case 1:
                        DataSizeType = 1;
                        break;
                    case 2:
                        DataSizeType = 2;
                        break;
                    case 3:
                        printf( "Usage:\n" );
                        printf( "\thw0501 [options]\n" );
                        printf( " Options:\n" );
                        printf( " -b, --bytes           show output in bytes\n" );
                        printf( "     --kilo            show output in kilobytes (default)\n" );
                        printf( "     --mega            show output in megabytes\n" );
                        printf( " -s N, --seconds N repeat printing every N seconds\n" );
                        printf( " -c N, --count N repeat printing N times , then exit\n" );
                        printf( "     --help display this help and exit\n" );
                        exit(0);
                        break;
                }
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
    uint64_t AvailableSize = 0;
    FILE *file = open_file( "/proc/meminfo", "r" );
    for( int i = 0 ; i < CountNTimes; i = (seconds && !count) ? i : i + 1 ) {
        for( int i = 0;i < 3; i++ ) {
            fscanf( file, "%*[^0-9]%lu kB\n", &AvailableSize );
        }
        printf( "Available: " );
        switch ( DataSizeType ) {
            case 0:
                printf( "%lu BYTES\n", AvailableSize * 1024 );
                break;
            case 1:
                printf( "%lu KB\n", AvailableSize );
                break;
            case 2:
                printf( "%lu MB\n", AvailableSize / 1024 );
                break;
        }
        if( i != CountNTimes - 1 || (seconds && !count) ) {
            sleep( EveryNSecond );
            rewind( file );
        }
    }

    fclose( file );
    return 0;
}