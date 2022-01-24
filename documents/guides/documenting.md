# Notes on writing code documentation
## Document the build system
* Include the copy of [make algorithm](Makefile)
* Have a section that describes how the makefiles from all directories are connected and how to add new directories with code(modules) to the project
* Have a description of rules and variables that are global in the project's build system and their values can be changed in order to change the behavior of the build system

## Document code
* Document the directory structure of code - in the directory structure section write `directory name(e.g. include) - directory's description`
* Document how different parts of code(modules) are connected to each other - the API/IPC or config/text files they use to interact and how they do it
	* Document how the code can be extended not only from build system perspetive, but also from code perspective(which functions, APIs to use)
* Document APIs exposed to the user and the APIs that are used to connect parts of code - they can be just documented in comments above the functions in the header file and the documentation should link to the header files
	* Example of the comment above function in a header file - `@brief : description\n @param <param name> : parameter description\n <other parameters description>\n @return : what function returns and in what cases`
* Document the hardest algorithms and how they can be extended

## Usage instructions
* If it is a small utility, then just add the help message that the program outputs when `--help` flag is supplied
	* Make sure that the help message includes a small description telling how to use the program in addition to the program's flags descriptions
* If it is a larger program, them add a help message and write additional instructions on usage in the `usage instructions` section of the documentation

## Creating Documentation
* Markdown - the easiest and the best documentation format that follows WYSIWYM(What You See Is What You Mean) paradigm
