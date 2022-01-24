/*
	@author : eltertrias
	@brief : contains prototypes for global functions in cli argument parser
*/


#ifndef CLI_ARG_PARSER_GLOBAL_H
#define CLI_ARG_PARSER_GLOBAL_H


/*
	@brief : reads and interprets command line arguments
	@param argc : argc from main()
	@param argv : argv from main()
	@param parser_info : parserInfo struct pointer, function fills the output and input file paths
	@return : 0 on success, -1 on error
*/
extern int parseCLIarguments(int argc, char** argv, struct parserInfo *parser_info);
#endif