/**
 * Contains tests to test the linked list implementation.
 * 
 * STUDENT TODO: You should feel free to modify this file adding their own
 * tests if they feel any are missing. 
 * 
 * If you implemented a double linked list instead of as singled linked
 * list, this test file should still work. If it doesn't, please double
 * check your implementation that you haven't modified any of the core
 * functions/layout (such as head/tail naming, etc).
*/


#include <stdio.h>

#include "../src/red_black.h"
#include "testing_util.h"


#define GROUP_GENERAL "GENERAL"
#define GROUP_ADD "ADD"
#define GROUP_REMOVE "REMOVE"
#define GROUP_GET "GET"
#define GROUP_TO_STRING "STRING"
// setup a different group for strings since it involves different traversals


/******** TESTS  ****************/

/**
 * Tests the createNode() function.
 * 
 * @return true if the test passed, false if it failed
*/
bool test_new_node() {
    rbNode *node = createNode(100);
    bool passed = true;
    passed &= ASSERT_EQUAL(node->data, 100);
    passed &= ASSERT_EQUAL(node->color, 'R');
    passed &= ASSERT_NULL(node->left);
    passed &= ASSERT_NULL(node->right);
    passed &= ASSERT_NULL(node->parent);

    free(node);
    return passed;
}



/**
 * Tests the createNode() function.
 * 
 * @return true if the test passed, false if it failed
*/
bool test_new_tree() {
    rbTree *tree = createTree();
    bool passed = true;
    passed &= ASSERT_NULL(tree->root);
    free(tree);
    return passed;
}


// test rotate left
bool test_rotate_left() {
    
    rbTree* tree = createTree();
    tree->root = createNode(11);
    tree->root->left = createNode(9);
    tree->root->right = createNode(18);
    tree->root->right->right = createNode(10);
    if (DEBUG) {
        printf("Rotate Left: Initial Tree\n");
        printTree(tree);
        printf("\n");
    }

    rbNode* newRoot = rotateLeft(tree->root);
    tree->root = newRoot;

    if (DEBUG) {
        printf("Rotate Left: After Rotation\n");
        printTree(tree);
        printf("\n");
    } 
    
    bool passed = true;
    passed &= ASSERT_EQUAL(tree->root->data, 18);
    passed &= ASSERT_EQUAL(tree->root->left->data, 11);
    passed &= ASSERT_EQUAL(tree->root->left->left->data, 9);
    passed &= ASSERT_EQUAL(tree->root->right->data, 10);
    
    free(tree);
    return passed;
}




// test rotate right
bool test_rotate_right() {
    
    rbTree* tree = createTree();
    tree->root = createNode(11);
    tree->root->left = createNode(9);
    tree->root->left->right = createNode(18);
    tree->root->left->left = createNode(10);
    if (DEBUG) {
        printf("Rotate Right: Initial Tree\n");
        printTree(tree);
        printf("\n");
    }

    rbNode* newRoot = rotateRight(tree->root);
    tree->root = newRoot;

    if (DEBUG) {
        printf("Rotate Right: After Rotation\n");
        printTree(tree);
        printf("\n");
    } 
    
    bool passed = true;
    passed &= ASSERT_EQUAL(tree->root->data, 9);
    passed &= ASSERT_EQUAL(tree->root->right->data, 11);
    passed &= ASSERT_EQUAL(tree->root->left->data, 10);
    passed &= ASSERT_EQUAL(tree->root->right->left->data, 18);
    
    free(tree);
    return passed;
}

// test insert - single
bool test_insert_single() {
    rbTree* tree = createTree();

    insert(tree, 17);

    bool passed = true;
    passed &= ASSERT_EQUAL(tree->root->data, 17);
    passed &= ASSERT_EQUAL(tree->root->color, 'B');
    passed &= ASSERT_NULL(tree->root->left);
    passed &= ASSERT_NULL(tree->root->right);
    passed &= ASSERT_NULL(tree->root->parent);
    
    free(tree);
    return passed;
}


// test insert - multiple
bool test_insert_multiple() {
    rbTree* tree = createTree();

    insert(tree, 17);
    insert(tree, 10);
    insert(tree, 100);
    insert(tree, 42);
    insert(tree, 16);

    bool passed = true;
    passed &= ASSERT_EQUAL(tree->root->data, 17);
    passed &= ASSERT_EQUAL(tree->root->color, 'B');

    passed &= ASSERT_EQUAL(tree->root->left->data, 10);
    passed &= ASSERT_EQUAL(tree->root->left->color, 'B');

    passed &= ASSERT_EQUAL(tree->root->right->data, 100);
    passed &= ASSERT_EQUAL(tree->root->right->color, 'B');

    passed &= ASSERT_EQUAL(tree->root->right->left->data, 42);
    passed &= ASSERT_EQUAL(tree->root->right->left->color, 'R');

    passed &= ASSERT_EQUAL(tree->root->left->right->data, 16);
    passed &= ASSERT_EQUAL(tree->root->left->right->color, 'R');    

    free(tree);
    return passed;
}


// test insert - duplicate
bool test_insert_duplicate() {
    rbTree* tree = createTree();

    insert(tree, 17);
    insert(tree, 10);
    insert(tree, 100);
    insert(tree, 17);

    bool passed = true;
    passed &= ASSERT_EQUAL(tree->root->data, 17);
    passed &= ASSERT_EQUAL(tree->root->color, 'B');

    passed &= ASSERT_EQUAL(tree->root->left->data, 10);
    passed &= ASSERT_EQUAL(tree->root->left->color, 'R');

    passed &= ASSERT_EQUAL(tree->root->right->data, 100);
    passed &= ASSERT_EQUAL(tree->root->right->color, 'R');

    passed &= ASSERT_NULL(tree->root->right->left);
    passed &= ASSERT_NULL(tree->root->right->right);

    passed &= ASSERT_NULL(tree->root->left->left);
    passed &= ASSERT_NULL(tree->root->left->right);

    free(tree);
    return passed;
}




/******* END TESTS ************/





/**
 * Adds every testing function to the testing set.
 * Includes the name of the test, the group tag, and the function to run.
*/
TestingSet * init_testing_set() {
    TestingSet * set = new_testing_set();
    add_test(set, "test_new_node() creates a node", GROUP_GENERAL, 
        test_new_node);  
    add_test(set, "test_new_tree() creates an empty tree", GROUP_GENERAL, 
        test_new_tree);  
    add_test(set, "test_rotate_left() rotates left", GROUP_GENERAL, 
        test_rotate_left); 
    add_test(set, "test_rotate_right() rotates right", GROUP_GENERAL, 
        test_rotate_right); 
    add_test(set, "test_insert_single() inserts single value", GROUP_ADD, 
        test_insert_single); 
    add_test(set, "test_insert_multiple() inserts multiple values", GROUP_ADD, 
        test_insert_multiple);     
    add_test(set, "test_insert_duplicate() attempts to insert duplicate values", GROUP_ADD, 
        test_insert_duplicate);    
    // add_test(set, "ll_add_front() adds a node to the front of the list", GROUP_ADD, 
    //    test_ll_add_front);  
    // add_test(set, "ll_add_back() adds a node to the back of the list", GROUP_ADD,
    //     test_ll_add_back); 
    // add_test(set, "ll_insert() adds a node to the list at the given index", GROUP_ADD,
    //     test_ll_insert); 
    // add_test(set, "ll_insert() does nothing if the index is out of bounds", GROUP_ADD,
    //     test_ll_insert_out_of_bounds); 
    // add_test(set, "ll_remove_front() removes a node from the front of the list", GROUP_REMOVE,
    //     test_ll_remove_front); 
    // add_test(set, "ll_remove_back() removes a node from the back of the list", GROUP_REMOVE,
    //     test_ll_remove_back); 
    // add_test(set, "ll_remove() removes a node from the list at the given index", GROUP_REMOVE,
    //     test_ll_remove); 
    // add_test(set, "ll_remove() does nothing if the index is out of bounds", GROUP_REMOVE,
    //     test_ll_remove_out_of_bounds); 
    // add_test(set, "ll_get() gets a node from the list at the given index", GROUP_GET,
    //     test_ll_get); 
    // add_test(set, "ll_get() does nothing if the index is out of bounds", GROUP_GET,
    //     test_ll_get_out_of_bounds); 
    // add_test(set, "ll_is_empty() returns true if the list is empty", GROUP_GENERAL,
    //     test_ll_is_empty); 
    // add_test(set, "ll_to_str() returns a string representation of the list", GROUP_GENERAL,
    //     test_ll_to_str); 
    // add_test(set, "add_to_sorted_list() adds a movie to the sorted list", GROUP_SORTED,
    //     test_sorted_list_add);
    // add_test(set, "find_in_sorted_list() finds a movie in the sorted list", GROUP_SORTED,
    //     test_sorted_list_find);
    // add_test(set, "sorted_list_remove() properly removes movies based on title", GROUP_SORTED,
    //     test_sorted_list_remove);

    return set;
}

/**
 * Runs the tests for the linked list implementation.
 * 
 * @param start_test the test to start running from
 * @param end_test the test to stop running at
*/
int main(const int argc, const char *argv[]) {

    TestingSet * set = init_testing_set(); // initialize the testing set
    
    // now proccess args and run the test program
    VERBOSE = check_for_verbose(argc, argv); // check for verbose flag and set the global variable found in testing_util.h
    DEBUG = check_for_debug(argc, argv); // check for debug flag and set the global variable found in testing_util.h

    const char * group_tag = check_for_group_tag(argc, argv); // check for group tag and set the global variable found in testing_util.h
    
    if (group_tag == NULL) {
        int test_start_loc = 1; // the index to start looking for tests at, but may change if -v is there
        int start_test = get_int_arg(argc, argv, 1, 0, &test_start_loc); // get the start test, default to 0
        int end_test = get_int_arg(argc, argv, test_start_loc + 1, set->num_tests-1, &test_start_loc); // get the end test, default to 0
        PRINT_VERBOSE("Running tests %d through %d\n", start_test, end_test);
        run_tests(set, start_test, end_test);
    } else {
        PRINT_VERBOSE("Running tests for group %s\n", group_tag);
        run_tests_group(set, (char *)group_tag);
    }
 



    // this has to be done separately because movies are used across multiple lists
    // free_movies();
    // free_testing_set(set);
    return 0;
}