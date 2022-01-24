/*
	@author : eltertrias
	@brief : includes global architecture specific functions
*/


#ifndef ARCH_GLOBAL_H
#define ARCH_GLOBAL_H


#include <asm-config.h> // Will automatically include the correct one as it should be in arch directory which will automatically be resolved using build system
#include <common.h>
#include <parser-global.h>


/*
	@brief : fills in the architecture specific part of the parserInfo struct
	@param parser_info : a pointer to a parserInfo struct, archInit fills in the opcodes and mnemonics fields in this struct
	@return : 0 on success, -1 on fail
*/
extern int archInit(struct parserInfo* parser_info);

/*
	@brief : combines the arguments(data) and the opcode into one binary instruction
	@param parser_info : pointer to parserInfo struct to access file path and line number
	@param opcode : current instruction opcode in a binary form
	@param arguments : a list of binary equivalents for the arguments supplied by the user
	@param arguments_amount : amount of arguments supplied by the user on the current line
	@param output_buffer : the buffer where binary for opcodes and arguments combined will be put
	@return : 0 on success, -1 on fail
*/
extern int archCombineOpcodeData(struct parserInfo* parser_info, arch_opcode_t opcode, arch_opcode_t* arguments, uint8_t arguments_amount, arch_opcode_t* output_buffer);
#endif