#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "keyword.h"

#define COLOR_RED "\33[91m"
#define COLOR_NONE "\33[0m"

struct option long_options[] = {
    { "linenum", 0, NULL, 'n' }, 
    { "color", 0, NULL, 'c' }, 
    { "language", 1, NULL, 'l' }, 
    { 0, 0, 0, 0 }
};

bool linenum = false, color = false, language = false;
char language_name[128] = {0};

void read_option( int argc, char *argv[] ) {
    char c = 0;
    while( ( c = getopt_long( argc, argv, "ncl:", long_options, NULL ) ) != -1 ) {
        switch ( c ) {
            case 'n':
                linenum = true;
                break;
            case 'c':
                color = true;
                break;
            case 'l':
                language = true;
                strcpy( language_name, optarg );
                break;
            case '?':
                printf( "Wrong option!\n" );
                exit(0);
                break;
        }
    }
    return ;
}

uint64_t util_getFdSize( int fd )
{
    struct stat statbuf;
    
    if( fstat( fd, &statbuf ) < 0 )
    {
        close( fd );
        return -1;
    }
    
    return statbuf.st_size;
}

bool compare( uint16_t type, uint32_t keyword_len, char cur_word[] ) {
    for( int i = 0; i < keyword_len; i++ ) {
        if( !strcmp( key_word[type][i], cur_word ) ) {
            return true;
        }
    }
    return false;
}

int main( int argc, char *argv[] ) {
    language_name[0] = 'C';

    int32_t fd = open( argv[argc - 1], O_RDONLY );
    if( fd == -1 ) {
        printf("File can't be opned.\n");
        exit(0);
    }
    read_option( argc, argv );
    
    uint64_t file_size = util_getFdSize( fd );
    char *p_file = mmap( 0, file_size, PROT_READ, MAP_SHARED, fd, 0 );



    char support_laguage[5][20] = { "C", "CPP", "JS", "Java", "Rust" };
    uint32_t language_len[5] = { 2, 4, 3, 5, 5 };
    uint32_t language_keyword_len[5] = { 44, 84, 38, 51, 53 };
    uint32_t type = 0;
    for( int i = 0; i <= 5; i++ ) {
        if( i == 5 ) {
            printf("NOT SUPPORT THIS LANGUAGE.\n");
            exit(0);
        }
        if( !strncmp( language_name, support_laguage[i], language_len[i] ) ) {
            type = i;
            break;
        }
    }

    uint64_t offset = 0;
    uint64_t line_num = 1;
    bool one_line_annotation = false;
    bool many_line_annotation = false;
    bool quotation = false;
    if( linenum ) printf( "%4lu ", line_num++ );

    while( offset < file_size ) {
        char cur_word[4096] = {0};
        
        int64_t word_size = sscanf( p_file + offset, "%[^] \n\t(){}[;,\"\'=-*/%%&|^~!+<>]", cur_word );
        if( word_size == 0 ) {
            printf("%c", *(p_file + offset) );
            if( *(p_file + offset) == '\n' ) {
                printf( "%4lu ", line_num++ );
                one_line_annotation = false;
            }
            if( !strncmp( p_file + offset, "//", 2 ) && !quotation  ) {
                one_line_annotation = true;
            }
            if( !strncmp( p_file + offset, "/*", 2 ) && !quotation ) {
                many_line_annotation = true;
            }
            if( !strncmp( p_file + offset, "*/", 2 ) ) {
                many_line_annotation = false;
            }
            if( *(p_file + offset) == '\"' && *(p_file + offset - 1) != '\\' && !many_line_annotation && !one_line_annotation ) {
                quotation = quotation ^ 1;
            }
            offset++;
            continue;
        }
        if( compare( type, language_keyword_len[type], cur_word ) && color && !one_line_annotation && !many_line_annotation && !quotation ) {
            printf( "%s%s%s", COLOR_RED, cur_word, COLOR_NONE );
        }
        else {
            printf( "%s", cur_word );
        }
        
        offset += strlen(cur_word);
    }
    munmap( p_file, file_size );
    return 0;
}