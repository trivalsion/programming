/*
	@author : eltertrias
	@brief : a local header for the program start code in main
*/


#ifndef MAIN_LOCAL_H
#define MAIN_LOCAL_H


#include <arch-global.h>
#include <asm-config.h>
#include <parser-global.h>
#include <string.h>
#include <common.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <cli_arg_parser-global.h>


#define TEXT_COLOR_ERROR_ON "\033[0;31m"
#define TEXT_COLOR_ERROR_OFF "\033[0m"

#define TEXT_COLOR_MAIN_MESSAGE_ON "\033[1m"
#define TEXT_COLOR_MAIN_MESSAGE_OFF "\033[0m"

#define TEXT_COLOR_EXTRA_MESSAGE_ON "\033[0;34m"
#define TEXT_COLOR_EXTRA_MESSAGE_OFF "\033[0m"
#endif