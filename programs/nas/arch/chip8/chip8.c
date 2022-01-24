/*
	@author : eltertrias
	@brief : contains the needed functions so the assembler could output chip8 machine code
*/


#include "include/chip8.h"


char* instruction_mnemonics[] =
{
	"scdown", "cls", "ret", "jmp", "call", "skeqc", "sknec", "skeq",
	"movc", "addc", "mov", "or", "and", "xor", "add", "sub",
	"shr", "rsb", "shl", "skne", "mvi", "jmi", "rand", "sprite",
	"skpr", "skup", "gdelay", "key", "sdelay", "ssound", "adi", "font",
	"bsd", "str", "ldr", NULL
};

uint16_t instruction_opcodes[] =
{
	0x0000, 0x00E0, 0x00EE, 0x1000, 0x2000, 0x3000, 0x4000, 0x5000,
	0x6000, 0x7000, 0x8000, 0x8001, 0x8002, 0x8003, 0x8004, 0x8005,
	0x8006, 0x8007, 0x800E, 0x9000, 0xA000, 0xB000, 0xC000, 0xD000,
	0xE09E, 0xE0A1, 0xF007, 0xF00A, 0xF015, 0xF018, 0xF01E, 0xF029,
	0xF033, 0xF055, 0xF065
};


int archInit(struct parserInfo* parser_info)
{
	parser_info->instruction_mnemonics = instruction_mnemonics;
	parser_info->instruction_opcodes = instruction_opcodes;

	return RETURN_SUCCESS;
}

int archCombineOpcodeData(struct parserInfo* parser_info, arch_opcode_t opcode, arch_opcode_t* arguments, uint8_t arguments_amount, arch_opcode_t* output_buffer)
{
	arch_opcode_t arguments_combined = 0;

	if (arguments_amount == 0)	// If there are no instruction arguments then it is only the opcode that will be in the composed binary
	{
		*output_buffer = htons(opcode);	// convert the binary of the assembly opcode combined with it's arguments from little endian format to big endian format because chip 8 is bigendian
		return RETURN_SUCCESS;
	}
	if (arguments_amount == 1)
	{
		if (arguments[0] <= 0xF)
			arguments_combined = arguments[0] << 8;	// combine the argument like(i - instruction, 1 - argument 1, 2 - argument 2) - i1ii
		else if (arguments[0] > 0xF && arguments[0] <= 0xFF)
			arguments_combined = arguments[0] << 4;	// combine the argument like - i11i
		else if (arguments[0] > 0xFF && arguments[0] <= 0xFFF)
			arguments_combined = arguments[0];	// combine the argument like - i111
		else
			return outputError("Argument is too large(max supported combined hex is - 0xFFF)", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);
	}
	else if (arguments_amount == 2)
	{
		if (arguments[0] > 0xF && arguments[1] > 0xF)	// if both arguments are more then 0xF(so are two hex digits wide) then they don't fit into the instruction
			return outputError("Combined arguments are too large(max supported combined hex is - 0xFFF)", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);
		else if (arguments[0] > 0xFFF || arguments[1] > 0xFFF)
			return outputError("One of the arguments is too large", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);
		else if (arguments[0] <= 0xF && arguments[1] <= 0xF)
			arguments_combined = (arguments[0] << 8) | (arguments[1] << 4); // combine arguments like(i - instruction, 1 - argument 1, 2 - arg 2) - i12i
		else if (arguments[0] > 0xF && arguments[1] <= 0xF)
			arguments_combined = (arguments[0] << 4) | arguments[1];	// combine arguments like(i - instruction, 1 - argument 1, 2 - arg 2) - i112
		else if (arguments[0] < 0xF && arguments[1] >= 0xF)
			arguments_combined = (arguments[0] << 8) | arguments[1];	// combine arguments like(i - instruction, 1 - argument 1, 2 - arg 2) - i122
	}
	else if (arguments_amount == 3)
	{
		if (arguments[0] > 0xF || arguments[1] > 0xF || arguments[2] > 0xF)
			return outputError("Combined arguments are too large(max supported combined hex is - 0xFFF)", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);
		else
			arguments_combined = (arguments[0] << 8) | (arguments[1] << 4) | arguments[2]; // combine the argument like(i - instruction, 1 - argument 1, 2 - argument 2, argument 3) - i123
	}
	else
		return outputError("Too much arguments supplied(max supported is 2)", ERROR_TYPE_SYNTAX, parser_info->input_file_path, parser_info->current_input_file_line_number);

	*output_buffer = opcode ^ arguments_combined;	// create the instruction by XORing the opcode with it's arguments
	*output_buffer = htons(*output_buffer); // convert the binary of the assembly opcode combined with it's arguments from little endian format to big endian format because chip 8 is bigendian

	outputError("Opcode - %hx, Argument's amount - %lu, Arguments - 0x%x, 0x%x, 0x%x, Arguments combined - 0x%hx, Output buffer - 0x%hx", ERROR_TYPE_DEBUG, opcode, arguments_amount, arguments[0], arguments[1], arguments[2], arguments_combined, *output_buffer);

	return RETURN_SUCCESS;
}