/*
	@author : eltertrias
	@brief : global header for the shell command line argument parser
*/


#ifndef SHELL_CMD_ARG_PARSER_GLOBAL_H
#define SHELL_CMD_ARG_PARSER_GLOBAL_H


#include <stdint.h>


#define BITFLAG_COMMAND 		0x1 // when a command is passed to the shell through -c command line argument
#define BITFLAG_FILE			0x2 // indicates that a file script was passed to the shell's binary as a command line argument


/*
	@brief : parses the command line arguments supplied to the shell executable. If this function was called then call freeCLIarguments() before the program's exit.
	@param argc : the argc variable passed to the main() function
	@param argv : the argv variable passed to the main() function
	@param flags : a pointer to variable where the bitflags would be set depending on what command line arguments were passed to the shell
	@return : 0 on success, -1 on fail
*/
extern int parseCLIarguments(int argc, char** argv, uint16_t* flags);

/*
	@brief : returns the data value for the CLI argument if it had any
	@param : the macro define for the flag(the flag that represents the argument) to know which data to return
	@param : pointer to a pointer where the address of data supplied to the flag will be put, the data will be in a form of a string
	@return : -1 on error, 0 on success
*/
extern int getCLIargumentValue(uint16_t flag, char** data);

/*
	@brief : frees all of the buffers in the command line argument parser and should always be called before exit
*/
extern void freeCLIarguments(void);
#endif