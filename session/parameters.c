#include <stdio.h>

void test(int* p) {
    printf("%p --> %d\n", p, *p);
}

int main() {
    int p = 10;

    printf("%p --> %d\n", p, p);

    test(&p);

    return 0;
}