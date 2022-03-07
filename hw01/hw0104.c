#include <stdio.h>
#include <string.h>
#include "mystring.h"

int main() {
    char test_str[] = "1,,2,,3,,4";
    char test_set[] = ",";
    char test_char = '1';
    
    printf("strchr:\n");
    if(strchr(test_str, test_char ) != NULL) {
        printf("%c\n", *strchr(test_str, test_char ));
    }
    else{
        printf("NULL\n");
    }
    if(mystrchr(test_str, test_char ) != NULL) {
        printf("%c\n", *mystrchr(test_str, test_char ));
    }
    else{
        printf("NULL\n");
    }

    printf("strrchr:\n");
    if(strrchr(test_str, test_char ) != NULL) {
        printf("%c\n", *strrchr(test_str, test_char ));
    }
    else{
        printf("NULL\n");
    }
    if(mystrrchr(test_str, test_char ) != NULL) {
        printf("%c\n", *mystrrchr(test_str, test_char ));
    }
    else{
        printf("NULL\n");
    }
   
    printf("strspn:\n");
    if(strspn(test_str, test_set) != 0) {
        printf("%ld\n", strspn(test_str, test_set));
    }
    else{
        printf("0\n");
    }
    if(mystrspn(test_str, test_set) != 0) {
        printf("%ld\n", mystrspn(test_str, test_set));
    }
    else{
        printf("0\n");
    }

    printf("strcspn:\n");
    if(strcspn(test_str, test_set) != 0) {
        printf("%ld\n", strcspn(test_str, test_set));
    }
    else{
        printf("0\n");
    }
    if(mystrcspn(test_str, test_set) != 0) {
        printf("%ld\n", mystrcspn(test_str, test_set));
    }
    else{
        printf("0\n");
    }

    printf("strbrk:\n");
    if(strpbrk(test_str, test_set) != NULL) {
        printf("%c\n", *strpbrk(test_str, test_set));
    }
    else{
        printf("NULL\n");
    }
    if(mystrpbrk(test_str, test_set) != NULL) {
        printf("%c\n", *mystrpbrk(test_str, test_set));
    }
    else{
        printf("NULL\n");
    }

    printf("strstr:\n");
    if(strstr(test_str, test_set) != NULL) {
        printf("%c\n", *strstr(test_str, test_set));
    }
    else{
        printf("NULL\n");
    }
    if(mystrstr(test_str, test_set) != NULL) {
        printf("%c\n", *mystrstr(test_str, test_set));
    }
    else{
        printf("NULL\n");
    }

    char test_strtok1[] = ",,,,1,,2,,3,,4,,5";
    char test_settok1[] = ",";
    printf("strtok:\n");
    char *p1 = strtok(test_strtok1, test_settok1);
    while(p1){
        printf("%s\n", p1);
        p1 = strtok(NULL, test_settok1);
    }
    
    char test_strtok2[] = ",,,,,1,,2,,3,,4,,5";
    char test_settok2[] = ",";
    char *p2 = mystrtok(test_strtok2, test_settok2);
    while(p2){
        printf("%s\n", p2);
        p2 = mystrtok(NULL, test_settok2);
    }
    return 0;
}