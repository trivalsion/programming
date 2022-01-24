## ToDo
* Add support for extensions other than .s in the core/cli_arg_parser.c
	* Convert the extension to lower case before checking against the array of acceptable extensions so that extensions could be in both upper and lower cases and still pass the check
	* Make the extensions be parsed by a loop checking if the extension is present in the array(the extensions could be of any size/any amount of letters). Add extensions like .ch8, .asm to the extension checking array
	* Make sure that no matter what the extension is, it is correctly replaced with `.o` in the output file path buffer and the size of the ouput file path malloced buffer is reallocated to the new size accordingly
	* Add support for situations when there is not extension - fail with a normal error type
* Add support for address labels
* Add support for pre-proccessor and add the following pre-proccessor directives - file inclusion, defines, conditionals(ifdef, ifndef, endif)


## Testing
Test the assembler by compiling simple stuff and running it in an emulator(e.g. chip8 emulator or 6502 emulator)


## Software architecutre
* Description - assembler should read human readable instruction mnemonics in the input file and convert them to numbers/binary opcodes and their arguments which are readable by the computer
* Parser
	* Setup
		* Remove all spaces and tabs
	* Rules
		* None of labels, instructions or preproccesor directives could include anything except letters and numbers. All of them should start with a letter

		* Assembly line types - each new line counts as a new instruction/label/preproccessor(so \n are instruction seperators). So the assembler interprters and reads the assembly source file in lines
			* All pre-proccessor directives(e.g. include file) start with `#`(e.g. #include file)
			* Comments should start with `//`(`//` makes only the line on which it is located a comment, not the lines beyond it)
			* Labels should start with a letter(not a number or a symbol) and finish with a :, there shouldn't be anything on a line with the label(e.g. no instructions) - e.g. `label:`

		* Instruction argument types
			* All register names start with `%`(e.g. %ax)
			* All label names start with `$`(e.g. $hello)
			* All hexadecimal numbers start with `0x`(e.g. 0xAFF)
			* All denary numbers start with `1,2...9`(e.g. 1234)
			* Instruction arguments should be seperated by commas - e.g. `mov arg1, arg2`

		* If a number is encountered in an instruction, assembler should check the symbol table and find if there is an instruction which has all the same letters and a number after them, if yes then continue reading, else if the insturction is present but there is not number, then finish interpreting the instruction and interpret next thing as an argument
			* If the instruction is not found, skip to the end of the line and if there is `:` then it is a label and line is correct

* Implementation details
	* Making mnemonics correspond to opcodes - there should be an array of strings which represent instruction names(mnemonics) and there should be an array of hexadecimals that correspond to strings in the first array, the hexadecimals should be opcodes(number/binary equivalents for the instructions)
		* So to write an instruction to the output file just output the correct hexadecimal dending on the format
	* Storing labels - Create two malloced arrays. First arrays would contain strings that are names of labels and the second one would contain the addresses they represent
	* Create an instruction and then write it - the opcodes should be of instruction size(e.g. 0xF00000000000) and then arguments will be put in the correct places in them using bit operations(shifted into correct bits inside the instruction)
		* e.g. Insturction is 0xF0E0 and then arguments are bit shifted into second and last hex and it becomes 0xFAEF

* Notes
	* Make sure to convert instruction's and data to the write endiannes(little/big) and as it is different for every architecture, it should be done in the `arch/<CPU-ARCH>` code



# Resources
* Assembler making resources
	* [Assembler making stack overflow description](https://stackoverflow.com/a/15984371)
* CHIP8
	* [Architecture overview](https://github.com/mattmikolay/chip-8)
	* [Emulator: minmalistic(no sound)](https://github.com/dmatlack/chip8)
	* [Emulator: Full](https://github.com/glouw/c8c)
* Other
	* [Linux MMAP syscall tutorial](https://linuxhint.com/using_mmap_function_linux/)
		* Make sure that the MAP_ANONYMOUS isn not used when mapping a file!!!!!!!!!!!!
