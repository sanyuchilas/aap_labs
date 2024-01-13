#include <stdio.h> // Input/output library.
#include <math.h> // Math library.

int percisionChecker(int n, int i, double percision, double previousElement, double currentElement) {
    return fabs(currentElement - previousElement) > percision;
}

int nChecker(int n, int i, double percision, double previousElement, double currentElement) {
    return i < n;
}

double calculateByCriterion(int n, double percision, double x, int (*critertionChecker) (int, int, double, double, double)) {
    int i = 1;
    double s = 1, previousElement = 1, currentElement = 1;

    if (n == 1)  {
        return 1;
    }

    do {
        previousElement = currentElement;
        currentElement *= ((3 - 2 * i) * x) / (2 * i);

        s += currentElement;
        i++;
    } while (critertionChecker(n, i, percision, previousElement, currentElement));

    return s;
}

int main() {
    int n, isUpToNElement;
    double x, percision = 0.001;

    // Friendly input interface.
    printf("Please, enter -1 <= x <= 1: ");
    scanf("%lf", &x);

    printf("Please, enter \"1\" or \"0\" to select the sequence counting mode (\"1\" - up to n-element, \"0\" - up to precision): ");
    scanf("%d", &isUpToNElement);

    switch (isUpToNElement) {
        case 1:
            printf("Please, enter natural \"n\": ");
            scanf("%d", &n);

            printf("Answer: %lf", calculateByCriterion(n, percision, x, nChecker));
            printf("\nCorrect function value: %lf", sqrt(1 + x));

            break;

        case 0:
            printf("Please, enter precision: ");
            scanf("%lf", &percision);

            printf("Answer: %lf", calculateByCriterion(n, percision, x, percisionChecker));
            printf("\nCorrect function value: %lf", sqrt(1 + x));

            break;

        default:
            printf("Calculations are carried out with an precision of 0.001");

            printf("\nAnswer: %lf", calculateByCriterion(n, percision, x, percisionChecker));
            printf("\nCorrect function value: %lf", sqrt(1 + x));
    }

    return 0;
}