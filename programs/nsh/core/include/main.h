/*
	@author : eltertrias
	@brief : local header for the main file
*/


#ifndef MAIN_LOCAL_H
#define MAIN_LOCAL_H


#include <shell_cmd_arg_parser.h>
#include <common.h>
#include <interpreter.h>
#include <get_input.h>
#include <env_variables.h>
#include <main.h>


/*
	@brief : the function that calls all of the other functions, it is needed so there is only one return path to main and main has to do cleanup work like freeing only in one control path and not after return of each function called by it
	@param argc : argc that is passed to the main function
	@param argv : argv that is passed to the main function
	@return : -1 on fail, 0 on success
*/
static int calling_function(int argc, char* argv[]);
#endif