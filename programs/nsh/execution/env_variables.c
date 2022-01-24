/*
	@author : eltertrias
	@brief : manages environment variables of the shell
*/


#include "include/env_variables.h"


static char** environment_variable_names;
static char** environment_variable_values;
static size_t environment_variables_amount;


int initEnvVars()
{
	environment_variables_amount = 1;
	if ((environment_variable_names = malloc(environment_variables_amount * sizeof(environment_variable_names))) == NULL)
		return outputError("Failed to allocate memory for environment variable names", ERROR_TYPE_LIB);
	if ((environment_variable_values = malloc(environment_variables_amount * sizeof(environment_variable_values))) == NULL)
		return outputError("Failed to allocate memory for environment variable values", ERROR_TYPE_LIB);
	memset(environment_variable_names, 0, environment_variables_amount * sizeof(environment_variable_names)); // clean the array before using
	memset(environment_variable_values, 0, environment_variables_amount * sizeof(environment_variable_values));

	if (setEnvVar("PATH", "/usr/bin:/usr/sbin:/bin:/sbin") == RETURN_FAIL)	// set the path variable which should contain search directories for finding executables by the name of user supplied command if built-in command like that does not exist
		return RETURN_FAIL;
	if (setEnvVar("ALIASES", "") == RETURN_FAIL)	// set the variable which should hold the array of declared aliases
		return RETURN_FAIL;

	if (setEnvVar("PS0", "") == RETURN_FAIL) 	// set the variable whos value is displayed every time after command was entered but before it was executed
		return RETURN_FAIL;
	if (setEnvVar("PS1", "> ") == RETURN_FAIL)	// set the variable which is responsible for holding the string that is displayed every time a new prompt is called
		return RETURN_FAIL;
	if (setEnvVar("PS2", ": ") == RETURN_FAIL) 	// set the variable which is responsible for holding the string that is displayed every time a new prompt is called if it is one command broken into multiple lines with "\" located after the command(e.g. "ls \")
		return RETURN_FAIL;
	if (setEnvVar("PWD", "/") == RETURN_FAIL)	// set the variable which should contain current working directory
		return RETURN_FAIL;
	if (setEnvVar("SHELL", "nSH") == RETURN_FAIL)	// set the variable containing current shell's name
		return RETURN_FAIL;

	return RETURN_SUCCESS;
}

int setEnvVar(char* var_name, char* var_value)
{
	for (size_t i = 0; i < environment_variables_amount; i++)
	{
		if (environment_variable_names[i] == NULL && environment_variable_values[i] == NULL)	// if empty space for a variable is found then use it instead of reallocting the array to be largerss
		{
			if ((environment_variable_names[i] = strdup(var_name)) == NULL)
				return outputError("Failed to allocate space to create a variable", ERROR_TYPE_LIB);
			if ((environment_variable_values[i] = strdup(var_value)) == NULL)
				return outputError("Failed to allocate space to store variables value", ERROR_TYPE_LIB);
			return RETURN_SUCCESS; // return so that searching does not go on, as variable was created
		}
	}

	environment_variables_amount += 1;
	if ((environment_variable_names = realloc(environment_variable_names, environment_variables_amount * sizeof(environment_variable_names))) == NULL)	/* create space for environment variable name and for it's data */
		return outputError("Failed to reallocate memory for envrionment variable names", ERROR_TYPE_LIB);
	if ((environment_variable_values = realloc(environment_variable_values, environment_variables_amount * sizeof(environment_variable_values))) == NULL)
		return outputError("Failed to reallocate memory for envrionment variable values", ERROR_TYPE_LIB);

	if ((environment_variable_names[environment_variables_amount-1] = strdup(var_name)) == NULL)	/* fill in element at chosen index in the variable names array with the name of the current variable */
		return outputError("Failed to allocate space to create a variable", ERROR_TYPE_LIB);
	if ((environment_variable_values[environment_variables_amount-1] = strdup(var_value)) == NULL)	/* fill in element at chosen index in the variable data array with the data of the current variable */
		return outputError("Failed to allocate space to store variables value", ERROR_TYPE_LIB);

	return RETURN_SUCCESS;
}

int unsetEnvVar(char* var_name)
{
	for (size_t i = 0; i < environment_variables_amount; i++)
	{
		if (strcmp(var_name, environment_variable_names[i]) == 0)	/* find the variable name in the list of variable names and free it in the corresponding list of pointers and also free the string in the list of names, after that replace values for it in both arrays with NULL */
		{
			if (environment_variable_names[i] != NULL && environment_variable_values[i] != NULL)
			{
				free(environment_variable_names[i]);
				free(environment_variable_values[i]);
				environment_variable_names[i] = NULL;
				environment_variable_values[i] = NULL;
				return RETURN_SUCCESS;
			}
		}
	}

	return RETURN_SUCCESS;
}

int getEnvVarValue(char* var_name, char** var_value_output)
{
	for (size_t i = 0; i < environment_variables_amount; i++)	/* if the variable was found while searching through the list of current variable names, then return data from the corresponding index in the variable data array */
	{
		if (strcmp(var_name, environment_variable_names[i]) == 0)
		{
			*var_value_output = environment_variable_values[i];
			return RETURN_SUCCESS;
		}
	}

	*var_value_output = NULL;
	return RETURN_SUCCESS;
}

void freeEnvVars()
{
	if (environment_variable_names != NULL)
	{
		for (size_t i = 0; i < environment_variables_amount; i++)
			if (environment_variable_names[i] != NULL)
				free(environment_variable_names[i]);

		free(environment_variable_names);
	}

	if (environment_variable_values != NULL)
	{
		for (size_t i = 0; i < environment_variables_amount; i++)
			if (environment_variable_values[i] != NULL)
				free(environment_variable_values[i]);

		free(environment_variable_values);
	}
}