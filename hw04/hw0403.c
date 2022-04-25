#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "file_processing.h"

struct option long_options[] = {
    { "linenum", 0, NULL, 'n' }, 
    { "color", 0, NULL, 'c' }, 
    { "language", 2, NULL, 'l' }, 
    { 0, 0, 0, 0 },
};

bool linenum = false, color = false, language = false;

void read_option( int argc, char *argv[] ) {
    char c = 0;
    while( ( c = getopt_long( argc, argv, "ncl:", long_options, NULL ) ) != -1 ) {
        switch ( c ) {
            case 'n':
                printf("n");
                linenum = true;
                break;
            case 'c':
                printf("c");
                color = true;
                break;
            case 'l':
                printf("l");
                language = true;
                printf("%s", optarg);
                break;
            
            case '?':
                exit(0);
                break;
        }
    }
    return ;
}

int main( int argc, char *argv[] ) {

    FILE *file = open_file( argv[argc - 1], "r" );
    read_option( argc, argv );
    
    





    return 0;
}