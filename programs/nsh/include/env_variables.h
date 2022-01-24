/*
	@author : eltertrias
	@brief : global header for environment variable proccessing code
*/


#ifndef ENV_VARIABLE_GLOBAL_H
#define ENV_VARIABLE_GLOBAL_H


/*
	@brief : intializes default environment variables like PATH and sets up the things like environment variables malloced array. If this function was called then freeEnvVars() function should be called before programs exit
	@return : -1 on fail, 0 on success
*/
extern int initEnvVars(void);

/*
	@brief : sets the value held in an evironement variable and creates it if it doesn't exist
	@param var_name : a string that contains the name of the environment variable
	@param var_value : a string that contains the value that should be set in the variable
	@return : -1 on fail, 0 on success
*/
extern int setEnvVar(char* var_name, char* var_value);

/*
	@brief : removes the environment variable meaning that it's value is cleaned until it is accessed again in which case setEnvVar recreates it, if variables do not exist function doesn't return error and just does nothing
	@param var_name : the name of the environment variable to unset
	@return : -1 on fail, 0 on success
*/
extern int unsetEnvVar(char* var_name);

/*
	@brief : gets the value located in the environemnt variable and returns pointer to it
	@param var_name : the name of the environment variable from which the value should be read
	@param var_value_output : pointer to a pointer which will be filled with the address of the value of chosen environment variable. If the variable doesn't exist var_value_output will be filled with NULL
	@return : -1 on fail, 0 on success
*/
extern int getEnvVarValue(char* var_name, char** var_value_output);

/*
	@brief : frees all of the memory allocated by the env variables processing code
*/
extern void freeEnvVars(void);
#endif