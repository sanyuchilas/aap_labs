#include "football.h" // Footballer info.

#include <stdio.h> // Input/output library.
#include <stdlib.h> // Memory allocation.
#include <time.h> // Time library.
#include <assert.h> // Assertion library.

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

int main() {
  srand(time(NULL)); // Init first random number.

  int n = 1000;
  struct footballerType* arr = generateFootballersArray(n);

  printFootballers(arr, n);

  return 0;
}