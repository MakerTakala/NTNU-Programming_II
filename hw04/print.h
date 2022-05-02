#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int64_t x = 0;
int64_t value = 0;
double value_d = 0;
extern uint16_t *p_file;

void ask();
void print_outline();
void print_attributes();
void print_health_status();
void print_money();
void print_item();
void print_essentail();
void print_ability();
void print_evaluation();
void print_chores();

void ask() {
    printf( "Your Chose: " );
    scanf( "%ld", &x );
}

void ask_value() {
    printf( "Input the value you wnat to change to: " );
    scanf( "%ld", &value );
    if( value < 0 || 999 < value ) {
        printf( "Wrong Input!!\n" );
        exit(0);
    }
}

void ask_value_d() {
    printf( "Input the value you wnat to change to: " );
    scanf( "%lf", &value_d );
    if( value_d < 0 || 999 < value_d ) {
        printf( "Wrong Input!!\n" );
        exit(0);
    }
}

void ask_money() {
    printf( "Input the money you wnat to change to: " );
    scanf( "%ld", &value );
    if( value < 0 || 65535 < value ) {
        printf( "Wrong Input!!\n" );
        exit(0);
    }
}

void print_outline() {
    system("clear");
    printf("Chose the type you wnat to fix.\n");
    printf( "\t1) Attributes\n" );  
    printf( "\t2) Health Status\n" );
    printf( "\t3) Money\n" );
    printf( "\t4) Item\n" );
    printf( "\t5) Exit\n" );
    printf( "\n" );
    ask();
    if( x == 1 ) {
        print_attributes();
    }
    else if( x == 2 ) {
        print_health_status();
    }
    else if( x == 3 ){
        print_money();
    }
    else if( x == 4 ) {
        print_item();
    }
    else if( x == 5 ) {
        exit(0);
    }
    else {
        printf( "Wrong Input!!\n" );
        exit(0);
    }
}

void print_attributes() {
    system("clear");
    printf("Chose the type you wnat to fix.\n");
    printf( "\t1) Essential\n" );  
    printf( "\t2) Ability\n" );
    printf( "\t3) Evaluation\n" );
    printf( "\t4) Chores\n" );
    printf( "\t5) Exit\n" );
    printf( "\n" );
    ask();
    if( x == 1 ) {
        print_essentail();
    }
    else if( x == 2 ) {
        print_ability();
    }
    else if( x == 3 ){
        print_evaluation();
    }
    else if( x == 4 ) {
        print_chores();
    }
    else if( x == 5 ) {
        exit(0);
    }
    else {
        printf( "Wrong Input!!\n" );
        exit(0);
    }
}

void print_essentail() {
    system("clear");
    printf("Chose the type you wnat to fix.\n");
    printf( "\t1) Physical Strength\n" );
    printf( "\t2) Wrist Strength\n" );
    printf( "\t3) Intelligence\n" );
    printf( "\t4) Temperament\n" );
    printf( "\t5) Charm\n" );
    printf( "\t6) Morality\n" );
    printf( "\t7) Belief\n" );
    printf( "\t8) Sin\n" );
    printf( "\t9) Feeling\n" );
    printf( "\t10) Fatigue\n" );
    printf( "\t11) Exit\n" );
    printf( "\n" );
    ask();
    if( x < 1 || 11 < x ) {
        printf( "Wrong Input!\n" );
        exit(0);
    }
    if( x == 11 ) exit(0);
    ask_value();
    p_file[0X1E + x] = value;
}

void print_ability() {
    system("clear");
    printf("Chose the type you wnat to fix.\n");
    printf( "\t1) Combat Technique\n" );
    printf( "\t2) Attack Ability\n" );
    printf( "\t3) Defensive Ability\n" );
    printf( "\t4) Magic Technology\n" );
    printf( "\t5) Magic Ability\n" );
    printf( "\t6) Magic Resistance\n" );
    printf( "\t7) Exit\n" );
    printf( "\n" );
    ask();
    if( x < 1 || 7 < x ) {
        printf( "Wrong Input!\n" );
        exit(0);
    }
    if( x == 7 ) exit(0);
    ask_value();
    p_file[0X2D + x] = value;
}

void print_evaluation() {
    system("clear");
    printf("Chose the type you wnat to fix.\n");
    printf( "\t1) Warriort Evaluation\n" );
    printf( "\t2) Magic Evaluation\n" );
    printf( "\t3) Social Contact Evaluation\n" );
    printf( "\t4) Housework Evaluation\n" );
    printf( "\t5) Exit\n" );
    printf( "\n" );
    ask();
    if( x < 1 || 5 < x ) {
        printf( "Wrong Input!\n" );
        exit(0);
    }
    if( x == 5 ) exit(0);
    ask_value();
    p_file[0X29 + x] = value;
}

void print_chores() {
    system("clear");
    printf("Chose the type you wnat to fix.\n");
    printf( "\t1) Etiquette\n" );
    printf( "\t2) Artistic Accomplishment Ability\n" );
    printf( "\t3) Conversation Skills Ability\n" );
    printf( "\t4) Cooking Technique\n" );
    printf( "\t5) Cleaning And Do The Laundry\n" );
    printf( "\t6) Greet People\n" );
    printf( "\t7) Exit\n" );
    printf( "\n" );
    ask();
    if( x < 1 || 7 < x ) {
        printf( "Wrong Input!\n" );
        exit(0);
    }
    if( x == 7 ) exit(0);
    ask_value();
    p_file[0X33 + x] = value;
}

void print_health_status() {
    system("clear");
    printf("Chose the type you wnat to fix.\n");
    printf( "\t1) Height\n" );
    printf( "\t2) Weight\n" );
    printf( "\t3) Chest Circumference\n" );
    printf( "\t4) Waistline\n" );
    printf( "\t5) Hip Circumference\n" );
    printf( "\t6) Exit\n" );
    printf( "\n" );
    ask();
    if( x < 1 || 6 < x ) {
        printf( "Wrong Input!\n" );
        exit(0);
    }
    if( x == 6 ) exit(0);
    ask_value_d();
    p_file[0X68 + x] = (uint16_t)(value_d * 100);
}

void print_money() {
    system("clear");
    printf("now:%hu\n", p_file[0X58]);
    ask_money();
    p_file[0X58] = value ;
}

void print_item() {
    system("clear");
    printf( "Sorry, I didn't finish it, and I have no intention to finish it\n" );
    exit(0);
}