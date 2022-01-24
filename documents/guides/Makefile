### Make build system tutorial ###
#   * Make documentation - https://www.gnu.org/software/make/manual/
#   * Make tutorials
#     * GNU Manual Example - https://www.gnu.org/software/make/manual/make.html#Complex-Makefile
#     * Full tutorial website - https://makefiletutorial.com/
#
#     * https://wiki.osdev.org/Makefile
#     * http://nuclear.mutantstargoat.com/articles/make/
#   * Make books
#     * Advanced C and C++ Compiling(Ed. 1) - Milan Stevanovic
#     * Managing Projects with GNU Make(Ed. 3) - Robert Mecklenburg



### Managing projects with a makefile ###
# Bad make usage: Managing large projects with recursive make - e.g. "make -C makefile"
# Make algorithm:
#	Root makefile - create a Makefile following instructions below in the root of the project:
#		1. Declare global variables - global vars are declared as normal variables but in the root makefile, because any declared variable is passed onto included makefiles. Global vars should include:
#			* CC - for holding the compiler executable name
#			* LD - for holding linker executable name
#			* CFLAGS for compiler flags, put "-c" flag in this variable(produces objects from c files that could be lnked together)
#			* LDFLAGS - for linker flags
#			* DEBUG_MODE - for turning debug mode ON and OFF
#			* OBJECTS - for holding names of objects to compile
#			* BUILD_DIR - contains directory path to put compiled objects in
#			* PROGRAM_NAME - has the program name in it, which would also be the output executable name
#		2. Then submakefiles should be included from subdirectores in the project, if they arent't yet created just write the include statements(include <subdir/Makefile>) for non-existant Makefiles(they will be created in one of the next steps), write an include statement for all subdirectories that will include code
#		3. Finally global make rules should be added to root makefile:
#			* "all" make rule - is that main rule of the project which calls all other rules by having them as dependencies in corresponding order: "clean" rule; "init_modules" rule; "build" rule.
#			* "clean" - should remove all of the object files, binaries and the build directory. After that it should recreate(mkdir -p build) the build directory(but empty)
#			* "init_modules" - should have all of "all_$(MODULE-NAME)" rules as dependencies
#			* "build" - is the linking rule that should link all the variables in the $(OBJECT) variable. To link the objects in $(OBJECTS), "build" rule should have the $(OBJECTS) variable as dependency. Having $(OBJECTS) as dependendency is needed before the "build" rule runs because then "Make" program looks for the rules declared in makefile(or makefiles included in it) which have the same pattern as the objects file path(e.g. "%.o" rule for "file.o" object, or "build/%.o" rule for "build/file.o" object)
#				build: $(OBJECTS)
#					$(LD) $(LDFLAGS) $^ -o $(BUILD_DIR)/$(PROGRAM_NAME)
#		4. Add a ifdef for debugging to the makefile which would pass a debug mode define to C and would add a debug flag(-g) to program
#			ifeq ("$(DEBUG_MODE)", "ON")
#			CFLAGS += -D DEBUG_MODE -g
#			endif
#		5. Set the default rule of the makefile to "all" - ".DEFAULT_GOAL = all"
#		6. Add the needed rules to .PHONY(so they are not interpreted as filenames) - ".PHONY: clean, all, build"(add others if that is not all)

#	Submakefiles - create Makefile following instructions below in each subdirectory with code inside the project's directory:
#		* Here <MODULE_NAME> means the path to the folder where submakefile is(name of subdirectory)
#		1. Declare a local build path variable "OUTPUT_DIR_<MODULE_NAME>" which should contain the path to directory inside $(BUILD_DIR), this directory would contain compiled objects from code in this folder(this is needed so that make calls the right compilation rule depending on the objects path)
#			* Variable declaration - "OUTPUT_DIR_<MODULE_NAME> = $(BUILD_DIR)/<MODULE_NAME>"
#		2. Add all of the objects that current submakefile produces into the global $(OBJECTS) variable
#			* Adding - "OBJECTS += $(addprefix $(OUTPUT_DIR_<MODULE_NAME>)/, file.o file2.o)"
#		3. Create "all_<MODULE_NAME>" rule which would do extra stuff(if it is needed) that is needed before compiling objects from this submakefile. By default the only thing that "all_$(MODULE_NAME)" rules should do is create "$(BUILD_DIR)/$(MODULE_NAME)" folder
#			* Creating folder - mkdir -p $(OUTPUT_DIR_<MODULE_NAME>)
#		4. Using "%.o" variable gives only the file name of %.o objects into account and not the prefix or suffix/extension, so rules to compile the sources should look like the one in the example and be put in every subdirectory's Makefile, this rule would only be called to compile objects that should end up in $(OUTPUT_DIR_<MODULE_NAME>) direcotry which means the right make rule would be called for right files. So add the following rule to the submakefile:
#			$(OUTPUT_DIR_<MODULE_NAME>)/%.o: subdirectory/%.c
#				$(CC) $(CFLAGS) $^ -o $@
#		5. Add the needed rules to .PHONY - ".PHONY: all_$(MODULE_NAME)"

#	SubSubmakefiles - there should be no makefiles in subfolders if these subfolders are already in a subfolder with a makefile, but there could be subfolders without makefiles inside subfolders with makefiles and in that case Makefile in subfolder should handle code in the subsubfolder



## Variables - it is just a name for a string that might change and is used to replace strings that are often used through the makefile(e.g. gcc) ###
#   * Variable could be a part of other variables name, part of a rules name or part of any statement in the rule and pretty much everything and is just a string
#   * No variable must end with spaces as it also puts them in the string
VAR = string # Variable delaration

## Standard variables - these variables are not specified by make, but are most commonly used in all C projects
CC = gcc # C compiler
LD = ld # Linker
CFLAGS = -c -Wmissing-prototypes -Wshadow -Wall -Wextra -I include # C compiler flags
LDFLAGS = -ffreestanding # Linker flags

OBJECTS = *.o



### Conditions - only do thing between their start and end if condition is true(e.g. variable is defined or has a certain value) ###
ifeq($(var), yes)
NO = False
endif


## Compilation rules - compilation rules compile files and connect dependancies and produce an output file that is mostly names the same as the rules name ###
all: out.o out2.o # All is a name most projects use for the rule that would compile a project

%.o : %.c # %.o is the rule name and also the rules output file name(% is a special var), %.c is dependency which means it is a name of another rule or a name of a file that is needed to be done/compiled before current rule is executed. % is a special variable which indicated "any filename", so in the current case if some other rule has a *.o file as it's dependancy then this rule will be called as it matches the filename, while c is put after : which means that it's % filters the filename from previous rule(so gets not file.o, but file) and adds .c  to it. The %.o only matches file in current directory and dir/%.o rule name only matches files in dir (so % is only the filename and does not count the path prefix of the file).
  # Rule itself - a collection of instructions that are normally executed by the shell in the system
  $(CC) $(CFLAGS) $^ # $(VAR_NAME) is how the variables are used and during running they are replaced with strings. $^ and similar are special variables that are assigned value by make(e.g. $^ expands to names all of the dependancies with space between(stuff after rule:)
  $(LD) $(LDFLAGS) $(OBJECTS) -o $@ # Here is also a shell command but now $@ is a special variable and which means the name of rule itself


.PHONY: all # all targets listed as dependancies of PHONY are interpreted by make as targets whos name is not the name of their output file(or they might not make a file)
.DEFAULT_GOAL = rule # makes the selected rule be onvoked when make is run without specifying the rule(e.g. it will be called if "make" is used without sny CLI arguments)
