/*
	@author : eltertrias
	@brief : includes the code for parsing the command line arguments supplied to the shell executable when it is called
*/


#include "include/shell_cmd_arg_parser.h"


static size_t data_arguments_amount = 1;
static uint16_t* data_arguments;
static char** data_array;


int parseCLIarguments(int argc, char** argv, uint16_t* flags)
{
	int c;
	//uint8_t filename_argument_present = false;

	*flags = 0; // clean out the flags variable

	if ((data_arguments = malloc(sizeof(uint16_t) * data_arguments_amount)) == NULL)
		return outputError("Failed to allocate the array for command line arguments", ERROR_TYPE_LIB);
	if ((data_array = malloc(sizeof(char*) * data_arguments_amount)) == NULL)
		return outputError("Failed to allocate the array for command line argument's data", ERROR_TYPE_LIB);

	while (1)
	{
		static struct option long_options[] =	// available command line options
		{
			{"version", no_argument, 0, 'v'},
			{"help", 	no_argument, 0, 'h'},
			{"command", required_argument, 0, 'c'},
			{0, 0, 0, 0}
		};
		int option_index = 0;

		c = getopt_long(argc, argv, "vhc:", long_options, &option_index);
		if (c == -1)
			break;

		switch(c)	// find out what the currently parsed option is
		{
			case 0:	// returned if the current option sets a flag
				break;
			case 'h':
				printHelp();
				break;
			case 'v':
				printVersion();
				break;
			case 'c':	/* get string with user input in case of the -c option */
				*flags = *flags ^ BITFLAG_COMMAND;
				data_arguments[data_arguments_amount-1] = BITFLAG_COMMAND;
				data_array[data_arguments_amount-1] = strdup(optarg);

				data_arguments_amount++;
				if ((data_arguments = realloc(data_arguments, data_arguments_amount)) == NULL)
					return outputError("Failed to reallocate the array for CLI arguments", ERROR_TYPE_LIB);
				if ((data_array = realloc(data_array, data_arguments_amount)) == NULL)
					return outputError("Failed to reallocate the array for CLI arguments data", ERROR_TYPE_LIB);
				break;
			case '?':	// unknown option
				return outputError("Unknown command line option", ERROR_TYPE_NORMAL);
				break;
		}
	}

	data_arguments_amount--; // subtract 1 as the variable is increased before something is put into it, so the last entry is always empty

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)	/* find arguments that do not start with - and interpret them as filenames by putting them into according array entry */
		{
			if (argv[i][0] != '-')	/* if CLI argument does njot start with '-' then interpret it as a filename */
			{
				data_arguments_amount++;
				if ((data_arguments = realloc(data_arguments, data_arguments_amount)) == NULL)
					return outputError("Failed to reallocate the array for CLI arguments", ERROR_TYPE_LIB);
				if ((data_array = realloc(data_array, data_arguments_amount)) == NULL)
					return outputError("Failed to reallocate the array for CLI arguments data", ERROR_TYPE_LIB);

				*flags = *flags ^ BITFLAG_FILE;
				data_arguments[data_arguments_amount-1] = BITFLAG_FILE;
				data_array[data_arguments_amount-1] = strdup(argv[i]);
				break;
			}
		}
	}

	return RETURN_SUCCESS;
}

int getCLIargumentValue(uint16_t flag, char** data)
{
	for (size_t i = 0; i < data_arguments_amount; i++)	// find the cli argument in the lust and then return data supplied with it
	{
		if (data_arguments[i] == flag)
		{
			*data = data_array[i];
			return RETURN_SUCCESS;
		}
	}

	return RETURN_FAIL; // if no right CLI argument was found then exit
}

void freeCLIarguments()
{
	if (data_arguments != NULL)
	{
		free(data_arguments);
		data_arguments = NULL;
	}

	for (size_t i = 0; i < data_arguments_amount; i++)
		free(data_array[i]);

	if (data_array != NULL)
	{
		free(data_array);
		data_array = NULL;
	}
}

static void printHelp()
{
	printf(
VERSION_INFO"\n"
"Usage: nas [option] file ...\n\
Options:\n\
	-v	--version	Prints out current version of the program and exits\n\
	-h	--help		Prints out this help message and exits\n");

	exit(EXIT_SUCCESS);
}

static void printVersion()
{
	printf(VERSION_INFO"\n");

	exit(EXIT_SUCCESS);
}