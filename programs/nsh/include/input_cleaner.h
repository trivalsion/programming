/*
	@author : eltertrias
	@brief : global header for the input cleaner
*/


#ifndef INPUT_CLEANER_GLOBAL_H
#define INPUT_CLEANER_GLOBAL_H


#include <stddef.h>


/*
	@brief : cleans the input buffer and it's output is located directly in the input variable's array as it is just changed and reallocated to new size
	@param input : pointer to a pointer to a string containing input(could be either from the file or stdin). The string passed to input argument SHOULD be MALLOCED so it could be resized, the pointer to pointer is needed so that address could be changed after realloc
	@param input_size : pointer to the size of the input buffer, pointer is needed so that size could be changed
	@return : -1 on fail, 0 on success
*/
extern int cleanInput(char** input, size_t* input_size);
#endif