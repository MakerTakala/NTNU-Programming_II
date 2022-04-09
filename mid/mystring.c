#include <string.h>
#include "mystring.h"

char *mystrtok_r(char *str, const char *delim , char **saveptr) {

    if( !str ) {
        str = *saveptr;
    }
    if( !*str ) {
        *saveptr = str;
        return NULL;
    }
    str += strspn( str, delim );
    if( !*str ) {
        *saveptr = str;
        return NULL;
    }

    char *tail = str + strcspn( str, delim );
    if( !*tail ) {
        *saveptr = tail;
        return str;
    }
    *tail = 0;
    *saveptr = tail + 1;
    return str;
}