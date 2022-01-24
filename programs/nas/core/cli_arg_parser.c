/*
	@author : eltertrias
	@brief : parses command line arguments
*/


#include "include/cli_arg_parser.h"


int parseCLIarguments(int argc, char** argv, struct parserInfo *parser_info)
{
	if (argc < 2)
	{
		outputError("Not enough arguments supplied", ERROR_TYPE_NORMAL);
		printHelp();
	}

	int c;
	uint8_t filename_argument_present = false;

	while (1)
	{
		static struct option long_options[] =	// available command line options
		{
			{"version", no_argument, 0, 'v'},
			{"help", 	no_argument, 0, 'h'},
			{0, 0, 0, 0}
		};
		int option_index = 0;

		c = getopt_long(argc, argv, "vh", long_options, &option_index);
		if (c == -1)
			break;

		switch(c)	// find out what the currently parsedoption is
		{
			case 0:	// returned if the current option sets a flag
				break;
			case 'h':
				printHelp();
				break;
			case 'v':
				printVersion();
				break;
			case '?':	// unknown option
				exit(EXIT_FAILURE);
				break;
		}
	}

	for (int i = 0; i < argc; i++)	/* Fill in the file path of the source file in the parserInfo data structure */
	{
		if (argv[i][0] != '-')	/* find a CLI arguments which does not have -(which means it is not a flag) and use this string as a file */
		{
			if ((parser_info->input_file_path = realloc(parser_info->input_file_path, strlen(argv[i]))) == NULL)
				return outputError("Failed to allocate space for the input file name", ERROR_TYPE_LIB);
			if ((parser_info->output_file_path = realloc(parser_info->output_file_path, strlen(argv[i]))) == NULL)
				return outputError("Failed to allocate space for the output file name", ERROR_TYPE_LIB);
			memcpy(parser_info->input_file_path, argv[i], strlen(argv[i])+1); /* Add +1 to the size of copied data in memcpy statements so that the 0 which shows the end of the string, is also copied, because without zero, when priting the string - behaviour is undefined */
			memcpy(parser_info->output_file_path, argv[i], strlen(argv[i])+1);
			parser_info->input_file_path[strlen(argv[i])] = '\0';	// Add 0 as the last character of filename string so it is properly ended
			filename_argument_present = true;
		}
	}
	if (filename_argument_present == false)
		return outputError("File to assemble was not supplied", ERROR_TYPE_NORMAL);

	if (strncmp(&parser_info->input_file_path[strlen(parser_info->input_file_path)-2], ".s", 2) == 0)
		parser_info->output_file_path[strlen(parser_info->output_file_path)-1] = 'o';
	else
		return outputError("Wrong extension, file type unsupported", ERROR_TYPE_NORMAL);

	return RETURN_SUCCESS;
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