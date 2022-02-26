#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "mystring.h"


int main() {     //0         1    
    extern errno;// 123456789 123456789
    char str[30] = "   -   ylnw  LxUb19SQXg";
    char* endptr1;
    char* endptr2;
    for(int i = 0 ;i <= 36; i++){
        int64_t errno1, errno2;
        mystrtol(str, &endptr2, i);
        errno2 = errno;
        strtol(str, &endptr1, i);
        errno1 = errno;
        if(mystrtol(str, &endptr2, i) == strtol(str, &endptr1, i)  && errno1 == errno2 && endptr1 == endptr2){   
            printf("Base: %d\nsuccess\n", i);
        }
        else {
            printf("Base: %d\nwrong\n", i);
            printf("%ld\n", mystrtol(str, &endptr2, i));
            printf("%d\n", endptr2 - str);
            printf("%s\n\n", strerror(errno2));
            printf("%ld\n", strtol(str, &endptr1, i));
            printf("%d\n", endptr1 - str);
            printf("%s\n\n", strerror(errno1));
        }
    }
    return 0;
}