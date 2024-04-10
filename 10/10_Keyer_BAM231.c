#include <stdio.h> // Input/output library.
#include <stdlib.h> // Memory allocation.
#include <time.h> // Time library.
#include <assert.h> // Assertion library.
#include <string.h> // String functions library.

struct M {
  int a;
  unsigned n;
};
typedef struct M M;

struct PListItem {
  struct M* valueP;
  struct PListItem* nextP;
};
typedef PListItem PListItem;

struct PList {
  PListItem* headP;
};
typedef struct PList PList;

char* parsePListToPString(PList* pListP) {

}

PList* parsePStringToPList(char* pStringP) {
  
}

void printPList(PList* PListP) {
  printf("%s", parsePListToPString(PListP));
};

PList* mixTwoPLists(PList* pListP1, PList* pListP2) {

};

char* mixTwoPStrings(PList* pStringP1, PList* pStringP2) {
  return parsePListToPString(mixTwoPLists(
    parsePStringToPList(pStringP1),
    parsePStringToPList(pStringP2)
  ));
}

void readPStringFromUser(char* pStringP) {

}

int main() {
  char* pStringP1;
  char* pStringP2;

  printf("Lab 10. Keyer, BAM231.\n");

  readPStringFromUser(pStringP1);
  readPStringFromUser(pStringP2);

  printf("Polynomials mixin: %s\n", mixTwoPStrings(pStringP1, pStringP2));  

  return 0;
}