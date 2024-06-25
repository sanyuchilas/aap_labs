#include <stdio.h>

int main() {
    // Question 1.
    char var; // 8 bit = 1 byte, [-128, 127]
    signed char var; // 8 bit = 1 byte, [-128, 127]
    unsigned char var; // 8 bit = 1 byte, [0, 256]

    short int var; // 16 bit = 2 byte
    signed short int var;
    unsigned short int var;

    int var; // 32 bit = 4 byte
    signed int var;
    unsigned int var;

    long int var; // >= 32 bit = 4 byte
    signed long int var;
    unsigned long int var;

    long long int  var; // 64 bit = 4 byte
    signed long long int var;
    unsigned long long int var;

    double var;
    long double var;

    const char var; // The constant, but we also have a #define directive

    return 0;
}