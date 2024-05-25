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
  printf("%4s|%30s|%30s|%30s|%10d|%10d|%10d|\n", "?", footballer->fullName, footballer->clubName, footballer->role, footballer->age, footballer->numberOfGames, footballer->numberOfGoals);
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

// =================
// Hash table dope.
// Hash table crazy.
// Hash table here.
// =================

struct ListItem {
  Footballer* footballer;
  struct ListItem* next;
};
typedef struct ListItem ListItem;

ListItem* createListItem(Footballer* footballer) {
  ListItem* listItem = (ListItem*)malloc(sizeof(ListItem));

  listItem->footballer = footballer;
  listItem->next = NULL;

  return listItem;
}

struct HashTable {
  int size;
  ListItem** table;
};
typedef struct HashTable HashTable;

HashTable* createHashTable(int size) {
  HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
  ListItem** table = (ListItem**)malloc(sizeof(ListItem*) * size);

  hashTable->table = table;
  hashTable->size = size;

  for (int i = 0; i < size; i++) {
    table[i] = NULL;
  }

  return hashTable;
}

int hashFunction(HashTable* hashTable, char* fullName) {
  int hash = 0;

  while (*fullName != 0) {
    hash = (hash + *fullName++) % hashTable->size;
  }

  return hash;
}

void insertFootballerIntoHashTable(HashTable* hashTable, Footballer* footballer) {
  int hash = hashFunction(hashTable, footballer->fullName);

  ListItem* listItem = createListItem(footballer);

  listItem->next = hashTable->table[hash];
  hashTable->table[hash] = listItem;
}

HashTable* createHashTableFromFootballersArray(Footballer* footballers, int footballersCount) {
  HashTable* hashTable = createHashTable(footballersCount);

  for (int i = 0; i < footballersCount; i++) {
    insertFootballerIntoHashTable(hashTable, footballers + i);
  }

  return hashTable;
}

int findAllListItemsInHashTableByFootballerFullName(HashTable* hashTable, char* fullName, ListItem** listItems) {
  int hash = hashFunction(hashTable, fullName);

  int listItemsCount = 0;

  ListItem* listItem = hashTable->table[hash];

  while (listItem != NULL) {
    if (strcmp(listItem->footballer->fullName, fullName) == 0) {
      listItems[listItemsCount] = listItem;
    }

    listItem = listItem->next;

    listItemsCount++;
  }

  return listItemsCount;
}

void printFootballersHashTable(HashTable* hashTable) {
  for (int hash = 0; hash < hashTable->size; hash++) {
    if (hashTable->table[hash] == NULL) {
      continue;
    }
    
    ListItem* listItem = hashTable->table[hash];

    while (listItem != NULL) {
      printFootballer(listItem->footballer);

      listItem = listItem->next;
    }
  }
}

void printFootballersListItems(ListItem** listItems, int listItemsCount) {
  if (listItemsCount == 0) {
    printf("Footballers with this name were not found.\n");
  }

  for (int i = 0; i < listItemsCount; i++) {
    printFootballer(listItems[i]->footballer);
  }
}

int main() {
  printf("Lab 11. Keyer, BAM231.\n");

  int n = 3;
  char* fullName = "b";

  printf("\n==== Initialize program ====\n\n");

  // Prepare program and generate footballers array.

  Footballer* footballers = generateFootballersArray(n);

  printf("\nPrint footballers array.\n");
  printFootballersArray(footballers, n);

  printf("\n==== Binary tree ====\n");

  // Create binary search tree.

  Node* root = createTreeFromFootballersArray(footballers, n);

  printf("\nPrint footballers binary tree.\n");
  printTableHeader();
  printFootabllersBinarySearchTree(root);

  // Work with binary search tree.

  Node** nodes = (Node**)malloc(sizeof(Node*) * n);

  int nodesCount = findAllNodesInBinarySearchTreeByFootballerFullName(root, fullName, nodes);

  printf("\nAll nodes with footballer fullName = \"%s\".\n", fullName);
  printTableHeader();
  printNodesArray(nodes, nodesCount);

  printf("\n==== Hash table ====\n");

  // Create hash table.

  HashTable* hashTable = createHashTableFromFootballersArray(footballers, n);

  printf("\nPrint footballers hash table.\n");
  printTableHeader();
  printFootballersHashTable(hashTable);

  // Work with hash table.

  ListItem** listItems = (ListItem**)malloc(sizeof(ListItem*) * n);

  int listItemsCount = findAllListItemsInHashTableByFootballerFullName(hashTable, fullName, listItems);

  printf("\nAll list items with footballer fullName = \"%s\".\n", fullName);
  printTableHeader();
  printFootballersListItems(listItems, listItemsCount);

  // End program and free allocated memory.

  free(footballers);
  free(root);

  return 0;
}