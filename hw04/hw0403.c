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

int main( int argc, char *argv[] ) {

    char file_name[4096] = {0};
    strncpy( file_name, argv[argc - 1], 4096 );
    FILE *file = open_file( file_name, "r" );
    printf("file:%s\n", file_name);

    bool linenum = false, color = false, language = false;

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





    return 0;
}