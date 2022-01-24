/*
	@author : eltertrias
	@brief : the main file for builtin commands, containing most or all of them
*/


#include "include/builtin.h"


static char* builtin_commands[] =
{
	"cd", "echo", "help", "exit", NULL
};

static int (*builtin_commands_functions[])(char**, size_t) =
{
	builtin_cd, builtin_echo, builtin_help, builtin_exit, /*builtin_type,  builtin_alias, builtin_unalias, builtin_include,*/ NULL
};


int builtinExecute(char* builtin_command_name, char** command_arguments, size_t command_arguments_amount)
{
	size_t command_array_index;
	uint8_t command_exists = false;

	for (command_array_index = 0; builtin_commands[command_array_index] != NULL; command_array_index++)	/* loop through all of the commands and try to match the name supplied through the arguments to any one of them, if it matches set the command_exists var to true */
	{
		if (strcmp(builtin_command_name, builtin_commands[command_array_index]) == 0)
		{
			command_exists = true;
			break;
		}
	}

	if (command_exists == false)
		return BUILTIN_COMMAND_NOT_FOUND; // if command wasn't found(and true wasn't set in checked variable) then it does not exist and function should fail

	if (builtin_commands_functions[command_array_index](command_arguments, command_arguments_amount) == -1)	// execute the built-in command if it passed the existance check and was found
		return BUILTIN_EXECUTION_FAILED; // if built-in command fails return fail

	return RETURN_SUCCESS;
}

int builtinExists(char* builtin_command_name)
{
	size_t command_array_index;

	for (command_array_index = 0; builtin_commands[command_array_index] != NULL; command_array_index++)	/* loop through all of the commands and try to match the name supplied through the builtin_command_name argument to any one of them, if it matches return success */
	{
		if (strcmp(builtin_command_name, builtin_commands[command_array_index]) == 0)
			return RETURN_SUCCESS; // return success(0) if the command string was found in the list of built-in commands
	}

	return RETURN_FAIL; // return fail(-1) if the command string was not found in the list of built-in commands
}

static int builtin_exit(char** arguments, size_t arguments_amount)
{
	if (arguments_amount > 1)
		return outputError("Arguments supplied to exit which doesn't support arguments", ERROR_TYPE_NORMAL);

	REMOVE_UNUSED_WARNING(arguments);

	exitShell(EXIT_SUCCESS);

	return RETURN_SUCCESS;
}

static int builtin_cd(char** arguments, size_t arguments_amount)
{
	if (arguments_amount > 1)
		return outputError("Too much arguments supplied to cd, only one is supported", ERROR_TYPE_NORMAL);

	if (chdir(arguments[0]) == -1)
		return outputError("Failed to change directory", ERROR_TYPE_LIB);

	return RETURN_SUCCESS;
}

static int builtin_echo(char** arguments, size_t arguments_amount)
{
	for (size_t i = 0; i < arguments_amount; i++)
		fprintf(stdout, "%s ", arguments[i]);
	fprintf(stdout, "\n");

	return RETURN_SUCCESS;
}

static int builtin_help(char** arguments, size_t arguments_amount)
{
	if (arguments_amount > 1)
		return outputError("Too much arguments supplied to help, while non are supported", ERROR_TYPE_NORMAL);

	REMOVE_UNUSED_WARNING(arguments);

	fprintf(stdout, "\
Shell Built-In commands\n\
cd [dir]\n\
 - Changes current working directory to [dir]\n\
\n\
echo \n\
 - Prints out all of it's arguments\n\
\n\
help\n\
 - Outputs this message; No arguments are supported\n\
\n\
exit\n\
 - Exits the shell; No arguments are supported\n\
");

	return RETURN_SUCCESS;
}