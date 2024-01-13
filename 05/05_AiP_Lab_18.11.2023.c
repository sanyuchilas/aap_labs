#include <stdio.h> // Input/output library.
#include <math.h> // Math library.

const int N = 100;

// Finding pointer on maximum odd element in row function.
int* findPMaxOddInRow(int arr[][N], int i, int n) {
    int* pMaxOdd = NULL;

    for (int j = 0; j < n; j++) {
        if (arr[i][j] % 2 != 0 && (pMaxOdd == NULL || arr[i][j] > *pMaxOdd)) {
            pMaxOdd = &arr[i][j];
        }
    }

    return pMaxOdd;
}

// Function implementing solution.
int* solution(int arr[][N], int m, int n) {
    int* out = NULL;
    int* pMaxOdd = NULL;

    for (int i = 0; i < m; i++) {
        if (arr[i][i] % 2 == 0) {
            pMaxOdd = findPMaxOddInRow(arr, i, n);
            
            if (pMaxOdd != NULL && (out == NULL || *pMaxOdd > *out)) {
                out = pMaxOdd;
            }
        }
    }

    return out;
}

// Array reading function.
int readArr(int arr[][N], int *pm, int *pn) {
    printf("Enter m >= 2 and n <= 10 numbers: ");
    scanf("%d %d", pm, pn);

    for (int i = 0; i < *pm; i++) {
        for (int j = 0; j < *pn; j++) {
            printf("Enter int arr[%d][%d]: ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }

    return 0;
}

// Arrya printing function.
int printArr(int arr[][N], int m, int n) {

    for (int i = 0; i < m; i++) {
        printf("\n");

        for (int j = 0; j < n; j++) {
            printf(" %d", arr[i][j]);
        }
    }

    return 0;
}

int main() {
    // Greeting.
    printf("Lab #5 made by Alexander Keyer from BAM231 group.\n\n");

    int m, n, arr[N][N];

    // Reading array.
    readArr(arr, &m, &n);

    // Entered array demonstration.
    printf("\nYou entered this array: ");
    printArr(arr, m, n);

    // Get answer.
    int* result = solution(arr, m, n);

    printf("\n\n");

    // Print answer.
    if (result != NULL) {
        printf("The corresponding answer: %d", *result);
    } else {
        printf("Cannot find corresponding answer.");
    }

    return 0;
}