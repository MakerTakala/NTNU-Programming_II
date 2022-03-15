#include <stdio.h>
#include "myvector.h"

int main() {
    sVector *v = myvector_init();
    printf("%d", v->type);
    myvector_set(v, 1, 1.0, -1.0);
    return 0;
}