/*
	@author : eltertrias
	@brief : gets input from the user using either the supplied batch script or directly reading stdin from the user
*/


#include "include/get_input.h"


int getInput(uint16_t input_type, struct commandInfo* command_info_array[])
{
	char* input_buffer = NULL;
	size_t input_buffer_size = 0;

	if (input_type == INPUT_TYPE_FILE) // read user's input from a file supplied by the user
	{
		struct stat statbuf;
		FILE* script_file = NULL;
		char* filename;
		int script_file_fd = 0;

		if (getCLIargumentValue(BITFLAG_FILE, &filename) == -1)	// obtain the filename that was supplied to the shell by using the function that returns the data supplied to command line flags
			return -1;

		if ((script_file = fopen(filename, "r")) == NULL)
			return outputError("Failed to open the script file", ERROR_TYPE_LIB);

		if ((script_file_fd = fileno(script_file)) == -1)	// get the file's file descriptor number from file stream(FILE*) struct
		{
			fclose(script_file);
			return outputError("Failed to get the file descriptor for the script file", ERROR_TYPE_LIB);
		}

		if (fstat(script_file_fd, &statbuf) == -1)	// obtain fail stats to get it's size
		{
			fclose(script_file);
			return outputError("Failes to get the stats for the script file", ERROR_TYPE_LIB);
		}

		if ((input_buffer = malloc(statbuf.st_size)) == NULL)	// allocate a buffer to put file's contents into
		{
			fclose(script_file);
			return outputError("Failed to allocate the command buffer", ERROR_TYPE_LIB);
		}

		if (fread(input_buffer, sizeof(char), statbuf.st_size, script_file) != (size_t)statbuf.st_size)	// read all of file's contents into the buffer allocated for them
		{
			fclose(script_file);
			free(input_buffer);
			return outputError("Failed to read all of the data from the script file", ERROR_TYPE_LIB);
		}

		input_buffer_size = statbuf.st_size;

		fclose(script_file);
	}
	else if (input_type == INPUT_TYPE_STDIN)	// read user's input fromt the tty/stdin
	{
		size_t input_buffer_size_extra = 0; // variable that receives the full buffer size from getline which is not needed because only return value of getline return the real size of the string that was got through getline
		ssize_t input_buffer_size_unconverted = 0;	// variable that receives the real size of the inputted string in bytes
		char* prompt_string;

		if (getEnvVarValue("PS1", &prompt_string) == -1)	// get the string that should be displayed when prompt is called, this prompt stirng stored in PS1 variable so the string from this variable is read and then printed, if it is unavailble then the the shell fails
			return RETURN_FAIL;
		if (prompt_string != NULL)
			printf(prompt_string);
		else
			outputError("Prompt can not be displayed because PS1 variable is unset", ERROR_TYPE_NORMAL);

		fflush(stdin);	// Clean out the stdin so it doesn't contain any leftover
		if ((input_buffer_size_unconverted = getline(&input_buffer, &input_buffer_size_extra, stdin)) == -1)	// obtain users's input line from stdin
			return outputError("Failed to read user input", ERROR_TYPE_LIB);

		if (input_buffer_size_unconverted == 1 && input_buffer[input_buffer_size_unconverted-1] == '\n')	// do not interpret the command if it is empty(if the only character in the command is \n meaning that user entered nothing and just pressed enter)
			return GET_INPUT_RETURN_NO_COMMAND_SUPPLIED;

		input_buffer_size = (size_t)input_buffer_size_unconverted;

		if (input_buffer_size > 3)	/* do not try to check wether \ is the last character with space before it unless there are at least 4 characters in input_buffer which is the minimum amount needed so conditions below could be true while command being present */
		{
			if (input_buffer[input_buffer_size-2] == '\\' && input_buffer[input_buffer_size-3] == ' ')	// if the user's input line ends with '\'(so '\' is before '\n') and the '\' is an argument(so it is seperated from other arguments with a space(' ')) then split the command into two seperate lines and go on with reading the second line of user input for this command
			{
				if (get_commands_next_line_input(&input_buffer, &input_buffer_size) == RETURN_FAIL)
					return RETURN_FAIL;
			}
		}
	}
	else if (input_type == INPUT_TYPE_COMMAND)	// read user's input from the -c CLI attribute
	{
		if (getCLIargumentValue(BITFLAG_FILE, &input_buffer) == -1)
			return -1;
		input_buffer_size = strlen(input_buffer);
	}
	else
		return outputError("Failed to determine input type", ERROR_TYPE_NORMAL);

	if (cleanInput(&input_buffer, &input_buffer_size) == -1)	// clean user's input from stuff like tabs and consecutive spaces using the cleaning function
	{
		free(input_buffer);
		return -1;
	}

	if (parseInput(&input_buffer, &input_buffer_size, input_type, command_info_array) == -1)	// pass the user input onto the parser so it could be interpreted and put into structures to be returned to the caller function instead of returning raw stream of characters
	{
		free(input_buffer);
		return -1;
	}

	free(input_buffer);
	return RETURN_SUCCESS;
}

static int get_commands_next_line_input(char** input_buffer, size_t* input_buffer_size)
{
	char* split_line_input_buffer = NULL;
	char* prompt_string = NULL;
	size_t input_buffer_size_extra = 0;	// variable that receives the full buffer size from getline which is not needed because only return value of getline return the real size of the string that was got through getline
	ssize_t input_buffer_size_unconverted = 0;	// variable that receives the real size of the inputted string in bytes
	ssize_t input_buffer_size_unconverted_previous = (ssize_t)*input_buffer_size; // variable that holds the unconverted input size for the previous buffer which is needed to know where the previous buffer ends when adding multiple buffers together in case of a multi-line string, assign this only at the end of the loop

	while (1)
	{
		input_buffer_size_extra = 0;
		input_buffer_size_unconverted = 0;

		if (getEnvVarValue("PS2", &prompt_string) == -1)	// displays the prompt to enter the splitted out line, the value for the prompt is stored in PS2 so it is used to display it
			return RETURN_FAIL;
		if (prompt_string != NULL)
			fprintf(stdout, prompt_string);
		else
			outputError("Prompt can not be displayed because PS2 variable is unset", ERROR_TYPE_NORMAL);

		if ((input_buffer_size_unconverted = getline(&split_line_input_buffer, &input_buffer_size_extra, stdin)) == -1)	// get the continuation of the command from the current line(after \)
			return outputError("Failed to read user input", ERROR_TYPE_LIB);

		*input_buffer_size += (size_t)input_buffer_size_unconverted-2;	// increase the input_buffer_size so input_buffer can be reallocated(using this variable) making it bigger so it can fit the continuation of the command that was split into a seperate line(line which was got in current loop iteration). Decrease the unconverted size by 2 because when the current line is copied into the input_buffer with memcpy, the characters from current line are copied into input_buffer and the first index to where the character from current line is copied represents the \n in the previous string(for the previous line of user input) which means that both \n and \0 in the previous string would be overwritten by the current lines's string and so the current string starts to take less space in the newly allocated memory because 2 chars of it are fit into space where there was previous string before and so newly allocated space could be decreased by 2

		if ((*input_buffer = realloc(*input_buffer, *input_buffer_size)) == NULL)	// reallocate the input_buffer so that the current line's string could fit there in addition to the command that is already there
		{
			free(split_line_input_buffer);
			return outputError("Failed to reallocate the input buffer to fit the user input from the next line", ERROR_TYPE_LIB);
		}
		memcpy(&(*input_buffer)[input_buffer_size_unconverted_previous-2], split_line_input_buffer, input_buffer_size_unconverted);	// input_buffer_size_unconverted is used so that the copying destination(the place where current line's string is copied) starts not from the end of currently allocated memory which has been extended with realloc, but instead so it starts from the end of the command that was in input_buffer before this line(so that this line in the buffer goes immidiatly after the input that is already there); -2 from the end of the input that is already there is needed so copying of current line of user input starts from the index which represents \n in the destinations string so that the current line overwrites the \n and \0 with it's first two characters(first two characters of the current line) as current line has it's own \n and \0 in it's end

		if (split_line_input_buffer[input_buffer_size_unconverted-2] != '\\')	// if the current line does not end with \ then do not continue to prompt for next line parts of current command and go to execute the current command
		{
			free(split_line_input_buffer);
			break;
		}
		else
			free(split_line_input_buffer);

		input_buffer_size_unconverted_previous = (ssize_t)*input_buffer_size;
	}

	return RETURN_SUCCESS;
}

void freeCommandInfo(struct commandInfo* command_info)
{
	if (command_info->arguments != NULL)
	{
		for (size_t i = 0; i < command_info->arguments_amount; i++)
			if (command_info->arguments[i] != NULL)
				free(command_info->arguments[i]);
		free(command_info->arguments);
		command_info->arguments = NULL;
	}

	if (command_info->command != NULL)
	{
		free(command_info->command);
		command_info->command = NULL;
	}
}