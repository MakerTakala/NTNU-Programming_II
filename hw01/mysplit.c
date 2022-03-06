#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mysplit.h"

int mystrsplit( char ***ppList , int *pCounter , const char *pStr, const char *pSeparator ) {
    if( ppList == NULL) {
        return -1;
    }
    if( pCounter == NULL || pStr == NULL || ( pSeparator != NULL && *pSeparator == 0 ) ) {
        *ppList = NULL;
        return -1;
    }
    if( *pStr == 0) {
        *pCounter = 0;
        **ppList = 0;
    }
    
    int str_length = strlen(pStr);
    *ppList = calloc( str_length , sizeof(char*) );
    char *start = (char*)pStr;
    char *cur_string = calloc( str_length + 1, sizeof(char) );
    int i = 0, j = 0;

    if( pSeparator == NULL ) {
        while( *start != 0 ) {
            j = 0;
            while( *start != ' ' && *start != '\n' && *start != '\t' && *start != 0 ) {
                *(cur_string + j) = *start;
                j++;
                start++;
            }
            cur_string = realloc(cur_string, j + 1);
            *(*ppList + i) = cur_string;
            cur_string = calloc( str_length + 1 , sizeof(char) );
            i++;
            while( *start == ' ' || *start == '\n' || *start == '\t' ) {
                start++;
            }
        }
        *pCounter = i;
        *ppList = realloc( *ppList, (*pCounter) * sizeof(char*) );
        return 0;
    }
    char *find = strstr( start, pSeparator );
    while( find != NULL ) {
        j = 0;
        while( start != find ) {
            *(cur_string + j) = *start;
            j++;
            start++;
        }
        start += strlen(pSeparator);
        find = strstr( start, pSeparator );
        cur_string = realloc(cur_string, j + 1);
        *(*ppList + i) = cur_string;
        cur_string = calloc( str_length + 1 , sizeof(char) );
        i++;
    }
    j = 0;
    while( *start != 0 ) {
        *(cur_string + j) = *start;
        j++;
        start++;
    }
    cur_string = realloc( cur_string, j + 1 );
    *(*ppList + i) = cur_string;
    *pCounter = i + 1;
    *ppList = realloc( *ppList, (*pCounter) * sizeof(char*) );
    return 0;
}