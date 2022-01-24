/*
	@author : eltertrias
	@brief : the main file of the nSH shell
*/


#include "include/main.h"


static struct commandInfo* command_info_array;


int main(int argc, char* argv[])
{
	if (calling_function(argc, argv) == RETURN_FAIL)
		exitShell(EXIT_FAILURE);

	exitShell(EXIT_SUCCESS);
}

void exitShell(uint8_t exit_status)
{
	freeEnvVars();	// free all of the memory allocated for storing envrionment varaible related data

	freeCLIarguments();	// free all of the memory allocated for storing data related to command line arguments

	for (size_t i = 0; command_info_array[i].command != NULL; i++)	// free all of the user input
		freeCommandInfo(&command_info_array[i]);

	if (command_info_array != NULL)	// free the array of parsed user commands itself
	{
		free(command_info_array);
		command_info_array = NULL;
	}

	exit(exit_status);
}

static int calling_function(int argc, char* argv[])
{
	uint16_t flags;
	uint16_t input_type = INPUT_TYPE_STDIN;

	if (initEnvVars() == RETURN_FAIL)	// intialize all of the environment variables
		return RETURN_FAIL;

	if (parseCLIarguments(argc, argv, &flags) == RETURN_FAIL)
		return RETURN_FAIL;

	if (flags & BITFLAG_FILE)	/* change the input type(e.g. from file or from stdin) that should be used depending on the CLI arguments supplied */
		input_type = INPUT_TYPE_FILE;
	else if (flags & BITFLAG_COMMAND)
		input_type = INPUT_TYPE_COMMAND;

	if (input_type == INPUT_TYPE_STDIN)
	{
		while(1)
		{
			int get_input_status = 0;

			if ((get_input_status = getInput(input_type, &command_info_array)) == RETURN_FAIL)	// get user input in a parsed form
				return RETURN_FAIL;

			if (get_input_status == GET_INPUT_RETURN_NO_COMMAND_SUPPLIED)	// if no command was inputted by the user(meaning user just pressed enter) during this shell iteration, skip to the next shell iteration to take input again as empty command shouldn't be interpreted
				continue;

			if (interpretCommand(command_info_array) == RETURN_FAIL)	// interpret the parsed user input
				return RETURN_FAIL;

			for (size_t i = 0; command_info_array[i].command != NULL; i++)
				freeCommandInfo(&command_info_array[i]);	// free all of the user input

			if (command_info_array != NULL)	// free the array of parsed user commands itself
			{
				free(command_info_array);
				command_info_array = NULL;
			}
		}
	}


	return RETURN_SUCCESS;
}