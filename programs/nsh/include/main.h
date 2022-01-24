/*
	@author : eltertrias
	@brief : global header for main control code
*/


#ifndef MAIN_GLOBAL_H
#define MAIN_GLOBAL_H


#include <stdlib.h>
#include <stdint.h>


/*
	@brief : cleanly exits the shell by freeing memory and shuting down everything else unneeded
	@param exit_status : determines the status program will exit with, use EXIT_FAILURE and EXIT_SUCCESS macros here
*/
extern void exitShell(uint8_t exit_status);
#endif