#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "print.h"


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

uint64_t file_size;
uint16_t *p_file;

void close_file() {
    munmap( p_file, file_size );
    return;
}

int main( int argc, char *argv[] ) {

    int32_t file = open( "/home/takala/game/F101.GNX", O_RDWR );
    if( file == -1 ) {
        printf("File can't be opned.\n" );
        perror("error");
        exit(0);
    }
    file_size = util_getFdSize( file );
    p_file = mmap( 0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0 );
    atexit( close_file );
    
    while( 1 ) {
        print_outline();
        
    }
    
    return 0;
}