/*
	@author = eltertrias
	@brief = defines for the coreutils_library
*/


#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>


#define ERROR_TYPE_NORMAL 		0x0
#define ERROR_TYPE_DEBUG		0x1
#define ERROR_TYPE_DEBUG_FATAL	0x2

#define ERROR_LOCATION_NO		NULL

#define TOGGLE_BIT_ON   1
#define TOGGLE_BIT_OFF  0


/*
	@brief : sets everything according to the supplied CLI flags/attributes
	@param argc : specifies amount of command line arguments
	@param argv : list of strings that are command line arguments
	@param cli_flags : the string representations of flags that should be searched for in argv, the last element should be NULL to indicate the end of list
	@param cli_flags_bits : the bits that should be set in the return variable to turn on the flag, the last element should be 0 to indicate the end of list
	@return : 0 on success, -1 on error
*/
extern size_t interpretCLIattributes(int argc, char **argv, char* cli_flags[], size_t cli_flags_bits[]);

/*
	@brief : Outputs the error in formated way to stderr and exits if needed
	@param location : When outputing errors in debug mode, string is output to stderr and described as location
	@param error : String that will be outputed to stderr which describes the error
	@param type : Tells if the error is debug(can be disabled) or norma(will be available in non-debug program)
	@return : -1 or just exits the program depending on the error type
*/
extern int outputError(uint8_t type, char* location, const char* error, ...);

/*
    @brief : changes the chosen bit in supplied variable to chosen value(ON(1) or OFF(0))
    @param var : pointer to variable where the changes will be made
    @param bitmask : the bit which has to be changed
    @param bit_status : to which status the bit should be changed
*/
extern void toggleBit(size_t* var, size_t bitmask, uint8_t bit_status);

/*
	@brief : Outputs help information and exits
	@str : the help string that should be outputted
*/
extern void outputHelp(char* str);

/*
	@brief : Outputs the version of cat and exits
	@str: the version string that should be outputed
*/
extern void outputVersion(char* str);