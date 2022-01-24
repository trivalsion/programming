/*
	@author : eltertrias
	@brief : a header for the common functions file
*/


#ifndef COMMON_GLOBAL_H
#define COMMON_GLOBAL_H


#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>


#define ERROR_TYPE_NORMAL 	0	// Use when error was not caused by an external libraries functions. 	Output format - "error: <CALLER_SUPPLIED_ERROR_STRING>\n"
#define ERROR_TYPE_LIB		1	// Use when error was caused by external libraries functions. 			Output format - "library error: <CALLER_SUPPLIED_ERROR_STRING>: <PERROR_ERROR_STRING\n"
#define ERROR_TYPE_SYNTAX 	2	// Error for when the syntax of the input file is incorrect, requires additional arguments in the place of optional arguments(...) in the function call in the corresponding order - parsed file path and currently parsed line number in it.			Output format - "syntax error: <PARSED_FILE_PATH>:<CURRENTLY_PARSED_LINE_NUM>: <CALLER_SUPPLIED_ERROR_STRING>\n"
#define ERROR_TYPE_DEBUG 	3	// Not an error but a debug message, different from printf in a way that it can be disabled using the makefile. Output format - "debug: <CALLER_SUPPLIED_ERROR_STRING>\n"

#define RETURN_FAIL 	-1
#define RETURN_SUCCESS 	0

#define TEXT_COLOR_ERROR_ON "\033[0;31m"
#define TEXT_COLOR_ERROR_OFF "\033[0m"

#define TEXT_COLOR_MAIN_MESSAGE_ON "\033[1m"
#define TEXT_COLOR_MAIN_MESSAGE_OFF "\033[0m"

#define TEXT_COLOR_EXTRA_MESSAGE_ON "\033[0;34m"
#define TEXT_COLOR_EXTRA_MESSAGE_OFF "\033[0m"

#define REMOVE_UNUSED_WARNING(x) (void)(x)

#define TOGGLE_BIT_ON   1	// turns the bit on(sets it to 1)
#define TOGGLE_BIT_OFF  0	// turns the bit off(sets it to 0)


/*
	@brief : outputs an error message to stderr
	@param error_message : the string that will be outputted to stderr
	@param error_type : changes the output depending on why error function was called
	@param ... : extra parameters for different error types and arguments for vfpritnf
	@return : -1
*/
extern int outputError(char* error_message, uint8_t error_type, ...);

/*
	@brief : toggles/sets a particular bit on or off
	@param var : pointer to the variable where the bit should be toggled
	@param bitmask : bitmask/number where the bit which should be toggled in the variable is set to 1
	@param bit_status : indicates whether the bit should turned on or off
*/
extern void toggleBit(size_t* var, size_t bitmask, uint8_t bit_status);
#endif