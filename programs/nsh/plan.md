# To Do
* Implement a function that would go through the user input detecting special characters or commands in the list of arguments(e.g. `<<` or `&&`) and if it finds one it should react accordinly to what this special command or character does
	* That would require going through every character in the user input and checking if that character corresponds to characters in another array(array of all special commands) and that would be very slow so faster algorithm should be found for this purpose
	* This function should be used to detect `<</>>`, `&&` and others, but not `\` or `&` as their are always in the end of the line's and could be detected using other functions
* Output redirection using `<</>> >\<`


# Features
## Not Implemented
* Support for logic constructs like `if`. The syntax for the logic constructs should be like in C or powershell and shouldn't be POSIX compatible as POSIX shell logic constructs are a mess
* Shell should support special escape or "\" sequences that should be expanded by shell to stuff like current user mode(root(#)/user($))
* Plugins support
* Add support for saving shell command history
* Add support for going to the previous/next command by using up and down arrows on the keyboard
* Add support for going between characters written by the user in the prompt using the left and right arrows
* POSIX
	* Output redirection using `<</>> >\<`

## Implemented
* User input from:
	* Batch files(.nsh/.sh)
	* stdin(from the command line(tty))
	* From strings supplied with `-c` argument passed to the shell executable
* Cleaning of user input: any garbage can be entered(in terms of spaces, tabs...) and it would be cleaned by cleaner and then interpreted if it is a real command and not just garbage
* All of the commands are tokenized for it to be easy to be used from the code and to make code more extensible
* Shell supports different types of commands that could be executed:
	* Built-in(which are added through shell code) - e.g. `cd`
	* Executables from directories in the PATH variable - e.g. `ls`
	* Executables from some local directory(local executables have to be prefixed with `./`) - e.g. `./test.o`
* POSIX
	* Environment variables support is implemented and some UNIX ones are defined by default like PS1 and PS2
	* Several built-in unix commands are implemented including `cd` and `quit`
	* Splitting one command into several lines using `/`
		* **Usage:** To use this feature the last `argument`(space seperated from previous argument and not just last character) of the command should be `\`
	* Logic operators: `||`, `&&`
	* Starting background proccess by putting `&` after the command
		* **Usage:** To use this feature the last `argument`(space seperated from previous argument and not just last character) of the command should be `&`
		* Currently only external executables are put in background execution while built-in commands just don't run if their last argument is &


# Software Architecture
* The shell will support config files in form of normal `.sh/.nsh` files which it would run at startup, but some special shell specific configurations would be done by the built-in `nsh-conf` command by supplying it with various command line argument's like option names and their new values
* Batch execution of files. The interpretation of files and commands should be done by one interpreter, just when the commands are entered through the prompt they are inputed when the user presses `\n` and in files it is just when the `\n` is encountered
* All of command types or special characters/commands(e.g. `>>\<<`, `&&/||`, `\`) should be split into seperate arguments(be seperated from the command and other arguments with a space) or a command(be at the start of new line and be seperated from arguments by a space after it) to be interpreted - for example to be interpreted `\` should be seperated by space(e.g. `ls cd \` and not `ls cd\`) or boolean operators like `&&` or `||` should also be seperate arguments(e.g. `ls core && ls io` and not `ls core&& ls io`). If somehting like `&` or `\` isn't a seperate argument and this argument isn't the last one then they just don't execute
* All commands(command = command name + arguments) no matter if they are multi-line or single-line are put into commandInfo structures and these structures are what the interpreter uses to run command
	* All types of commands(commands which represent built-in functions and the ones which represent external binaries) are interpreted by the same pipeline in the interpreter(interpreter.c) which calls the appropriate functions to execute either built-in function or an external binary
	* Special symbols/commands(e.g. `&` or `\`) are devided into two parts - the ones which reach the interpreter as seperate commandInfo structs(where command field is filled with them(e.g. is filled with `&&`)) and the ones which do not reach the interpreter as the part of the command and are only acted upon in the parser
		* Symbols/commands which reach interpreter as seperate commandInfo structs are split into them by the parser(e.g. `command && command` is split into `command\n&&\ncommand\n`)
		* Symbols which do not reach the interpreter as the part of the command either just change the way the command is parsed(`\` causes two or more lines to be merged into one)


# Resources
