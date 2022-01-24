/*
	@author : eltertrias
	@brief : local header for getting input
*/


#ifndef GET_INPUT_LOCAL_H
#define GET_INPUT_LOCAL_H


#include <stdio.h>
#include <stdlib.h>
#include <get_input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <common.h>
#include <ctype.h>
#include <string.h>
#include <input_cleaner.h>
#include <shell_cmd_arg_parser.h>
#include <parser.h>
#include <env_variables.h>


/*
	@brief : gets the rest of the current command from the next lines if the user has split the current command in 2 or more lines using \
	@param input_buffer : pointer to pointer to NULL-terminated malloced buffer containing user's input from the first line of the command, pointer to pointer is needed so that the buffer pointer could be altered during reallocation
	@param input_buffer_size : pointer to the size of the input_buffer in bytes
	@return : -1 on error, 0 on success
*/
static int get_commands_next_line_input(char** input_buffer, size_t* input_buffer_size);
#endif