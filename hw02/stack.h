#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "fraction_Arithmetic.h"
#define MAX_LENGTH 4097

typedef struct {
    int32_t top;
    char content[MAX_LENGTH];
}_char_stack;

typedef struct {
    int32_t top;
    sMixedNumber content[MAX_LENGTH];
}_sMixedNumber_stack;

char char_stack_top( _char_stack *stack );
void char_stack_push( _char_stack *stack, char c );
void char_stack_pop( _char_stack *stack );
bool char_stack_empty( _char_stack *stack );
sMixedNumber sMixedNumber_stack_top( _sMixedNumber_stack *stack );
void sMixedNumber_stack_push( _sMixedNumber_stack *stack, sMixedNumber num );
void sMixedNumber_stack_pop( _sMixedNumber_stack *stack );
uint8_t operator_priority( char c );
sMixedNumber calculate( _char_stack *operator_stack, _sMixedNumber_stack *number_stack );