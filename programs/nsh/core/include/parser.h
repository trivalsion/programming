/*
	@author : eltertrias
	@brief : local header for the parser
*/


#ifndef PARSER_LOCAL_H
#define PARSER_LOCAL_H


#include <stddef.h>
#include <get_input.h>
#include <common.h>
#include <parser.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
	@breif : parses a line and puts it into a commandInfo structure
	@param line_info : pointer to a commandInfo struct to fill all of the fields in it, fields in the structure are allocated using malloc to free use freeCommandInfo()
	@param buffer : pointer to a buffer with command(s)
	@param buffer_location : index in the buffer, index should correspond to the start of the line which has to be parsed
	@return : -1 on error, 0 on success
*/
static int parse_line(struct commandInfo* command_info, char* buffer, size_t buffer_location);

/*
	@brief : merges multiline strings into single line by removing the '\n' characters after the line if the line end in `\`
	@param input_buffer : user input buffer where lines should be merged
	@param input_buffer_size : byte size of the input buffer
*/
static void merge_multi_line_commands(char* input_buffer, size_t input_buffer_size);

/*
	@brief : splits the lines into several commands when boolean operators(|| or &&) are encountered
	@param input_buffer : pointer to a buffer with user input
	@param current_input_buffer_location : the index in the input buffer for where the current line starts
*/
static void parse_boolean_operators(char* input_buffer, size_t current_input_buffer_location);
#endif