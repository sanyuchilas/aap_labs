#include <stdio.h> // Input/output library.
#include <stdlib.h> // Memory allocation.
#include <assert.h> // Assertion library.
#include <string.h> // String functions library.

// Useful directives for string tokens.
#define separator ' '
#define endToken '.'

// Function validating a string.
void isSValid(char* s) {
    // Checking string for incorrect symbols.
    for (int i = 0; s[i] != 0; i++) {
        if (s[i] < 'a' || s[i] > 'b') {
            printf("The string contains incorrect symbols.\n");
            assert(s[i] >= 'a' && s[i] <= 'z');
        }
    }
}

// Function reading a string from stdin.
int readingStringFromUser() {
  printf("Please, enter correct string:\n");

  char* s = (char*)malloc(sizeof(char) * 100);

  fflush(stdin);
  fgets(s, 100, stdin);
  s[strcspn(s, endToken)] = 0;

  return s;
}

int main() {
    char* s = readingStringFromUser();
    isSValid(s);

    printf("Work with string: %s", s);

    free(s);
}