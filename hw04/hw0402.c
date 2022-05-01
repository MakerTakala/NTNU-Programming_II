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
        
        for( int i = 0, j = 0; i < strlen(cur_member_name); i++ ) {
            if( isalnum( cur_member_name[i] ) ) {
                member_name[member_index][j++] = tolower(cur_member_name[i]);
            } 
        }    
        member_size[member_index] = ( strlen(cur_member_name) + 1 ) / 2;
        printf("%s: %d\n", member_name[member_index], member_size[member_index]);
        
        member_index++;
    }
    















    /*
    int32_t h_file = open( strcat( output_name, ".c"), O_WRONLY );
    if( h_file == -1 ) {
        printf("File can't be opned.\n");
        exit(0);
    }
    char *h_p_file = mmap( 0, 100000, PROT_WRITE, MAP_SHARED, h_file, 0 );

    int32_t c_file = open( strcat( output_name, ".h"), O_WRONLY );
    if( c_file == -1 ) {
        printf("File can't be opned.\n");
        exit(0);
    }
    char *c_p_file = mmap( 0, 100000, PROT_WRITE, MAP_SHARED, c_file, 0 );
    */
    


    return 0;
}