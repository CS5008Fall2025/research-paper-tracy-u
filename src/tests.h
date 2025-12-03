/**
 * 
 * A series of tests to run on each data structure to compare their speed.
 * 
 * @author Albert Lionelle 
*/

#ifndef TESTS_H
#define TESTS_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "logging.h"
#include "../lib/movie.h"
#include "../lib/linked_list.h"
#include "../lib/vector.h"
#include "../lib/bst.h"

#define CSV_HEADER "N,SortedVector Add,LinkedList Add,BST Add,SortedVector Search,LinkedList Search,BST Search,SortedVector Save,SortedList Save, BST Save,SortedVector Remove,SortedList Remove,BST Remove,Vector Add Front,LinkedList Add Front,Vector Add Back,LinkedList Add Back,Vector Remove Front,LinkedList Remove Front,Vector Remove Back,LinkedList Remove Back,Vector Get,LinkedList Get\n"
#define RESULTS_LENGTH 23

#define ADD_START 1
#define SEARCH_START 4
#define WRITE_START 7
#define REMOVE_START 10
#define ADD_FRONT 13
#define ADD_BACK 15
#define REMOVE_FRONT 17
#define REMOVE_BACK 19
#define GET 21


#define VECTOR_LOC 0
#define LIST_LOC 1
#define BST_LOC 2

#define SAMPLE_SPLIT .7 // 70% of the movies will exist, 30% may or may not exist


#define SORTED_VECTOR_OUT "speed_test_files/sorted_vector.txt"
#define SORTED_LIST_OUT "speed_test_files/sorted_list.txt"
#define BST_OUT "speed_test_files/bst.txt"

/**
 * Adds movies to each data structure, and records the time it takes to add them
 * 
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param sorted_vector the SortedVector to add movies to
 * @param sorted_list the SortedList to add movies to
 * @param bst the BST to add movies to
*/
void add_movies(MovieVector* movies, int total, double* results, SortedMovieVector* sorted_vector, SortedList* sorted_list, BST* bst) {
    // add movies to each data structure
    LOG_INFO("Adding movies %d to each data structure\n", total);

    LOG_DEBUG("Adding to sorted vector\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++) {
        add_to_sorted_vector(sorted_vector, movies->movies[i]);
    }
    clock_t end = clock();
    results[ADD_START + VECTOR_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[ADD_START + VECTOR_LOC]);

    LOG_DEBUG("Adding to sorted list\n");
    start = clock();
    for (int i = 0; i < total; i++) {
        add_to_sorted_list(sorted_list, movies->movies[i]);
    }
    end = clock();
    results[ADD_START + LIST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[ADD_START + LIST_LOC]);

    LOG_DEBUG("Adding to bst\n");
    start = clock();
    for (int i = 0; i < total; i++) {
       bst_add(bst, movies->movies[i]);
    }
    end = clock();
    results[ADD_START + BST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("..result was %f\n", results[ADD_START + BST_LOC]);
}

/**
 * Build sample indexes - builds an array of indexes to pull from the MovieVector
 * 
 * The sample uses SAMPLE_SPLIT to ensure that 70% of the movies will exist in the data structures
 * While the remaining 30% may or may not exist in the data structures (forcing worst case search/remove)
 * 
 * @param split_max Every number in sample split must be under this number 
 * @param total_movies the size of the MovieVector, all indexes must be under this
 * @param sample_size the total number of movies to pull from MovieVector
 * 
 * @return an array of indexes to pull from the MovieVector
*/
int* build_sample_indexes(int split_max, int total_movies, int sample_size) {
    int* sample_indexes = malloc(sizeof(int) * sample_size);
    LOG_DEBUG("Building sample indexes\n");
    for(int i = 0; i < sample_size; i++) {
        int index = rand() % total_movies;
        while (index > split_max && i < (sample_size * SAMPLE_SPLIT))
        {
            index = rand() % total_movies;
        }
        sample_indexes[i] = index;
    }
    float percent_under_split_max = 0;
    for(int i = 0; i < sample_size; i++) {
        if(sample_indexes[i] <= split_max) {
            percent_under_split_max++;
        }
    }
    LOG_DEBUG("... Percent that are findable: %f\n", percent_under_split_max / sample_size);

    return sample_indexes;
}


/**
 * Searches for movies in each data structure, and records the time it takes to search for them
 * 
 * 
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param sorted_vector the SortedVector to search for movies in
 * @param sorted_list the SortedList to search for movies in
 * @param bst the BST to search for movies in
*/
void search_movies(MovieVector *movies, int total, double *results, SortedMovieVector *sorted_vector, SortedList *sorted_list, BST *bst){

    LOG_INFO("Searching for movies %d in each data structure\n", total);

    int* random_sample = build_sample_indexes(total, movies->size-1, total);

    LOG_DEBUG("Searching sorted vector\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++) {
        find_in_sorted_vector(sorted_vector, movies->movies[random_sample[i]]->title);
    }
    clock_t end = clock();
    results[SEARCH_START + VECTOR_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[SEARCH_START + VECTOR_LOC]);

    LOG_DEBUG("Searching sorted list\n");
    start = clock();
    for (int i = 0; i < total; i++) {
        find_in_sorted_list(sorted_list, movies->movies[random_sample[i]]->title);
    }
    end = clock();
    results[SEARCH_START + LIST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[SEARCH_START + LIST_LOC]);

    LOG_DEBUG("Searching bst\n");
    start = clock();
    for (int i = 0; i < total; i++) {
        bst_find(bst, movies->movies[random_sample[i]]->title);
    }
    end = clock();
    results[SEARCH_START + BST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[SEARCH_START + BST_LOC]);

    free(random_sample);

}

/**
 * Tests that involve writing the data structures out to a file in sorted order.
 *
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param sorted_vector the SortedVector to search for movies in
 * @param sorted_list the SortedList to search for movies in
 * @param bst the BST to search for movies in
 */
void write_tests(MovieVector *movies, int total, double *results, SortedMovieVector *sorted_vector, SortedList *sorted_list, BST *bst){

    LOG_INFO("Writing movies %d in each data structure\n", total);

    LOG_DEBUG("Writing sorted vector\n");
    FILE *file = fopen(SORTED_VECTOR_OUT, "w");

    clock_t start = clock();
    for (int i = 0; i < total; i++) {
        fprintf(file, "%s\n", sorted_vector->movies[i]->title);
    }
    clock_t end = clock();
    fclose(file);

    results[WRITE_START + VECTOR_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[WRITE_START + VECTOR_LOC]);
    
    file = fopen(SORTED_LIST_OUT, "w");
    LOG_DEBUG("Writing sorted list\n");
    start = clock();
    node *node = sorted_list->head;
    while (node != NULL) {
        fprintf(file, "%s\n", node->movie->title);
        node = node->next;
    }
    end = clock();
    fclose(file);
    results[WRITE_START + LIST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[WRITE_START + LIST_LOC]);
    

    LOG_DEBUG("Writing bst\n");
    file = fopen(BST_OUT, "w");
    start = clock();
    Movie ** bst_sorted_array = bst_to_sorted_array(bst); // extra step for BST
    for (int i = 0; i < total; i++) {
        fprintf(file, "%s\n", bst_sorted_array[i]->title);
    }
    end = clock();
    fclose(file);
    free(bst_sorted_array);

    results[WRITE_START + BST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[WRITE_START + BST_LOC]);

}

/**
 * Removes movies from each data structure, and records the time it takes to remove them
 *
 *
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param sorted_vector the SortedVector to search for movies in
 * @param sorted_list the SortedList to search for movies in
 * @param bst the BST to search for movies in
 */
void remove_tests(MovieVector *movies, int total, double *results, SortedMovieVector *sorted_vector, SortedList *sorted_list, BST *bst) {
    LOG_INFO("Removing movies %d in each data structure\n", total);

    int* random_sample = build_sample_indexes(total, movies->size-1, total);

    LOG_DEBUG("Removing sorted vector\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++) {
        sorted_vector_remove(sorted_vector, movies->movies[random_sample[i]]->title);
    }
    clock_t end = clock();
    results[REMOVE_START + VECTOR_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[REMOVE_START + VECTOR_LOC]);

    LOG_DEBUG("Removing sorted list\n");
    start = clock();
    for (int i = 0; i < total; i++) {
        sorted_list_remove(sorted_list, movies->movies[random_sample[i]]->title);
    }
    end = clock();
    results[REMOVE_START + LIST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[REMOVE_START + LIST_LOC]);

    LOG_DEBUG("Removing bst\n");
    start = clock();
    for (int i = 0; i < total; i++) {
        bst_remove(bst, movies->movies[random_sample[i]]);
    }
    end = clock();
    results[REMOVE_START + BST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[REMOVE_START + BST_LOC]);

    free(random_sample);


}


/**
 * Runs add front for Vector and Linked List
 * 
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param vector the MovieVector to add movies to
 * @param list the LinkedList to add movies to
*/
void add_front_tests(MovieVector *movies, int total, double *results, MovieVector *vector, LinkedList *list) {

    LOG_INFO("Adding movies %d to front of each data structure\n", total);

    LOG_DEBUG("Adding to vector\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++) {
        vector_add_front(vector, movies->movies[i]);
    }
    clock_t end = clock();
    results[ADD_FRONT + VECTOR_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[ADD_FRONT + VECTOR_LOC]);

    LOG_DEBUG("Adding to list\n");
    start = clock();
    for (int i = 0; i < total; i++) {
        ll_add_front(list, movies->movies[i]);
    }
    end = clock();
    results[ADD_FRONT + LIST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[ADD_FRONT + LIST_LOC]);

}

/**
 * Runs add back for Vector and Linked List
 * 
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param vector the MovieVector to add movies to
 * @param list the LinkedList to add movies to
*/
void add_back_tests(MovieVector *movies, int total, double *results, MovieVector *vector, LinkedList *list) {

    LOG_INFO("Adding movies %d to back of each data structure\n", total);

    LOG_DEBUG("Adding to vector\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++) {
        vector_add_back(vector, movies->movies[i]);
    }
    clock_t end = clock();
    results[ADD_BACK + VECTOR_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[ADD_BACK + VECTOR_LOC]);

    LOG_DEBUG("Adding to list\n");
    start = clock();
    for (int i = 0; i < total; i++) {
        ll_add_back(list, movies->movies[i]);
    }
    end = clock();
    results[ADD_BACK + LIST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[ADD_BACK + LIST_LOC]);

}

/**
 * Runs get for Vector and Linked List
 *
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param vector the MovieVector to add movies to
 * @param list the LinkedList to add movies to

 */
void get_tests(MovieVector *movies, int total, double *results, MovieVector *vector, LinkedList *list)
{

    int *random_sample = build_sample_indexes(total, movies->size - 1, total);

    LOG_INFO("Getting movies %d from each data structure\n", total);

    LOG_DEBUG("Getting from vector\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++)
    {
        vector_get(vector, random_sample[i]);
    }
    clock_t end = clock();
    results[GET + VECTOR_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[GET + VECTOR_LOC]);

    LOG_DEBUG("Getting from list\n");
    start = clock();
    for (int i = 0; i < total; i++)
    {
        ll_get(list, random_sample[i]);
    }
    end = clock();
    results[GET + LIST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[GET + LIST_LOC]);
}

/**
 * Runs remove front for Vector and Linked List
 * 
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param vector the MovieVector to add movies to
 * @param list the LinkedList to add movies to
*/
void remove_front_tests(int total, double *results, MovieVector *vector, LinkedList *list) {

    LOG_INFO("Removing movies %d from front of each data structure\n", total);

    LOG_DEBUG("Removing from vector\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++) {
        vector_remove_front(vector);
    }
    clock_t end = clock();
    results[REMOVE_FRONT + VECTOR_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[REMOVE_FRONT + VECTOR_LOC]);

    LOG_DEBUG("Removing from list\n");
    start = clock();
    for (int i = 0; i < total; i++) {
        ll_remove_front(list);
    }
    end = clock();
    results[REMOVE_FRONT + LIST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[REMOVE_FRONT + LIST_LOC]);

}


/**
 * Runs remove back for Vector and Linked List
 * 
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 * @param vector the MovieVector to add movies to
 * @param list the LinkedList to add movies to
*/
void remove_back_tests(int total, double *results, MovieVector *vector, LinkedList *list) {



    LOG_INFO("Removing movies %d from back of each data structure\n", total);

    LOG_DEBUG("Removing from vector\n");
    clock_t start = clock();
    for (int i = 0; i < total; i++) {
        vector_remove_back(vector);
    }
    clock_t end = clock();
    results[REMOVE_BACK + VECTOR_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[REMOVE_BACK + VECTOR_LOC]);

    LOG_DEBUG("Removing from list\n");
    start = clock();
    for (int i = 0; i < total; i++) {
        ll_remove_back(list);
    }
    end = clock();
    results[REMOVE_BACK + LIST_LOC] = (double)(end - start) / CLOCKS_PER_SEC;
    LOG_DEBUG("...result was %f\n", results[REMOVE_BACK + LIST_LOC]);

}


/**
 * Runs all tests, entry function to running the tests
 *
 * @param movies the MovieVector to act as the TestSet
 * @param total the total number of movies to pull from MovieVector
 * @param results array of doubles to store the results in
 */
void run_tests(MovieVector *movies, int total, double *results) {
// initialize the data structures

    LOG_INFO("Running Tests on %d movies\n", total);
    SortedMovieVector *sorted_vector = new_sorted_vector();
    SortedList *sorted_list = new_sorted_list();
    BST *bst = new_bst();

    // add movies to each data structure
    add_movies(movies, total, results, sorted_vector, sorted_list, bst);

    // search for movies in each data structure
    search_movies(movies, total, results, sorted_vector, sorted_list, bst);

    //write out to files
    write_tests(movies, total, results, sorted_vector, sorted_list, bst);

    // remove movies from each data structure
    remove_tests(movies, total, results, sorted_vector, sorted_list, bst);


    // MoviesVector and LinkedList for add front, get and add back
    MovieVector *vector = new_vector();
    LinkedList *list = new_linked_list();    
    
    // add movies to front of each data structure
    add_front_tests(movies, total, results, vector, list);
    get_tests(movies, total, results, vector, list);
    remove_front_tests(total, results, vector, list);

    // resetting due to capacity of vector already being the correct size
    free_vector(vector);
    free_linked_list(list);
    vector = new_vector();
    list = new_linked_list();

    // add movies to back of each data structure
    add_back_tests(movies, total, results, vector, list);
    remove_back_tests(total, results, vector, list);


    // free data structures (just free, no need to remove movies from them)
    free_sorted_vector(sorted_vector);
    free_sorted_list(sorted_list);
    free_vector(vector);
    free_linked_list(list);

    free_bst(bst);
    LOG_INFO("Finished running tests\n\n");
}


#endif // TESTS_H