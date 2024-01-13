#include <stdio.h> // Input/output library.
#include <math.h> // Math library.

int main() {
    // Greeting.
    printf("Lab #3 made by Alexander Keyer from BAM231 group.\n\n");

    int n, isUpToNElement;
    double x, percision = 0.001, s = 1, currentElement = 1;

    // Friendly input interface.
    printf("Enter -1 <= x <= 1: ");
    scanf("%lf", &x);

    printf("Sequence counting mode (\"1\" - up to n, \"0\" - up to precision): ");
    scanf("%d", &isUpToNElement);

    switch (isUpToNElement) {
        case 1:
            // Friendly n's input.
            printf("Enter natural \"n\": ");
            scanf("%d", &n);

            for (int i = 1; i < n; i++) {
                currentElement *= ((3 - 2 * i) * x) / (2 * i);

                s += currentElement;
            }

            break;

        case 0:
            // Friendly persiocion's input.
            printf("Enter precision: ");
            scanf("%lf", &percision);

            int i = 1;

            while (fabs(currentElement) > percision) {
                currentElement *= ((3 - 2 * i) * x) / (2 * i);

                s += currentElement;
                i++;
            }

            break;

        default:
            // Print explainations.
            printf("Calculations are carried out with an precision of 0.001\n");
    }

    // Print my answer.
    printf("\nAnswer: %lf", s);

    // Print correct function value.
    printf("\nCorrect function value: %lf", sqrt(1 + x));

    return 0;
}