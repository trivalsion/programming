/*
	@author : eltertrias
	@brief : global header for getting input
*/


#ifndef GET_INPUT_GLOBAL_H
#define GET_INPUT_GLOBAL_H


#include <stdio.h>
#include <stdint.h>


#define INPUT_TYPE_STDIN		0
#define INPUT_TYPE_FILE 		1
#define INPUT_TYPE_COMMAND 		2

#define GET_INPUT_RETURN_NO_COMMAND_SUPPLIED -2	// return if no command(only \n) was supplied by the user to the getInput function


struct commandInfo
{
	char* input_file_path; // if the input is from stdin it should be NULL, otherwise it should be the path to the file from which the current command was read

	char* command; // the common (e.g. built-in or external executable)
	char** arguments;	// An array of arguments in form strings

	size_t arguments_amount;	// amount of arguments in the arguments array in variable above
	size_t current_line_number; // If this is not zero then on syntax error line number should be reported by the shell(beacuse if it is not zero then it is a file)
};


/*
	@brief : the function initializes the getting input proccess
	@param input_type : the type of input that should be used to get input
	@param command_info_array : pointer to pointer which will be filled with an address of malloced commandInfo array, the end of the array is marked with commandInfo structure where command field is NULL
	@return : 0 on success, -1 on fail
*/
extern int getInput(uint16_t input_type, struct commandInfo* command_info_array[]);

/*
	@brief : frees the pointer fields in supplied commandInfo structure and replaces addresses in pointers with NULL
	@param command_info : pointer to the commandInfo struct so that fields could be edited to replace pointers with NULL
*/
extern void freeCommandInfo(struct commandInfo* command_info);
#endif