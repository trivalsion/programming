/*
	@author : eltertrias
	@brief : header for built-in command's code
*/


#ifndef BUILTIN_GLOBAL_H
#define BUILTIN_GLOBAL_H


#define BUILTIN_EXECUTION_FAILED 	-1
#define BUILTIN_COMMAND_NOT_FOUND	-2


#include <stddef.h>


/*
	@brief : executes the builtin command if it exists
	@param builtin_command_name : string with the name of the builtin command
	@param command_arguments : the list of arguments(strings) that should be passed to the builtin command
	@param command_arguments_amount : amount of arguments in the command_arguments
	@return : 0 if command was found and executed, -1 if execution failed, -2 if the built-in command does not exist
*/
int builtinExecute(char* builtin_command_name, char** command_arguments, size_t command_arguments_amount);

/*
	@brief : tells if the builtin command exists or not, but does not execute it
	@param builtin_command_name : string with the name of the command that should be checked for wether it is a builtin command
	@return : 0 if the built-in command with supplied name exists, -1 if the built-in command with supplied name does not exit
*/
int builtinExists(char* builtin_command_name);
#endif