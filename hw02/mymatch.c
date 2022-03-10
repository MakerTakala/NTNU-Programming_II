#include <string.h>
#include "mymatch.h"

int mymatch( char ***pppList , const char *pStr, const char *pPattern ) {
    int counter = 0;
    char seprator = ' ';
    char *Str = (char*)pStr;
    char *str_start = strtok( Str, &seprator );
    while( str_start ) {
        char* cur_str = str_start;
        while( *pPattern && *cur_str ) {
            if( *pPattern == '?' ) {
                pPattern++;
                cur_str++;
            }
            else if( *pPattern == '*' ) {
                if( *(pPattern + 1) == 0 ) {

                }
                else {

                }
            }
            else {
                if( *pPattern == *cur_str ){
                    pPattern++;
                    cur_str++;
                }
                else {
                    break;
                }
            }
        }
        if( *pPattern == 0 && *cur_str == 0 ) {
            //malloc
        }


        str_start = strtok(NULL, &seprator);
    }

    return counter;
}