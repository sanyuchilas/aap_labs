#include <stdio.h> // Input/output library.
#include <math.h> // Math library.

// Maximum finding function.
int maxBelongingToXYInterval(int arr[], int *pn, int x, int y) {
    int m = x - 1;

    for (int i = 0; i < *pn; i++) {
        if (arr[i] >= x && arr[i] <= y && arr[i] > m) {
            m = arr[i];
        }
    }

    return m;
}

// Arithmetic mean finding function.
double findArithmeticMean(int arr[], int *pn) {
    double result = 0;
    int *minOdd = NULL;
    double s = 0;

    for (int i = 0; i < *pn; i++) {
        if (arr[i] % 2 != 0) {
            if (minOdd == NULL) {
                minOdd = arr + i;
                result = s / i;
            }

            if (arr[i] < *minOdd) {
                minOdd = arr + i;
                result = s / i;
            }
        }

        s += arr[i];
    }

    if (minOdd == arr) {
        return NAN;
    } else if (minOdd == NULL) {
        return s / *pn;
    }

    return result;
}

// Array reading function.
int readArr(int arr[], int *pn) {
    printf("Enter array's elements count: ");
    scanf("%d", pn);

    for (int i = 0; i < *pn; i++) {
        printf("Enter int arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    return 0;
}

// Array printiing function.
int printArr(int arr[], int* pn) {
    printf("{");

    for (int i = 0; i < *pn - 1; i++) {
        printf("%d, ", arr[i]);
    }

    printf("%d}", arr[*pn - 1]);
}

int main() {
    // Greeting.
    printf("Lab #4 made by Alexander Keyer from BAM231 group.\n\n");

    int x, y, arr[10];
    int *pn;

    // Reading array.
    readArr(arr, pn);

    // Entered array demonstration.
    printf("\nYou entered this array: ");
    printArr(arr, pn);

    // Reading threshold values.
    printf("\n\nEnter x and y, x <= y: ");
    scanf("%d %d", &x, &y);

    // Calculating maximum.
    int m = maxBelongingToXYInterval(arr, pn, x, y);

    // Corresponding maximum demonstration.
    if (m == x - 1) {
        printf("\nArray doesn't contain numbers belonging to XY interval.");
    } else {
        printf("\nCorresponding maximum value: %d", m);
    }
    
    // Calculating arithmetic mean.
    double arithmeticMean = findArithmeticMean(arr, pn);

    if (isnan(arithmeticMean)) {
        // Cannot find correct arithmetic mean.
        printf("\nCorresponding arithmetic mean: 0");
    } else {
        printf("\nCorresponding arithmetic mean: %lf", arithmeticMean);
    }

    return 0;
}