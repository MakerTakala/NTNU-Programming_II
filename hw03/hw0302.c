#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 4097

void string_input_template( char input[] );

typedef struct {
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
    uint32_t millisecond;
}Time;

int main() {
    Time cur_time = {0, 0, 0, 0};

    FILE *srt_file = NULL;
    char srt_file_name[MAX_STRING_SIZE] = {0};
    string_input_template( srt_file_name );
    if( ( srt_file  = fopen( srt_file_name, "r" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }

    while( !feof( srt_file ) ) {
        char number[16] = {0};
        fgets( number, 10, srt_file );
        Time start_time = {0, 0, 0, 0};
        Time end_time = {0, 0, 0, 0};
        char time_input[128] = {0};
        fgets( time_input, 128, srt_file );
        sscanf( time_input, "%u:%u:%u,%u --> %u:%u:%u,%u\n", \
        &start_time.hour, &start_time.minute, &start_time.second, &start_time.millisecond, \
        &end_time.hour,   &end_time.minute,   &end_time.second,   &end_time.millisecond );
        char line[256] = {0};
        fgets( line, 256, srt_file );



        system( "clear" );
    }

    fclose( srt_file );

    return 0;
}


void string_input_template( char input[] ) {
    if( fgets( input, MAX_STRING_SIZE, stdin ) == NULL ) {
        printf( "Error!\n" );
        exit(0);
    }
    if( input[ strlen( input ) - 1 ] == '\n' ) {
        input[ strlen( input ) - 1 ] = 0;
    }
    else {
        uint32_t c = 0;
        while( ( c = fgetc( stdin ) ) != '\n' && c != EOF ){}
    }
}