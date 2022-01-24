/*
	@author : eltertrias
	@brief : a local header for the assemblers parser
*/


#ifndef PARSER_LOCAL_H
#define PARSER_LOCAL_H


#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arch-global.h>
#include <asm-config.h>
#include <common.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <parser-global.h>
#include <output_composer-global.h>
#include <stdint.h>


#define LINE_TYPE_ERROR			0
#define LINE_TYPE_PREPROCESSOR 	1
#define LINE_TYPE_COMMENT 		2
#define LINE_TYPE_LABEL			3
#define LINE_TYPE_INSTRUCTION	4


/*
	@brief : controls the file parsing proccess
	@param parser_info : pointer to parserInfo struct so mnemonics and opcodes could be read
	@param parsed_file_buffer : the buffer where mmap(), memory mapped the file. parseFile functions puts a \n at the end of it so every line is ended equally
	@paran parsed_file_stats : pointer to a stat structure with information about the mapped file
	@return : 0 on success, -1 on fail
*/
static int parseFile(struct parserInfo* parser_info, char* parsed_file_buffer, struct stat* parsed_file_stats);

/*
	@brief : gets the type of the current line(e.g. comment, label, preproccesor directive, instruction...)
	@param parser_info : pointer to parser Info struct for input file path and current line number
	@param file_buffer : pointer to a buffer with assembly file contents
	@param file_buffer_location : index in the array in file_buffer that is the start of the line which has to be parsed
	@return : 0 on error, line type's number equivalent on success
*/
static size_t getLineType(struct parserInfo* parser_info, char* file_buffer, size_t file_buffer_location);

/*
	@breif : parses a line an seperates it into a lineInfo structure
	@param parser_info : pointer to parserInfo struct for input file path and current line number
	@param line_info : pointer to a lineInfo struct to fill all of the fields in it, fields in the structure are allocated using malloc to free use freelineInfo()
	@param file_buffer : pointer to a buffer with assembly file contents
	@param file_buffer_location : index in the array in file_buffer that is the start of the line which has to be parsed
	@return : -1 on error, 0 on success
*/
static int parseLine(struct parserInfo* parser_info, struct lineInfo* line_info, char* file_buffer, size_t file_buffer_location);

/*
	@brief : frees the fields in supplied lineInfo structure and replaces pointers with NULL
	@param line_info : pointer to the line info struct so that fields could be edited to replace pointers with NULL
*/
static void freelineInfo(struct lineInfo* line_info);
#endif