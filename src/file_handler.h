/**
 * Name: Tracy U
 * CS 5008, Fall 2025
 * 
 * 
 * Reference: From Speed Comparison Homework. 
 * Various functions for handling files.
 * 
 * @author Albert Lionelle
*/

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include "logging.h"


/**
 * Initializes the results file with a header. This will either create
 * or overwrite the file if one already exists.
 * 
 * @param filename The name of the file to write to.
 * @param header The header to write to the file.
 * @return true if the file was created successfully, false otherwise.
*/
bool initialize_results_file(const char * filename, const char * header) {
    FILE * file = fopen(filename, "w");
    if (file == NULL) {
        LOG_ERROR("Could not open file: %s", filename);
        return false;
    }
    fprintf(file, "%s", header);
    fclose(file);
    return true;
}

/**
 * Writes a line to the results file. This appends to the filename,
 * so assumes it is already created with a header.
 * 
 * @param filename The name of the file to write to.
 * @param line The line to write to the file. Double value array.
 * 
 * @return true if the line was written successfully, false otherwise.
*/
bool write_line(const char * filename, double* line, int length) {
    
    FILE * file = fopen(filename, "a");
    if (file == NULL) {
        LOG_ERROR("Could not open file: %s", filename);
        return false;
    }
    for (int i = 0; i < length; i++) {
        if(i > 0) {
            fprintf(file, ",");
        }
        fprintf(file, "%f", line[i]);
    }
    fprintf(file, "\n");
    fclose(file);
    return true;
}



#endif // FILE_HANDLER_H