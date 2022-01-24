/*
	@author : eltertrias
	@brief : local header for the interpretation code
*/


#ifndef INTERPRETER_LOCAL_H
#define INTERPRETER_LOCAL_H


#include <interpreter.h>
#include <builtin.h>
#include <common.h>
#include <env_variables.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>


#define INTERPRETER_FLAG_AND 	0x1 // if this flag is on, it indicates that the previous command was &&
#define INTERPRETER_FLAG_OR		0x2	// if this flag is on, it indicates that the previous command was ||


/*
	@brief : concatenates the executable name and the prefix creating it's full path
	@param executable_name : the string with the name of the executable(command) that is needs to be attatched to the prefix
	@param path_prefix : the string with the prefix which has to be attached to the name of the executable
	@param output : NULL-terminated string where the concatenated output should be sent
	@param max_length : the max length of the output string
	@return : -1 on fail, 0 on success
*/
static int create_full_executable_path(char* executable_name, char* path_prefix, char* output, size_t max_length);

/*
	@brief : creates an array of arguments with the executable name going first so it is compatible with execv
	@param executable_name : string containing the executable name or full path
	@param command_info : command_info struct used to obtain the arguments that were supplied to the command
	@param output_array : pointer to a character piointer array, this pointer will be filled with the address of a malloc array created for execv from executable name and the arguments
	@param output_array_elements_amount : the amount of arguments/array elements that are in the output_array
	@return : 0 on success, -1 on fail
*/
static int create_exec_argument_input(char* executable_name, struct commandInfo* command_info, char*** output_array, size_t *output_array_elements_amount);

/*
	@brief : frees the exec input created by create_exec_argument_input()
	@param exec_argument_input : the array allocated for exec input
	@param exec_argument_input_size : the size of the allocated array
	@return : 0 on success, -1 on fail
*/
static void free_exec_argument_input(char** exec_argument_input, size_t exec_argument_input_size);

/*
	@brief : starts the binary selected by user in shells child proccess
	@param path_var_value : the value of path variable
	@param path_dirs_delimiter : the string that is the delimiter between the directory paths in the PATH variable
	@param command_info : list of command info struct parsed from used input
	@param current_command : current command location index in the commandInfo struct list
*/
static void execute_program_as_child_proc(char* path_var_value, char* path_dirs_delimiter, struct commandInfo* command_info, size_t current_command);
#endif