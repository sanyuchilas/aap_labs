#include <stdio.h> // Input/output library.
#include <math.h> // Math library.

// Function checking dot containing.
int isContainDot(double x, double y) {
    return (x >= 0 && x <= 1 && y >= -2 && y <= x) || (x < 0 && x >= -1 && y >= -2 && y <= -x); 
}

int main() {
    // Greeting.
    printf("Lab #2 made by Alexander Keyer from BAM231 group.\n\n");

    double x, y;
    
    // Friendly input interface.
    printf("Please, enter two float numbers \"x\" and \"y\" separated by a space: ");
    scanf("%lf %lf", &x, &y);
    
    printf("Solution 1: ");
    
    // First solution. Checking dot position
    if (x >= 0) {
        // First x half check.
        if (x <= 1) {
            // Frist y half check.
            if (y >= -2) {
                // First diagonal check.
                if (y <= x) {
                    printf("Is figure contain dot: true");
                } else {
                    printf("Is figure contain dot: false");
                }
            } else {
                printf("Is figure contain dot: false");
            }
        } else {
            printf("Is figure contain dot: false");
        }
    } else {
        // Second x half check.
        if (x >= -1) {
            // Second y half check.
            if (y >= -2) {
                // Second diagonal check.
                if (y <= -x) {
                    printf("Is figure contain dot: true"); 
                } else {
                    printf("Is figure contain dot: false");
                }
            } else {
                printf("Is figure contain dot: false");
            }
        } else {
            printf("Is figure contain dot: false");
        }
    }
    
    printf("\nSolution 2: ");
    
    // Second solution. Checking dot position
    if ((x >= 0 && x <= 1 && y >= -2 && y <= x) || (x < 0 && x >= -1 && y >= -2 && y <= -x)) {
        printf("Is figure contain dot: true");
    } else {
        printf("Is figure contain dot: false");
    }
    
    printf("\nSolution 3: ");
    
    // Third solution. Checking dot position
    if (isContainDot(x, y)) {
        printf("Is figure contain dot: true");
    } else {
        printf("Is figure contain dot: false");
    }
    
    return 0;
}