#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "mymatch.h"

bool match( char *str, char *pattern ) {
    char *last_star = NULL;
    char *last_match = str;
    while( *str  ) {
        if( *pattern == '?' || *str == *pattern ) {
            str++;
            pattern++;
        }
        else if( *pattern == '*' ) {
            last_star = pattern;
            pattern++;
            last_match = str;
        }
        else if( last_star != NULL ) {
            pattern = last_star + 1;
            last_match++;
            str = last_match;
        }
        else {
            return false;
        }
    }
    while( *pattern == '*' ) {
        pattern++;
    }
    return *pattern == 0;
}

uint16_t substr_size( char *str ) {
    uint16_t counter = 0;
    while( *str ) {
        if( *str == ' ' ) {
            counter++;
        }
        str++;
    }
    return counter + 1;
}

int mymatch( char ***pppList , const char *pStr, const char *pPattern ) {
    uint16_t counter = 0;
    char *str = calloc( strlen(pStr), sizeof(char) );
    str = strcpy( str, pStr );
    *pppList = calloc( substr_size( str ), sizeof(char*) );
    char *str_start = strtok( str, " " );
    while( str_start ) {
        if( match( str_start, (char*)pPattern ) ) {
            *( *pppList + counter ) = str_start;
            counter++;
        }
        str_start = strtok( NULL, " " );
    }
    *pppList = realloc( *pppList, counter * sizeof(char*) );
    return counter;
}