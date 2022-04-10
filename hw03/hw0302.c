#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_STRING_SIZE 4097

typedef struct {
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
    uint32_t millisecond;
}Time;

typedef struct {
    Time start;
    Time end;
    char line[4096];
}Data;

void string_input_template( char input[] );
uint64_t diff( Time a, Time b );

int main() {
    Time cur_time = {0, 0, 0, 0};

    FILE *srt_file = NULL;
    char srt_file_name[MAX_STRING_SIZE] = {0};
    printf( "Open a srt file: " );
    string_input_template( srt_file_name );
    if( ( srt_file  = fopen( srt_file_name, "r" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }

    double speed = 0;
    char buffer[MAX_STRING_SIZE] = {0};
    printf( "Speed (0.5-2): " );
    string_input_template( buffer );
    char *end = NULL;
    speed = strtod( buffer, &end );
    if( *end != 0 ) {
        printf( "Wrong input!!\n" );
        exit(0);
    }
    if( speed < 0.5 || 2.0 < speed ) {
        printf( "Wrong speed!!\n" );
        exit(0);
    }

    system( "clear" );

    Data data[1028];
    uint32_t counter = 0;
    char number[16] = {0};
    char time_input[128] = {0};
    while( fgets( number, 16, srt_file ) ) {

        fgets( time_input, 128, srt_file );
        sscanf( time_input, "%u:%u:%u,%u --> %u:%u:%u,%u\n",
        &(data[counter].start.hour), &(data[counter].start.minute), &(data[counter].start.second), &(data[counter].start.millisecond),
        &(data[counter].end.hour),   &(data[counter].end.minute),   &(data[counter].end.second),   &(data[counter].end.millisecond) ); 

        while( true ) {
            char line[MAX_STRING_SIZE] = {0};
            fgets( line, MAX_STRING_SIZE, srt_file );
            if( line[0] == '\n' ) {
                break;
            }
            strcat( data[counter].line, line );
        }
        counter++;
    }
    fclose( srt_file );
    uint64_t duration = 0;
    for( int i = 0; i < counter; i++ ) {
        
        duration = diff( cur_time, data[i].start );
        usleep( ( (double)duration * 1000 ) / speed );
        printf( "%s" ,data[i].line );
        duration = diff( data[i].start, data[i].end );
        usleep( ( (double)duration * 1000 ) / speed );
        cur_time = data[i].end;
        system( "clear" );
    }

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

uint64_t diff( Time a, Time b ) {
    uint64_t a_t, b_t;
    a_t = ( ( a.hour * 60 + a.minute ) * 60 + a.second ) * 1000 + a.millisecond;
    b_t = ( ( b.hour * 60 + b.minute ) * 60 + b.second ) * 1000 + b.millisecond;
    return b_t - a_t;
}