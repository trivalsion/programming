/*
	@author : eltertrias
	@brief : includes functions used for cleaning of input text assembly files
*/


#include "include/cleaner.h"


int cleanFile(ssize_t parsed_file_size, char** output_buffer_pointer_variable, ssize_t* output_buffer_size)
{
	uint8_t space_found = false;

	for (ssize_t i = 0; i < parsed_file_size; i++)	/* Replace all tabs with spaces */
	{
		if ((*output_buffer_pointer_variable)[i] == '\t')
			(*output_buffer_pointer_variable)[i] = ' ';
	}

	for (ssize_t i = 0, j = 0; i < parsed_file_size; i++)	/* Remove all consecutive white spaces - it outputs the characters, missing consecutive spaces, to the same string it is reading them from, but just to the start of it. So it just overwrites output buffer with the same contents as were there, but without consecutive spaces, also the buffer is shrinked so leftover(from previous output buffer contents) does not reside in the current buffer */
	{
		if ((*output_buffer_pointer_variable)[i] == ' ')
		{
			if (space_found == true)	// If previous character was a space and current is also, don't copy current character to the output buffer and skip to the next one(which does not allow trailing spaces in the output buffer)
				continue;
			else if (space_found == false)	// If previous character was not a space, but current is, copy current character to the output buffer
			{
				space_found = true;

				if ((*output_buffer_pointer_variable)[i-1] == '\n' || i == 0)	// Remove any(consecutive or not) whitespaces at the start of the lines
					continue;
				if ((*output_buffer_pointer_variable)[i-1] == ',' || (*output_buffer_pointer_variable)[i+1] == ',') // Remove spaces before or after commas
					continue;
				if ((*output_buffer_pointer_variable)[i+1] == '\n' || (i+1) == parsed_file_size) // Remove spaces before \n
					continue;

				(*output_buffer_pointer_variable)[j++] = (*output_buffer_pointer_variable)[i];
				(*output_buffer_size)++;
			}
		}
		else if ((*output_buffer_pointer_variable)[i] != ' ')
		{
			if ((*output_buffer_pointer_variable)[i] == '\n' && ((*output_buffer_pointer_variable)[i-1] == '\n' || i == 0)) // Do not copy character to the output buffer if it is a blank line(only \n)
				continue;
			if ((*output_buffer_pointer_variable)[i] == '\n' && (i+1) >= parsed_file_size) // Do not copy \n if it is the last character in the file buffer(as there is not next line, and \n will be added to the end of file by the parser)
				continue;

			(*output_buffer_pointer_variable)[j++] = (*output_buffer_pointer_variable)[i];	// If current character is not a space and passed through all tests above - copy it to the output buffer
			(*output_buffer_size)++;

			space_found = false;
		}
	}

	if ((*output_buffer_pointer_variable = realloc(*output_buffer_pointer_variable, *output_buffer_size)) == NULL)	// Change the size of the buffer to correspond to the cleaned file's size
	{
		free(*output_buffer_pointer_variable);
		return outputError("Failed to reallocated the buffer for the cleaned file", ERROR_TYPE_LIB);
	}

	// printf("cleanFile()\n");
	// for (ssize_t i = 0; i < *output_buffer_size; i++)
	// 	printf("%c", (*output_buffer_pointer_variable)[i]);	// TEMPORARY CHECKER TO SEE IF SOMETHING WAS READ INCORRECTLY FROM THE FILE
	// printf("\n\n");

	return RETURN_SUCCESS;
}