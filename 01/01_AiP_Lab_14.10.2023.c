#include <stdio.h> // Input/output library.
#include <math.h> // Math library.

int main() {
    int x, y;
    double z, a, b;

    // Friendly input interface.
    printf("Please, enter two integers \"x\", \"y\" and one float \"z\" separated by a space: ");
    scanf("%d %d %lf", &x, &y, &z);

    // Calculating "a".
    a = z + ((x - fabs(pow(y, 2) / (y + pow(x, 3) / (double) 3))) / pow(y, 2));

    // Calculating "b".
    b = exp(pow(y, 2) * z) * atan(x / pow(x + y, 0.5));

    // Output "x", "y" and "z".
    printf("\nx = %10d\ny = %10d\nz = %10.5e", x, y, z);

    // Output "a" and "b".
    printf("\na = %10.4lf\nb = %10.4lf", a, b);

    // Output x in oct.
    printf("\nx(oct) = %o", x);

    // Output x in hex.
    printf("\ny(hex) = %x", y);

    return 0;
}