#include <stdio.h> // Input/output library.
#include <stdlib.h> // Memory allocation.
#include <assert.h> // Assertion library.
#include <string.h> // String functions library.

#include "football.h" // Footballer info.

// Function printing horizontal line.
void printHr(int length) {
  for (int j = 0; j < length; j++) {
      printf("- ");
    }
    printf("\n");
}

// Function printing table header.
void printTableHeader() {
  printHr(65);
  printf("%4s|%30s|%30s|%30s|%10s|%10s|%10s|\n", "ID", "FULL NAME", "CLUB NAME", "ROLE", "AGE", "GAMES", "GOALS");
  printHr(65);
}

// Function printing footballer.
void printFootballer(Footballer* footballer) {
  printf("%4d|%30s|%30s|%30s|%10d|%10d|%10d|\n", -1, footballer->fullName, footballer->clubName, footballer->role, footballer->age, footballer->numberOfGames, footballer->numberOfGoals);
  printHr(65);
}

// Function printing footballers.
void printFootballersArray(Footballer* footballers, int length) {
  if (footballers == NULL) {
    printf("Incorrect array.\n");
    return;
  }

  printTableHeader();

  for (int i = 0; i < length; i++) {
    printFootballer(footballers + i);
  }
}

// Function generating string.
char* generateString(int length, int countOfUsedSymbols) {
  assert(countOfUsedSymbols <= 26);

  char* out = (char*)malloc(sizeof(char) * (length + 1));
  char alphabet[26] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
  };

  for (int i = 0; i < length; i++) {
    out[i] = alphabet[rand() % countOfUsedSymbols];
  }

  out[length] = '\0';

  return out;
}

// Function generating footballer.
Footballer generateFootballer() {
  Footballer out = {
    .fullName=generateString(1, 3),
    .clubName=generateString(1, 1),
    .role=generateString(1, 1),
    .age=(rand() % 100),
    .numberOfGames=(rand() % 100),
    .numberOfGoals=(rand() % 100),
  };

  return out;
}

// Function generating footballer array.
Footballer* generateFootballersArray(int length) {
  Footballer* arr = (Footballer*)malloc(sizeof(Footballer) * length);
  
  for (int i = 0; i < length; i++) {
    arr[i] = generateFootballer();
  }

  printf("Successfully generated %d footballers array.\n", length);
  return arr;
}

// Function comparing footballers.
int compareFootballers(Footballer* footballer1, Footballer* footballer2, int direction) {
  return strcmp(footballer1->fullName, footballer2->fullName);
}

struct Node {
  Footballer* footballer;
  struct Node* left;
  struct Node* right;
};
typedef struct Node Node;

Node* createNode(Footballer* footballer) {
  Node* node = (Node*)malloc(sizeof(Node));

  node->footballer = footballer;
  node->left = node->right = NULL;

  return node;
}

Node* insertNode(Node* root, Node* insertionNode) {
  if (root == NULL) {
    return insertionNode;
  }

  if (compareFootballers(insertionNode->footballer, root->footballer, 1) >= 0) {
    // printf("Right: %20p %20p\n", root, root->right);
    root->right = insertNode(root->right, insertionNode);
    // printf("Right: %20p %20p\n", root, root->right);
  } else {
    // printf("Left : %20p %20p\n", root, root->left);
    root->left = insertNode(root->left, insertionNode);
    // printf("Left : %20p %20p\n", root, root->left);
  }

  return root;
}

void insertNodeByFootballer(Node* root, Footballer* footballer) {
  insertNode(root, createNode(footballer));
}

Node* createTreeFromFootballersArray(Footballer* footballers, int footballersCount) {
  Node* root = (Node*)malloc(sizeof(Node));

  root->footballer = footballers;
  root->left = root->right = NULL;

  for (int i = 1; i < footballersCount; i++) {
    insertNodeByFootballer(root, footballers + i);
  }

  return root;
}

void printFootabllersBinarySearchTree(Node* root) {
  if (root == NULL) {
    return;
  }

  printFootabllersBinarySearchTree(root->left);
  printFootballer(root->footballer);
  printFootabllersBinarySearchTree(root->right);
}

void printNodesArray(Node** nodes, int nodesCount) {
  if (nodesCount == 0) {
    printf("Footballers with this name were not found.\n");
  }

  for (int i = 0; i < nodesCount; i++) {
    printFootballer(nodes[i]->footballer);
  };
}

Node* findNodeInBinarySearchTreeByFootballerFullName(Node* root, char* fullName) {
  if (root == NULL || strcmp(root->footballer->fullName, fullName) == 0) {
    return root;
  }

  if (strcmp(root->footballer->fullName, fullName) > 0) {
    return findNodeInBinarySearchTreeByFootballerFullName(root->left, fullName);
  }

  return findNodeInBinarySearchTreeByFootballerFullName(root->right, fullName);
}

int findAllNodesInBinarySearchTreeByFootballerFullName(Node* root, char* fullName, Node** nodes) {
  Node* curNode = findNodeInBinarySearchTreeByFootballerFullName(root, fullName);

  int nodesCount = 0;

  if (curNode == NULL) {
    nodes = NULL;

    return nodesCount;
  }

  nodes[0] = curNode;
  nodesCount++;

  Node* nextNode = curNode->right;

  while (nextNode != NULL && strcmp(curNode->footballer->fullName, nextNode->footballer->fullName) == 0) {
    nodes[nodesCount] = nextNode;
    nextNode = nextNode->right;
    nodesCount++;
  }

  return nodesCount;
}

int main() {
  printf("Lab 11. Keyer, BAM231.\n");

  Footballer* footballers = generateFootballersArray(3);

  Node* root = createTreeFromFootballersArray(footballers, 3);
  Node** allGoodNodes = (Node**)malloc(sizeof(Node*) * 3);

  printf("Print footballers array.\n");
  printFootballersArray(footballers, 3);

  printf("Print footballers binary tree.\n");
  printTableHeader();
  printFootabllersBinarySearchTree(root);

  printf("All nodes with footballer fullName = \"a\".\n");
  int nodesCount = findAllNodesInBinarySearchTreeByFootballerFullName(root, "ab", allGoodNodes);
  
  printTableHeader();
  printNodesArray(allGoodNodes, nodesCount);

  free(footballers);
  free(root);

  return 0;
}