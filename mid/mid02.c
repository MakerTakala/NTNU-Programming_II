#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "mid_helper.h"
#define MAX_INPUT 32768

typedef struct{
    char name1[32];
    char code1[32];
    char name2[32];
    char code2[32];
    uint8_t population[256];
}City;

int main() {
    FILE *data_file = open_file( "Please enter the data name: ", "r", 4096 );

    char buffer[MAX_INPUT] = {0};
    for( int i = 0 ;i < 5; i++ ) {
        fgets(buffer, MAX_INPUT, data_file);
    }
    int counter = 0;
    City *city = calloc( sizeof(City), 300 );
    while( fgets(buffer, MAX_INPUT, data_file) ) {
         
        

    }




    uint64_t start_time = ask( "Please enter the analysis start time:" );
    uint64_t end_time = ask( "Please enter the analysis end time :" );
    if( end_time > start_time ) {
        printf("Wrong input\n");
        exit(0);
    }
    while(1) {
        print_menu();
        uint64_t in = ask( "Your choice:" );
        if( in == 1 ) {

        }
        else if( in == 2 ) {

        }
        else if( in == 3 ) {
            
        }
        else if( in == 4 ) {
            
        }
        else if( in == 5 ) {
            
        }
        else if( in == 6 ) {
            
        }
        else if( in == 7 ) {
            
        }
        else if( in == 8 ) {
            
        }
        else {
            printf("Wrong number\n");
            exit(0);
        }
        

    }
    

    return 0;
}