#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "mystring.h"

int main() {
    char str1[1000] = "12345678 23456789 37890 ";
    char *saveptr1= NULL;
    char *split1 = strtok_r( str1, " ", &saveptr1 );
    
    while( split1 ) {
        printf("%s\n", split1);
        split1 = strtok_r( NULL, " ", &saveptr1 );
    }

    char str2[1000] = "12345678 23456789 37890 ";
    char *saveptr2 = NULL;
    char *split2 = strtok_r( str2, " ", &saveptr2 );
    
    while( split2 ) {
        printf("%s\n", split2);
        split2 = strtok_r( NULL, " ", &saveptr2 );
    }

    return 0;
}