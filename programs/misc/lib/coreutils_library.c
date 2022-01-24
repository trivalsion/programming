/*
	@author = eltertrias
	@breif = a library that has defines for several functions that are used accross all of the coreutils
	@todo :
		* Add ability to pass flags like this if “-“ is used - “-T”, “-e” to be “-Te”. If “- -“ is used then “- -Te” should be interpreted as one cli argument "--Te"
*/


#include "include/coreutils_library.h"


void outputVersion(char* str)
{
	fprintf(stdout, "%s", str);
	exit(EXIT_SUCCESS);
}

void outputHelp(char* str)
{
	fprintf(stdout, "%s", str);
	exit(EXIT_SUCCESS);
}

size_t interpretCLIattributes(int argc, char **argv, char* cli_flags[], size_t cli_flags_bits[])
{
	int argv_index, flags_index;
	uint8_t flag_present = 0;
	size_t output_flags = 0;				// Flags that were set by the CLI attributes that change how the output looks(e.g. add line numbers)

	for (argv_index = 1; argv_index < argc; argv_index++)
	{
		flag_present = 0;
		if (argv[argv_index][0] == '-')
		{
			if (strcmp(argv[argv_index], "-") == 0)	// "-" in cat means - read from stdin to stdout
				continue;
			for (flags_index = 0; cli_flags[flags_index] != NULL; flags_index++)
			{
				if (strcmp(cli_flags[flags_index], argv[argv_index]) == 0)
				{
					toggleBit(&output_flags, cli_flags_bits[flags_index], TOGGLE_BIT_ON);
					flag_present = 1;
				}
			}

			if (flag_present != 1)
				outputError(ERROR_TYPE_NORMAL, ERROR_LOCATION_NO, "Unknown CLI argument %s", argv[argv_index]);
		}
	}

	return output_flags;
}

void toggleBit(size_t* var, size_t bitmask, uint8_t bit_status)
{
    if ((bit_status == TOGGLE_BIT_ON && (*var & bitmask)) || (bit_status == TOGGLE_BIT_OFF && !(*var & bitmask)))
        ;
    else if ((bit_status == TOGGLE_BIT_ON && !(*var & bitmask)) || (bit_status == TOGGLE_BIT_OFF && (*var & bitmask)))
        *var ^= bitmask;
}

int outputError(uint8_t type, char* location, const char* error, ...)
{
	va_list args;
	va_start(args, error);

	#ifdef __linux__
	fprintf(stderr, "\033[1;31m");	// Change terminal text color to red - !!only next printed thing would be red!!
	#endif

	if (error == NULL)
	{
		fprintf(stderr, "Internal problem: wrong error output arguments");
		va_end(args);
		exit(EXIT_FAILURE);
	}

	switch (type)
	{
		case ERROR_TYPE_NORMAL:
			fprintf(stderr, "Error: ");
			vfprintf(stderr, error, args);
			fprintf(stderr, "\n");

			va_end(args);
			exit(EXIT_FAILURE);
			break;
		case ERROR_TYPE_DEBUG:
			fprintf(stderr, "(DEBUG)Error at %s: ", location);
			vfprintf(stderr, error, args);
			fprintf(stderr, "\n");

			va_end(args);
			return -1;
			break;
		case ERROR_TYPE_DEBUG_FATAL:
			fprintf(stderr, "(DEBUG)Fatal at %s: ", location);
			vfprintf(stderr, error, args);
			fprintf(stderr, "\n");

			va_end(args);
			exit(EXIT_FAILURE);
			break;
		default:
			fprintf(stderr, "Internal problem: unknown error type\n");
			break;
	}

	va_end(args);
	exit(EXIT_FAILURE);
	return -1;
}