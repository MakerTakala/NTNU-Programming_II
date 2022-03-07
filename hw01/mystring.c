#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "mystring.h"

extern errno;

//hw0104

char *mystrchr( const char *s, int c ) {
    if( s == NULL ) {
        return NULL;
    }
    int n = strlen(s);
    for( int i = 0; i < n; i++ ) {
        if( *(s + i) == c ) {
            return (char*)(s + i);
        }
    }
    return NULL;
}

char *mystrrchr( const char *s, int c ) {
    if( s == NULL ) {
        return NULL;
    }
    int n = strlen(s);
    for( int i = n - 1; i >= 0 ; i-- ) {
        if( *(s + i) == c ) {
            return (char*)(s + i);
        }
    }
    return NULL;
}

size_t mystrspn( const char *s, const char *accept ) {
    if( s == NULL || accept == NULL ) {
        return 0;
    }
    int n = strlen(s), m = strlen(accept);
    for( int i = 0; i < n; i++ ) {
        for( int j = 0; j < n; j++ ) {
            if( *(s + i) == *(accept + j) ) {
                break;
            }
            if( j == m - 1 ){
                return i;
            }
        }
    }
    return n;
}
size_t mystrcspn( const char *s, const char *reject ) {
    if( s == NULL ) {
        return 0;
    }
    if( reject == NULL ) {
        return strlen(s);
    }
    int n = strlen(s), m = strlen(reject);
    for( int i = 0; i < n; i++ ) {
        for( int j = 0; j < m; j++ ) {
            if( *(s + i) == *(reject + j) ) {
                return i;
            }
        }
    }
    return n;
}
char *mystrpbrk( const char *s, const char *accept ) {
    if( s == NULL || accept == NULL ) {
        return NULL;
    }
    int n = strlen(s), m = strlen(accept);
    for( int i = 0; i < n; i++ ) {
        for( int j = 0; j < m; j++ ) {
            if( *(s + i) == *(accept + j) ) {
                return (char*)(s + i);
            }
        }
    }
    return NULL;
}

char *mystrstr( const char *haystack , const char *needle ) {
    if( haystack == NULL || needle == NULL ) {
        return NULL;
    }
    int n = strlen(haystack), m = strlen(needle);
    for( int i = 0; i <= (n - m); i++ ) {
        for( int j = 0; j < m; j++ ) {
            if( *(haystack + i + j) != *(needle + j) ) {
                break;
            }
            if( j == (m - 1) ) {
                return (char*)(haystack + i);
            }
        }
    }
    return NULL;
}

char *mystrtok( char *str, const char *delim ) {
    static char* tmp;
    char *start = (char*)str, *tail;
    if( str == NULL ) {
        start = tmp;
    }
    if( *start == 0 ) {
        tmp = start;
        return NULL;
    }
    start += mystrspn(start, delim);
    if( *start == 0 ) {
        tmp = start;
        return NULL;
    }

    tail = start + mystrcspn(start, delim);
    if( *tail == 0 ) {
        tmp = tail;
        return start;
    }
    *tail = 0;
    tmp = tail + 1;
    return start;
}


//hw0103

bool isallowrange( char c , int base ) {
    if( base <= 10 ) {
        return '0' <= c && c < '0' + base;
    }
    return ( '0' <= c && c <= '9' ) || ( 'a' <= c && c < ( 'a' +  base - 10 ) ) || ( 'A' <= c && c < ('A' +  base - 10 ) );
}

long int mystrtol( const char *nptr, char **endptr , int base ) {
    char *start = (char*)nptr; 

    while( *start == ' ' ) {
        start++;
    }

    if( ( base < 2 || 36 < base ) && base != 0 ) {
        errno = EINVAL;
        return 0;
    }

    char sign = '+';
    if( *start == '+' ) {
        start++;
    }
    if( *start == '-' ) {
        sign = '-';
        start++;
    }

    bool hadread = false;
    if( base == 0 ) {
        if( *start == '0') {
            start++;
            if( *start == 'x' || *start == 'X') {
                base = 16;
                start++;
            }
            else {
                base = 8;
            }
            hadread = true;
        }
        else{
            base = 10;
        }
    }

    if( base == 8 ) {
        if( *start == 0 ) {
            start++;
        }
    }
    if( base == 16 ) {
        if( *start == 0 && ( *(start + 1) == 'x' || *(start + 1) == 'X' ) ) {
            start += 2;
        }
    }

    if( !isallowrange( *start, base) ) {
        if( endptr != NULL ) {
            if( hadread ) {
                if( base == 16 ) {
                    *endptr = start - 1;
                }
                else {
                    *endptr = start;
                }
            }
            else {
                *endptr = (char*)nptr;
            }
        }
        return 0;
    }

    int64_t num = 0;
    bool overflow = false;

    while( isallowrange( *start, base ) ) {
        uint8_t c = *start;
        if( isdigit(*start) ) {
            c = c - '0';
        }
        else {
            c = tolower(c);
            c = c - 'a' + 10;
        }
        
        if( ( (LONG_MAX - c) / base ) < num ) {
            overflow = true;
        }
        num = num * base + c ;
        start++;
    }
    if( endptr != NULL ) {
        *endptr = start;
    }
    if( overflow ) {
        errno = ERANGE;
        return sign == '+' ? LONG_MAX : LONG_MIN;
    }

    return sign == '+' ? num : -num;
}