#include "mysplit.h"
#include <stdio.h>

int main() {
    char split_str[] = "1234567890122o37rbyo2345678901234567890";
    char separator[] = "456";
    char **ppList;
    int counter;
    printf("retrun: %d\n", mystrsplit(&ppList, &counter, split_str, separator));
    printf("counter: %d\n", counter);
    for(int i = 0; i < counter ; i++){
        printf("%s\n", *(ppList + i));
    }
    return 0;
}