/*
	@author = eltertrias
	@brief = include file for cat programm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>


enum CLI_FLAGS
{
	CLI_FLAG_E 		= 0x1,
	CLI_FLAG_n 		= 0x2,
	CLI_FLAG_T 		= 0x4,
	CLI_FLAG_HELP	= 0x8,
	CLI_FLAG_VER	= 0x10
};


/*
	@brief : interprets command line arguments that aren't flags, but are files(or stdin -)
	@param argc : amount of CLU arguments
	@param argv : list of strings that are CLI arguments
	@return : 0 on success, -1 on error
*/
static int interpretInput(int argc, char **argv);

/*
	@breif : reads from FD to stdout
	@param input : specifies the FD to read from
	@return : 0 on success, -1 on error
*/
static int readToStdout(FILE* input);