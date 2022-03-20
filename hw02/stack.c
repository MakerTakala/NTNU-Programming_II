#include <stdint.h>
#include <stdio.h>
#include "stack.h"
#include "fraction_Arithmetic.h"

uint8_t operator_priority( char c ) {
    if( c == '+' || c == '-' ) {
        return 1;
    }
    if( c == '*' || c == '/' ) {
        return 2;
    }
    return 0;
}

sMixedNumber calculate( _char_stack *operator_stack, _sMixedNumber_stack *number_stack ) {
    char oper = char_stack_top( operator_stack );
    char_stack_pop( operator_stack );
    sMixedNumber num2 = sMixedNumber_stack_top( number_stack );
    sMixedNumber_stack_pop( number_stack );
    sMixedNumber num1 = sMixedNumber_stack_top( number_stack );
    sMixedNumber_stack_pop( number_stack );

    sMixedNumber return_number = { .upper = 0, .lower = 0 };
    if(oper == '+') mixed_add( &return_number, num1, num2 );
    if(oper == '-') mixed_sub( &return_number, num1, num2 );
    if(oper == '*') mixed_mul( &return_number, num1, num2 );
    if(oper == '/') mixed_div( &return_number, num1, num2 );

    return return_number;
}

char char_stack_top( _char_stack *stack ) {
    return stack -> content[stack -> top];
}

void char_stack_push( _char_stack *stack, char c ) {
    (stack -> top)++;
    stack -> content[stack -> top] = c;
    return;
}

void char_stack_pop( _char_stack *stack ) {
    (stack -> top)--;
    return;
}

bool char_stack_empty( _char_stack *stack ) {
    return stack -> top == -1;
}

sMixedNumber sMixedNumber_stack_top( _sMixedNumber_stack *stack ) {
    return stack -> content[stack -> top];
}

void sMixedNumber_stack_push( _sMixedNumber_stack *stack, sMixedNumber num ) {
    (stack -> top)++;
    stack -> content[stack -> top] = num;
    return;
}

void sMixedNumber_stack_pop( _sMixedNumber_stack *stack ) {
    (stack -> top)--;
    return;
}