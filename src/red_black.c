/**
 * Name: Tracy U
 * CS 5008, Fall 2025
 * 
 * reference: https://www.geeksforgeeks.org/dsa/insertion-in-red-black-tree/
 * 
 */

#include "red_black.h"
#include <stdbool.h>
#include <stdio.h>

bool ll; // Left-Left Rotation flag
bool rr; // Right-Right Rotation flag
bool lr; // Left-Right Rotation flag
bool rl; // Right-Left Rotation flag


/**
 * Creates a red black node.
 * 
 * @param data the value to store in the node
 * @return the newly created node, or NULL if memory allocation error
*/
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


/**
 * Creates an empty red black tree.
 * 
 * @return the newly created tree, or NULL if memory allocation error
*/
rbTree* createTree() {
    struct rbTree *newTree = (struct rbTree *)malloc(sizeof(struct rbTree));
    if (newTree == NULL) {
        return NULL;
    }
    newTree->root = NULL;
    return newTree;
}


/**
 * Rotates a node left
 * 
 * @param node the node to rotate left
 * @return the rotated node
*/
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

/**
 * Rotates a node right
 * 
 * @param node the node to rotate right
 * @return the rotated node
*/
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


/**
 * A helper function that inserts data into the red black tree
 * 
 * @param tree the tree to insert the data into 
 * @param root the node to start with
 * @param data the data to insert
 * @return the root node of the tree
*/
rbNode* __insert(rbTree* tree, rbNode* root, int data) {
    bool f = false; // Flag to check RED-RED conflict

    if (root == NULL)
        return createNode(data);
    else if (data < root->data) {
        root->left = __insert(tree, root->left, data);
        root->left->parent = root;
        if (root != tree->root) { 
            if (root->color == 'R' && root->left->color == 'R')
                f = true;
        }
    } else if (data > root->data) {
        root->right = __insert(tree, root->right, data);
        root->right->parent = root;
        if (root != tree->root) {
            if (root->color == 'R' && root->right->color == 'R')
                f = true;
        }
    } else {
        // reject duplicates
        return root;
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


/**
 * Inserts data into the red black tree
 * 
 * @param tree the tree to insert the data into 
 * @param data the data to insert
*/
void insert(rbTree* tree, int data) {
    if (tree->root == NULL) {
        tree->root = createNode(data);
        tree->root->color = 'B';
    } else
        tree->root = __insert(tree, tree->root, data);
}

/**
 * A helper function to print the red black tree
 * 
 * @param root the root of the tree
 * @param space the space
*/
void __printTree(rbNode* root, int space) {
    if (root != NULL) {
        space += 10; // TODO
        __printTree(root->right, space);
        printf("\n");
        for (int i = 10; i < space; i++)
            printf(" ");
        printf("%d\n", root->data);
        __printTree(root->left, space);
    }
}

/**
 * Prints a red black tree
 * 
 * @param tree The red black tree to print
*/
void printTree(rbTree *tree) {
    __printTree(tree->root, 0);
}

/**
 * A helper function to print an in order traversal of the tree
 * 
 * @param node The node to print
*/
void __inorderTraversal(rbNode* node) {
    if (node != NULL) {
        __inorderTraversal(node->left);
        printf("%d ", node->data);
        __inorderTraversal(node->right);
    }
}

/**
 * Prints an in order traversal of the tree
 * 
 * @param tree The red black tree to print
*/
void inorderTraversal(rbTree* tree) {
    __inorderTraversal(tree->root);
}



/**
 * Helper function for getting a node from the redblack tree.
 *
 * Reference: Speed Comaparison Homework
 *
 * @param curr the current node
 * @param value the value to search for
 * @return the node that was found
*/
rbNode* __find(rbNode * curr, int value) {
    if(curr == NULL){
        return NULL;
    }
   else if (curr->data == value) {
       return curr;
   }
   else if (curr->data < value) {
       return __find(curr->right, value);
   }
   else if (curr->data > value) {
       return __find(curr->left, value);
   }
   return NULL;
}

/**
 * Finds the given node from the rbTree. 
 * 
 *  Reference: Speed Comaparison Homework
 * 
 * @param tree the tree to get from
 * @param title the value to get
 * @return the node that was found
*/
rbNode* find(rbTree* tree, int value) {
    rbNode* node = __find(tree->root, value);
    if (node == NULL) {
        return NULL;
    }
    return node;
}

/**
 * Helper function to free the tree and its nodes. 
 * 
 * @param node the node
*/
void __freeTree(rbNode* node) {
    if (node != NULL) {
        __freeTree(node->left);
        free(node);
        __freeTree(node->right);
    }
}

/**
 * Free the tree and its nodes. 
 * 
 * @param tree the tree to get from
*/
void freeTree(rbTree* tree) {
    __freeTree(tree->root);
}