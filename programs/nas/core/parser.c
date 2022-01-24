/*
	@author : eltertrias
	@brief : parses the assembly language mnemonics
*/


#include "include/parser.h"


static FILE* output_binary_file_fd = NULL;


int parserInit(struct parserInfo* parser_info)
{
	int parsed_file_fd;
	char* parsed_file_mapping;
	char* parsed_file_buffer;
	struct stat parsed_file_stats;

	if ((sizeof(parser_info->instruction_mnemonics) / sizeof(char**)) != (sizeof(parser_info->instruction_opcodes) / sizeof(arch_opcode_t*))) // check if the amount of elements in mnemonics list is the same as the amount of elements in the opcode list(if no - fail)
		return outputError("Amount of mnemonics and opcodes do not match", ERROR_TYPE_NORMAL);

	if ((parsed_file_fd = open(parser_info->input_file_path, O_RDONLY)) == -1)
		return outputError("Failed to open the file", ERROR_TYPE_LIB);

	if (fstat(parsed_file_fd, &parsed_file_stats) < 0)	// get the file information(including file's size)
	{
		close(parsed_file_fd);
		return outputError("Failed to obtain file stats", ERROR_TYPE_LIB);
	}

	if ((parsed_file_mapping = mmap(NULL, parsed_file_stats.st_size, PROT_READ, MAP_PRIVATE, parsed_file_fd, 0)) == MAP_FAILED) // map the file to be private to the current proccess and be mapped in read only mode
	{
		close(parsed_file_fd);
		return outputError("Failed to memory map the file", ERROR_TYPE_LIB);
	}
	if ((parsed_file_buffer = malloc(parsed_file_stats.st_size)) == NULL)
		return outputError("Failed to allocate buffer to output cleaned file to", ERROR_TYPE_LIB);
	memcpy(parsed_file_buffer, parsed_file_mapping, parsed_file_stats.st_size);

	close(parsed_file_fd); // descriptor could be closed after the file was mapped
	munmap(parsed_file_mapping, parsed_file_stats.st_size);

	if (parseFile(parser_info, parsed_file_buffer, &parsed_file_stats) == -1)
	{
		free(parsed_file_buffer);
		return RETURN_FAIL;
	}

	free(parsed_file_buffer);
	return RETURN_SUCCESS;
}

static int parseFile(struct parserInfo* parser_info, char* parsed_file_buffer, struct stat* parsed_file_stats)
{
	ssize_t cleaned_file_buffer_size = 0;

	if (cleanFile(parsed_file_stats->st_size, &parsed_file_buffer, &cleaned_file_buffer_size) == -1)
		return RETURN_FAIL;

	cleaned_file_buffer_size += 1;
	if ((parsed_file_buffer = realloc(parsed_file_buffer, cleaned_file_buffer_size)) == NULL)
		return outputError("Failed to re-allocate memory", ERROR_TYPE_LIB);
	parsed_file_buffer[cleaned_file_buffer_size-1] = '\n'; // Add a \n in the end to remove the need to check wether the next char is \n or it is the end of the file

	for (ssize_t i = 0; i < cleaned_file_buffer_size; i++)
	{
		arch_opcode_t current_instruction_binary; // contains the arguments and instruction opcode combined in a binary form
		struct lineInfo line_info = {0};

		parser_info->current_input_file_line_number += 1; // inscrease current line counter each time a line is parsed

		if (parseLine(parser_info, &line_info, parsed_file_buffer, i) == RETURN_FAIL)
			return RETURN_FAIL;

		if (line_info.line_type == LINE_TYPE_INSTRUCTION)	// compose and write binary(binary where opcode and arguments are combined) to the output file if the current line type is an instruction
		{
			if (composeBinaryOutput(parser_info, &line_info, &current_instruction_binary) == -1)
				return RETURN_FAIL;
			if (writeFile(&output_binary_file_fd, parser_info, &current_instruction_binary, sizeof(current_instruction_binary)) == -1)
				return RETURN_FAIL;
		}

		freelineInfo(&line_info);

		for (;parsed_file_buffer[i] != '\n'; i++)	// go to the next line by increasing index var in a loop until current character is \n which would mean that next character is the start of next line, so in the next loop iteration index would increase by one and so it would go to the next char which is the next line
			;
	}

	fclose(output_binary_file_fd);
	return RETURN_SUCCESS;
}

static int parseLine(struct parserInfo* parser_info, struct lineInfo* line_info, char* file_buffer, size_t file_buffer_location)
{
	size_t instruction_buffer_size;

	/* get the type of the current line */
	if ((line_info->line_type = getLineType(parser_info, file_buffer, file_buffer_location)) == LINE_TYPE_ERROR)
		return RETURN_FAIL;

	/* put the command from the current line into a buffer */
	for (instruction_buffer_size = 0; file_buffer[file_buffer_location+instruction_buffer_size] != ' ' && file_buffer[file_buffer_location+instruction_buffer_size] != '\n'; instruction_buffer_size++)	// find the current line command size, which is all characters until space or \n
		;
	if ((line_info->command = malloc(instruction_buffer_size+1)) == NULL)	// allocate the buffer for the current line's command and make it one char larger so there is space for the \0
		return outputError("Failed to allocate a temporary buffer for command", ERROR_TYPE_LIB);
	memcpy(line_info->command, &file_buffer[file_buffer_location], instruction_buffer_size);	// copy the command from file buffer to the buffer allocated for the command
	line_info->command[instruction_buffer_size] = '\0';

	if (line_info->line_type == LINE_TYPE_INSTRUCTION)
	{
		size_t char_after_instruction_location = file_buffer_location + instruction_buffer_size;	// file buffer index where the command's arguments start

		/* count the amount of argments on the current line*/
		if (file_buffer[char_after_instruction_location] == ' ' && file_buffer[char_after_instruction_location+1] != '\n')	// there should be a space right after the instruction as a separator between it and arugments and the next character should be something from the argument and not \n
		{
			line_info->arguments_amount = 1;
			for (size_t i = char_after_instruction_location+1; file_buffer[i] != '\n'; i++) // start the loop from the character right after the space after instruction, so the loop is started with the first character of the first argument
			{
				if (file_buffer[i] == ',')
				{
					if (file_buffer[i+1] == '\n') // if character after comma is \n the argument is missing
						return outputError("The argument is missing", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);

					line_info->arguments_amount++;	// if comma is encountered and the argument is present increase the counter of arguments amount
				}
			}
		}
		else if (file_buffer[char_after_instruction_location] == '\n') // if \n goes after the instruction, then it has no arguments
			line_info->arguments_amount = 0;
		else
			return outputError("Instruction not seperated from the arguments", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);

		/* put the arguments from the current line into a list */
		if (line_info->arguments_amount != 0)
			if ((line_info->arguments = malloc(line_info->arguments_amount * sizeof(line_info->arguments_amount))) == NULL)	// allocate the array for command arguments
				return outputError("Failed to allocate the argument buffer", ERROR_TYPE_LIB);

		for (size_t current_argument = 0, current_buffer_location = char_after_instruction_location+1; file_buffer[current_buffer_location] != '\n' && current_argument < line_info->arguments_amount; current_argument++) // loop through the whole argument array and fill all of the cells in it
		{
			size_t current_argument_start = current_buffer_location;
			size_t current_argument_size = 0;

			for (current_argument_size = 0; file_buffer[current_buffer_location+current_argument_size] != '\n' && file_buffer[current_buffer_location+current_argument_size] != ','; current_argument_size++) // get argument size by counting the amount of characters before , or \n(in case of last arg)
				;

			if ((line_info->arguments[current_argument] = strndup(&file_buffer[current_buffer_location], current_argument_size)) == NULL)	// copy the argument from the file buffer into a dedicated buffer
				return outputError("Failed to allocate space for the instruction argument", ERROR_TYPE_LIB);

			if ((current_argument+1) < line_info->arguments_amount) // if there is a next argument then loop to be at it's start, if current is the last one and there is no more arguments after it then go on and do nothing to not waste time
			{
				for (; file_buffer[current_buffer_location-1] != ',' || current_buffer_location == current_argument_start; current_buffer_location++) // go to the next argument by looping until previous character is , which means that current char is start of an arg. Also check if the current locationis not the start of current argument to not falsly finish the loop as both argument 2 and 3 have buffer_location-1 as , which means that if you are at argument 2, the parser just would not go to argument 3 as the start of argument 2 satisfies the requirement for the start of new argument(buffer_location-1 == ,) - this problem is seen only when there are more then 2 args
					;
			}
		}
	}

	return RETURN_SUCCESS;
}

static size_t getLineType(struct parserInfo* parser_info, char* file_buffer, size_t file_buffer_location)
{
	if (file_buffer[file_buffer_location] == '#')	/* Go through possible line starts and determine which type does this line belong to */
		return LINE_TYPE_PREPROCESSOR;
	else if (strncmp(&file_buffer[file_buffer_location], "//", 2) == 0)
		return LINE_TYPE_COMMENT;
	else if (isalpha(file_buffer[file_buffer_location]) != 0)
	{
		for (size_t i = 0; file_buffer[file_buffer_location+i] != '\n'; i++)
		{
			if (file_buffer[file_buffer_location+i] == ' ' || (isalnum(file_buffer[file_buffer_location+i]) != 0 && file_buffer[file_buffer_location+i+1] == '\n')) // the second check, checks if current character is number or letter(which are only possible ending of an instruction mnemonic) and the next is \n in which case it is certainly an instruction just without arguments
				return LINE_TYPE_INSTRUCTION;
			else if (file_buffer[file_buffer_location+i] == ':')
				return LINE_TYPE_LABEL;
			else if (isalnum(file_buffer[file_buffer_location+i]) == 0) // If it is not a character or a number and also it is not a space or :
			{
				outputError("Encountered non alpha-numeric character which does not correspond to any type in the parser", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);
				return LINE_TYPE_ERROR;
			}

		}
	}

	outputError("Failed to determine the line type", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);
	return LINE_TYPE_ERROR;
}

static void freelineInfo(struct lineInfo* line_info)
{
	if (line_info->arguments != NULL)
	{
		for (size_t i = 0; i < line_info->arguments_amount; i++)
			if (line_info->arguments[i] != NULL)
				free(line_info->arguments[i]);
		free(line_info->arguments);
		line_info->arguments = NULL;
	}

	if (line_info->command != NULL)
	{
		free(line_info->command);
		line_info->command = NULL;
	}
}