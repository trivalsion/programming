/*
	@author : eltertrias
	@brief : local header for built-in functions
*/


#ifndef BUILTIN_LOCAL_H
#define BUILTIN_LOCAL_H


#include <builtin.h>
#include <stddef.h>
#include <common.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <main.h>


/*
	@brief : cleanly(e.g. cleans memory) exits the shell
	@param arguments : the list of arguments(strings) that were supplied to this built-in command
	@param arguments_amount : amount of arguments in the arguments list array
	@return : 0 on success, -1 on fail
*/
static int builtin_exit(char** arguments, size_t arguments_amount);

/*
	@brief : changes the current working directory of the shell
	@param arguments : the list of arguments(strings) that were supplied to this built-in command
	@param arguments_amount : amount of arguments in the arguments list array
	@return : 0 on success, -1 on fail
*/
static int builtin_cd(char** arguments, size_t arguments_amount);

/*
	@brief : prints it's arguments to stdin
	@param arguments : the list of arguments(strings) that were supplied to this built-in command
	@param arguments_amount : amount of arguments in the arguments list array
	@return : 0 on success, -1 on fail
*/
static int builtin_echo(char** arguments, size_t arguments_amount);

/*
	@brief : prints out the help message
	@param arguments : the list of arguments(strings) that were supplied to this built-in command
	@param arguments_amount : amount of arguments in the arguments list array
	@return : 0 on success, -1 on fail
*/
static int builtin_help(char** arguments, size_t arguments_amount);
#endif