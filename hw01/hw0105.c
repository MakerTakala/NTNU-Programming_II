#include "mysplit.h"
#include <stdio.h>

int main() {
    char split_str[] = "123  \t    901  \t \n 23\n4578  9012\t34567890";
    char separator[] = "123";
    char **ppList;
    int counter = 0;
    printf("retrun: %d\n", mystrsplit(&ppList, &counter, split_str, NULL));
    printf("counter: %d\n", counter);
    for(int i = 0; i < counter ; i++){
        printf("%s\n", *(ppList + i));
    }
    return 0;
}