/*
	@author : eltertrias
	@brief : includes global funcions prototypes from the output_composer
*/


#ifndef OUTPUT_COMPOSER_GLOBAL_H
#define OUTPUT_COMPOSER_GLOBAL_H


#include <stdio.h>
#include <arch-global.h>


/*
	@brief : writes out instructions and data into the binary output file
	@param output_binary_file_fd : a pointer to a FILE struct pointer so that output_composer could modify the contents of the FILE struct
	@param parser_info : pointer to parserInfo struct to get file paths
	@param data_buffer : binary data that should be written to the output binary file
	@param data_buffer_size : byte size of the data_buffer
	@return : -1 on fail, 0 on success
*/
int writeFile(FILE** output_binary_file_fd, struct parserInfo* parser_info, void* data_buffer, size_t data_buffer_size);

/*
	@brief : composes binary output out of the line from the input assembly file by mixing opcode and the data supplied to it
	@param parser_info : pointer to a parser info struct to get mnemonics and opcodes
	@param line_info : pointer to the line structure of the currently parsed line
	@param output_binary : the binary instruction made by interpreting a line in the input assembly file and combining opcode and it's arguments
	@return : 0 on success, -1 on fail
*/
int composeBinaryOutput(struct parserInfo* parser_info, struct lineInfo* line_info, arch_opcode_t* output_binary);

/*
	@brief : converts argument from mnemonic into numbers/binary
	@param parser_info : pointer to a parser info struct to get file path and current line number
	@param argument_buffer : pointer to the buffer with the argument string
	@param converted_argument : input argument converted into binary form
	@return : 0 on success, -1 on fail
*/
int stringToBinaryArgumentConverter(struct parserInfo* parser_info, char* argument_buffer, arch_opcode_t* converted_argument);

#endif