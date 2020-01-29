/**
 * This is a file with standard macros for printing and asserting with a fail message
 */
#pragma once

#include <stdio.h>
#include <assert.h>

// based off of code in https://stackoverflow.com/questions/15305310/predefined-macros-for-function-name-func 
// determine the name of the function MACRO
#ifndef __FUNCTION_NAME__
    #ifdef WIN32   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__  
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__ 
    #endif
#endif

// printing
// print a String message 
#define LOG(msg) fprintf(stdout, "(File: %s, Function: %s, line: %d): %s\n", __FILE__ , __FUNCTION_NAME__, __LINE__ , msg)

// print a integer message
#define LOG_D(integer) fprintf(stdout, "(File: %s, Function: %s, line: %d): %d\n", __FILE__ , __FUNCTION_NAME__, __LINE__ , integer)

// print a char message
#define LOG_C(character) fprintf(stdout, "(File: %s, Function: %s, line: %d): %c\n", __FILE__ , __FUNCTION_NAME__, __LINE__ , character)

//print a size_t message
#define LOG_ZU(size) fprintf(stdout, "(File: %s, Function: %s, line: %d): %zu\n", __FILE__ , __FUNCTION_NAME__, __LINE__ , size)

//print a size_t message
#define LOG_F(size) fprintf(stdout, "(File: %s, Function: %s, line: %d): %f\n", __FILE__ , __FUNCTION_NAME__, __LINE__ , size)

// Print a fail message and abort 
#define FAIL(msg) \
    fprintf(stderr, "(File: %s, Function: %s, line: %d) - FAIL: %s\n", __FILE__ , __FUNCTION_NAME__, __LINE__ , msg);\
    abort()

// print the OK message
#define OK(msg) fprintf(stdout, "(File: %s, Function: %s, line: %d) - OK: %s\n", __FILE__ , __FUNCTION_NAME__, __LINE__ , msg)

// testing
// If test is true print OK message with test name
// otherwise print FAIL message with name and exit
#define T_TRUE(test, name) \
    if(test) { \
        OK(name); \
    } else { \
        FAIL(name); \
    }
// If test is false print OK message with test name
// otherwise print FAIL message with name and exit
#define T_FALSE(test, name) T_TRUE(!(test), name)

// ASSERT MACRO
// Print the message and abort only if the test is false
#define ASSERT(test, msg) \
    if (!(test)){ \
        fprintf(stderr, "%s\n", msg); \
        abort(); \
    }
