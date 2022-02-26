#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

extern errno;

bool isallowrange( char c , int base ) {
    if( base <= 10 ) {
        return '0' <= c && c < '0' + base;
    }
    return ( '0' <= c && c <= '9' ) || ( 'a' <= c && c < ( 'a' +  base - 10 ) ) || ( 'A' <= c && c < ('A' +  base - 10 ) );
}

long int mystrtol( const char *nptr, char **endptr , int base ) {
    char* start = nptr; 
    //skip space
    while( (*start) == ' ' ) {
        start++;
    }

    //exclude wrong base
    if( ( base < 2 || 36 < base ) && base != 0 ) {
        errno = EINVAL;
        return 0;
    }

    char sign = '+';

    if( (*start) == '+' ) {
        start++;
    }
    if( (*start) == '-' ) {
        sign = '-';
        start++;
    }
    if( base == 0 || base == 8 || base == 16 ) {
        if( base == 0 && (*start) != '0' ) {
            base = 10;
        }
        if( (*start) == '0') {
            start++;
            if( (*start) == 'x' ) {
                base = 16;
                start++;
            }
            else {
                base = 8;
            }
        }
    }

    if( !isallowrange(*start, base) ) {
        (*endptr) = nptr;
        return 0;
    }

    uint64_t num = 0;
    bool overflow = false;

    while( isallowrange( (*start), base ) ) {
        uint8_t c = (*start);
        if( isdigit( (*start) ) ) {
            c = c - '0';
        }
        else {
            c = tolower( c );
            c = c - 'a' + 10;
        }
        
        if( ( ( LONG_MAX - c ) / base ) < num ) {
            overflow = true;
        }
        num = num * base + c ;
        start++;
    }
    if( endptr != NULL ) {
        (*endptr) = start;
    }
    if( overflow ) {
        errno = ERANGE;
        return sign == '+' ? LONG_MAX : LONG_MIN;
    }

    return sign == '+' ? num : -num;
}