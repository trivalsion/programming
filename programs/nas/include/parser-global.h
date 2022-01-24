/*
	@author : eltertrias
	@brief : contains global parser functions
*/


#ifndef INIT_GLOBAL_H
#define INIT_GLOBAL_H


#include <asm-config.h> // Will automatically include the correct one as it should be in arch directory which will automatically be resolved using build system
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>


struct parserInfo
{
	char* input_file_path; // file with assembly sources
	char* output_file_path;	// file to which binary output will be written

	char** instruction_mnemonics;
	arch_opcode_t* instruction_opcodes;

	size_t current_input_file_line_number;
};

struct lineInfo
{
	size_t line_type;	// Type of the current line
	size_t arguments_amount;
	char* command;	// The command on the current line - e.g. insturction mnemonic or a label name
	char** arguments; // An array of arguments in form strings
};


/*
	@brief : starts the file parsing proccess
	@param parser_info : a pointer to a parserInfo structure where all fields are filled in, used for getting file names and mnemonic:opcode pairs
	@return : 0 on success, -1 on fail
*/
extern int parserInit(struct parserInfo* parser_info);

/*
	@brief : cleans the file from tabs and consecutive spaces by replacing them with single spaces
	@param parsed_file_size : the size of the mapped file
	@param output_buffer_pointer_variable : a pointer to a pointer variable, here the pointer to malloc buffer with cleaned file will be put, the buffer will be of parsed_file_size
	@param output_buffer_size : a pointer to a variable which will hold the size of the new malloc buffer in output_buffer_pointer_variable
	@return : -1 on fail, 0 on success
*/
extern int cleanFile(ssize_t parsed_file_size, char** output_buffer_pointer_variable, ssize_t* output_buffer_size);
#endif