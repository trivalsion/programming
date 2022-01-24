/*
	@author : eltertrias
	@brief : includes the functions and it's header the defines that are general-purpose and are common in the most part of the project
*/


#include <common.h>


int outputError(char* error_message, uint8_t error_type, ...)
{
	va_list optional_arguments;
	va_start(optional_arguments, error_type);

	if (error_message == NULL)
	{
		va_end(optional_arguments);
		return RETURN_FAIL;
	}

	if (error_type == ERROR_TYPE_NORMAL)
	{
		fprintf(stderr, TEXT_COLOR_ERROR_ON);
		fprintf(stderr, "error: ");
		fprintf(stderr, TEXT_COLOR_ERROR_OFF);

		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_ON);
		vfprintf(stderr, error_message, optional_arguments);
		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_OFF);

		fprintf(stderr, "\n");
	}
	else if (error_type == ERROR_TYPE_LIB)
	{
		fprintf(stderr, TEXT_COLOR_ERROR_ON);
		fprintf(stderr, "library error: ");
		fprintf(stderr, TEXT_COLOR_ERROR_OFF);

		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_ON);
		vfprintf(stderr, error_message, optional_arguments);
		fprintf(stderr, ": ");
		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_OFF);

		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_ON);
		perror(NULL);
		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_OFF);
	}
	else if (error_type == ERROR_TYPE_SYNTAX)
	{
		fprintf(stderr, TEXT_COLOR_ERROR_ON);
		fprintf(stderr, "syntax error: ");
		fprintf(stderr, TEXT_COLOR_ERROR_OFF);

		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_ON);
		fprintf(stderr, "%s", va_arg(optional_arguments, char*)); // file path
		fprintf(stderr, ": ");
		fprintf(stderr, "%lu", va_arg(optional_arguments, size_t)); // line number
		fprintf(stderr, ": ");
		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_OFF);

		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_ON);
		vfprintf(stderr, error_message, optional_arguments);
		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_OFF);

		fprintf(stderr, "\n");
	}
	else if (error_type == ERROR_TYPE_DEBUG)
	{
		#ifdef DEBUG_MODE	// only print messages if the debug mode is on
		fprintf(stderr, TEXT_COLOR_ERROR_ON);
		fprintf(stderr, "debug: ");
		fprintf(stderr, TEXT_COLOR_ERROR_OFF);

		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_ON);
		vfprintf(stderr, error_message, optional_arguments);
		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_OFF);

		fprintf(stderr, "\n");
		#endif
	}

	va_end(optional_arguments);
	return RETURN_FAIL;
}

void toggleBit(size_t* var, size_t bitmask, uint8_t bit_status)
{
    if ((bit_status == TOGGLE_BIT_ON && (*var & bitmask)) || (bit_status == TOGGLE_BIT_OFF && !(*var & bitmask)))
        ;
    else if ((bit_status == TOGGLE_BIT_ON && !(*var & bitmask)) || (bit_status == TOGGLE_BIT_OFF && (*var & bitmask)))
        *var ^= bitmask;
}