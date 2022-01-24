/*
	@author : eltertrias
	@brief : global header for the parser
*/


#ifndef PARSER_GLOBAL_H
#define PARSER_GLOBAL_H


#include <stdint.h>
#include <stddef.h>


/*
	@brief : the function interprets the user input, pases it on to other parsing functions and returns already parsed objects
	@param input_buffer : pointer to a pointer to a string containing input(could be either from the file or stdin). The string passed to input argument SHOULD be MALLOCED so it could be resized, the pointer to pointer is needed so that address could be changed after realloc
	@param input_buffer_size : pointer to the size of the input buffer, pointer is needed so that size could be changed
	@param input_buffer_type : type of input(e.g. script or stdin)
	@param command_info_array: pointer to pointer which will be filled with an address malloced of commandInfo array, the end of the array is marked with commandInfo structure where command field is NULL
	@return : -1 on fail, 0 on success
*/
extern int parseInput(char** input_buffer, size_t* input_buffer_size, uint8_t input_buffer_type, struct commandInfo** command_info_array);
#endif