/**
 * Name: Tracy U
 * CS 5008, Fall 2025
 * 
 * Reference: From previous assignments
 * 
 * @author Albert Lionelle
 * 
 * Written for CS 5008 @ Northeastern University
*/


#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

#define LOG_LEVEL __shared__log_level
#define LOG_LEVEL_ERROR 3 // mainly want error messages to always show
#define LOG_LEVEL_WARN 2 // sometimes want warning messages to show in addition to errors
#define LOG_LEVEL_INFO 1 // info is pretty common, also called verbose.
#define LOG_LEVEL_DEBUG 0 // the most detailed, only for debugging, shows everything

int LOG_LEVEL = LOG_LEVEL_ERROR;


#define LOG(level, str, ...) if (level >= LOG_LEVEL) { printf(str __VA_ARGS__); }
#define LOG_ERROR(...) LOG(LOG_LEVEL_WARN,"(ERROR): ", __VA_ARGS__)
#define LOG_WARN(...) LOG(LOG_LEVEL_WARN, "(WARNING): ", __VA_ARGS__)
#define LOG_DEBUG(...) LOG(LOG_LEVEL_DEBUG, "(DEBUG): ", __VA_ARGS__)
#define LOG_INFO(...) LOG(LOG_LEVEL_INFO, "(INFO): ", __VA_ARGS__)

#endif // LOGGING_H