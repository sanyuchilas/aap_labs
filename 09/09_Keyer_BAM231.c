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
    .fullName=generateString(2, 26),
    .clubName=generateString(2, 26),
    .role=generateString(2, 26),
    .age=(rand() % 100),
    .numberOfGames=(rand() % 100),
    .numberOfGoals=(rand() % 100),
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
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < i; j++) {
      if (compareFootballers(arr[j], arr[j + 1], direction) > 0) {
        struct footballerType tmp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = tmp;
      }
    }
  }

  printf("Successfully bubble sort.\n");
}

int main() {
  srand(time(NULL)); // Init first random number.

  int n = 10;
  struct footballerType* arr = generateFootballersArray(n);

  printFootballers(arr, n);
  // bubbleSort(arr, n, 1);
  // printFootballers(arr, n);

  return 0;
}