#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#include "file_processing.h"

bool encode = false, decode = false, output = false;
char processing_file_name[4097] = {0}, output_file_name[4097] = {0};

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
    FILE *output_file = open_file( processing_file_name, "w" );

    





    
    fclose( processing_file );
    fclose( output_file );
    return 0;
}