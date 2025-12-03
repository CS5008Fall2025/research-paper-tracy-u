// reference: https://www.geeksforgeeks.org/dsa/insertion-in-red-black-tree/

#include "red_black.h"
#include <stdbool.h>
#include <stdio.h>


rbNode* root;
bool ll; // Left-Left Rotation flag
bool rr; // Right-Right Rotation flag
bool lr; // Left-Right Rotation flag
bool rl; // Right-Left Rotation flag


//  function to create node
rbNode* createNode(int data) {
    struct rbNode *newNode = (struct rbNode *)malloc(sizeof(struct rbNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 'R';
    newNode->parent = NULL;
    return newNode;
}

rbTree* createTree() {
    struct rbTree *newTree = (struct rbTree *)malloc(sizeof(struct rbTree));
    newTree->root = NULL;
    return newTree;
}


int main() {
    rbNode *node = createNode(100);
    printf("%d\n", node->data);

    rbTree *tree = createTree();
    tree->root = node;
    printf("%d\n", tree->root->data);

    return 0;
}


