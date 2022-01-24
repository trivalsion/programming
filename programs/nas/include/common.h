/*
	@author : eltertrias
	@brief : includes functions common for multiple parts of the assembler like error handling
*/


#ifndef COMMON_GLOBAL_H
#define COMMON_GLOBAL_H


#include <stdint.h>
#include <asm-config.h>
#include <stddef.h>


#define ERROR_TYPE_NORMAL 	0	// Use when error was not caused by an external libraries functions. 	Output format - "error: <CALLER_SUPPLIED_ERROR_STRING>\n"
#define ERROR_TYPE_LIB		1	// Use when error was caused by external libraries functions. 			Output format - "library error: <CALLER_SUPPLIED_ERROR_STRING>: <PERROR_ERROR_STRING\n"
#define ERROR_TYPE_SYNTAX 	2	// Error for when the syntax of the input file is incorrect, requires additional arguments in the place of optional arguments(...) in the function call in the corresponding order - parsed file path and currently parsed line number in it.			Output format - "syntax error: <PARSED_FILE_PATH>:<CURRENTLY_PARSED_LINE_NUM>: <CALLER_SUPPLIED_ERROR_STRING>\n"
#define ERROR_TYPE_DEBUG 	3	// Not an error but a debug message, different from printf in a way that it can be disabled using the makefile. Output format - "debug: <CALLER_SUPPLIED_ERROR_STRING>\n"

#define RETURN_FAIL 	-1
#define RETURN_SUCCESS 	0


/*
	@brief : outputs an error message to stderr
	@param error_message : the string that will be outputted to stderr
	@param error_type : changes the output depending on why error function was called
	@param ... : extra parameters for different error types and arguments for vfpritnf
	@return : -1
*/
extern int outputError(char* error_message, uint8_t error_type, ...);
#endif