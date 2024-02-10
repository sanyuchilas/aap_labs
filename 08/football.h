#define fieldLength 64
#define fieldSize fieldLength * sizeof(char)
#define entryLength 6

struct footballerType {
  char fullName[fieldLength];
  char clubName[fieldLength];
  char role[fieldLength];
  int age;
  int numberOfGames;
  int numberOfGoals;
};