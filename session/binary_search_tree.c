#include <stdlib.h>
#include <stdio.h>

struct Node {
    int number;
    struct Node* left;
    struct Node* right;
};
typedef struct Node Node;

Node* insertNodeIntoBinarySearchTree(Node* root, Node* insertionNode) {
    if (root == NULL) {
        return insertionNode;
    }

    if (insertionNode->number >= root->number) {
        root->right = insertNodeIntoBinarySearchTree(root->right, insertionNode);
    } else {
        root->left = insertNodeIntoBinarySearchTree(root->left, insertionNode);
    }

    return root;
}

Node* createBinaryTreeFromArray(int array[10]) {
    Node* root = (Node*)malloc(sizeof(Node));

    root->left = NULL;
    root->right = NULL;

    root->number = array[0];

    for (int i = 1; i < 10; i++) {
        Node* insertionNode = (Node*)malloc(sizeof(Node));

        insertionNode->number = array[i];
        insertionNode->right = NULL;
        insertionNode->left = NULL;

        insertNodeIntoBinarySearchTree(root, insertionNode);
    }

    return root;
}

void printBinarySearchTree(Node* root) {
    if (root == NULL) {
        return;
    }

    printBinarySearchTree(root->left);
    printf("%d\n", root->number);
    printBinarySearchTree(root->right);
}

int main() {
    int array[10] = {9, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    Node* root = createBinaryTreeFromArray(array);

    printBinarySearchTree(root);
    return 0;
}