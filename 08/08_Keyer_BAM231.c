#include "football.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>

#define FILE_NAME "footbaler.bin"
#define INPUT_TYPE 'a'

void printEntry(struct footballerType entry) {
  printf("%s, %s, %s, %d, %d, %d\n", entry.fullName, entry.clubName, entry.role, entry.age, entry.numberOfGames, entry.numberOfGoals);
}

int getFileLength(FILE *f) {
  fseek(f, 0, SEEK_END);
  int fileLength = ftell(f) / sizeof(struct footballerType);
  fseek(f, 0, SEEK_SET);

  return fileLength;
}

void createBinaryFile(char *fileName, struct footballerType entry) {
  FILE *f = fopen(fileName, "wb");

  if (!f) {
    printf("File with name %s could not be open for write.\n", fileName);
    return;
  }

  fwrite(&entry, sizeof(struct footballerType), 1, f);
  fclose(f);
}

void appendEntry(char *fileName, struct footballerType entry) {
  FILE *f = fopen(fileName, "ab");

  if (!f) {
    printf("File with name %s could not be open for write.\n", fileName);
    return;
  }

  fwrite(&entry, sizeof(struct footballerType), 1, f);
  fclose(f);
}

void deleteEntryById(char *fileName, int entryId) {
  FILE *f = fopen(fileName, "r+b");

  if (!f) {
    printf("File with name %s could not be open for changes.\n", fileName);
    return;
  }

  int fileLength = getFileLength(f);

  struct footballerType tmpEntry;
  struct footballerType deletedEntry;

  if (entryId >= fileLength) {
    printf("Couldn't delete entry.\n");
    return;
  }
  
  fseek(f, entryId * sizeof(struct footballerType), SEEK_SET);
  fread(&deletedEntry, sizeof(struct footballerType), 1, f);

  for (int i = entryId + 1; i < fileLength; i++) {
    fread(&tmpEntry, sizeof(struct footballerType), 1, f);
    fseek(f, (i - 1) * sizeof(struct footballerType), SEEK_SET);
    fwrite(&tmpEntry, sizeof(struct footballerType), 1, f);
    fseek(f, (i + 1) * sizeof(struct footballerType), SEEK_SET);
  }

  _chsize(_fileno(f), (fileLength - 1) * sizeof(struct footballerType));
  fclose(f);
  printf("Successfully deleted '%s' from binary file.\n", deletedEntry.fullName);
}

void findAllEntriesByFullName(char *fileName, char fieldValue[fieldLength]) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File with name %s could not be open for reading.\n", fileName);
    return;
  }

  printf("\nFound all entries by full name '%s':\n", fieldValue);

  struct footballerType entry;
  int fileLength = getFileLength(f);
  int entriesCount = 0;

  for (int i = 0; i < fileLength; i++) {
    fread(&entry, sizeof(struct footballerType), 1, f);
    
    if (!strcmp(entry.fullName, fieldValue)) {
      printEntry(entry);
      entriesCount++;
    }
  }

  if (entriesCount == 0) {
    printf("No entries were found.\n");
  }

  printf("\n");
  fclose(f);
}

void findAllEntriesByClubName(char *fileName, char fieldValue[fieldLength]) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File with name %s could not be open for reading.\n", fileName);
    return;
  }

  printf("\nFound all entries by club name '%s':\n", fieldValue);

  struct footballerType entry;
  int fileLength = getFileLength(f);
  int entriesCount = 0;

  for (int i = 0; i < fileLength; i++) {
    fread(&entry, sizeof(struct footballerType), 1, f);
    
    if (!strcmp(entry.clubName, fieldValue)) {
      printEntry(entry);
      entriesCount++;
    }
  }

  if (entriesCount == 0) {
    printf("No entries were found.\n");
  }

  printf("\n");
  fclose(f);
}

void findAllEntriesByRole(char *fileName, char fieldValue[fieldLength]) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File with name %s could not be open for reading.\n", fileName);
    return;
  }

  printf("\nFound all entries by role '%s':\n", fieldValue);

  struct footballerType entry;
  int fileLength = getFileLength(f);
  int entriesCount = 0;

  for (int i = 0; i < fileLength; i++) {
    fread(&entry, sizeof(struct footballerType), 1, f);
    
    if (!strcmp(entry.role, fieldValue)) {
      printEntry(entry);
      entriesCount++;
    }
  }

  if (entriesCount == 0) {
    printf("No entries were found.\n");
  }

  printf("\n");
  fclose(f);
}

void findAllEntriesByAge(char *fileName, int fieldValue) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File with name %s could not be open for reading.\n", fileName);
    return;
  }

  printf("\nFound all entries by age '%d':\n", fieldValue);

  struct footballerType entry;
  int fileLength = getFileLength(f);
  int entriesCount = 0;

  for (int i = 0; i < fileLength; i++) {
    fread(&entry, sizeof(struct footballerType), 1, f);
    
    if (entry.age == fieldValue) {
      printEntry(entry);
      entriesCount++;
    }
  }

  if (entriesCount == 0) {
    printf("No entries were found.\n");
  }

  printf("\n");
  fclose(f);
}

void findAllEntriesByNumberOfGames(char *fileName, int fieldValue) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File with name %s could not be open for reading.\n", fileName);
    return;
  }

  printf("\nFound all entries by number of games '%d':\n", fieldValue);

  struct footballerType entry;
  int fileLength = getFileLength(f);
  int entriesCount = 0;

  for (int i = 0; i < fileLength; i++) {
    fread(&entry, sizeof(struct footballerType), 1, f);
    
    if (entry.numberOfGames == fieldValue) {
      printEntry(entry);
      entriesCount++;
    }
  }

  if (entriesCount == 0) {
    printf("No entries were found.\n");
  }

  printf("\n");
  fclose(f);
}

void findAllEntriesByNumberOfGoals(char *fileName, int fieldValue) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File with name %s could not be open for reading.\n", fileName);
    return;
  }

  printf("\nFound all entries by number of goals '%d':\n", fieldValue);

  struct footballerType entry;
  int fileLength = getFileLength(f);
  int entriesCount = 0;

  for (int i = 0; i < fileLength; i++) {
    fread(&entry, sizeof(struct footballerType), 1, f);
    
    if (entry.numberOfGoals == fieldValue) {
      printEntry(entry);
      entriesCount++;
    }
  }

  if (entriesCount == 0) {
    printf("No entries were found.\n");
  }

  fclose(f);
  printf("\n");
}

void updateEntryById(char *fileName, int entryId, struct footballerType newEntry) {
  FILE *f = fopen(fileName, "r+b");

  if (!f) {
    printf("File with name %s could not be open for changes.\n", fileName);
    return;
  }

  fseek(f, entryId * sizeof(struct footballerType), SEEK_SET);
  fwrite(&newEntry, sizeof(struct footballerType), 1, f);

  fclose(f);
  printf("\nSuccessfully updated entry '%d':\n", entryId);
}

void printBinaryFile(char *fileName) {
  FILE *f = fopen(fileName, "rb");

  if (!f) {
    printf("File isn't valid for printing.\n");
    return;
  }

  printf("\nPrint binary file:\n");

  struct footballerType entry;

  fread(&entry, sizeof(struct footballerType), 1, f);
  
  while (!feof(f)) {
    printEntry(entry);
    fread(&entry, sizeof(struct footballerType), 1, f);
  }

  fclose(f);
}

void printMainOperationsList() {
  printf("\n");
  printf("%30s %3s", "append entry:", "1\n");
  printf("%30s %3s", "delete entry:", "2\n");
  printf("%30s %3s", "find all entries by:", "3\n");
  printf("%30s %3s", "update entry:", "4\n");
  printf("%30s %3s", "print database:", "5\n");
  printf("\n\n");
}

void startMenu() {
  printf("\n");
  printMainOperationsList();
  printf("Enter correct operation code: ");

  char operationCode = '0';

  scanf("%c", &operationCode);

  if (operationCode <= 48 || operationCode > 53) {
    fflush(stdin);
    startMenu();
    return;
  }

  switch (operationCode) {
    case '1':
      break;

    case '2':
      break;

    case '3':
      break;

    case '4':
      break;
      
    case '5':
      break;
  }

  printf("\n");
  // startMenu();
}

int main() {
  #if INPUT_TYPE == 'u'
  printf("User input.\n");

  struct footballerType footballer;

  printf("Enter full name: ");
  fgets(footballer.fullName, fieldLength, stdin);
  footballer.fullName[strcspn(footballer.fullName, "\n")] = 0;

  printf("Enter club name: ");
  fgets(footballer.clubName, fieldLength, stdin);
  footballer.clubName[strcspn(footballer.clubName, "\n")] = 0;

  printf("Enter role: ");
  fgets(footballer.role, fieldLength, stdin);
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
    .age=1,
    .numberOfGames=2,
    .numberOfGoals=3,
  };
  #endif

  createBinaryFile(FILE_NAME, footballer);

   struct footballerType alex = {
    .fullName="Kachmazov Alex Volphram",
    .clubName="Innopolis",
    .role="Guardian",
    .age=4,
    .numberOfGames=5,
    .numberOfGoals=6,
  };

   struct footballerType igor = {
    .fullName="Kuzmenkov Igor Druid",
    .clubName="Innopolis",
    .role="Goalkeeper",
    .age=1,
    .numberOfGames=5,
    .numberOfGoals=3,
  };

  appendEntry(FILE_NAME, alex);
  appendEntry(FILE_NAME, igor);

  // findAllEntriesByFullName(FILE_NAME, "Keyer Alexander Petrovich");
  // findAllEntriesByClubName(FILE_NAME, "sfdsfh");
  // findAllEntriesByRole(FILE_NAME, "Goalkeeper");
  // findAllEntriesByAge(FILE_NAME, 1);
  // findAllEntriesByNumberOfGames(FILE_NAME, 5);
  // findAllEntriesByNumberOfGoals(FILE_NAME, 3);

  // printBinaryFile(FILE_NAME);
  // printf("\n");
  // deleteEntryById(FILE_NAME, 1);
  // printf("\n");
  // printBinaryFile(FILE_NAME);

  // printBinaryFile(FILE_NAME);
  // updateEntryById(FILE_NAME, 0, alex);
  // printBinaryFile(FILE_NAME);

  startMenu();

  return 0;
}