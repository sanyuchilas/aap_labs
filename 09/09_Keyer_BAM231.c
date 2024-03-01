#include "football.h" // Footballer info.

#include <stdio.h> // Input/output library.
#include <stdlib.h> // Memory allocation.
#include <time.h> // Time library.
#include <assert.h> // Assertion library.
#include <string.h> // String functions library.

void printHr(int length) {
  for (int j = 0; j < length; j++) {
      printf("- ");
    }
    printf("\n");
}

void printTableHeader() {
  printHr(65);
  printf("%2s|%30s|%30s|%30s|%10s|%10s|%10s|\n", "ID", "FULL NAME", "CLUB NAME", "ROLE", "AGE", "GAMES", "GOALS");
  printHr(65);
}

void printFootballer(struct footballerType footballer, int id) {
  printf("%2d|%30s|%30s|%30s|%10d|%10d|%10d|\n", id, footballer.fullName, footballer.clubName, footballer.role, footballer.age, footballer.numberOfGames, footballer.numberOfGoals);
  printHr(65);
}

void printFootballers(struct footballerType* footballers, int length) {
  printTableHeader();

  for (int i = 0; i < length; i++) {
    printFootballer(footballers[i], i);
  }
}

char* generateString(int length, int countOfUsedSymbols) {
  assert(countOfUsedSymbols <= 26);

  char* out = (char*)malloc(sizeof(char) * (length + 1));
  char alphabet[26] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
  };

  for (int i = 0; i < length; i++) {
    out[i] = alphabet[rand() % countOfUsedSymbols];
  }

  out[length] = '\0';

  return out;
}

struct footballerType generateFootballer() {
  struct footballerType out = {
    .fullName=generateString(2, 1),
    .clubName=generateString(2, 1),
    .role=generateString(2, 1),
    .age=(rand() % 50),
    .numberOfGames=(rand() % 50),
    .numberOfGoals=(rand() % 50),
  };

  return out;
}

struct footballerType* generateFootballersArray(int length) {
  struct footballerType* arr = (struct footballerType*)malloc(sizeof(struct footballerType) * length);
  
  for (int i = 0; i < length; i++) {
    arr[i] = generateFootballer();
  }

  return arr;
}

int compareFootballers(struct footballerType footballer1, struct footballerType footballer2, int direction) {
  int cmpFullNames = strcmp(footballer1.fullName, footballer2.fullName);

  if (cmpFullNames != 0) {
    return direction * cmpFullNames;    
  }

  int cmpClubNames = strcmp(footballer1.clubName, footballer2.clubName);

  if (cmpClubNames != 0) {
    return direction * cmpClubNames;    
  }

  int cmpRole = strcmp(footballer1.role, footballer2.role);

  if (cmpRole != 0) {
    return direction * cmpRole;    
  }

  if (footballer1.age != footballer2.age) {
    return direction * (footballer1.age - footballer2.age);
  }

  if (footballer1.numberOfGames != footballer2.numberOfGames) {
    return direction * (footballer1.numberOfGames - footballer2.numberOfGames);
  }
  if (footballer1.numberOfGoals != footballer2.numberOfGoals) {
    return direction * (footballer1.numberOfGoals - footballer2.numberOfGoals);
  }
}

void bubbleSort(struct footballerType* arr, int n, char direction) {
  struct footballerType tmp;

  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < i; j++) {
      if (compareFootballers(arr[j], arr[j + 1], direction) > 0) {
        tmp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = tmp;
      }
    }
  }

  printf("Successfully bubble sort.\n");
}

void insertSort(struct footballerType* arr, int n, char direction) {
  int j;
  struct footballerType tmp;

  for (int i = 1; i < n; i++) {
    tmp = arr[i];

    for (j = i - 1; j >= 0 && compareFootballers(arr[j], tmp, direction) > 0; j--) {
      arr[j + 1] = arr[j];
    }

    arr[j + 1] = tmp;
  }

  printf("Successfully insert sort.\n");
}

void shakerSort(struct footballerType* arr, int n, char direction) {
  struct footballerType tmp;
  int  l = 1, r = n;
  int j;

  do {
    for(j = --r; j >= l; j--) {
      if (compareFootballers(arr[j - 1], arr[j], direction) > 0) {
        tmp = arr[j - 1];
        arr[j - 1] = arr[j];
        arr[j] = tmp;
      }
    }

    for (j = ++l; j <= r; j++) {
      if (compareFootballers(arr[j - 1], arr[j], direction) > 0) {
        tmp = arr[j - 1];
        arr[j - 1] = arr[j];
        arr[j] = tmp;
      }
    }
  } while (l < r);

  printf("Successfully shaker sort.\n");
}

void merge(struct footballerType* arr, int l, int m, int r, char direction) {
  int i = l;
  int j = m + 1;
  int k = 0;

  struct footballerType* tmp = (struct footballerType*)malloc(sizeof(struct footballerType) * (r - l + 1));

  while (i <= m && j <= r) {
    if (compareFootballers(arr[i], arr[j], direction) >= 0) {
      tmp[k] = arr[j];
      j++;
    } else {
      tmp[k] = arr[i];
      i++;
    }

    k++;
  }

  if (i > m) {
    while (j <= r) {
      tmp[k] = arr[j];

      j++;
      k++;
    }
  } else {
    while (i <= m) {
      tmp[k] = arr[i];

      i++;
      k++;
    }
  }

  for (k = 0; k <= r - l; k++) {
    arr[l + k] = tmp[k];
  };

  free(tmp);
}

void splitAndMerge(struct footballerType* arr, int l, int r, char direction) {
  if (l < r) {
    int m = (l + r) / 2;
    splitAndMerge(arr, l, m, direction);
    splitAndMerge(arr, m + 1, r, direction);
    merge(arr, l, m, r, direction);
  }
}

void mergeSort(struct footballerType* arr, int n, char direction) {
  splitAndMerge(arr, 0, n - 1, direction);
  printf("Successfully merge sort.\n");
}

int main() {
  srand(time(NULL)); // Init first random number.

  int n = 10;
  struct footballerType* arr = generateFootballersArray(n);

  printFootballers(arr, n);
  mergeSort(arr, n, -1);
  printFootballers(arr, n);

  return 0;
}