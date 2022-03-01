#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mysplit.h"

int mystrsplit( char ***ppList , int *pCounter , const char *pStr, const char *pSeparator ) {
    if( pStr == NULL || pCounter == NULL ) {
        return -1;
    }
    int str_length = strlen(pStr);
    *ppList = calloc( str_length , sizeof(char*) );

    if( pSeparator == NULL || *pSeparator == 0 ) {
        for(int i = 0 ; i < str_length ; i++) {
            char *cur_string = calloc( 2, sizeof(char) );
            *cur_string = *(pStr + i);
            *(*ppList + i) = cur_string;
        }
        return 0;
    }

    char *start = (char*)pStr;
    char *find = strstr( start, pSeparator );
    char *cur_string = calloc( str_length + 1, sizeof(char) );
    int i = 0, j = 0;
    while( find != NULL ) {
        j = 0;
        while( (start + j) != find ) {
            *(cur_string + j) = *(start + j);
            j++;
        }
        start = find + strlen(pSeparator);
        find = strstr( start, pSeparator );
        cur_string = realloc(cur_string, j + 1);
        *(*ppList + i) = cur_string;
        cur_string = calloc( str_length + 1 , sizeof(char) );
        i++;
    }

    j = 0;
    while( *(start + j) != 0 ) {
        *(cur_string + j) = *(start + j);
        j++;
    }
    cur_string = realloc( cur_string, j + 1 );
    *(*ppList + i) = cur_string;
    *pCounter = i + 1;
    *ppList = realloc( *ppList, (*pCounter) * sizeof(char*) );
    return 0;
}