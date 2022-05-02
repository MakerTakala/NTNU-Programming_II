#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "file_processing.h"


bool if_file = false, if_struct_name = false, if_output_name = false;
char file_name[256] = {0}, struct_name[256] = {0}, output_name[256] = {0};

void read_option( int argc, char *argv[] ) {
    char c = 0;
    while( ( c = getopt( argc, argv, "i:n:p:" ) ) != -1 ) {
        switch ( c ) {
            case 'i':
                if_file = true;
                strcpy( file_name, optarg );
                break;
            case 'n':
                if_struct_name = true;
                memset( struct_name, 0, 256 );
                strcpy( struct_name, optarg );
                break;
            case 'p':
                if_output_name = true;
                memset( output_name, 0, 256 );
                strcpy( output_name, optarg );
                break;
            case '?':
                printf( "Wrong option!\n" );
                exit(0);
                break;
        }
    }
    if( !if_file ) {
        printf("Need text file name which contains the structure!\n");
        exit(0);
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


int main( int argc, char *argv[] ) {
    strcpy( struct_name, "Test" );
    strcpy( output_name, "test" );

    read_option( argc, argv );

    int32_t file = open( file_name, O_RDONLY );
    if( file == -1 ) {
        printf("File can't be opned.\n");
        exit(0);
    }
    uint64_t file_size = util_getFdSize( file );
    char *p_file = mmap( 0, file_size, PROT_READ, MAP_SHARED, file, 0 );
    uint64_t offset = 0;
    char buffer[256] = {0};
    sscanf( p_file, "%[^|]|" , buffer );
    offset += strlen( buffer ) + 1;

    char member_name[128][256] = {{0}};
    int32_t member_size[128] = {0};
    int32_t member_index = 0;
    while( offset < file_size ) {
        char cur_member_name[256] = {0};
        sscanf( p_file + offset, "%[^|\n]|", cur_member_name );
        if( strlen(cur_member_name) == 0 ) {
            sscanf( p_file + offset + 1, "%[^|]", cur_member_name );
            offset += strlen(cur_member_name) + 2;
            continue;
        }
        offset += strlen(cur_member_name) + 1;
        char tmp_cur_member_name[256] = {0};
        
        for( int i = 0, j = 0; i < strlen(cur_member_name); i++ ) {
            if( isalnum( cur_member_name[i] ) ) {
                tmp_cur_member_name[j++] = tolower(cur_member_name[i]);
            } 
        }
        if( index != 0 && !strcmp( member_name[member_index - 1], tmp_cur_member_name ) ) {
            member_size[member_index] += ( strlen(cur_member_name) + 1 ) / 2;
        }
        else {
            member_size[member_index] = ( strlen(cur_member_name) + 1 ) / 2;
            strcpy( member_name[member_index], tmp_cur_member_name );
            printf("%s: %d\n", member_name[member_index], member_size[member_index]);
            member_index++;
        }
    }

    char tmp_h_output_name[256];
    strcpy( tmp_h_output_name, output_name );
    FILE *p_h_file = open_file( strcat( tmp_h_output_name, ".h"), "w" );
    fprintf( p_h_file, "#pragma once\n\n#include <stdint.h>\n\ntypedef struct _s%s\n{\n", struct_name );
    for( int i = 0; i < member_index; i++ ) {
        if( member_size[i] != 8 && member_size[i] != 16 && member_size[i] != 32 && member_size[i] !=64 ) {
            if( member_size[i] % 8 == 0) fprintf( p_h_file, "\tuint8_t %s[%d];\n", member_name[i], (member_size[i] - 1) / 8 + 1 );
            else if( member_size[i] <= 8 ) fprintf( p_h_file, "\tuint8_t %s;\n", member_name[i] );
            else if( member_size[i] <= 16 ) fprintf( p_h_file, "\tuint16_t %s;\n", member_name[i] );
            else if( member_size[i] <= 32 ) fprintf( p_h_file, "\tuint32_t %s;\n", member_name[i] );
            else if( member_size[i] <= 64 ) fprintf( p_h_file, "\tuint64_t %s;\n", member_name[i] );
            else fprintf( p_h_file, "\tuint8_t %s[%d];\n", member_name[i], member_size[i] / 8 + 1 );
        }
        else {
            fprintf( p_h_file, "\tuint%d_t %s;\n", member_size[i], member_name[i] );
        }
    }
    fprintf( p_h_file, "}__attribute__((packed)) %s;\n\nIPH * iph_init( void );\nvoid iph_free( IPH * );\nint iph_encode( void *, const IPH * );\nint iph_decode( const void *, IPH * );", struct_name );
    fclose( p_h_file );

    char tmp_c_output_name[256];
    strcpy( tmp_c_output_name, output_name );
    FILE *p_c_file = open_file( strcat( tmp_c_output_name, ".c"), "w" );
    fprintf( p_c_file, "#include <stdint.h>\n#include <stdlib.h>\n#include \"%s.h\"\n\n", output_name );
    fprintf( p_c_file, "IPH * iph_init( void ){\n\treturn malloc( sizeof(%s) );\n}\n\n", struct_name );
    fprintf( p_c_file, "void iph_free( IPH * this){\n\tfree(this);\n\treturn;\n}\n\n" );

    fprintf( p_c_file, "int iph_encode( void *buffer, const %s *this ){\n", struct_name );
    fprintf( p_c_file, "\tif(!buffer||!this) {\n\t\treturn 0;\n\t}\n");
    uint64_t buffer_index = 0, struct_index = 0;
    for( int i = 0; i < member_index; i++ ) {
        for( int j = member_size[i]; j > 0; j -= 8 ) {
            for( int k = 0 ; k < ( j > 8 ? 8 : j ) ; k++ ) {
                if( buffer_index % 8 == 0 ) {
                    fprintf( p_c_file, "\t*((uint8_t*)buffer+%lu) = 0;\n", buffer_index / 8 );
                }
                fprintf( p_c_file, "\t*((uint8_t*)buffer+%lu) |= ((((uint8_t)1<<%d)&(*((uint8_t*)this + %lu)))&1)<<%lu;\n", buffer_index / 8, k, struct_index, 7 - buffer_index % 8 );
                buffer_index++;
            }
            struct_index++;
        }
    }
    fprintf( p_c_file, "\treturn 1;\n}\n\n");

    fprintf( p_c_file, "int iph_decode( const void *buffer, %s *this ){\n", struct_name );
    fprintf( p_c_file, "\tif(!buffer||!this) {\n\t\treturn 0;\n\t}\n");
    buffer_index = 0, struct_index = 0;
    for( int i = 0 ; i < member_index; i++ ) {
        for( int j = member_size[i]; j > 0; j -= 8 ) {
            for( int k = j > 7 ? 7 : j - 1 ; k >= 0; k-- ) {
                
            }
            struct_index++;
        }
    }
    fprintf( p_c_file, "\treturn 1;\n}\n\n");

    fclose( p_c_file );

    munmap( p_file, file_size );
    close( file );
    
    return 0;
}

