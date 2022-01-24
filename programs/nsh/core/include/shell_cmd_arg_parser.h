/*
	@author : eltertrias
	@brief : local header for for the shell command line arguments parser
*/


#ifndef SHELL_CMD_ARG_PARSER_LOCAL_H
#define SHELL_CMD_ARG_PARSER_LOCAL_H


#include <getopt.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <common.h>
#include <shell_cmd_arg_parser.h>


#define VERSION_INFO "nSH Shell, Version Beta 0.1"


/*
	@brief : prints out a help message
*/
static void printHelp(void);

/*
	@brief : prints out the version of the current program
*/
static void printVersion(void);
#endif