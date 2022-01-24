/*
	@author : eltertrias
	@brief : includes code for interpreting commands
*/


#include "include/interpreter.h"


static uint8_t interpreter_flags = 0;
static uint8_t execute_proccess_in_background = false;	// declare this as a global variable so that it could be accessed by the child proccess function in addition to interpretCommand() function


int interpretCommand(struct commandInfo* command_info)
{
	int previous_command_return_status = RETURN_SUCCESS;

	for (size_t current_command = 0; command_info[current_command].command != NULL; current_command++)
	{
		int builtin_return_status = BUILTIN_EXECUTION_FAILED;
		execute_proccess_in_background = false;

		if (command_info[current_command].arguments_amount > 0)	// only try to check what the last argument is when there is more then 0 arguments(e.g. at least one)
		{
			if (strncmp(command_info[current_command].arguments[command_info[current_command].arguments_amount-1], "&", strlen("&")) == 0)	// set the background execution flag if the last argument supplied to the command is &
				execute_proccess_in_background = true;
		}

		/* Set the flags for logic operators(&&/||) in case they are the current command */
		if (strncmp(command_info[current_command].command, "&&", strlen("&&")) == 0) /* React to the && boolean operator */
		{
			toggleBit((size_t*)&interpreter_flags, INTERPRETER_FLAG_AND, TOGGLE_BIT_ON);
			continue;	// go to the next command as current one(&&) is handled by only setting the bit in this if
		}
		else if (strncmp(command_info[current_command].command, "||", strlen("||")) == 0)	/* React to the || boolean operator */
		{
			toggleBit((size_t*)&interpreter_flags, INTERPRETER_FLAG_OR, TOGGLE_BIT_ON);
			continue;	// go to the next command as current one(||) is handled by only setting the bit in this if
		}

		/* If AND/OR flags are set, act upon the AND/OR(&&/||) interpreter flags when reached the command directly after the the boolean operator command(e.g. &&) by letting or not letting the current command execute */
		if (interpreter_flags & INTERPRETER_FLAG_AND)	/* skip the command after && if the command before && failed as it is the work of this logic operator */
		{
			toggleBit((size_t*)&interpreter_flags, INTERPRETER_FLAG_AND, TOGGLE_BIT_OFF);	// turn off the OR flag when reached the command after directly &&, so that the && flag acts only on the command after it(current command)

			if (previous_command_return_status == RETURN_FAIL)	// if the return status of command before && was a fail, then don't execute current command(which is directly after &&) and go to next command(after the current one) as && operator permits execution of the command right after &&, only if the command before && succeeded
				continue;	// skip to next command by going to next loop iteration
		}
		else if (interpreter_flags & INTERPRETER_FLAG_OR) /* fail and do not execute anything after || if the command before || succeeded as it is the work of this logic operator */
		{
			toggleBit((size_t*)&interpreter_flags, INTERPRETER_FLAG_OR, TOGGLE_BIT_OFF);	// turn off the OR flag when reached the command after directly ||, so that the || flag acts only on the command after it(current command)

			if (previous_command_return_status == RETURN_SUCCESS)	// if the return status of command before || was a success, then don't execute current command(which is directly after ||) and go to next command(after the current one) as || operator permits execution of the command right after ||, only if the command before || failed
				continue;	// skip to next command by going to next loop iteration
		}

		/* Execute the command */
		if (execute_proccess_in_background == false && (builtin_return_status = builtinExecute(command_info[current_command].command, command_info[current_command].arguments, command_info[current_command].arguments_amount)) == BUILTIN_EXECUTION_FAILED)	/* try finding and executing a built-in command with the same name as the command supplied by user on the current line using the builtinExecute() function. Only execute built-in command if background execution flag is off because if it is on then built-in commands shouldn't be executed */
		{
			previous_command_return_status = RETURN_FAIL; // set fail for the return status
			continue;	// go to next commandInfo struct if current command was present as a built-in but failed during execution
		}
		else if (execute_proccess_in_background == true && builtinExists(command_info[current_command].command) == RETURN_SUCCESS)	/* if the current commands is present in the list of built-in commands but background execution flag is on then just skip the current command(with continue) as built-in commands shouldn't be executed in the background and just shouldn't be started in that case, but exeternal executable also shouldn't be started because built-in command with current command name already exists and so just skip current command as nothing should be executed */
			continue;
		else if (builtin_return_status == BUILTIN_COMMAND_NOT_FOUND || (builtin_return_status == BUILTIN_EXECUTION_FAILED && execute_proccess_in_background == true))	// try to execute an external binary with the same name as user supplied command if the built-in command wasn't found with that name or if built-in execution failed and background execution flag is on(because if background execution flag is on, builtin status is failed and continue in the previous if did not miss current loop iteration then the built-in command was not found and so external binary should be executed in the background)
		{
			int child_pid;
			char* path_var_value;
			char path_dirs_delimiter[2] = ":";	// delimiter that seperates directory path's in the PATH variable

			if (getEnvVarValue("PATH", &path_var_value) == -1)
				return RETURN_FAIL;

			if (path_var_value == NULL)
				return outputError("The PATH variable is unset making execution of binaries impossible", ERROR_TYPE_NORMAL);

			if ((child_pid = fork()) == -1)	// create a child proccess to open the executable in(so the executable does not overwrite the shell in the current proccess)
				outputError("Failed to create a child proccess for starting the executable", ERROR_TYPE_LIB);
			else if (child_pid == 0)	// code executing as the child proccess return's childs pid to parent and returns 0 to the child
				execute_program_as_child_proc(path_var_value, path_dirs_delimiter, command_info, current_command);
			else
			{
				if (execute_proccess_in_background == true)	// if the proccess background execution flag is ON then just continue shell's operation not waiting for the proccess to end as it runs in the background
					continue;
				int child_exit_status = 0;
				if (wait(&child_exit_status) == -1)	// wait untill child proccess finishes and then put the information about how it exited into child_exit_status var
					outputError("Waiting for the child proccess to finish failed", ERROR_TYPE_LIB);

				if (WIFEXITED(child_exit_status) && WEXITSTATUS(child_exit_status) == EXIT_SUCCESS)	// if child exited normally and returned success(0) then set previous_return_status to success
					previous_command_return_status = RETURN_SUCCESS;
				else	// if child exited unsuccessfully or returned an error at exit
					previous_command_return_status = RETURN_FAIL;
			}
		}
	}

	return RETURN_SUCCESS;
}

static int create_full_executable_path(char* executable_name, char* path_prefix, char* output, size_t max_length)
{
	size_t current_length = 0;
	for (size_t i = 0; i < strlen(path_prefix) && current_length < max_length; current_length++, i++)	// copy all of the characters from path prefix to the path that is created for the output(the full executable path)
		output[current_length] = path_prefix[i];

	output[current_length] = '/'; // add a / after the path prefix
	current_length++;

	for (size_t i = 0; i < strlen(executable_name) && current_length < max_length; current_length++, i++)	// copy all of the characters from executable name to the path that is created for the output(the full executable path)
		output[current_length] = executable_name[i];

	output[max_length-1] = '\0'; // NULL-terminate the string

	return RETURN_SUCCESS;
}

static int create_exec_argument_input(char* executable_name, struct commandInfo* command_info, char*** output_array, size_t *output_array_elements_amount)
{
	*output_array_elements_amount = command_info->arguments_amount+1;	// make the output_array_elements_amount one element larger as the path of the executable would be added as the first element/argument to it as it is required by exec(exec requires first argument to be the name of the executable as it is how the argv works, as the argv has executable name as the first argument)

	if ((*output_array = malloc(*output_array_elements_amount * sizeof(char*))) == NULL)	// allocate array for the input to exec
		return outputError("Failed to allocate space for the list of arguments for execv", ERROR_TYPE_LIB);

	for (size_t output_array_index = 0, current_arguments_array_index = 0; output_array_index < *output_array_elements_amount; output_array_index++)	/* put all of the commands and arguments into the exec input array */
	{
		if (output_array_index == 0)
		{
			if (((*output_array)[output_array_index] = strdup(executable_name)) == NULL)	// put command as the first thing in the array of arguments as it is required by the execv
				return outputError("Failed to dublicate string for the list of arguments for execv", ERROR_TYPE_LIB);
			continue; // go to next loop iteration so the current duplication isn't overwritten
		}

		if (((*output_array)[output_array_index] = strdup(command_info->arguments[current_arguments_array_index])) == NULL)
			return outputError("Failed to dublicate string for the list of arguments for execv", ERROR_TYPE_LIB);
		current_arguments_array_index++; // this incrementation is put here instead of incremetation part of for loop so that argument array index does not increase during the first iteration of the loop where command path and not an argument is written into the first element of the array
	}

	*output_array_elements_amount += 1;
	if ((*output_array = realloc(*output_array, *output_array_elements_amount * sizeof(char*))) == NULL)	// increase the array by one element by reallocating it, this is done to create space to put NULL in the end
		return outputError("Failed to reallocate the execv input list to fit NULL in the end", ERROR_TYPE_LIB);
	(*output_array)[*output_array_elements_amount-1] = NULL;	// end the array of arguments for exec with a NULL as it is required by exec

	return RETURN_SUCCESS;
}

static void execute_program_as_child_proc(char* path_var_value, char* path_dirs_delimiter, struct commandInfo* command_info, size_t current_command)
{
	char* executable_full_path;	// the path of the executable
	size_t executable_full_path_length;
	char* token = strtok(path_var_value, path_dirs_delimiter);
	char** exec_input;
	size_t exec_input_array_elements_amount;

	if ((executable_full_path = malloc(1)) == NULL) // allocate array for the full path of the executable to be supplied to exec(pre allocation is required by create_full_executable_path because it needs a malloc pointer)
	{
		outputError("Failed to allocate memory for the executable path", ERROR_TYPE_LIB);
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; token != NULL; i++)	/* try to find and execute the executable using the paths in PATH variable as prefixes */
	{
		executable_full_path_length = strlen(token) + strlen(command_info[current_command].command) + strlen("/") + 1;	// get the full path length including prefix, command/executable name and the / between them which would be added by the create_full_executable_path() function. Add 1 so there is space for '\0' in the end
		if ((executable_full_path = realloc(executable_full_path, executable_full_path_length)) == NULL)
		{
			outputError("Failed to reallocate memory for the executable path", ERROR_TYPE_LIB);
			exit(EXIT_FAILURE); // exit the child proccess if it fails as returning would just cause execution to continue as the child proccess
		}
		create_full_executable_path(command_info[current_command].command, token, executable_full_path, executable_full_path_length);

		if (access(executable_full_path, X_OK) == 0) // check if file on the supplied path is executable and even exists, and if it does both then execute it
		{
			if (create_exec_argument_input(executable_full_path, &command_info[current_command], &exec_input, &exec_input_array_elements_amount) == RETURN_FAIL)	// create the list of arguments for exec
			{
				outputError("Failed to create an argument buffer for executing the command", ERROR_TYPE_NORMAL);
				free_exec_argument_input(exec_input, exec_input_array_elements_amount);
				free(executable_full_path);
				exit(EXIT_FAILURE);
			}

			if (execute_proccess_in_background == true)
			{
				int dev_null_file_descriptor = 0;
				if ((dev_null_file_descriptor = open("/dev/null", O_RDWR)) == -1)	// open /dev/null so that standard input and output could be redirected there as it just discards all of it or fills it with zeroes
				{
					outputError("Failed to open the /dev/null for remapping stdin, stdout and stderr", ERROR_TYPE_LIB);
					free_exec_argument_input(exec_input, exec_input_array_elements_amount);
					free(executable_full_path);
					exit(EXIT_FAILURE);
				}

				if (dup2(dev_null_file_descriptor, STDIN_FILENO) == -1 || dup2(dev_null_file_descriptor, STDOUT_FILENO) == -1 || dup2(dev_null_file_descriptor, STDERR_FILENO) == -1)	/* change the destination of child proccess's stdout, stdin and stderr to /dev/null because the the output(stdout and stderr) of a background prccess(which current one is if execution got to this code) should not be sent to tty(so it does not interupt the shell) and instead should be discarded like it is here by being sent to /dev/null, and the input(stdin) of the background proccess is also redirected to /dev/null as it shouldn't interrupt the tty and just could be discarded because only zeroes could be read from /dev/null where stdin was redirected. The redirection of the file descriptors is done by dup2 which makes the file descriptor in it's second argument point to the same place as the file descriptor in it's first argument and so making stdin, stdout and sterr the second arguments of dup2(), while having /dev/null file descriptor as first argument redirects all of them to /dev/null */
				{
					outputError("Failed to remap child's proccesses to /dev/null so it does not output to tty as it is a background proccess", ERROR_TYPE_LIB);
					free_exec_argument_input(exec_input, exec_input_array_elements_amount);
					free(executable_full_path);
					close(dev_null_file_descriptor);
					exit(EXIT_FAILURE);
				}
			}

			if (execv(executable_full_path, exec_input) == -1)	// execute the external program
			{
				outputError("Failed to execute the supplied program", ERROR_TYPE_LIB);
				free_exec_argument_input(exec_input, exec_input_array_elements_amount);
				free(executable_full_path);
				exit(EXIT_FAILURE);
			}
			free(executable_full_path);
			free_exec_argument_input(exec_input, exec_input_array_elements_amount);
			exit(EXIT_SUCCESS); // exit the child proccess successfully if the child finished successfully
		}

		token = strtok(NULL, path_dirs_delimiter);
	}
	free(executable_full_path);

	if (strncmp(command_info[current_command].command, "./", strlen("./")) == 0)	/* if finding executable in PATH failed try running it from current working directory if it has "./" before it's name */
	{
		if (access(command_info[current_command].command, X_OK) == 0) // check if executable on the path exists and is executable and if it is run it, use only the command name as searching is done in current working directory and not in some path
		{
			if (create_exec_argument_input(command_info[current_command].command, &command_info[current_command], &exec_input, &exec_input_array_elements_amount) == RETURN_FAIL)
			{
				free_exec_argument_input(exec_input, exec_input_array_elements_amount);
				exit(EXIT_FAILURE); // exit the child proccess
			}
			if (execv(command_info[current_command].command, exec_input) == -1)
			{
				outputError("Failed to execute the supplied program", ERROR_TYPE_LIB);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
	}

	outputError("Command or executable not found", ERROR_TYPE_NORMAL);
	exit(EXIT_FAILURE); // exit if no command was found
}

static void free_exec_argument_input(char** exec_argument_input, size_t exec_argument_input_size)
{
	if (exec_argument_input != NULL)
	{
		for (size_t i = 0; i < exec_argument_input_size; i++)
		{
			if (exec_argument_input[i] != NULL)
			{
				free(exec_argument_input[i]);
				exec_argument_input[i] = NULL;
			}
		}

		free(exec_argument_input);
	}
}