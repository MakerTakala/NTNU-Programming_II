#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "fraction_Arithmetic.h"
#include "stack.h"

int main() {
    char str[4097] = {0};
    fgets( str, 4096, stdin );
    str[ strlen(str) - 1 ] = 0;
    char *cur = str;

    _sMixedNumber_stack number_stack = { -1, {-1} };
    _char_stack oper_stack = { -1, {-1} };

    while( *cur != 0 ) {
        sMixedNumber num_number = { .upper = 0, .lower = 1 };
        int64_t tmp_int = 0;

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
                printf("Wrong Input!\n");
                exit(0);
            }
        }
        
        if( *cur == ')' ) cur++;

        if( tmp_int > 0 ) {
            num_number.upper = tmp_int * num_number.lower + num_number.upper;
        }
        if( tmp_int < 0 ) {
            num_number.upper = tmp_int * num_number.lower - num_number.upper;
        }
        sMixedNumber_stack_push( &number_stack, num_number );
        // number has been dealed

        if( *cur == 0 ) break;

        if( operator_priority( char_stack_top( &oper_stack ) ) < operator_priority( *cur ) ) {
            char_stack_push( &oper_stack, *cur );
        }
        else {
            while( !char_stack_empty( &oper_stack ) && operator_priority( char_stack_top( &oper_stack ) ) >= operator_priority( *cur ) ) {
                sMixedNumber_stack_push( &number_stack, calculate( &oper_stack, &number_stack ) );
            }
        }
        cur++;
    }

    sMixedNumber top;
    while( !char_stack_empty( &oper_stack ) ) {
        top = sMixedNumber_stack_top( &number_stack );
        sMixedNumber_stack_push( &number_stack, calculate( &oper_stack, &number_stack ) );
    }
    top = sMixedNumber_stack_top( &number_stack );
    fixMixedNumber( &top );

    if( abs( top.upper ) >= abs( top.lower ) ) {
        printf( "%ld\\frac{%ld}{%ld}\n", top.upper / top.lower, abs(top.upper) % top.lower, top.lower );
    }
    else{
        printf( "\\frac{%ld}{%ld}\n", top.upper, top.lower );
    }

    return 0;
}