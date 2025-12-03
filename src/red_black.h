

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




