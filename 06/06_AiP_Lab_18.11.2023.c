#include <stdio.h> // Input/output library.
#include <math.h> // Math library.
#include <stdlib.h> // Dynamic memory library.

// Finding corresponding array's minimum function.
int* findMinOddPointer(int *arr, int n) {
    int *out = NULL;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0 && (out == NULL || arr[i] < *out)) {
            out = arr + i;
        }
    }

    return out;
}

// Modifying array function.
int* getModifiedArray(int *arr, int *pn) {
    int *pMinOdd = findMinOddPointer(arr, *pn);

    if (pMinOdd == NULL) {
        return arr;
    }

    int newArrLength = 0;

    for (int i = 0; i < *pn; i++) {
        if (arr + i <= pMinOdd || arr[i] % 2 == 0) {
            arr[newArrLength] = arr[i];
            newArrLength++;
        }
    }

    *pn = newArrLength;

    return realloc(arr, sizeof(int) * newArrLength);
}

// Array printing function.
int printArr(int *arr, int n) {
    for (int i = 0; i < n; i++ ) {
        printf(" %d", arr[i]);
    }

    return 0;
}

// Array reading function.
int* readArr(int* pn) {
    // Array's elements count reading.
    printf("Array length: ");
    scanf("%d", pn);

    int* arr = (int*)malloc(sizeof(int) * *pn);

    for (int i = 0; i < *pn; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", arr + i);
    }

    return arr; 
}

int main() {
    // Greeting.
    printf("Lab #6 made by Alexander Keyer from BAM231 group.\n\n");

    int n;

    // Array reading.
    int* arr = readArr(&n);

    if (arr == NULL) {
        printf("Cannot create array correctly.");
        return -1;
    }

    // Entered array demonstration.
    printf("\nYou entered this array:");
    printArr(arr, n);

    // Work with modified array.
    int* modifiedArr = getModifiedArray(arr, &n);

    printf("\nModified array:");    
    printArr(modifiedArr, n);

    // Freeing up allocated memory.
    free(arr);

    return 0;
}