/*
	@author : eltertrias
	@brief : local header for Conway's game of life
	@information:
		* Terminal manipulation ANSI Escape Codes
			* Terminal ANSI Escape Codes list - https://wiki.bash-hackers.org/scripting/terminalcodes
				* Man page containing terminal capabilities and all of the supported ANSI codes - "man terminfo"
			* Using ANSI codes guide - https://notes.burke.libbey.me/ansi-escape-codes/
*/


#ifndef CONWAY_GAME_OF_LIFE_LOCAL_H
#define CONWAY_GAME_OF_LIFE_LOCAL_H


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <termios.h>


#define RETURN_FAIL 	-1
#define RETURN_SUCCESS 	0

#define REMOVE_UNUSED_WARNING(x) (void)(x)

#define VERSION_INFO "Conway's Game of Life Implementation"

/*
'\x1b'(same as '\033') is a control sequence introducer(CSI) which is a byte representing the start of an escape sequence(start of an escape sequence in ANSI terminal is always a byte with number 27 = 0x1b = 033) that terminal must not interpret as normal character(in c \x in a string means that the numbers after \x represent a hexadecimal number and not ASCII characters, \0 is the same, but means it is octal). '[...' that goes after the CSI, is the escape sequence itself which represents a command that the terminal must execute and not interpret it as normal ASCII characters, and thus not output them to the screen */
#define RESET_CURSOR 			"\x1B[0m"		// reset cursor
#define MOVE_CURSOR(x, y)		printf("\x1B[%lu;%luH", (x), (y))	// x and y arguments should be unsigned integers indicating cell coordinates in the terminal(e.g. (6, 67)). !!!! In ANSI escape sequences the first character cell in terminal is not at coordinates 0,0 but instead at 1,1 !!!!! !!!!! In ANSI terminals the x and y are basically the wrong way round with x representing height and y representing width(while on real coordinate systems x is width and y is height) so that has to be accounted for when using this and other coordinate-using escape sequences !!!!
#define MOVE_CURSOR_FIXED(x, y)	printf("\x1B[%lu;%luH", (size_t)((y)+1), (size_t)((x)+1)) // macro that accounts for first cell being at 0,0 by adding 1 to x and 1 to y, and accounts for x and y being the wrong way round by supplying y variable on the place of x argument in escape sequence and x variable on the place of y argument
#define HIDE_CURSOR 			"\x1B[?25l"		// makes the cursor invisible
#define SHOW_CURSOR				"\x1B[?25h"		// make cursor visible again

#define RESET_ATTRIB			"\x1B[0m"		// resets all of the text attributes
#define SET_BOLD_ATTRIB			"\x1B[1m"		// sets bold text attribute

#define SET_BACKGROUND_BLUE		"\x1B[44m"

#define CLEAR_SCREEN			"\x1B[H\x1B[J"
#define CLEAR_WHOLE_LINE		"\x1B[2K"		// Cleares the whole line where the cursor is

#define ERROR_TYPE_NORMAL 	0	// Use when error was not caused by an external libraries functions. 	Output format - "error: <CALLER_SUPPLIED_ERROR_STRING>\n"
#define ERROR_TYPE_LIB		1	// Use when error was caused by external libraries functions. 			Output format - "library error: <CALLER_SUPPLIED_ERROR_STRING>: <PERROR_ERROR_STRING\n"
#define ERROR_TYPE_SYNTAX 	2	// Error for when the syntax of the input file is incorrect, requires additional arguments in the place of optional arguments(...) in the function call in the corresponding order - parsed file path and currently parsed line number in it.			Output format - "syntax error: <PARSED_FILE_PATH>:<CURRENTLY_PARSED_LINE_NUM>: <CALLER_SUPPLIED_ERROR_STRING>\n"
#define ERROR_TYPE_DEBUG 	3	// Not an error but a debug message, different from printf in a way that it can be disabled using the makefile. Output format - "debug: <CALLER_SUPPLIED_ERROR_STRING>\n"

#define TEXT_COLOR_ERROR_ON "\x1B[0;31m"
#define TEXT_COLOR_ERROR_OFF "\x1B[0m"

#define TEXT_COLOR_MAIN_MESSAGE_ON "\x1B[1m"
#define TEXT_COLOR_MAIN_MESSAGE_OFF "\x1B[0m"

#define TEXT_COLOR_EXTRA_MESSAGE_ON "\x1B[0;34m"
#define TEXT_COLOR_EXTRA_MESSAGE_OFF "\x1B[0m"

#define SET_FOREGROUND_COLOR_DEFAULT	"\x1B[39m"
#define SET_FOREGROUND_COLOR_BLACK		"\x1B[30m"
#define SET_BACKGROUND_COLOR_DEFAULT	"\x1B[49m"
#define SET_BACKGROUND_COLOR_BLACK		"\x1B[40m"
#define SET_BACKGROUND_COLOR_BLUE		"\x1B[44m"


#define NUMBER_OF_ROWS 		40
#define NUMBER_OF_COLUMNS 	40

#define CELL_ALIVE 	1
#define CELL_DEAD 	0


/*
	@brief : prints out a help message
*/
static void printHelp(void);

/*
	@brief : prints out the version of the current program
*/
static void printVersion(void);

/*
	@brief : outputs an error message to stderr
	@param error_message : the string that will be outputted to stderr
	@param error_type : changes the output depending on why error function was called
	@param ... : extra parameters for different error types and arguments for vfpritnf
	@return : -1
*/
static int outputError(char* error_message, uint8_t error_type, ...);

/*
	@brief : parses the command line arguments supplied to the shell executable. If this function was called then call freeCLIarguments() before the program's exit.
	@param argc : the argc variable passed to the main() function
	@param argv : the argv variable passed to the main() function
	@param flags : a pointer to variable where the bitflags would be set depending on what command line arguments were passed to the shell
	@return : 0 on success, -1 on fail
*/
static int parseCLIarguments(int argc, char** argv);

/*
	@brief : frees all of the buffers in the command line argument parser and should always be called before exit
*/
static void freeCLIarguments(void);

/*
	@brief : places a cell on the character cell in the terminal and in the local array
	@param x : x coordinate of the cell
	@param y : y coordinate of the the cell
*/
static void place_cell(uint8_t x, uint8_t y);

/*
	@brief : removes a cell from the character cell in the terminal and in the local array
	@param x : x coordinate of the cell
	@param y : y coordinate of the the cell
*/
static void remove_cell(uint8_t x, uint8_t y);

/*
	@brief : places cells from on coordinates supplied by the user in command line arguments and turns on corresponding bytes in the array
	@return : 0 on success, -1 on fail
*/
static int place_initial_cells();

/*
	@brief : the main game loop of the game which places and removes all of the cells
	@return : 0 on success, -1 on fail
*/
static int main_game_loop();

/*
	@brief : prints a string to the terminal in a place where it won't be overwritten by cells
	@param string : the string that should be printed out
	@return : 0 on success, -1 on fail
*/
static int safe_stdin_print(char* string, ...);

/*
	@brief : checks wether the terminal window is large enough to display the game
	@return : 0 if the terminal is large enough, -1 if the terminal isn't large enough
*/
static int terminal_size_check();

/*
	@brief : exits the program safely by freeing allocated memory and restoring terminal settings
	@param exit_status : the status with which the program should exit(success/fail)
*/
static void safe_exit(int exit_status);
#endif