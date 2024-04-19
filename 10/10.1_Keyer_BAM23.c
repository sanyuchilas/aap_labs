#include <stdio.h> // Input/output library.
#include <stdlib.h> // Memory allocation.
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

void printPList(PList* pListP) {
  PListItem* cur = pListP->headP;

  if (cur == NULL) {
    printf("unfortunately this polynomial list is incorrect or empty =(\n");
  }

  char tmp = '+';

  while (cur != NULL) {
    if (cur->valueP->a < 0) {
      tmp = 0;
    } else {
      tmp = '+';
    }

    printf("%c%ldx^%ld", tmp, cur->valueP->a, cur->valueP->n);

    cur = cur->nextP;
  }
}

PList* parsePStringToPList(char* pStringP) {
  PList* out = (PList*)malloc(sizeof(PList));
  out->headP = (PListItem*)malloc(sizeof(PListItem));

  if (pStringP[0] == 0) {
    out->headP = NULL;
    return out;
  }

  PListItem* cur = (PListItem*)malloc(sizeof(PListItem));
  out->headP = cur;
  cur->valueP = (M*)malloc(sizeof(M));

  char placeholderP[100] = "";

  for (int i = 0; pStringP[i] != 0; i++) {
    if (pStringP[i] == ' ') {
      continue;
    }

    if ((pStringP[i] == '+' || pStringP[i] == '-') && placeholderP[0] != 0) {
      cur->valueP->n = parseStringToLongInt(placeholderP);

      cur->nextP = (PListItem*)malloc(sizeof(PListItem));
      cur = cur->nextP;
      cur->valueP = (M*)malloc(sizeof(M));

      placeholderP[0] = placeholderP[i];
      placeholderP[1] = 0;
    }

    if (pStringP[i] == 'x') {
      cur->valueP->a = parseStringToLongInt(placeholderP);
      assert(cur->valueP->a != 0);
      
      placeholderP[0] = 0;
    }

    if (pStringP[i] <= '9' && pStringP[i] >= '0') {
      placeholderP[strlen(placeholderP) + 1] = 0;
      placeholderP[strlen(placeholderP)] = pStringP[i];
    } else if (
      pStringP[i] != 'x'
      && pStringP[i] != '+'
      && pStringP[i] != '-'
      && pStringP[i] != '^'
    ) {
      out->headP = NULL;
      return out;
    }
  }

  cur->valueP->n = parseStringToLongInt(placeholderP);
  cur->nextP = NULL;

  return out;
}

PList* mixTwoPLists(PList* pListP1, PList* pListP2) {
  PList* out;

  PListItem* cur1 = pListP1->headP;
  PListItem* cur2 = pListP2->headP;

  PListItem* curGood = NULL;
  PListItem* prevGood = NULL;

  out->headP = NULL;

  while (cur1 != NULL) {
    cur2 = pListP2->headP;

    while (cur2 != NULL && cur2->valueP->n != cur1->valueP->n) {
      cur2 = cur2->nextP;
    }

    if (cur2 != NULL) {
      if (cur2->valueP->a >= cur1->valueP->a) {
        curGood = cur2;
      } else {
        curGood = cur1;
      }

      if (out->headP == NULL) {
        out->headP = curGood;
      } else {
        prevGood->nextP = curGood;
      }

      prevGood = curGood;
    }

    cur1 = cur1->nextP;
  }

  return out;
};

PList* mixTwoPStrings(char* pStringP1, char* pStringP2) {
  return mixTwoPLists(
    parsePStringToPList(pStringP1),
    parsePStringToPList(pStringP2)
  );
}

void readPStringFromUser(int pi, char* pStringP) {
  printf("Enter P%d: ", pi);

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

  printf("Polynomials mixin: ");
  printPList(mixTwoPStrings(pStringP1, pStringP2));

  free(pStringP1);
  free(pStringP2);

  return 0;
}