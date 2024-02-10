#include "football.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "footbaler.bin"
#define INPUT_TYPE 'a'
#define maxNumberOfFilesElements 66

int getMatrixFromBinaryFile(char *fileName, char *matrix[maxNumberOfFilesElements]) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File with name %s could not be open for reading.\n", fileName);
    return -1;
  }

  int i = 0;

  while (!feof(f)) {
    fread(matrix[i], sByteSize, 1, f);
    i++;
  }

  fclose(f);

  return i;
}

void createBinaryFile(char *fileName, struct footballerType footballer) {
  FILE *f = fopen(fileName, "wb");

  if (!f) {
    printf("File with name %s could not be open for write.\n", fileName);
    return;
  }

  fwrite(&footballer.fullName, sByteSize, 1, f);
  fwrite(&footballer.clubName, sByteSize, 1, f);
  fwrite(&footballer.role, sByteSize, 1, f);
  fwrite(&footballer.age, sByteSize, 1, f);
  fwrite(&footballer.numberOfGames, sByteSize, 1, f);
  fwrite(&footballer.numberOfGoals, sByteSize, 1, f);

  fclose(f);
}

void appendToBinaryFile(char *fileName, char entry[sLength]) {
  FILE *f = fopen(fileName, "ab");

  if (!f) {
    printf("File with name %s could not be open for write.\n", fileName);
    return;
  }

  fwrite(entry, sByteSize, 1, f);
  fclose(f);
}

void deleteRowFromMatrix(char *matrix[maxNumberOfFilesElements], int rowsCount, int rowI) {
  for (int i = rowI; i < rowsCount - 1; i++) {
    matrix[i] = matrix[i + 1];
  }
}

void updateRowInMatrix(char *matrix[maxNumberOfFilesElements], int rowI, char newEntry[sLength]) {
  matrix[rowI] = newEntry;
}

void deleteFromBinaryFile(char *fileName, int entryNumber) {
  char *footballers[maxNumberOfFilesElements];
  for (int i = 0; i < 66; i++) {
    footballers[i] = (char*)malloc(sLength * sizeof(char));
  }

  int numberOfFilesElements = getMatrixFromBinaryFile(FILE_NAME, footballers);
  
  deleteRowFromMatrix(footballers, numberOfFilesElements, entryNumber);

  FILE *f = fopen(fileName, "wb");

  if (!f) {
    printf("File with name %s could not be open for changes.\n", fileName);
    return;
  }

  for (int j = 0; j < numberOfFilesElements - 1; j++) {
    fwrite(footballers[j], sByteSize, 1, f);
  }

  fclose(f);

  for (int i = 0; i < maxNumberOfFilesElements; i++) {
    free(footballers[i]);
  }

  printf("Successfully deleted element from binary file.");
}

void findInBinaryFile(char *fileName, int entryNumber) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File with name %s could not be open for reading.\n", fileName);
    return;
  }

  char entry[sLength];

  fseek(f, entryNumber * sByteSize, SEEK_SET);
  fread(&entry, sByteSize, 1, f);

  printf("\nFind element: %s\n", entry);
}

void updateInBinaryFile(char *fileName, int entryNumber, char newEntry[sLength]) {
  char *footballers[maxNumberOfFilesElements];
  for (int i = 0; i < 66; i++) {
    footballers[i] = (char*)malloc(sLength * sizeof(char));
  }

  int numberOfFilesElements = getMatrixFromBinaryFile(FILE_NAME, footballers);
  
  updateRowInMatrix(footballers, entryNumber, newEntry);

  FILE *f = fopen(fileName, "wb");

  if (!f) {
    printf("File with name %s could not be open for changes.\n", fileName);
    return;
  }

  for (int j = 0; j < numberOfFilesElements; j++) {
    fwrite(footballers[j], sByteSize, 1, f);
  }

  fclose(f);

  for (int i = 0; i < maxNumberOfFilesElements; i++) {
    free(footballers[i]);
  }

  printf("Successfully updated element in binary file.");
}

void printBinaryFile(char *fileName) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File isn't valid for printing.\n");
    return;
  }

  char row[sLength];
  unsigned num;

  printf("\nPrint binary file:\n");

  fread(row, sByteSize, 1, f);
  while (!feof(f)) {
    printf("%s\n", row);
    fread(row, sByteSize, 1, f);
  }

  fclose(f);
} 

int main() {
  #if INPUT_TYPE == 'u'
  printf("User input.\n");

  struct footballerType footballer;

  printf("Enter full name: ");
  fgets(footballer.fullName, sLength, stdin);
  footballer.fullName[strcspn(footballer.fullName, "\n")] = 0;

  printf("Enter club name: ");
  fgets(footballer.clubName, sLength, stdin);
  footballer.clubName[strcspn(footballer.clubName, "\n")] = 0;

  printf("Enter role: ");
  fgets(footballer.role, sLength, stdin);
  footballer.role[strcspn(footballer.role, "\n")] = 0;

  printf("Enter age: ");
  scanf("%d", &footballer.age);

  printf("Enter number of games: ");
  scanf("%d", &footballer.numberOfGames);

  printf("Enter count of goals: ");
  scanf("%d", &footballer.numberOfGoals);

  #else
  printf("Input from array.\n");

  struct footballerType footballer = {
    .fullName="Keyer Alexander Petrovich",
    .clubName="BAM231",
    .role="Goalkeeper",
    .age="1",
    .numberOfGames="2",
    .numberOfGoals="3",
  };
  #endif

  createBinaryFile(FILE_NAME, footballer);

  appendToBinaryFile(FILE_NAME, "Kachmazov Alexander");
  appendToBinaryFile(FILE_NAME, "Innopolis");
  appendToBinaryFile(FILE_NAME, "Guardian");
  appendToBinaryFile(FILE_NAME, "4");
  appendToBinaryFile(FILE_NAME, "5");
  appendToBinaryFile(FILE_NAME, "6");

  printBinaryFile(FILE_NAME);

  findInBinaryFile(FILE_NAME, 2);
  deleteFromBinaryFile(FILE_NAME, 2);
  findInBinaryFile(FILE_NAME, 2);

  findInBinaryFile(FILE_NAME, 1);
  updateInBinaryFile(FILE_NAME, 1, "Innopolis");
  findInBinaryFile(FILE_NAME, 1);

  return 0;
}