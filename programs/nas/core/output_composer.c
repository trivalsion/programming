/*
	@author : eltertrias
	@brief : includes functions for composing and then writing binary output to the output file
*/


#include "include/output_composer.h"


int writeFile(FILE** output_binary_file_fd, struct parserInfo* parser_info, void* data_buffer, size_t data_buffer_size)
{
	if (*output_binary_file_fd == NULL) // if the file descriptor isn't opened yet, open it
	{
		if ((*output_binary_file_fd = fopen(parser_info->output_file_path, "w")) == NULL)
			return outputError("Failed to open the output file", ERROR_TYPE_LIB);
	}

	if (fwrite(data_buffer, data_buffer_size, 1, *output_binary_file_fd) < 1)
		return outputError("Failed to write to the output file", ERROR_TYPE_LIB);

	return RETURN_SUCCESS;
}

int composeBinaryOutput(struct parserInfo* parser_info, struct lineInfo* line_info, arch_opcode_t* output_binary)
{
	for (size_t i = 0; parser_info->instruction_mnemonics[i] != NULL; i++)	/* Check if the instruction exists, and if it does then parse the line with it, else fail */
	{
		if (strcmp(line_info->command, parser_info->instruction_mnemonics[i]) == 0)
		{
			//outputError("Opcode - %hx", ERROR_TYPE_DEBUG, parser_info->instruction_opcodes[i]);

			arch_opcode_t* arguments_binaries_list;
			if ((arguments_binaries_list = malloc(line_info->arguments_amount * sizeof(arch_opcode_t))) == NULL)
				return outputError("Failed to allocate a list to store the instruction arguments", ERROR_TYPE_LIB);

			for (size_t current_argument_index = 0; current_argument_index < line_info->arguments_amount; current_argument_index++)
			{
				if (stringToBinaryArgumentConverter(parser_info, line_info->arguments[current_argument_index], &arguments_binaries_list[current_argument_index]) == RETURN_FAIL)
					return RETURN_FAIL;
			}

			archCombineOpcodeData(parser_info, parser_info->instruction_opcodes[i], arguments_binaries_list, line_info->arguments_amount, output_binary);	// in a binary form combine the instruction mnemonics with it's arguments

			return RETURN_SUCCESS;
		}
	}

	return outputError("Instruction does not exist", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number); // If program reaches this point, it means that the instruction mnemonic from the current line wasn't found in the list
}

int stringToBinaryArgumentConverter(struct parserInfo* parser_info, char* argument_buffer, arch_opcode_t* converted_argument)
{
	if (strncmp(argument_buffer, "0x", 2) == 0)
		*converted_argument = strtoul(argument_buffer, NULL, 16);	// hex - convert to unsigned hex equivalent
	else if (argument_buffer[0] == '$')	// label
		;
	else if (argument_buffer[0] == '%')
		*converted_argument = strtoul(argument_buffer, NULL, 16);	// register - convert to unsigned hex equivalent
	else if (isdigit(argument_buffer[0]) != 0)
		*converted_argument = strtoul(argument_buffer, NULL, 10);	// decimal - convert to unsigned decimal equivalent
	else
		return outputError("Failed to determine argument type", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);

	return RETURN_SUCCESS;
}