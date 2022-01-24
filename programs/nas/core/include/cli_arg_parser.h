/*
	@author : eltertrias
	@brief : a header for cli argument parser
*/


#ifndef CLI_ARG_PARSER_LOCAL_H
#define CLI_ARG_PARSER_LOCAL_H


#include <getopt.h>
#include <common.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <parser-global.h>
#include <cli_arg_parser-global.h>


#define VERSION_INFO "NAS Assembler, Version Beta"


/*
	@brief : prints out a help message
*/
static void printHelp(void);

/*
	@brief : prints out the version of the current program
*/
static void printVersion(void);
#endif