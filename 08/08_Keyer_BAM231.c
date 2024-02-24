#include "football.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>

#define FILE_NAME "footbaler.bin"
#define INPUT_TYPE 'u'

void printEntry(struct footballerType entry) {
  printf("%s, %s, %s, %d, %d, %d\n", entry.fullName, entry.clubName, entry.role, entry.age, entry.numberOfGames, entry.numberOfGoals);
}

void getFootballerFullNameByUser(char fullName[fieldLength]) {
  printf("Enter full name: ");

  fflush(stdin);
  fgets(fullName, fieldLength, stdin);
  fullName[strcspn(fullName, "\n")] = 0;
}

void getFootballerClubNameByUser(char clubName[fieldLength]) {
  printf("Enter club name: ");

  fflush(stdin);
  fgets(clubName, fieldLength, stdin);
  clubName[strcspn(clubName, "\n")] = 0;
}

void getFootballerRoleByUser(char role[fieldLength]) {
  printf("Enter role: ");

  fflush(stdin);
  fgets(role, fieldLength, stdin);
  role[strcspn(role, "\n")] = 0;
}

void getFootballerAgeByUser(int *age) {
  printf("Enter age: ");
  
  fflush(stdin);
  scanf("%d", age);
}

void getFootballerNumberOfGamesByUser(int *numberOfGames) {
  printf("Enter number of games: ");

  fflush(stdin);
  scanf("%d", numberOfGames);
}

void getFootballerNumberOfGoalsByUser(int *numberOfGoals) {
  printf("Enter count of goals: ");

  fflush(stdin);
  scanf("%d", numberOfGoals);
}

void getFootballerByUser(struct footballerType *footballer) {
  getFootballerFullNameByUser(footballer->fullName);
  getFootballerClubNameByUser(footballer->clubName);
  getFootballerRoleByUser(footballer->role);
  getFootballerAgeByUser(&(footballer->age));
  getFootballerNumberOfGamesByUser(&(footballer->numberOfGames));
  getFootballerNumberOfGoalsByUser(&(footballer->numberOfGoals));
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

  if (entryId >= fileLength || entryId < 0) {
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

void printFindAllOperationsList() {
  printf("\n");
  printf("%30s %3s", "full name:", "1\n");
  printf("%30s %3s", "club name:", "2\n");
  printf("%30s %3s", "role:", "3\n");
  printf("%30s %3s", "age:", "4\n");
  printf("%30s %3s", "number of goals:", "5\n");
  printf("%30s %3s", "number of games:", "6\n");
  printf("\n\n");
}

void startFindAllEntriesMenu() {
  printf("\n");
  printFindAllOperationsList();
  printf("Enter correct find all code: ");

  int operationCode = 0;

  fflush(stdin);
  scanf("%d", &operationCode);

  if (operationCode <= 0 || operationCode > 6) {
    startFindAllEntriesMenu();
    return;
  }

  switch (operationCode) {
    case 1: {
      char fullName[fieldLength];
      getFootballerFullNameByUser(fullName);
      findAllEntriesByFullName(FILE_NAME, fullName);
      break;
    }

    case 2: {
      char clubName[fieldLength];
      getFootballerClubNameByUser(clubName);
      findAllEntriesByClubName(FILE_NAME, clubName);
      break;
    }

    case 3: {
      char role[fieldLength];
      getFootballerRoleByUser(role);
      findAllEntriesByRole(FILE_NAME, role);
      break;
    }

    case 4: {
      int age;
      getFootballerAgeByUser(age);
      findAllEntriesByAge(FILE_NAME, &age);
      break;
    }

    case 5: {
      int numberOfGoals;
      getFootballerNumberOfGoalsByUser(numberOfGoals);
      findAllEntriesByNumberOfGoals(FILE_NAME, &numberOfGoals);
      break;
    }

    case 6: {
      int numberOfGames;
      getFootballerNumberOfGamesByUser(numberOfGames);
      findAllEntriesByNumberOfGames(FILE_NAME, &numberOfGames);
      break;
    }
  }
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

  int operationCode = 0;

  fflush(stdin);
  scanf("%d", &operationCode);

  if (operationCode <= 0 || operationCode > 5) {
    startMenu();
    return;
  }

  switch (operationCode) {
    case 1: {
      struct footballerType footballer;

      getFootballerByUser(&footballer);
      appendEntry(FILE_NAME, footballer);
      break;
    }

    case 2: {
      int entryId;

      printf("Enter footballer id: ");

      fflush(stdin);
      scanf("%d", &entryId);

      deleteEntryById(FILE_NAME, entryId);
      break;
    }

    case 3: {
      startFindAllEntriesMenu();
      break;
    }

    case 4:
      break;

    case 5:
      printBinaryFile(FILE_NAME);
      break;
  }

  printf("\n");
  startMenu();
}

int main() {
  #if INPUT_TYPE == 'u'
  printf("User input.\n");

  struct footballerType footballer;

  getFootballerByUser(&footballer);

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