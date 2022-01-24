# nAS Documentation
## Authored by: eltertrias
## July 31, 2021




## Source information
### Layout
* **arch/<arch_name>** - contains code specific to a certain target architecture
* **core** - contains the core parts of the assembler like parser which are the same for all target architectures
* **include** - contains global headers
* **test** - contains the assembly sources used for testing the assembler



## Build system - how is the assembler built
* Description - assemblers build system includes a main root file that includes all of the submakefiles into it and each of the submakefiles add objects to objects dir and later all of it is compiled
* Make Algorithm:
	* Root makefile(one in the root folder of the project):
		1. Declare global variables(e.g. CC. Variables that are needed for all submakefiles and the root makefile - global vars are declared as normal variables because any declared variable is passed onto included files). Global vars should include: $(OBJECTS) variable for holding names of compiled objects, $(CFLAGS) with "-c"(produces objects from c files that could be lnked together) as a flag and $(BUILD_DIR) to put compiled object files in.
		2. Then submakefiles should be included from projects subdirectores(include path/to/Makefile)
		3. Finally global rules should be added to root makefile and should include: all and clean(should create the build directory after deleting it). "All" rule in the root makefile should have the clean rule, "all_$(MODULE-NAME)" rules and a linking rule as depenencies in the corresponding order. The linking rule should link($(LD) $(LDFLAGS) $^(dependencies should include objects) -o exe) all the variables in the $(OBJECT) variable and have the $(OBJECTS) variable as dependency so the objects in it become dependencies and make searches for a rule to compile them and selects the one in the right makefile depending on the prefix of the object.
		4. Make sure to set the default rule of makefile and add the needed rules to .PHONY(e.g. clean, all, build)

	* Submakefiles:
		1. Declare a local build path variable $(OUTPUT_DIR_$(MODULE_NAME)) which would have the path to directory inside $(BUILD_DIR) for objects from this module(this is needed so that make calls the right compilation rule depending on the objects path) - `<OUTPUT_DIR_$(MODULE_NAME) = $(BUILD_DIR)/$(MODULE_NAME)>`
		2. Submakefile should add all of the objects it produces into the global $(OBJECTS) variable in a form of `<OBJECTS += $(addprefix $(OUTPUT_DIR_$(MODULE_NAME))/, file.o file2.o)>`
		3. Have "all_$(MODULE_NAME)" rules(MODULE_NAME is the name of the folder/module where submakefile is) which would do extra stuff that is needed before compiling objects, but they should not compile sources into objects themseleves(e.g. make a directory inside the build directory).
		4. As in %.o, % takes only the file name into account and not the prefix, rules to compile the sources should look like the one in the example and be put in every modules Makefile, this rule would only be called to compile objects that should end up in $(OUTPUT_DIR_$(MODULE_NAME)) direcotry which means the right make rule would be called for right files.
				$(OUTPUT_DIR_$(MODULE_NAME))/%.o: dir/to/sources/%.c
					$(CC) $(CFLAGS) $^ -o $@
		5. Add the needed rules to .PHONY(e.g. local all)
		6. If there are include submakefiles of subdirectories in the current makefiles subdirectory(subsubdirectories)
* Configuring Make:
	* To enable debug mode run `make` with the following argument - `DEBUG_MODE=ON`
	* To select the target architecutre to which assembler will compile code run `make` with the following argument - `ARCH=<ARCH_NAME>`



## Extending(with programming) the assembler
* Add a new target architecture
	1. Create a subdirectory in "arch" called the same as the new target architecture
	2. Create a submakefile(follow the submakefile tutorial in section above) inside the subdirectory you created in "arch"
		* Name for local all rule should be exactly "all_ARCH"
	3. Create an `include` directory in the subdirectory you created in "arch"
	4. Inside the `include` directory create an `asm-config.h` file and create a `typedef` of `arch_opcode_t` type, that will have word/instruction size of the target arch. e.g. `typedef uint16_t arch_opcode_t;`
	5. Finally the C files(the ones that are compiled) from the subdirectory you created in "arch" should define all of the functions from `include/arch-global.h`
* Create a subdirectory in a subdirectory
	* Local submakefile - should be included in submakefiles in a directory before them and should not have a local "all rule". So this kind of submakefile should only add objects to the objects var and have a compile
* Add a new subfolder with a submakefile to source directory structure -
	1. Create a submakefile and fill it like it is described in the "submakefiles" section of make algorithm.
	2. Place the include of submakefile near other includes in the root makefile
	3. Add the `all_<subfolder-name>` rule as a dependency to "all" rule in the root makefile right after previous `all_<subfolder-name>` rules



## Using the assembler
* Opcode and argument binary combination - after the opcode and all of it's arguments are converted into binary by the general pupose code common for all architectures, the combination of opcode with it's arguments is done by an architecture specific code, so for each architecture argument and opcode combination rules may be different.
	* CHIP8 Combination Rules
		* Chip8 argument combination rules(when arguments are combined together, but not with the opcode yet)`(i - instruction, 1 - argument 1, 2 - argument 2, argument 3)`
			* If one argument
				* If `argument <= 0xF` - i1ii
				* If `arg > 0xF && arg <= 0xFF` - i11i
				* If `arg > 0xFF && arg <= 0xFFF` - i111
			* If two arguments
				* If `arg1 <= 0xF && arg2 <= 0xF` - i12i
				* If `arg1 > 0xF && arg1 <= 0xF` - i112
				* If `arg1 < 0xF && arg2 >= 0xF`- i122
			* If 3 arguments
				* If `arg1 < 0xF && arg2 < 0xF && arg3 < 0xF` - i123
			* In all other cases not specific here - it is a fail with an error message returned
		* Chip8 opcode and argument combination rules
			* The arguments combined in the previous step are XORed with the opcode(opcode ^ arguments_combined)