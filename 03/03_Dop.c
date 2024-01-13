#include <stdio.h> // Input/output library.
#include <math.h> // Math library.
void printDivides(int n) {
    int d = 1;

    while (d <= (n / 2)) {
        if (n % d == 0) {
            printf( "\n%d %d", d, n / d);
        }

        d++;
    }
}

int main() {
    int n;

    printf("Please, input natural n: ");
    scanf("%d", &n);

    printDivides(n);

    return 0;
}