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

  printf("\n");
}

PListItem* findWithSameN(PList* pList, int n) {
  PListItem* cur = pList->headP;

  while (cur != NULL) {
    if (cur->valueP->n == n) {
      return cur;
    }

    cur = cur->nextP;
  }

  return NULL;
}

PListItem* clearPListItem(PListItem* pListItem) {
  PListItem* nextP = pListItem->nextP;

  free(pListItem->valueP);
  free(pListItem);

  return nextP;
}

PList* clearPList(PList* pList) {
  PListItem* cur = pList->headP;

  while (cur != NULL) {
    cur = clearPListItem(cur);
  }

  free(pList);
  pList = NULL;

  return pList;
}

void clearMonomWithA0(PList* pList) {
  PListItem* cur = pList->headP->nextP;
  PListItem* prev = pList->headP;

  while (cur != NULL) {
    if (cur->valueP->a == 0) {
      prev->nextP = cur->nextP;
      clearPListItem(cur);
    } else {
      prev = prev->nextP;
    }

    cur = prev->nextP;
  }

  if (pList->headP->valueP->a == 0) {
    cur = pList->headP;
    pList->headP = pList->headP->nextP;
    clearPListItem(cur);
  }
}

PList* parsePStringToPList(char* pStringP) {
  PList* out = (PList*)malloc(sizeof(PList));
  out->headP = (PListItem*)malloc(sizeof(PListItem));
  out->headP = NULL;

  if (pStringP[0] == 0) {
    return out;
  }

  PListItem* sameNCandidate = NULL;
  PListItem* prev = NULL;
  PListItem* cur = (PListItem*)malloc(sizeof(PListItem));
  cur->valueP = (M*)malloc(sizeof(M));
  cur->nextP = NULL;

  char placeholderP[100] = "";

  for (int i = 0; pStringP[i] != 0; i++) {
    if (pStringP[i] == ' ') {
      continue;
    }

    if ((pStringP[i] == '+' || pStringP[i] == '-')) {
      if (placeholderP[0] != 0) {
        cur->valueP->n = parseStringToLongInt(placeholderP);

        PListItem* sameNCandidate = findWithSameN(out, cur->valueP->n);

        if (sameNCandidate == NULL) {
          if (out->headP == NULL) {
            out->headP = cur;
          } else {
            prev->nextP = cur;
          }

          prev = cur;
        } else {
          sameNCandidate->valueP->a += cur->valueP->a;
          clearPListItem(cur);
        }

        cur = (PListItem*)malloc(sizeof(PListItem));
        cur->valueP = (M*)malloc(sizeof(M));
        cur->nextP = NULL;
      }

      placeholderP[0] = pStringP[i];
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

  sameNCandidate = findWithSameN(out, cur->valueP->n);

  if (sameNCandidate == NULL) {
    if (out->headP == NULL) {
      out->headP = cur;
    } else {
      prev->nextP = cur;
    }
  } else {
    sameNCandidate->valueP->a += cur->valueP->a;
    clearPListItem(cur);
  }

  clearMonomWithA0(out);

  return out;
}

void copyPListItem(PListItem* new, PListItem* cur) {
  new->nextP = NULL;
  new->valueP->a = cur->valueP->a;
  new->valueP->n = cur->valueP->n;
}

PList* mixTwoPLists(PList* pListP1, PList* pListP2) {
  PList* out = (PList*)malloc(sizeof(PList));

  PListItem* cur1 = pListP1->headP;
  PListItem* cur2 = pListP2->headP;

  PListItem* prevGood = NULL;

  out->headP = NULL;

  while (cur1 != NULL) {
    cur2 = pListP2->headP;

    while (cur2 != NULL && cur2->valueP->n != cur1->valueP->n) {
      cur2 = cur2->nextP;
    }

    if (cur2 != NULL) {
      PListItem* curGood = (PListItem*)malloc(sizeof(PListItem));
      curGood->valueP = (M*)malloc(sizeof(M));

      if (cur2->valueP->a >= cur1->valueP->a) {
        copyPListItem(curGood, cur2);
      } else {
        copyPListItem(curGood, cur1);
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

void readPStringFromUser(int pi, char* pStringP) {
  printf("Enter P%d: ", pi);

  fflush(stdin);
  fgets(pStringP, 100, stdin);
  pStringP[strcspn(pStringP, "\n")] = 0;
}

int main() {
  char* pStringP1 = (char*)malloc(100 * sizeof(char));
  char* pStringP2 = (char*)malloc(100 * sizeof(char));

  printf("Lab 10. Keyer, BAM231.\n");

  readPStringFromUser(1, pStringP1);
  readPStringFromUser(2, pStringP2);
  
  PList* pListP1 = parsePStringToPList(pStringP1);
  PList* pListP2 = parsePStringToPList(pStringP2);

  printPList(pListP1);
  printPList(pListP2);

  PList* finalPList = mixTwoPLists(pListP1, pListP2);
  
  printf("Polynomials mixin: ");
  printPList(finalPList);


  clearPList(pListP1);
  clearPList(pListP2);
  clearPList(finalPList);

  finalPList->headP = NULL;

  free(pStringP1);
  free(pStringP2);

  return 0;
}