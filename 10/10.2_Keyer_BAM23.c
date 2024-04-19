#include <stdio.h> // Input/output library.
#include <stdlib.h> // Memory allocation.
#include <string.h> // String functions library.

struct WordListItem {
    char* valueP;
    struct WordListItem* nextP;
    struct WordListItem* prevP;
};
typedef struct WordListItem WordListItem;

struct WordList {
    WordListItem* headP;
};
typedef struct WordList WordList;

// Function validating a string.
int isValid(char* s) {
    for (int i = 0; s[i] != 0; i++) {
        if ((s[i] < 'a' || s[i] > 'z') && s[i] != ' ' && s[i] != '.') {
            printf("String contains incorrect symbol: %c\n", s[i]);
            return 0;
        }
    }

    return 1;
}

WordList* parseStringToWordList(char* s) {
    WordList* out = (WordList*)malloc(sizeof(WordList));

    WordListItem* cur = (WordListItem*)malloc(sizeof(WordListItem));
    out->headP = cur;
    WordListItem* prev = NULL;

    cur->valueP = (char*)malloc(sizeof(char) * 100);
    cur->valueP[0] = 0;
    cur->prevP = NULL;

    printf("Parse WordList to string: ");

    for (int i = 0; s[i] != 0; i++) {
        if (s[i] != ' ') {
            cur->valueP[strlen(cur->valueP) + 1] = 0;
            cur->valueP[strlen(cur->valueP)] = s[i];
        } else {
            prev = cur;

            cur->nextP = (WordListItem*)malloc(sizeof(WordListItem));
            cur = cur->nextP;

            cur->prevP = prev;
            cur->valueP = (char*)malloc(sizeof(char) * 100);
            cur->valueP[0] = 0;
        }
    }

    cur->prevP = prev;
    cur->nextP = NULL;

    return out;
};

void printWordList(WordList* wordList) {
    if (wordList->headP == NULL) {
        printf("Incorrect word list was input");
        return;
    }

    WordListItem* cur = wordList->headP;

    printf("%s", cur->valueP);
    cur = cur->nextP;

    while (cur != NULL) {
        printf(" %s", cur->valueP);
        cur = cur->nextP;
    }

    printf(".");
};

// Function reading a string from stdin.
char* readingStringFromUser() {
  printf("Please, enter correct string: ");

  char* s = (char*)malloc(sizeof(char) * 100);

  fflush(stdin);
  fgets(s, 100, stdin);
  s[strcspn(s, "\n")] = 0;
  s[strcspn(s, ".")] = 0;

  return s;
};

int main() {
    char* s = readingStringFromUser();
    if (!isValid(s)) {
        return 1;
    }

    printf("Work with string: %s.\n", s);
    printWordList(parseStringToWordList(s));

    free(s);
    return 0;
};