#include <stdio.h>

int main() {
    fopen("abs.txt", "r");
    perror("ERROR");
    return 0;
}