#include <stdio.h>
#include <stdint.h>

int main() {
    char *str = "\\frac{5}{6}";
    int8_t i = 0, u = 0, l = 0;;
    printf("sscanf:%d\n", sscanf( str, "frac{%hhd}{%hhd}", &u, &l ));
    printf("%hhd %hhd %hhd\n", i, u, l);
}