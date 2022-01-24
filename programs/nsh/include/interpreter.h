/*
	@author : eltertrias
	@breif : global header for interpretation code
*/


#ifndef INTERPRETER_GLOBAL_H
#define INTERPRETER_GLOBAL_H


#include <get_input.h>


/*
	@brief : interprets all of the commands in the commandInfo list supplied and sends all of the commands to execution
	@param command_info : pointer which contains an address of a malloced commandInfo array, the end of the array is marked with commandInfo structure where command field is NULL
	@return : 0 on success, -1 on fail
*/
int interpretCommand(struct commandInfo* command_info);

#endif