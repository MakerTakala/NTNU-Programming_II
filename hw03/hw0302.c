#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_STRING_SIZE 4097
#define BASE_MILLISECOND 150
#define START_DELAY 500
#define ADD_DELAY 100

typedef struct {
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
    uint32_t millisecond;
}Time;

void string_input_template( char input[] );
void time_add( Time *time );
bool compare( Time *cur_time, Time *cmp_time );

int main() {
    Time cur_time = {0, 0, 0, 0};
    Time start_time = {0, 0, 0, 0};
    Time end_time = {0, 0, 0, 0};

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
    cur_time.millisecond += START_DELAY;
    while( !feof( srt_file ) ) {
        char number[16] = {0};
        fgets( number, 16, srt_file );
        char time_input[128] = {0};
        fgets( time_input, 128, srt_file );
        sscanf( time_input, "%u:%u:%u,%u --> %u:%u:%u,%u\n", \
        &start_time.hour, &start_time.minute, &start_time.second, &start_time.millisecond, \
        &end_time.hour,   &end_time.minute,   &end_time.second,   &end_time.millisecond );
        
        while( compare( &cur_time, &start_time ) ) {
            time_add( &cur_time );
            usleep( BASE_MILLISECOND * ( 1.0 / speed ) );
        }
        while( true ) {
            char line[MAX_STRING_SIZE] = {0};
            fgets( line, MAX_STRING_SIZE, srt_file );
            if( line[0] == '\n' ) {
                break;
            }
            printf("%s", line);
        }
        while( compare( &cur_time, &end_time ) ) {
            time_add( &cur_time );
            usleep( BASE_MILLISECOND * ( 1.0 / speed ) );
        }
        system( "clear" );
        cur_time.millisecond += ADD_DELAY * speed;
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

void time_add( Time *cur_time ) {
    cur_time->millisecond += 1;
    if( cur_time->millisecond >= 1000 ) {
        cur_time->millisecond -= 1000;
        cur_time->second += 1;
    }
    if( cur_time->second >= 60 ) {
        cur_time->second -= 60;
        cur_time->minute += 1;
    }
    if( cur_time->minute >= 60 ) {
        cur_time->minute -= 60;
        cur_time->hour += 1;
    }
}

bool compare( Time *cur_time, Time *cmp_time ) {
    if( cur_time->hour == cmp_time->hour ) {
        if( cur_time->minute == cmp_time->minute ) {
            if( cur_time->second == cmp_time->second ) {
                return cur_time->millisecond <= cmp_time->millisecond;
            }
            else {
                return cur_time->second < cmp_time->second;
            }
        }
        else {
            return cur_time->minute < cmp_time->minute;
        }
    }
    else {
        return cur_time->hour < cmp_time->hour;
    }
}