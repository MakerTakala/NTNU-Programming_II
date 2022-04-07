#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_VERSE_SIZE 4097
#define MAX_OUTPUT_LINE 32768

void string_to_lowercase( char* str) {
    while( *str != 0 ) {
        *str = tolower( *str );
        str++;
    }
    return;
}

int main(){

    char searching_string[MAX_VERSE_SIZE] = {0};
    printf( "Please enter the search target: " );
    if( fgets( searching_string, MAX_VERSE_SIZE, stdin ) == NULL ) {
        printf( "Wrong Input!\n" );
        exit(0);
    }
    if( searching_string[ strlen( searching_string ) - 1 ] == '\n' ) {
        searching_string[ strlen( searching_string ) - 1 ] = 0;
    }
    else {
        uint32_t c = 0;
        while( ( c = fgetc( stdin ) ) != '\n' && c != EOF ){}
    }
    if( *searching_string == 0 ) {
        printf("Wrong Input\n");
        exit(0);
    }
    string_to_lowercase( searching_string );

    FILE *bible = NULL;
    if( ( bible = fopen( "bible.txt", "r" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    
    typedef struct{
        char book_id[129];
        uint32_t chapter;
        uint32_t verse;
        char text[4097];
    }_line;

    char input[MAX_VERSE_SIZE] = {0};
    _line **output = calloc( sizeof( _line ), MAX_OUTPUT_LINE );

    uint32_t counter = 0;
    while( !feof( bible ) ) {
        fgets( input, MAX_VERSE_SIZE, bible );
        if( input[ strlen( input ) - 1 ] == '\n' ) {
            input[ strlen( input ) - 1 ] = 0;
        }
        else {
            uint32_t c = 0;
            while( ( c = fgetc( bible ) ) != '\n' && c != EOF ){}
        }
        _line *line = calloc( sizeof( _line ), 1 );
        char *book_id_start = strstr( input , "\"book_id\":\"" ) + 11;
        char *book_id_end = strchr( book_id_start, '\"' );
        strncpy( line->book_id, book_id_start, book_id_end - book_id_start );
        line->chapter = strtol( strstr( input, "\"chapter\":" ) + 10, NULL, 10 );
        line->verse = strtol( strstr( input, "\"verse\":" ) + 8, NULL, 10 );
        char *text_start = strstr( input , "\"text\":\"" ) + 8;
        char *text_end = strchr( text_start, '\"' );
        strncpy( line->text, text_start, text_end - text_start );
        if( strcasestr( line->text, searching_string ) != NULL ) {
            output[counter] = line;
            counter++;
        }
    }
    output = realloc( output, counter );

    printf( "Found %u time(s)\n", counter );
    for( int i = 0; i < counter; i++ ) {
        printf( "%u. %s %u:%u %s\n", i + 1, output[i]->book_id, output[i]->chapter, output[i]->verse, output[i]->text );
    }

    fclose( bible );
    return 0;
}