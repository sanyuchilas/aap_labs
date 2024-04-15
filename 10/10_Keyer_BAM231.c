#include <stdio.h> // Input/output library.
#include <stdlib.h> // Memory allocation.
#include <time.h> // Time library.
#include <assert.h> // Assertion library.
#include <string.h> // String functions library.

struct M {
  long a;
  unsigned n;
};
typedef struct M M;

struct PListItem {
  struct M* valueP;
  struct PListItem* nextP;
};
typedef struct PListItem PListItem;

struct PList {
  PListItem* headP;
};
typedef struct PList PList;

long parseStringToLongInt(char* s) {
  long out = 0;
  int placeholder10 = 1;
  int sLength = strlen(s);
  int k = 1;

  if (s[0] == '-') {
    k = -1;
  }

  for (int i = sLength - 1; i >= 0; i--) {
    if (s[i] == ' ' || s[i] < '0' || s[i] > '9') {
      continue;
    }

    out += k * placeholder10 * (s[i] - '0');
    placeholder10 *= 10;
  }

  return out;
}

char* parsePListToPString(PList* pListP) {
  char* out = (char*)malloc(2 * sizeof(char));

  if (pListP == NULL) {
    out = NULL;
    return out;
  }

  PListItem* cur = pListP->headP, *prev = NULL;

  while (cur->nextP != NULL) {
    // out
  }

  return out;
}

PList* parsePStringToPList(char* pStringP) {
  PList* out = (PList*)malloc(sizeof(PList));
  out->headP = (PListItem*)malloc(sizeof(PListItem));

  PListItem* cur = out->headP;

  char placeholderP[100] = "";

  for (int i = 0; pStringP[i] != 0; i++) {
    if (pStringP[i] == ' ') {
      continue;
    }

    if (pStringP[i] == '+' || pStringP[i] == '-') {
      if (placeholderP[0] != 0) {
        cur->valueP->n = parseStringToLongInt(placeholderP);
        cur = (PListItem*)malloc(sizeof(PListItem));

        placeholderP[0] = placeholderP[i];
        placeholderP[1] = 0;
      }
    }

    if (pStringP[i] == 'x') {
      if (placeholderP[0] != 0) {
        cur->valueP->a = parseStringToLongInt(placeholderP);
        placeholderP[0] = 0;
      }
    }

    if (pStringP[i] <= '9' && pStringP[i] >= '0') {
      placeholderP[strlen(placeholderP) + 1] = 0;
      placeholderP[strlen(placeholderP)] = pStringP[i];
    }
  }
}

void printPList(PList* PListP) {
  printf("%s", parsePListToPString(PListP));
};

PList* mixTwoPLists(PList* pListP1, PList* pListP2) {

};

char* mixTwoPStrings(char* pStringP1, char* pStringP2) {
  return parsePListToPString(mixTwoPLists(
    parsePStringToPList(pStringP1),
    parsePStringToPList(pStringP2)
  ));
}

void readPStringFromUser(int pi, char* pStringP) {
  printf("Enter P%d:", pi);

  fflush(stdin);
  fgets(pStringP, 100, stdin);
  pStringP[strcspn(pStringP, "\n")] = 0;
}

int main() {
  char* pStringP1 = malloc(100 * sizeof(char));
  char* pStringP2 = malloc(100 * sizeof(char));

  printf("Lab 10. Keyer, BAM231.\n");

  readPStringFromUser(1, pStringP1);
  readPStringFromUser(2, pStringP2);

  PList* pListP1 = parsePStringToPList(pStringP1);

  printf("%d", pListP1->headP->valueP->a);

  // printf("Polynomials mixin: %s\n", mixTwoPStrings(pStringP1, pStringP2));

  free(pStringP1);
  free(pStringP2);

  return 0;
}