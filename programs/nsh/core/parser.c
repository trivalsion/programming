/*
	@author : eltertrias
	@brief : parses the user input
*/


#include "include/parser.h"


int parseInput(char** input_buffer, size_t* input_buffer_size, uint8_t input_buffer_type, struct commandInfo** command_info_array)
{
	size_t new_input_size = *input_buffer_size;
	size_t current_file_line_number = 0;
	size_t command_info_array_size = 1;

	if (input_buffer_type == INPUT_TYPE_FILE)
		current_file_line_number = 1;

	new_input_size += 1;
	if ((*input_buffer = realloc(*input_buffer, new_input_size)) == NULL)	// increase the buffer size to fit a new \n in the end of the array
		return outputError("Failed to re-allocate memory", ERROR_TYPE_LIB);
	(*input_buffer)[new_input_size-1] = '\n';	// add a \n in the end to remove the need to check wether the next char is \n or it is the end of the file
	*input_buffer_size = new_input_size;

	if ((*command_info_array = malloc(sizeof(struct commandInfo) * command_info_array_size)) == NULL)	// allocate an array of commandInfo pointers
		return outputError("Failed to allocate an array of commandInfo structures", ERROR_TYPE_LIB);

	merge_multi_line_commands(*input_buffer, *input_buffer_size);	// removes all '\n' that go directly after a '\'

	for (size_t command_info_array_index = 0, current_input_buffer_location = 0; current_input_buffer_location < *input_buffer_size; current_input_buffer_location++, command_info_array_index++)	/* go through every line in the user input buffer turning them into commandInfo structures */
	{
		memset(&((*command_info_array)[command_info_array_index]), 0, sizeof(struct commandInfo));	// clear out the command info array member that would hold the current line's structure

		if (input_buffer_type == INPUT_TYPE_FILE)	// set the line number if file is used as the user input
		{
			current_file_line_number += 1;
			(*command_info_array)[command_info_array_index].current_line_number = current_file_line_number;
		}

		parse_boolean_operators(*input_buffer, current_input_buffer_location);

		if (parse_line(&((*command_info_array)[command_info_array_index]), *input_buffer, current_input_buffer_location) == RETURN_FAIL)	// parse the line and sort it into commandInfo structures
			return RETURN_FAIL;

		for (;(*input_buffer)[current_input_buffer_location] != '\n'; current_input_buffer_location++)	// go to the next line by increasing index in a loop until current character is \n, which would mean that next character is the start of the next line, so the next loop iteration index would increase array index by one and so index would go to the next char which is the start next line
			;

		if ((current_input_buffer_location+1) < *input_buffer_size)	// increase the array size so next commandInfo struct can fit into it
		{
			command_info_array_size++;
			if ((*command_info_array = realloc(*command_info_array, sizeof(struct commandInfo) * command_info_array_size)) == NULL)
				return outputError("Failed to reallocate the command info list to make it larger", ERROR_TYPE_LIB);
		}
	}

	command_info_array_size += 1;
	if ((*command_info_array = realloc(*command_info_array, sizeof(struct commandInfo) * command_info_array_size)) == NULL)	// increase the array size to create space for putting NULL there
		return outputError("Failed to reallocate command info array to add a NULL entry", ERROR_TYPE_LIB);
	(*command_info_array)[command_info_array_size-1].command = NULL;	// add NULL at the end of the malloc commandInfo list  so for loops know where to stop without using the size var

	return RETURN_SUCCESS;
}

static int parse_line(struct commandInfo* command_info, char* buffer, size_t buffer_location)
{
	size_t command_buffer_size = 0;
	size_t arguments_start_buffer_location = 0; // hold buffer location where the arguments start on the currently parsed line

	/* put the command from current line into command_info buffer for it */
	for (command_buffer_size = 0; buffer[buffer_location+command_buffer_size] != ' ' && buffer[buffer_location+command_buffer_size] != '\n'; command_buffer_size++)	// get the command size
		;
	if ((command_info->command = malloc(command_buffer_size+1)) == NULL)	// allocate buffer for the command and make it one char larger so there is space for the \0
		return outputError("Failed to allocate a temporary buffer for command", ERROR_TYPE_LIB);
	memcpy(command_info->command, &buffer[buffer_location], command_buffer_size);
	command_info->command[command_buffer_size] = '\0';	// end string with \0(\0 fits as buffer was made 1 char larger for it)

	/* put all of the arguments into the appropriate buffer */
	command_info->arguments_amount = 0;
	for (size_t i = buffer_location; buffer[i] != '\n'; i++)	/* count the amount of argments by counting the amount of spaces */
	{
		if (buffer[i] == ' ')
			command_info->arguments_amount++;
	}
	if (command_info->arguments_amount != 0)
	{
		for (size_t i = buffer_location; buffer[i] != '\n'; i++)	/* find at which index arguments start on the current line */
		{
			if (i != buffer_location && buffer[i-1] == ' ')
			{
				arguments_start_buffer_location = i;
				break; // break the loop so that the first occasion of "[i-1] == '\n'"" is treated as start of arguments
			}
		}
		if ((command_info->arguments = malloc(command_info->arguments_amount * sizeof(command_info->arguments))) == NULL)
			return outputError("Failed to allocate an array for arguments", ERROR_TYPE_LIB);
		for (size_t current_argument = 0, current_buffer_location = arguments_start_buffer_location; buffer[current_buffer_location] != '\n'; current_argument++)	/* fill-in the arguments array in commandInfo sturuct */
		{
			size_t current_argument_size = 0;

			if (buffer[current_buffer_location] == ' ')
				current_buffer_location++;	// go to the start of the current argument by increasing current_buffer_location as the current_buffer_location increase statement in the end of each loop iteration only increases current_buffer_location to represent ' '(space) before current argument(which is also right after previous argument)

			for (size_t i = current_buffer_location; buffer[i] != ' ' && buffer[i] != '\n'; i++)	// get the size of the current argument
				current_argument_size++;

			if ((command_info->arguments[current_argument] = strndup(&buffer[current_buffer_location], current_argument_size)) == NULL)	// put the argument into a buffer
				return outputError("Failed to copy the argument string into it's location in the list using strdup", ERROR_TYPE_LIB);

			current_buffer_location = current_buffer_location+current_argument_size;	// move/increase the current_buffer_location to the index corresponding to ' '(space) right after the current argument
		}
	}

	return RETURN_SUCCESS;
}

static void merge_multi_line_commands(char* input_buffer, size_t input_buffer_size)
{
	for (size_t i = 0; i < input_buffer_size; i++)
	{
		if (input_buffer[i] == '\\' && input_buffer[i+1] == '\n' && input_buffer[i-1] == ' ' && (i+1) != input_buffer_size && (i+2) != input_buffer_size)	/* remove \n after \ (if it exists) if the \n isn't the last character in the array(which would mean there are some characters after it and so there is one more \n as all user inputs are ended with them), also make sure that the character before the \ is ' '(space). Spaces(' ') are left between merged lines because only '\n' and '\' are removed while the space that was before '\' stays */
		{
			for (size_t j = i+1; (j+1) < input_buffer_size; j++)
				input_buffer[j] = input_buffer[j+1];
		}
		else if (input_buffer[i] == '\\' && input_buffer[i+1] != '\n')	// skip the \ if there isn't a \n after it
			continue;
	}
}

static void parse_boolean_operators(char* input_buffer, size_t current_input_buffer_location)
{
	for (size_t i = current_input_buffer_location; input_buffer[i] != '\n'; i++)	/* find any && or || and split them into their own lines by putting \n in front and after them; this loop only splits || and && into a seperate lines in cases when they aren't a part of an argument or a command(there is '\n' or ' ' before and after them) */
	{
		if (strncmp(&(input_buffer[i]), "&&", strlen("&&")) == 0 || strncmp(&(input_buffer[i]), "||", strlen("||")) == 0)
		{
			if (isalnum(input_buffer[i+2]) != 0 && isalnum(input_buffer[i-1]) != 0) // if there is an alphanumeric character after or before the && or || then it isn't a boolean operator, but instead it is just a part of a command or an argument so just skip this instance of predicted boolean operator
				continue;	// continue the search

			input_buffer[i-1] = '\n';

			if (input_buffer[i+2] != '\n') // continue the search for || and && only if the loop hasn't reached the end of the line
			{
				input_buffer[i+2] = '\n';
				i += 3; // go to the letter right after the newly put \n after &&
			}
		}
	}
}