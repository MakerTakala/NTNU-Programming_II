#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "fraction_Arithmetic.h"

int main() {
    char str[4097];
    fgets( str, 4096, stdin );
    char *cur = str;
    while(1) {
        sMixedNumber num_number = { .upper = 0, .lower = 1 };
        int8_t tmp_int = 0;

        if( *cur == '(' ) cur++;

        char *tmp_str = cur;
        tmp_int = strtol( tmp_str, &cur, 10);

        if( *cur == ')' ) cur++;

        if( *cur == '\\' ) {
            cur += 6;
            tmp_str = cur;
            num_number.upper = strtol( tmp_str, &cur, 10);
            cur += 2;
            tmp_str = cur;
            num_number.lower = strtol( tmp_str, &cur, 10);
            cur += 1;
            if( num_number.lower == 0 ) {
                exit(0);
            }
        }
        
        if( *cur == ')' ) cur++;




        if( tmp_int >= 0 ) {
            num_number.upper = tmp_int * num_number.lower + num_number.upper;
        }
        else {
            num_number.upper = tmp_int * num_number.lower - num_number.upper;
        }
        printf("%ld %ld\n", num_number.upper, num_number.lower);

        if( *cur == '+' || *cur == '-' || *cur == '*' || *cur == '/') {

        }
        else {
            break;
        }
    }



    return 0;
}