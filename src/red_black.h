

#include <stdlib.h>


typedef struct rbNode {
    int data;
    struct rbNode* left;
    struct rbNode* right;
    char color;
    struct rbNode* parent;
} rbNode;


typedef struct rbTree {
    struct rbNode* root;
} rbTree;

rbNode* createNode(int data);
rbTree* createTree();
rbNode* rotateLeft(rbNode* node);
rbNode* rotateRight(rbNode* node);
void insert(rbTree* tree, int data);
void printTree(rbTree* tree);
void inorderTraversal(rbTree* tree);
rbNode* find(rbTree* tree, int value);








