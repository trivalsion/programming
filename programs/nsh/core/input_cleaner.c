/*
	@author : eltertrias
	@brief : cleans the input by removing tabs, consecutive spaces...
*/


#include "include/input_cleaner.h"


int cleanInput(char** input, size_t* input_size)
{
	size_t cleaned_input_size = 0;
	uint8_t space_found = false;

	for (size_t i = 0; i < *input_size; i++)	/* replace all tabs with spaces */
	{
		if ((*input)[i] == '\t')
			(*input)[i] = ' ';
	}

	for (size_t i = 0, j = 0; i < *input_size; i++)	/* remove all consecutive white spaces - it outputs the characters(without missing consecutive spaces) to the same string it is reading them from, but just to the start of it. So it just overwrites output buffer with the same contents as were there, but without consecutive spaces, also the buffer is shrinked so leftover(from previous output buffer contents) does not stay there */
	{
		if ((*input)[i] == ' ')
		{
			if (space_found == true)	// if previous character was a space and current is also, don't copy current character to the output buffer and skip to the next one(which does not allow trailing spaces in the output buffer)
				continue;
			else if (space_found == false)	// if previous character was not a space, but current is, copy current character to the output buffer
			{
				space_found = true;

				if ((*input)[i-1] == '\n' || i == 0)	// remove(do not copy to output) any(consecutive or not) whitespaces at the start of the lines
					continue;
				if ((*input)[i-1] == ',' || (*input)[i+1] == ',') // remove(do not copy to output) spaces before or after commas
					continue;
				if ((*input)[i+1] == '\n' || (i+1) == *input_size) // remove(do not copy to output) spaces before \n
					continue;

				(*input)[j++] = (*input)[i];
				cleaned_input_size++;
			}
		}
		else if ((*input)[i] != ' ')
		{
			if (i != 0)	// check of i-1 is impossible if i is 0 because it would correspond to characters before the buffer
				if ((*input)[i] == '\n' && ((*input)[i-1] == '\n' || i == 0)) // do not copy character to the output buffer if it is a blank line(only \n)
					continue;
			if ((*input)[i] == '\n' && (i+1) >= *input_size) // do not copy \n if it is the last character in the file buffer(as there is not next line, and \n will be added to the end of file by the parser)
				continue;

			(*input)[j++] = (*input)[i];	// if current character is not a space and passed through all tests above - copy it to the output buffer
			cleaned_input_size++;

			space_found = false;
		}
	}

	if ((*input = realloc(*input, cleaned_input_size)) == NULL)	// change the size of the buffer to correspond to the cleaned file's size instead of initial file size
	{
		free(*input);
		return outputError("Failed to reallocate the buffer for the cleaned file", ERROR_TYPE_LIB);
	}

	*input_size = cleaned_input_size;	// change the input_size to it's new value which is the size after cleaning

	// for (size_t i = 0; i < cleaned_input_size; i++)
	// 	printf("%c", (*input)[i]);	// TEMPORARY CHECKER TO SEE IF SOMETHING WAS READ INCORRECTLY FROM THE FILE

	return RETURN_SUCCESS;
}