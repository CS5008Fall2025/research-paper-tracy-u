/**
 * Name: Tracy U
 * CS 5008, Fall 2025
 * 
 * Reference: Speed Comparison Homework
 * A series of tests to run on a data structure to track speed.
 * 
 * @author Albert Lionelle 
*/

#ifndef TESTS_H
#define TESTS_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "logging.h"
#include "../src/red_black.h"

#define CSV_HEADER "N,Insert,Find\n"
#define RESULTS_LENGTH 3

#define ADD_START 1
#define SEARCH_START 2

#define SPEED_OUT "speed_test_files/speed_test.txt"




int *get_random_array(int size)
{
    // Allocate memory
    int *random = (int *)malloc(sizeof(int) * size);

    // Populate our test data set
    for (int i = 0; i < size; i++)
    {
        // Generate random values from 0 to 99
        random[i] = rand() % size;
    }
    return random;
}


/**
 * Adds nodes to each data structure, and records the time it takes to add them
 * 
 * @param tree the tree to add values to
 * @param values the values add to the tree
 * @param length the length of values to pull from the values array
 * @param results array of doubles to store the results in
*/
void add_nodes(rbTree* tree, int* values, int length, double* results) {

    LOG_INFO("Adding %d values to tree \n", length);

    LOG_DEBUG("Adding to rbTree\n");
    clock_t start = clock();
    for (int i = 0; i < length; i++) {
        insert(tree, values[i]);
    }
    clock_t end = clock();
    results[ADD_START] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[ADD_START]);

}

/**
 * Searches for value in a data structure, and records the time it takes to search for them
 * 
 * @param tree the tree to search for values in
 * @param values the values to act as the TestSet
 * @param length the total number of values to pull from array
 * @param results array of doubles to store the results in
*/
void search_tree(rbTree* tree, int* values, int length, double *results){

    LOG_INFO("Searching for %d values\n", length);

    clock_t start = clock();
    for (int i = 0; i < length; i++) {
        find(tree, values[i]);
    }
    clock_t end = clock();
    results[SEARCH_START] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[SEARCH_START]);
}

/**
 * Runs all tests, entry function to running the tests
 *
 * @param values the MovieVector to act as the TestSet
 * @param length the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 */
void run_tests(int* values, int length, double *results) {
// initialize the data structures

    LOG_INFO("Running Tests on %d values\n", length);
    rbTree* tree = createTree();

    // add movies to each data structure
    add_nodes(tree, values, length, results);

    // search for movies in each data structure
    search_tree(tree, values, length, results);

    // free data structures (just free, no need to remove movies from them)
    free(tree); 
   
    LOG_INFO("Finished running tests\n\n");
}


#endif // TEST