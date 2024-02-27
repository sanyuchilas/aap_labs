#define fieldSize fieldLength * sizeof(char)
#define entryLength 6

struct footballerType {
  char* fullName;
  char* clubName;
  char* role;
  int age;
  int numberOfGames;
  int numberOfGoals;
};