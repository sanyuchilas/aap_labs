#include <stdio.h> // Input/output library.
#include <stdlib.h> // Memory allocation.
#include <assert.h> // Assertion library.
#include <string.h> // String functions library.

// Function validating a string.
void isValid(char* s) {
    for (int i = 0; s[i] != 0; i++) {
        if (s[i] < 'a' || s[i] > 'z') {
            printf("String contains incorrect symbol: %c.\n", s[i]);
            assert(s[i] >= 'a' || s[i] <= 'z');
        }
    }
}

// Function reading a string from stdin.
char* readingStringFromUser() {
  printf("Please, enter correct string: ");

  char* s = (char*)malloc(sizeof(char) * 100);

  fflush(stdin);
  fgets(s, 100, stdin);
  s[strcspn(s, "\n")] = 0;
  s[strcspn(s, ".")] = 0;

  return s;
}

int main() {
    char* s = readingStringFromUser();
    isValid(s);

    printf("Work with string: %s", s);

    

    free(s);
}