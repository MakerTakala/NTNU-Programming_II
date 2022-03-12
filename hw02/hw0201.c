#include <stdio.h>
#include <stdint.h>
#include "mymatch.h"

int main() {
    char **ppList;
    char *pStr = "ae ace ache aaae baaae apple";
    char *pPattern = "a*e";
    
    uint64_t coutner = mymatch( &ppList, pStr, pPattern );
    
    printf("counter: %lu\n", coutner);
    for(int i = 0; i < coutner; i++) {
        printf("%d: %s\n", i + 1, *(ppList + i));
    }
    
    return 0;
}