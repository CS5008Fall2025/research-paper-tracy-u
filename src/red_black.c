// reference: https://www.geeksforgeeks.org/dsa/insertion-in-red-black-tree/

#include "red_black.h"
#include <stdbool.h>
#include <stdio.h>

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

// Function to perform Left Rotation
rbNode* rotateLeft(rbNode* node) {
    rbNode* x = node->right;
    rbNode* y = x->left;
    x->left = node;
    node->right = y;
    node->parent = x;
    if (y != NULL)
        y->parent = node;
    return x;
}

// Function to perform Right Rotation
rbNode* rotateRight(rbNode* node) {
    rbNode* x = node->left;
    rbNode* y = x->right;
    x->right = node;
    node->left = y;
    node->parent = x;
    if (y != NULL)
        y->parent = node;
    return x;
}


// Helper function for insertion
rbNode* insertHelper(rbTree* tree, rbNode* root, int data) {
    bool f = false; // Flag to check RED-RED conflict

    if (root == NULL)
        return createNode(data);
    else if (data < root->data) {
        root->left = insertHelper(tree, root->left, data);
        root->left->parent = root;
        if (root != tree->root) { // TO FIX
            if (root->color == 'R' && root->left->color == 'R')
                f = true;
        }
    } else {
        root->right = insertHelper(tree, root->right, data);
        root->right->parent = root;
        if (root != tree->root) {
            if (root->color == 'R' && root->right->color == 'R')
                f = true;
        }
    }

    // Perform rotations
    if (ll) {
        root = rotateLeft(root);
        root->color = 'B';
        root->left->color = 'R';
        ll = false;
    } else if (rr) {
        root = rotateRight(root);
        root->color = 'B';
        root->right->color = 'R';
        rr = false;
    } else if (rl) {
        root->right = rotateRight(root->right);
        root->right->parent = root;
        root = rotateLeft(root);
        root->color = 'B';
        root->left->color = 'R';
        rl = false;
    } else if (lr) {
        root->left = rotateLeft(root->left);
        root->left->parent = root;
        root = rotateRight(root);
        root->color = 'B';
        root->right->color = 'R';
        lr = false;
    }

    // Handle RED-RED conflicts
    if (f) {
        if (root->parent->right == root) {
            if (root->parent->left == NULL || root->parent->left->color == 'B') {
                if (root->left != NULL && root->left->color == 'R')
                    rl = true;
                else if (root->right != NULL && root->right->color == 'R')
                    ll = true;
            } else {
                root->parent->left->color = 'B';
                root->color = 'B';
                if (root->parent != tree->root)
                    root->parent->color = 'R';
            }
        } else {
            if (root->parent->right == NULL || root->parent->right->color == 'B') {
                if (root->left != NULL && root->left->color == 'R')
                    rr = true;
                else if (root->right != NULL && root->right->color == 'R')
                    lr = true;
            } else {
                root->parent->right->color = 'B';
                root->color = 'B';
                if (root->parent != tree->root)
                    root->parent->color = 'R';
            }
        }
        f = false;
    }
    return root;
}

void insert(rbTree* tree, int data) {
    if (tree->root == NULL) {
        tree->root = createNode(data);
        tree->root->color = 'B';
    } else
        tree->root = insertHelper(tree, tree->root, data);
}


// Helper function to print the tree
void printTreeHelper(rbNode* root, int space) {
    if (root != NULL) {
        space += 10;
        printTreeHelper(root->right, space);
        printf("\n");
        for (int i = 10; i < space; i++)
            printf(" ");
        printf("%d\n", root->data);
        printTreeHelper(root->left, space);
    }
}

void printTree(rbTree *tree) {
    printTreeHelper(tree->root, 0);
}

// Helper function to perform Inorder Traversal
void inorderTraversalHelper(rbNode* node) {
    if (node != NULL) {
        inorderTraversalHelper(node->left);
        printf("%d ", node->data);
        inorderTraversalHelper(node->right);
    }
}

// Function to perform Inorder Traversal of the tree
void inorderTraversal(rbTree* tree) {
    inorderTraversalHelper(tree->root);
}



// int main() {

//     rbTree *tree = createTree();
//     printf("print empty tree:\n");
//     printTree(tree);

//     rbNode *node = createNode(100);
//     printf("node: %d\n", node->data);

//     tree->root = node;

//     printf("print tree with node:\n");
//     printTree(tree);

//     rbTree* tree2 = createTree();
//     int arr[] = {1, 4, 6, 3, 5, 7, 8, 2, 9};
//         for (int i = 0; i < 9; i++) {
//             insert(tree2, arr[i]);
//         }
    
//     printTree(tree2);
//     inorderTraversal(tree2);
//     printf("\nroot tree2: %d\n", tree2->root->data);

//     return 0;
// }


