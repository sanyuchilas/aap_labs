#define sLength 64
#define sByteSize sizeof(char) * sLength

struct footballerType {
  char fullName[sLength];
  char clubName[sLength];
  char role[sLength];
  char age[sLength];
  char numberOfGames[sLength];
  char numberOfGoals[sLength];
};